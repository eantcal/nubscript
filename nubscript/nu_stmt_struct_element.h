//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_STMT_STRUCT_ELEMENT_H__
#define __NU_STMT_STRUCT_ELEMENT_H__


/* -------------------------------------------------------------------------- */

#include "nu_expr_any.h"
#include "nu_prog_ctx.h"
#include "nu_stmt.h"
#include "nu_token_list.h"
#include "nu_var_scope.h"
#include "nu_variable.h"

#include <string>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class stmt_struct_element_t : public stmt_t {
public:
    using vec_size_t = size_t;

    stmt_struct_element_t(prog_ctx_t& ctx, const std::string& name,
        const std::string& type, vec_size_t vect_size);

    stmt_struct_element_t() = delete;
    stmt_struct_element_t(const stmt_struct_element_t&) = delete;
    stmt_struct_element_t& operator=(const stmt_struct_element_t&) = delete;

    virtual void run(rt_prog_ctx_t& ctx) override;
};


/* -------------------------------------------------------------------------- */
}


/* -------------------------------------------------------------------------- */

#endif //__NU_STMT_DIM_H__