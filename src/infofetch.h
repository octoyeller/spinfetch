#include <string>



class OS_info {

    public:
    class System {
        bool successed;
        std::string username;
        std::string hostname;
        std::string name;
        std::string release;
        std::string codename;
        std::string kernel;

        public:
        void set_username ();
        void set_hostname ();
        bool set_os ();

        std::string get_username ();
        std::string get_hostname ();
        std::string get_name ();
        std::string get_release ();
        std::string get_codename ();
        std::string get_kernel ();

  //      System ();
    };
    System system;


    class Hardware {
        std::string name;
        bool has_battery;
        int battery_percent;
        std::string battery_status;
        unsigned long ram_total;         // in KB
        unsigned long ram_used;          // /proc/meminfo
        unsigned long swap_total;
        unsigned long swap_used;

        public:
        bool set_battery ();
        void obtain_battery ();
        bool see_if_has_battery ();
        bool set_ram ();


        std::string get_name ();
        int get_battery_percent ();
        std::string get_battery_status ();
        unsigned long get_ram_total ();
        unsigned long get_ram_used ();
        unsigned long get_swap_total ();
        unsigned long get_swap_used ();

    };
    Hardware hardware;




    class Uptime {
        int days;
        int hours;
        int minutes;

        public:
        int get_days ();
        int get_hours ();
        int get_minutes ();

        bool set_time ();
        Uptime ();
    };
    Uptime uptime;



    public:
//    OS_info ();
};
