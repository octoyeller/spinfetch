#include "print.h"
#include "console.h"
#include "arginterpreter.h"
#include "binary.h"

int main (int argc, char **argv) {

    Console console;

    Binary binary;
    binary.set_version ();
    binary.print_version ();


return 0;}
