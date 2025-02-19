#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <filesystem>
#include <fstream>
#include "infofetch.h"






void OS_info::System::set_username () {
    username = getenv ("USER");
}

void OS_info::System::set_hostname () {
    char buffer [1024];
    gethostname (buffer, 1024);
    hostname = buffer;
}

bool OS_info::System::set_os () {

    std::string file_contents [7];
    std::filesystem::path os_rel_path = "/etc/os-release";
    if (!std::filesystem::exists (os_rel_path) ) {
        std::cerr << os_rel_path << " does not exist" << std::endl;
        return false;
    }
    
    std::fstream os_rel;
    os_rel.open (os_rel_path, std::ios::in);
    if (!os_rel.good ()) {
        os_rel.close ();
        perror ("good");
        std::cerr << "Could not read " << os_rel_path << std::endl;
        return false;
    }

    os_rel.seekg (0, std::ios::beg);
    for (int i = 0; i < 7; ++i) {
        getline (os_rel, file_contents [i]);
    }
    os_rel.close ();


    size_t first, len;
    first = file_contents [1].find_first_of ('\"');
    len = file_contents [1] .find_last_of ('\"') - first;
    name = file_contents [1].substr (first + 1, len - 1);

    first = file_contents [2].find_first_of ('\"');
    len = file_contents [2] .find_last_of ('\"') - first;
    release = file_contents [2].substr (first + 1, len - 1);

    first = file_contents [4].find_first_of ('=');
    len = file_contents [4].length () - first;
    codename = file_contents [4].substr (first + 1, len);


    struct utsname buffer;
    if (uname (&buffer) != 0) {
        perror ("uname");
        std::cerr << "Could not get kernel version" << std::endl;
        return false;
    }
    kernel = buffer.release;


    return true;
}









std::string OS_info::System::get_username () {
    return username;
}

std::string OS_info::System::get_hostname () {
    return hostname;
}

std::string OS_info::System::get_name () {
    return name;
}

std::string OS_info::System::get_release () {
    return release;
}

std::string OS_info::System::get_codename () {
    return codename;
}

std::string OS_info::System::get_kernel () {
    return kernel;
}







int OS_info::Uptime::get_days () {
    return days;
}

int OS_info::Uptime::get_hours () {
    return hours;
}

int OS_info::Uptime::get_minutes () {
    return minutes;
}

bool OS_info::Uptime::set_time () {

    struct sysinfo si;
    if (sysinfo (&si) != 0) {
        std::cerr << "Failed to get uptime." << std::endl;
        return false;
    }

    days = si.uptime / 60 / 60 / 24;
    hours = si.uptime / 60 / 60 - days * 24;
    minutes = si.uptime / 60 - days * 24 - hours * 60;

    return true;
}

OS_info::Uptime::Uptime () {
    set_time ();
}




bool OS_info::Hardware::set_battery () {


    std::filesystem::path main_dir = "/sys/class/power_supply";
    if (!std::filesystem::exists (main_dir) || !std::filesystem::is_directory (main_dir)) {
        return false;
    }

    std::vector <std::filesystem::path> devices_in_dir;
    devices_in_dir.reserve (4);

    for (std::filesystem::directory_entry cur_ent : std::filesystem::directory_iterator {main_dir}) {
        if (std::filesystem::is_directory (cur_ent.path ())) {
            devices_in_dir.emplace_back (cur_ent.path ());
        }
    }

    std::filesystem::path enow_path, efull_path, stat_path;
    for (unsigned i = 0; i < devices_in_dir.size (); ++i) {
        if (
            !std::filesystem::exists (devices_in_dir [i] / "energy_now") ||
            !std::filesystem::exists (devices_in_dir [i] / "energy_full") ||
            !std::filesystem::exists (devices_in_dir [i] / "status")
        ) {
            if (i == devices_in_dir.size () - 1) {
                return false;
            }
            continue;
        }

        enow_path = devices_in_dir [i] / "energy_now";
        efull_path = devices_in_dir [i] / "energy_full";
        stat_path = devices_in_dir [i] / "status";
        break;
    }

    
    std::string file_cont;
    std::fstream enow_f;
    enow_f.open (enow_path, std::ios::in);
    if (!enow_f.good ()) {
        enow_f.close ();
        return false;
    }
    int energy_now;
    enow_f.seekg (0, std::ios::beg);
    getline (enow_f, file_cont);
    enow_f.close ();
    energy_now = std::stoi (file_cont);


    std::fstream efull_f;
    efull_f.open (efull_path, std::ios::in);
    if (!efull_f.good ()) {
        efull_f.close ();
        return false;
    }
    int energy_full;
    efull_f.seekg (0, std::ios::beg);
    getline (efull_f, file_cont);
    efull_f.close ();
    energy_full = std::stoi (file_cont);


    std::fstream stat_f;
    stat_f.open (stat_path, std::ios::in);
    if (!stat_f.good ()) {
        stat_f.close ();
        return false;
    }
    stat_f.seekg (0, std::ios::beg);
    getline (stat_f, battery_status);
    stat_f.close ();


    // /sys/class/power_supply/BAT/energy_now
    // /sys/class/power_supply/BAT/energy_full
    // /sys/class/power_supply/BAT/status

    battery_percent = energy_now / energy_full * 100;

    return true;
}


int OS_info::Hardware::get_battery_percent () {
    return battery_percent;
}

std::string OS_info::Hardware::get_battery_status () {
    return battery_status;
}
