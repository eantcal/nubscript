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

namespace nu {


/* -------------------------------------------------------------------------- */

variant_t new_api(
    rt_prog_ctx_t& ctx,
    const std::string& fname,
    const func_args_t& args)
{
    // API name
    std::cout << "Invoked the function '" << fname << "'" << std::endl;

    // Number of arguments
    std::cout << "with " << args.size() << " arguments" << std::endl << std::endl;

    // Each argument is an expression that must be evaluate against a
    // context. This will result in a variant argument can be processeds

    long64_t numeric_arg = 0;

    for (size_t i = 0; i<args.size(); ++i) 
    {
        auto value = args[i]->eval(ctx);
        std::cout << "Arugment N." << i + 1 << std::endl;
        std::cout << "is type "  << value.get_type_desc(value.get_type()) << std::endl;
        std::cout << "its Value is '" << value.to_str() << "'" << std::endl << std::endl;
        
        // Assuming the second argument is a number
        if (i == 1) {
            numeric_arg = value.to_long64();
        }
    }


    // The api must return a variant value (it could be undefined if 
    // return type were ignored)
    variant_t return_value(numeric_arg * 2);

    return return_value;
}


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
    // Declare new api
    nu::global_function_tbl_t::get_instance().define("new_api", nu::new_api);
    
    int n_of_lines = 0;
    std::stringstream ss;
    
    // Write a simple program in nuBScript calling the new_api() with 2
    // arguments:
    //   - the string 'Hello world'
    //   - a numeric integer argument (123)
    ss << "result = new_api(\"Hello World\", 123)" << std::endl;

    // Print out the result
    ss << "print \"Result is \"; result";

    // Create an interpreter instance, add program lines and run them
    nu::interpreter_t interpreter;

    try {
        interpreter.append(ss, n_of_lines);
        interpreter.run();
    }
    catch (nu::exception_t e) {
        std::cerr << "Error:" << e.what() << std::endl;
        return 1;
    }

    return 0;
}
