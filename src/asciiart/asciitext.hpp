#ifndef _ASCII_TEXTS_STRUCT_HPP_
#define _ASCII_TEXTS_STRUCT_HPP_

struct AsciiText {
    const char** text;
    const int height;
};

enum class Alignment {
    Left,
    Center,
    Right
};

#endif  // _ASCII_TEXTS_STRUCT_HPP_
