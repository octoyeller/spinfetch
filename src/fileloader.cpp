#include "fileloader.h"
#include "console.h"
#include <fstream>
#include <iostream>




File_loader::File_loader (std::string username, bool search_only, std::filesystem::path bin_dir, std::vector<std::filesystem::path> in_files) {


    if (search_only) {
        std::cout << "Spingfetch will search for and probe all the files provided and those in default config directory." << std::endl;
        exit (0);
    }

    parsed_files = in_files;
    user_conf_dir = "/home/" + username + "/.config/spingfetch";


    if (!std::filesystem::exists (user_conf_dir)) {
        std::cout << "No config files in default directory. Default configuration will be generated. If you parsed any files, these will be used instead.\nDefault config directory: " << user_conf_dir.string () << "\nPress `Q` to abort, anyother key to continue." << std::endl;

        char c = getch ();
        if (c == 'q' || c == 'Q') {
            std::cout << "\rAbort!" << std::endl;
            exit (0);
        }
    }

}

