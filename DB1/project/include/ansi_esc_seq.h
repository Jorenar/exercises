#ifndef ANSI_ESC_SEQ_H_
#define ANSI_ESC_SEQ_H_

// Refer to: http://ascii-table.com/ansi-escape-sequences.php

#define TERM_ESC  "\033"
#define ESC_SEQ(code, ...) TERM_ESC "[" #code #__VA_ARGS__

// Graphics Mode {{{

#define  RESET  ESC_SEQ(0, m)

#define  FG_RGB_SEQ(r,g,b) ESC_SEQ(38;2;r;g;b, m)
#define  BG_RGB_SEQ(r,g,b) ESC_SEQ(48;2;r;g;b, m)

// Text attributes {{{1

#define  BOLD           ESC_SEQ(1,  m)

#define  ITALIC         ESC_SEQ(3,  m)
#define  ITALIC_OFF     ESC_SEQ(23, m)

#define  UNDERLINE      ESC_SEQ(4,  m)
#define  UNDERLINE_OFF  ESC_SEQ(24, m)

#define  BLINK_SLOW     ESC_SEQ(5,  m)
#define  BLINK_RAPID    ESC_SEQ(6,  m)
#define  BLINK_OFF      ESC_SEQ(6,  m)

#define  INVERSE        ESC_SEQ(7,  m)
#define  INVERSE_OFF    ESC_SEQ(27, m)

#define  CROSSED        ESC_SEQ(9, m)
#define  CROSSED_OFF    ESC_SEQ(29, m)

// Text foreground colors {{{1

#define  BLACK          ESC_SEQ(30, m)
#define  RED            ESC_SEQ(31, m)
#define  GREEN          ESC_SEQ(32, m)
#define  YELLOW         ESC_SEQ(33, m)
#define  BLUE           ESC_SEQ(34, m)
#define  MAGENTA        ESC_SEQ(35, m)
#define  CYAN           ESC_SEQ(36, m)
#define  GREY           ESC_SEQ(90, m)
#define  WHITE          ESC_SEQ(97, m)

#define  LIGHT_GREY     ESC_SEQ(37, m)
#define  LIGHT_RED      ESC_SEQ(91, m)
#define  LIGHT_GREEN    ESC_SEQ(92, m)
#define  LIGHT_YELLOW   ESC_SEQ(93, m)
#define  LIGHT_BLUE     ESC_SEQ(94, m)
#define  LIGHT_MAGENTA  ESC_SEQ(95, m)
#define  LIGHT_CYAN     ESC_SEQ(96, m)

// Text background colors {{{1

#define  BG_BLACK          ESC_SEQ(40, m)
#define  BG_RED            ESC_SEQ(41, m)
#define  BG_GREEN          ESC_SEQ(42, m)
#define  BG_YELLOW         ESC_SEQ(43, m)
#define  BG_BLUE           ESC_SEQ(44, m)
#define  BG_MAGENTA        ESC_SEQ(45, m)
#define  BG_CYAN           ESC_SEQ(46, m)
#define  BG_GREY           ESC_SEQ(100, m)
#define  BG_WHITE          ESC_SEQ(107, m)

#define  BG_LIGHT_GREY     ESC_SEQ(47, m)
#define  BG_LIGHT_RED      ESC_SEQ(101, m)
#define  BG_LIGHT_GREEN    ESC_SEQ(102, m)
#define  BG_LIGHT_YELLOW   ESC_SEQ(103, m)
#define  BG_LIGHT_BLUE     ESC_SEQ(104, m)
#define  BG_LIGHT_MAGENTA  ESC_SEQ(105, m)
#define  BG_LIGHT_CYAN     ESC_SEQ(106, m)

// Graphics Mode }}}

#endif // ANSI_ESC_SEQ_H_
