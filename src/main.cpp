#include "printer.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"
#include "infofetch.h"






int main (int argc, char **argv) {

    Console console;

    Binary binary;
    binary.set_version ();

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
    os_info.system.set_username ();
    os_info.system.set_hostname ();
    std::cout << os_info.system.get_username () << '\n' << os_info.system.get_hostname () << std::endl;
    os_info.system.set_os ();
    std::cout << os_info.system.get_kernel () << std::endl;



return 0;}
