//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_os_std.h"
#include <ctime>
#include <stdlib.h>

#include <stdlib.h>

/* -------------------------------------------------------------------------- */

#if defined(__MINGW32__)
// For unknown reason putenv is not declared (but it is implemented)
extern "C" int putenv(const char*);
#endif


/* -------------------------------------------------------------------------- */

namespace nu {

/* -------------------------------------------------------------------------- */

int _os_get_time()
{
    time_t t = time(NULL);
    return int(t);
}


/* -------------------------------------------------------------------------- */

static inline tm* _get_local_tm()
{
    time_t t = time(NULL);
    return localtime(&t);
}


/* -------------------------------------------------------------------------- */

int _os_get_month() { return _get_local_tm()->tm_mon + 1; }


/* -------------------------------------------------------------------------- */

int _os_get_day() { return _get_local_tm()->tm_mday; }


/* -------------------------------------------------------------------------- */

int _os_get_wday() { return _get_local_tm()->tm_wday; }


/* -------------------------------------------------------------------------- */

int _os_get_yday() { return _get_local_tm()->tm_yday; }


/* -------------------------------------------------------------------------- */

int _os_get_year() { return _get_local_tm()->tm_year + 1900; }


/* -------------------------------------------------------------------------- */

int _os_get_hour() { return _get_local_tm()->tm_hour; }


/* -------------------------------------------------------------------------- */

int _os_get_min() { return _get_local_tm()->tm_min; }


/* -------------------------------------------------------------------------- */

int _os_get_sec() { return _get_local_tm()->tm_sec; }


/* -------------------------------------------------------------------------- */

std::string _os_get_systime()
{
    std::string s = asctime(_get_local_tm());

    // Remove \n or \r at the end of the string
    while (!s.empty()) {
        auto c = s.c_str()[s.size() - 1];

        if (c == '\n' || c == '\r')
            s = s.substr(0, s.size() - 1);
        else
            break;
    }

    return s;
}


/* -------------------------------------------------------------------------- */

void _os_beep() { putc(7, stdout); }


/* -------------------------------------------------------------------------- */




/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#ifdef _WIN32


/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <time.h>
#include <windows.h>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

std::string _os_get_app_path()
{
    char buffer[1024] = { 0 };
    GetModuleFileNameA(NULL, buffer, 1024);

    return buffer;
}


/* -------------------------------------------------------------------------- */

const __int64 DELTA_EPOCH_IN_MICROSECS = 11644473600000000;


/* -------------------------------------------------------------------------- */

struct timeval2 {
    __int32 tv_sec; /* seconds */
    __int32 tv_usec; /* microseconds */
};


/* -------------------------------------------------------------------------- */

static int gettimeofday(struct timeval2* tv)
{
    FILETIME ft = { 0 };
    __int64 tmpres = 0;
    int rez = 0;

    GetSystemTimeAsFileTime(&ft);

    tmpres = ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    /*converting file time to unix epoch*/
    tmpres /= 10; /*convert into microseconds*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
    tv->tv_sec = (__int32)(tmpres * 0.000001);
    tv->tv_usec = (tmpres % 1000000);

    return 0;
}


/* -------------------------------------------------------------------------- */

void _os_randomize()
{
    struct timeval2 t1 = { 0 };
    gettimeofday(&t1);
    srand(t1.tv_usec * t1.tv_sec);
}


/* -------------------------------------------------------------------------- */

void _os_delay(int s) { ::Sleep(s * 1000); }


/* -------------------------------------------------------------------------- */

void _os_mdelay(int s) { ::Sleep(s); }


/* -------------------------------------------------------------------------- */

bool _os_change_dir(const std::string& dir)
{
    return FALSE != SetCurrentDirectoryA(dir.c_str());
}


/* -------------------------------------------------------------------------- */

std::string _os_get_working_dir()
{
    char buf[MAX_PATH + 1] = { 0 };
    ::GetCurrentDirectoryA(MAX_PATH, buf);
    return buf;
}


/* -------------------------------------------------------------------------- */

#if defined(__MINGW32__)


int _os_setenv(const char* var, const char* val)
{
    std::string s = var;
    s += "=";
    s += val;
    return putenv(s.c_str());
}


/* -------------------------------------------------------------------------- */

int _os_unsetenv(const char* var)
{
    std::string s = var;
    s += "=";
    return putenv(s.c_str());
}


/* -------------------------------------------------------------------------- */

#endif


/* -------------------------------------------------------------------------- */

int _os_erase_file(const std::string& filepath)
{
    return ::DeleteFileA(filepath.c_str()) ? 0 : -1;
}


/* -------------------------------------------------------------------------- */

int _os_make_dir(const std::string& filepath)
{
    return ::CreateDirectoryA(filepath.c_str(), NULL) ? 0 : -1;
}


/* -------------------------------------------------------------------------- */

int _os_erase_dir(const std::string& filepath)
{
    return ::RemoveDirectoryA(filepath.c_str()) ? 0 : -1;
}


/* -------------------------------------------------------------------------- */
}


/* -------------------------------------------------------------------------- */

#else // LINUX -----------------------------------------------------------------


/* -------------------------------------------------------------------------- */

#include <fcntl.h>
#ifdef __linux__
#include <linux/kd.h>
#include <linux/limits.h>
#endif
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

void _os_randomize()
{
    struct timeval t1 = { 0 };
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
}


/* -------------------------------------------------------------------------- */

void _os_delay(int s) { sleep(s); }


/* -------------------------------------------------------------------------- */

void _os_mdelay(int s) { usleep(s * 1000); }


/* -------------------------------------------------------------------------- */

bool _os_change_dir(const std::string& dir) { return 0 == chdir(dir.c_str()); }


/* -------------------------------------------------------------------------- */

std::string _os_get_working_dir()
{
    char buf[PATH_MAX + 1] = { 0 };

    if (getcwd(buf, PATH_MAX) != nullptr) {
        return buf;
    }

    return "";
}


/* -------------------------------------------------------------------------- */

int _os_erase_file(const std::string& filepath)
{
    return ::unlink(filepath.c_str()) ? 0 : -1;
}


/* -------------------------------------------------------------------------- */

int _os_erase_dir(const std::string& filepath)
{
    return ::rmdir(filepath.c_str()) ? 0 : -1;
}


/* -------------------------------------------------------------------------- */

int _os_make_dir(const std::string& filepath)
{
    return ::mkdir(filepath.c_str(), 0777 /* & ~umask */);
}


/* -------------------------------------------------------------------------- */

std::string _os_get_app_path()
{
    char exepath[1024] = { 0 };

    ::readlink("/proc/self/exe", exepath, sizeof(exepath) - 1);
    return std::string(exepath);
}


} // namespace nu


/* -------------------------------------------------------------------------- */

#endif
