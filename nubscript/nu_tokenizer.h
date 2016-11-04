//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_TOKENIZER_H__
#define __NU_TOKENIZER_H__


/* -------------------------------------------------------------------------- */

#include "nu_basic_defs.h"
#include "nu_expr_tknzr.h"

#include <cstdio>
#include <map>
#include <string.h>
#include <string>

namespace nu {

struct tokenizer_t : public expr_tknzr_t {
    tokenizer_t(const std::string& data, size_t pos = 0)
        : expr_tknzr_t(
            data, 
            pos, 
            NUBSCRIPT_BLANKS, 
            NUBSCRIPT_NEWLINES,
            NUBSCRIPT_SINGLE_CHAR_OPS, 
            NUBSCRIPT_WORD_OPS,
            NUBSCRIPT_BEGIN_SUBEXPR, 
            NUBSCRIPT_END_SUBEXPR,
            NUBSCRIPT_BEGIN_STRING, 
            NUBSCRIPT_END_STRING, 
            NUBSCRIPT_ESCAPE_CHAR,
            {"'", "#"}
        )
    {
    }
};
}

#endif // NU_TOKENIZER
