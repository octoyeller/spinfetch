#include <vector>
#include <string>
#include <filesystem>



class Arg_interpreter {
    public:
    std::vector<std::string> arguments;
    std::vector<std::filesystem::path> files_parsed;
    std::vector<char> options;

    void set_defaults ();
    void sort_arguments ();

public:

    Arg_interpreter (int &argc, char **argv);

};
