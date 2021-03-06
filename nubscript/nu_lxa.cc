//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_lxa.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

bool lxa_word_t::accept(char c)
{
    // For each word in the list...
    for (const auto& keyword : _plist) {
        // Verify if the symbol belongs to the key-word
        if (keyword.find(c) != std::string::npos) {
            // Verify if <building-word>+<symbol> is sub-string of
            // key-word

            std::string tentative = _data;
            tentative.push_back(c);
            auto ldata = tentative.size();

            if (keyword.size() >= ldata
                && keyword.substr(0, ldata) == tentative) {
                // If tentative matches with key-word, save it and
                // terminates
                _data = tentative;
                keyword_matches = _data == keyword;

                return true;
            }
        }
    }

    return false;
}


/* -------------------------------------------------------------------------- */

bool lxa_symb_t::accept(char c)
{
    if (_data.empty() && _plist.find(c) != _plist.cend()) {
        _data = c;
        return true;
    }

    return false;
}


/* -------------------------------------------------------------------------- */

bool lxa_str_t::accept(char c)
{
    // escape can be accepted only if it is within the quotes
    if (_escape_prefix && !_escape_found && c == _escape_prefix) {
        if (_begin_found != _begin_quote || !_end_found.empty()) {
            return false;
        }

        _escape_found = c;
        return true;
    }

    if (_begin_found != _begin_quote) {
        if (_bindex < _begin_quote.size() && c == _begin_quote[_bindex]) {
            _begin_found += c;
            ++_bindex;
            return true;
        }

        return false;
    }

    else if (_end_found != _end_quote) {
        if (_escape_found) {
            switch (c) {
            case 'n':
                _data += '\n';
                break;

            case 'r':
                _data += '\r';
                break;

            case 'b':
                _data += '\b';
                break;

            case 't':
                _data += '\t';
                break;

            case 'a':
                _data += '\a';
                break;


            default:
                _data += c;
            }

            _escape_found = 0;
            return true;
        }

        if (_eindex < _end_quote.size() && c == _end_quote[_eindex]) {
            _end_found += c;
            ++_eindex;
        } else {
            _data += c;
        }

        return true;
    }

    return false;
}


/* -------------------------------------------------------------------------- */

void lxa_str_t::reset()
{
    _data.clear();
    _begin_found.clear();
    _end_found.clear();
    _bindex = 0;
    _eindex = 0;
    _escape_found = 0;
}


/* -------------------------------------------------------------------------- */

const std::string& lxa_str_t::data() const { return _data; }


/* -------------------------------------------------------------------------- */

} // namespace nu