#include "arginterpreter.h"



void Arg_interpreter::set_defaults () {}



void Arg_interpreter::sort_arguments () {

    for (std::string &cur : arguments) {
    
        if (cur [0] == '-') {
            for (unsigned u = 1; u < cur.length (); ++u) {
                options.emplace_back (cur [u]);
            }
        } else {
            files_parsed.emplace_back (cur);
        }
    }




}



Arg_interpreter::Arg_interpreter (int &argc, char **argv) {

    if (argc <= 1) {
        set_defaults ();
        return;
    }

    arguments.reserve (argc);
    files_parsed.reserve (argc);
    options.reserve (argc);

    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back (argv [i]);
    }

    sort_arguments ();



}
