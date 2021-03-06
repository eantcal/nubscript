//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_STMT_DO_H__
#define __NU_STMT_DO_H__


/* -------------------------------------------------------------------------- */

#include "nu_expr_any.h"
#include "nu_signal_handling.h"
#include "nu_stmt.h"
#include "nu_stmt_empty.h"

#include <string>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class stmt_do_t : public stmt_t {
public:
    stmt_do_t() = delete;
    stmt_do_t(const stmt_do_t&) = delete;
    stmt_do_t& operator=(const stmt_do_t&) = delete;

    // DO
    //   [stmt(s)]
    // LOOP WHILE <condition>
    stmt_do_t(prog_ctx_t& ctx);

    virtual stmt_cl_t get_cl() const noexcept override;
    virtual void run(rt_prog_ctx_t& ctx) override;
};


/* -------------------------------------------------------------------------- */
}


/* -------------------------------------------------------------------------- */

#endif //__NU_STMT_DO_H__