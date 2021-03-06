//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_STMT_STRUCT_H__
#define __NU_STMT_STRUCT_H__


/* -------------------------------------------------------------------------- */

#include "nu_stmt.h"
#include "nu_var_scope.h"
#include "nu_variable.h"

#include <algorithm>
#include <string>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class stmt_struct_t : public stmt_t {
public:
    stmt_struct_t() = delete;
    stmt_struct_t(const stmt_struct_t&) = delete;
    stmt_struct_t& operator=(const stmt_struct_t&) = delete;

    stmt_struct_t(prog_ctx_t& ctx, const std::string& id);

    virtual stmt_cl_t get_cl() const noexcept override;
    virtual void run(rt_prog_ctx_t& ctx) override;

protected:
    std::string _id;
};


/* -------------------------------------------------------------------------- */
}


/* -------------------------------------------------------------------------- */

#endif //__NU_STMT_STRUCT_H__