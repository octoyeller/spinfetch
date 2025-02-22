#include "printer.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"
#include "infofetch.h"
#include "fileloader.h"






int main (int argc, char **argv) {

    Console console;
    std::cout << console.get_height () << " x " << console.get_width () << std::endl;

    Binary binary;
    binary.set_version ();
    binary.print_version ();

    Arg_interpreter arg_interpreter (argc, argv);
    arg_interpreter.set_exit_command ();

    switch (arg_interpreter.get_exit_command ()) {
        case 'h':
            std::cout << "Help" << std::endl;
            return 0;
            break;
        case 'v':
            binary.print_version ();
            return 0;
            break;
        case 's':
            break;
        default:
            break;
    }







    OS_info os_info;
    std::cout << os_info.uptime.get_days() << " days " << os_info.uptime.get_hours () << " hours " << os_info.uptime.get_minutes() << " minutes" << std::endl; 
    os_info.system.set_username ();
    os_info.system.set_hostname ();
    os_info.system.set_os ();
    std::cout << "u: " << os_info.system.get_username () << "\nh: " << os_info.system.get_hostname () << "\nn: " << os_info.system.get_name () << "\nr: " << os_info.system.get_release () << "\ncn: " << os_info.system.get_codename () << "\nk: " << os_info.system.get_kernel () << std::endl;
    os_info.hardware.obtain_battery ();
    if (os_info.hardware.see_if_has_battery ()) {
        std::cout << "Battery: " << os_info.hardware.get_battery_percent () << "% " << os_info.hardware.get_battery_status () << std::endl;
    } else {
        std::cout << "no battery" << std::endl;
    }
    

    os_info.hardware.set_ram ();
    std::cout << "Ram total: " << os_info.hardware.get_ram_total () << "\nRam used: " << os_info.hardware.get_ram_used () << "\nSwap total: " << os_info.hardware.get_swap_total () << "\nSwap used: " << os_info.hardware.get_swap_used () << std::endl; 






return 0;}
