#include "print.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"

int main (int argc, char **argv) {

    Console console;

    Binary binary;
    binary.set_version ();
    binary.print_version ();

    Arg_interpreter arg_interpreter (argc, argv);
        std::cout << arg_interpreter.arguments.size () << '\n' << arg_interpreter.files_parsed.size () << '\n' << arg_interpreter.options.size () << std::endl;

    

return 0;}
