#include <string>



class Binary {

    bool successed;
    std::string name;           // filename on disk
    std::string directory;      // folder containg
    std::string path;           // full path to file

    std::string version;
    std::string release;
    std::string architecture;

public:
    std::string get_name ();
    std::string get_directory ();
    std::string get_path ();
    bool find_me ();
    void set_version ();
    std::string get_version ();
    std::string get_release ();
    std::string get_architecture ();
    void print_version ();
    Binary ();

};
