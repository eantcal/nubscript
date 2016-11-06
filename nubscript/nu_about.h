//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_ABOUT_H__
#define __NU_ABOUT_H__


/* -------------------------------------------------------------------------- */

#ifdef _WIN32
#include "../nubscriptwin/config.h"
#else
#include "config.h"
#endif

/* -------------------------------------------------------------------------- */

namespace nu {

/* -------------------------------------------------------------------------- */

namespace about {

    #define NU_PROGRAM_NAME "nuBScript"

    static const char* const progname = NU_PROGRAM_NAME;
    static const char* const author = "Antonino Calderone";
    static const char* const contacts = PACKAGE_BUGREPORT;
    static const char* const homepage = "http://www.eantcal.eu";
    static const char* const license = "MIT License";
    static const char* const version = PACKAGE_VERSION;
    static const char* const copyright = "2016";
    static const char* const description
        = "nuBScript is a programming language distributed under MIT License.";
}


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

#endif // __NU_ABOUT_H__

/* -------------------------------------------------------------------------- */
