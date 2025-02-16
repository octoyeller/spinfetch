#include <string>



class Binary {

    bool successed;
    std::string name;           // filename on disk
    std::string directory;      // folder containg
    std::string path;           // full path to file

public:
    std::string get_name ();
    std::string get_directory ();
    std::string get_path ();
    bool find_me ();
    Binary ();

};
