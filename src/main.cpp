#include "print.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"

int main (int argc, char **argv) {

    Console console;
    std::cout << "width " << console.get_width() << '\n' << "height " << console.get_height() << std::endl;


    Binary binary;
    std::cout << "name " << binary.get_name () << "\ndir " << binary.get_directory () << "\npath " << binary.get_path () << std::endl;



return 0;}
