//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_interpreter.h"


/* -------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr
            << "Usage:" << std::endl
            << "  nubscal \"<expression>\"" << std::endl << std::endl
            << "  e.g. " << std::endl
            << "       nubscalc \"print 25^2+sin(3.14156)\"" << std::endl
            << "       nubscalc \"a=5 : print a * sqrt(a)\"" << std::endl;

        return 1;
    }

    nu::interpreter_t basic;

    try {
        basic.exec_command(argv[1]);
    }
    catch (nu::runtime_error_t& e) {
        int line = e.get_line_num();
        line = line <= 0 ? basic.get_cur_line_n() : line;

        std::cerr
            << "Runtime Error #" << e.get_error_code()
            << " at " << line << ":" << e.what()
            << std::endl;
    }
    catch (std::exception& e) {
        if (basic.get_cur_line_n() > 0) {
            std::cerr
                << "At line " << basic.get_cur_line_n()
                << " " << e.what() << std::endl;
        }
        else {
            std::cerr << e.what() << std::endl;
        }

        return 1;
    }
    catch (...) {
        std::cerr << "Runtime Error" << std::endl;
        return 1;
    }

    return 0;
}

