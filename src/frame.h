#include <string>
#include <filesystem>
#include <vector>



class Frame {

    static int no_frames;
    static std::filesystem::path file_path;
    static unsigned width;
    static unsigned height;

    std::vector <std::string> line;




    public:
        // static pointer to array of frame objects init (std::filesystem::path file_path);
        int get_no_frames ();
        std::filesystem::path get_file_path ();
        unsigned get_width ();
        unsigned get_height ();
        std::string get_line ();

};






// Frame** frame = Frame::init (path);
// frame [x] .get_line (y);
