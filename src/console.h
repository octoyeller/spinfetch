#include <string>



class Console {

    bool successed;
    unsigned width;
    unsigned height;
    std::string shell;


public:
    unsigned get_width ();
    unsigned get_height ();
    std::string get_shell ();
    bool set_size ();
    bool set_shell ();
    Console ();



};



char getch ();
