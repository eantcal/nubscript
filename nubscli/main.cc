//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_os_console.h"
#include "nu_interpreter.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <string>

#ifdef WIN32
#include <Windows.h>
#endif


/* -------------------------------------------------------------------------- */

nu::interpreter_t::exec_res_t nubs_exec_command(
    nu::interpreter_t& basic, const std::string& command)
{
    try {
        auto res = basic.exec_command(command);

        if (basic.get_and_reset_break_event())
            std::cout << "Code execution has been interrupted by CTRL+C\n";

        if (res == nu::interpreter_t::exec_res_t::BREAKPOINT)
            std::cerr << "Execution stopped at breakpoint, line " 
                << basic.get_cur_line_n()
                << ". Type 'cont' to continue" 
                << std::endl;

        return res;
    }

    // Print out Runtime Error Messages
    catch (nu::runtime_error_t& e) {
        int line = e.get_line_num();
        line = line <= 0 ? basic.get_cur_line_n() : line;
        
        std::cerr 
            << "Runtime Error #" << e.get_error_code()
            << " at " << line << ":" << e.what()
            << std::endl;
    }

    // Print out Syntax Error Messages
    catch (std::exception& e) {
        if (basic.get_cur_line_n() > 0) {
            std::cerr 
                << "At line " << basic.get_cur_line_n() 
                << " " << e.what() << std::endl;
        } else {
            std::cerr << e.what() << std::endl;
        }

        return nu::interpreter_t::exec_res_t::RT_ERROR;
    }

    catch (...) {
        std::cerr << "Runtime Error" << std::endl;
        return nu::interpreter_t::exec_res_t::RT_ERROR;
    }

    return nu::interpreter_t::exec_res_t::CMD_EXEC;
}


/* -------------------------------------------------------------------------- */

int nuBScript_console(int argc, char* argv[])
{
    nu::_os_cls();

    nu::interpreter_t language;
    std::string command_line;
    bool first_command = false;

    if (argc >= 2) {
        int i = 1;

        while (argc-- > 1) {
            std::string param = argv[i];

            if (argc > 1 && param.size() == 2 && param.c_str()[0] == '-') {
                switch (param.c_str()[1]) {
                case NUBSCRIPT_EXEC_MACRO:
                    param = "EXEC \"" + std::string(argv[++i]) + "\"";
                    --argc;
                    break;

                case NUBSCRIPT_LOAD_MACRO:
                    param = "LOAD \"" + std::string(argv[++i]) + "\"";
                    --argc;
                    break;
                }
            }

            command_line += param + " ";
            ++i;
        }
    }

    std::string command;

    if (command_line.empty()) {
        auto ver_str = language.version();
        std::cout << ver_str.c_str();
        std::cout << NUBSCRIPT_MSG_STR__READY NUBSCRIPT_PROMPT_NEWLINE;
    }

    else {
        command = command_line;
        first_command = true;
    }

    while (1) {
        if (!first_command)
            command = nu::_os_input(stdin);
        else
            first_command = false;

        if (command.empty())
            continue;

        language.get_and_reset_break_event();
        auto res = nubs_exec_command(language, command);

        switch (res) {
        case nu::interpreter_t::exec_res_t::IO_ERROR:
            std::cerr << NUBSCRIPT_ERROR_STR__ERRORLOADING NUBSCRIPT_PROMPT_NEWLINE;
            break;

        case nu::interpreter_t::exec_res_t::SYNTAX_ERROR:
            std::cerr << NUBSCRIPT_ERROR_STR__SYNTAXERROR NUBSCRIPT_PROMPT_NEWLINE;
            break;

        case nu::interpreter_t::exec_res_t::CMD_EXEC:
            std::cerr << NUBSCRIPT_PROMPT_STR NUBSCRIPT_PROMPT_NEWLINE;
            break;

        case nu::interpreter_t::exec_res_t::NOP:
        case nu::interpreter_t::exec_res_t::BREAKPOINT:
        case nu::interpreter_t::exec_res_t::RT_ERROR:
        case nu::interpreter_t::exec_res_t::UPDATE_PROG:
            break;
        }
    }

    return 0;
}


/* -------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
    return nuBScript_console(argc, argv);
}
