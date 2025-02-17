#include <string>
#include <vector>
#include <filesystem>




class File_loader {

    bool successed;
    std::filesystem::path user_conf_dir;
    std::vector<std::filesystem::path> parsed_files;
    


    public:
        bool generate_defaults ();
        bool set_parsed_as_default ();
        File_loader (std::string username, bool search_only, std::filesystem::path bin_dir, std::vector<std::filesystem::path> in_files);

};
