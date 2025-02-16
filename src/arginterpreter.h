#include <vector>
#include <string>
#include <filesystem>



class Arg_interpreter {
    
    std::vector<std::string> arguments;
    std::vector<std::filesystem::path> files_parsed;
    std::vector<char> options;
    char exit_command;
        // c - continue
        // v - version
        // h - help - most important
        // s - no animation, show files

    void set_defaults ();
    void sort_arguments ();

public:

    void set_exit_command ();
    char get_exit_command ();
    Arg_interpreter (int &argc, char **argv);

};
