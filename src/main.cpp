#include "print.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"

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



return 0;}
