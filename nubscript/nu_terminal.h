//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


#if !defined(__MINGW32__) && !defined(_WIN32)
#ifndef __NU_TERMINAL_H__
#define __NU_TERMINAL_H__

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <list>
#include <set>
#include <string>
#include <vector>

#include "nu_cpp_lang.h"


//------------------------------------------------------------------------------


namespace nu {

//------------------------------------------------------------------------------

/*! \brief This class provides a simple terminal input mechanism
 * based on Unix General Terminal Interface (termios)
 */
class terminal_input_t {
private:
    bool _disable_stdin_echo;

public:
    enum vkey_t {
        CTRL_A = 1,
        CTRL_B,
        CTRL_C,
        CTRL_D,
        CTRL_E,
        CTRL_G,
        CTRL_F,
        CTRL_H,
        CTRL_I,
        CTRL_J,
        CTRL_K,
        CTRL_L,
        CTRL_M,
        CTRL_N,
        CTRL_O,
        CTRL_P,
        CTRL_Q,
        CTRL_R,
        CTRL_S,
        CTRL_T,
        CTRL_Y,
        CTRL_V,
        CTRL_W,
        CTRL_Z,

        RETURN = 0x0a,

        LF = 0x0a,
        CR = 0x0d,

        SPACE = 0x20,

        TAB = 0x09,
        ESCAPE = 0x1b,
        ESCAPE2 = 0x5b,
        BACKSPACE = 0x7f,

        HOME = 0x1b5b487e,
        END = 0x1b5b467e,
        PGUP = 0x1b5b357e,
        PGDOWN = 0x1b5b367e,
        DELETE = 0x1b5b337e,
        INSERT = 0x1b5b327e,

        UP = 0x1b5b41,
        DOWN = 0x1b5b42,
        RIGHT = 0x1b5b43,
        LEFT = 0x1b5b44,
    };


    inline terminal_input_t(bool disable_stdin_echo = true)
        : _disable_stdin_echo(disable_stdin_echo)
    {
    }

    virtual ~terminal_input_t() noexcept;
    virtual int getch() const noexcept;

    /*! \brief returns a nonzero value if a key has been pressed.
     *  Otherwise, it returns 0 (no events) or a
     *  negative value in case of error
     */
    virtual int keybhit() const noexcept;


    /*! \brief returns a character if a key has been pressed.
     *  Otherwise, it returns 0 (no events) or a
     *  negative value in case of error
     */
    virtual char getrawch() const noexcept;
};


//------------------------------------------------------------------------------


/* \brief This class specializes a standard stl vector of strings
 * in order to support the history feature of Terminal
 */
struct history_list_t : protected std::vector<std::string> {
public:
    typedef std::vector<std::string> svec_t;

    history_list_t(const svec_t& init_state = svec_t())
        : _cursor(0)
    {
    }

    inline int cursor() const noexcept { return _cursor; }

    inline void move_cursor_next()
    {
        ++_cursor;

        if (_cursor >= int(size()))
            _cursor = 0;
    }

    inline void move_cursor_prev()
    {
        if (empty())
            return;

        if (_cursor > 0)
            --_cursor;

        else
            _cursor = size() - 1;
    }

    inline void reset_cursor() { _cursor = 0; }

    inline void clear_history() { clear(); }

    inline void add_item(const std::string& line)
    {
        push_back(line);
        assert(!empty());
        _cursor = size();
    }

    inline std::string get_cur_item() const { return (*this)[_cursor]; }

    inline svec_t get_history() const { return *this; }

    inline bool is_empty() const { return empty(); }

    inline bool count() const { return size(); }

private:
    int _cursor;
};


//------------------------------------------------------------------------------


/*! \brief Terminal implementation
 */
class terminal_t {
public:
    typedef unsigned int flag_mask_t;

private:
    terminal_input_t& _term_input;
    std::set<int> _eol_code;
    int _cursor;
    std::string _line;
    flag_mask_t _flag;
    history_list_t _history;
    int _max_line_length;
    bool _insert_enabled;

public:
    enum flag_t { NONE = 0, APPEND = 1, ECHO_DIS = 2 };

    /*!
     * \brief Create a terminal using a terminal_input_t object to
     * extract character from the console. If term_input is not specified,
     * a basic terminal input object is created by default,
     * as instance of the terminal_input_t class
     *
     * \param term_input a terminal_input_t object instance
     *        (object will be deleted by terminal destructor)
     */
    terminal_t(terminal_input_t& term_input);
    virtual ~terminal_t();

    /*! \brief Get character from stdin */
    virtual int getch() const noexcept;

    /*! \brief returns a nonzero value if a key has been pressed.
     *  Otherwise, it returns 0 (no events) or a
     *  negative value in case of error. This function is not blocking
     */
    virtual int keybhit() const noexcept;

    /*! \brief returns a character if a key has been pressed.
     *  Otherwise, it returns 0 (no events) or a
     *  negative value in case of error. This function is not blocking
     */
    virtual char getrawch() const noexcept;

    /*! \brief Return true if ch is in the list of end-of-line characters */
    virtual bool end_of_line(int ch) const noexcept;

    /*! \brief Return true if ch is a printable character */
    virtual bool is_printable(int ch) const noexcept;

    /*! \brief Append the character ch to the editing string */
    virtual void edit_putc(int ch) noexcept;

    /*! \brief Process the vkey BACKSPACE */
    virtual void edit_backspace() noexcept;

    /*! \brief Process the vkey CTRL+H */
    virtual void edit_ctrl_h() noexcept;

    /*! \brief Process the vkey DELETE */
    virtual void edit_delete() noexcept;

    /*! \brief Process the vkey INSERT */
    virtual void edit_insert() noexcept;

    /*! \brief Process the vkey RIGHT */
    virtual void edit_right() noexcept;

    /*! \brief Process the vkey LEFT */
    virtual void edit_left() noexcept;

    /*! \brief Process the vkey UP */
    virtual void edit_up() noexcept;

    /*! \brief Process the vkey DOWN */
    virtual void edit_down() noexcept;

    /*! \brief Process a new input character ch updating the
     *  editing line
     */
    virtual void edit(int ch) noexcept;

    /*! \brief Delete the editing line */
    virtual void delete_line() noexcept;

    /*! \brief Refresh the editing line */
    virtual void refresh_line() noexcept;

    /*!
     * \brief Get a text line from the terminal_input_t object
     * \param line is update with text read from terminal
     * (line is not cleared if the flag terminal_input_t::APPEND is set)
     * \return the character (virtual key if not printable) that caused the
     * break of editing (see register_eol_ch)
     */
    virtual int get_line(
        std::string& line, bool return_on_len_max = false) noexcept;

    /* \brief Add a new code to the end-of-line code list */
    virtual void register_eol_ch(int vch_code) noexcept
    {
        _eol_code.insert(vch_code);
    }

    /* \brief Remove an existing code from the end-of-line code list */
    virtual void unregister_eol_ch(int vch_code) noexcept
    {
        _eol_code.erase(vch_code);
    }

    /* \brief Get Terminal flags */
    virtual flag_mask_t get_flags() const noexcept { return _flag; }

    /* \brief Replace Terminal flags */
    virtual void set_flags(flag_mask_t flg = NONE) noexcept { _flag = flg; }

    /* \brief Replace Terminal flags */
    virtual void set_insert_enabled(bool insert_enabled) noexcept
    {
        _insert_enabled = insert_enabled;
    }

    /* \brief Set max length of editing line */
    virtual void set_max_line_length(int max_len = 0 /* unlimted */) noexcept
    {
        _max_line_length = max_len;
    }

    /* \brief Get max length of editing line (0 means unlimited) */
    virtual int get_max_line_length() noexcept { return _max_line_length; }
};


} /* namespce nu */


#endif // __NU_TERMINAL_H__
#endif
