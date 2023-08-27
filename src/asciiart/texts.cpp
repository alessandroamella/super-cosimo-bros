#include "texts.hpp"

#include <fstream>
#include <iostream>
#include <string>

AsciiTexts::AsciiTexts() {
    splash = read_from_file("splash.txt");
    game_over = read_from_file("game_over.txt");
    shop = read_from_file("shop.txt");
}

List<const char*> AsciiTexts::read_from_file(const char* file_name) {
    std::ifstream infile(file_name);

    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file \"" + std::string(file_name) + "\"");
    }

    List<std::string> lines;

    std::string line;
    while (std::getline(infile, line)) {
        lines.push(line);
    }

    infile.close();

    List<const char*> char_lines;

    // Passaggio di copia OBBLIGATORIO per evitare che il puntatore venga distrutto
    for (int i = 0; i < lines.length(); i++) {
        char_lines.push(lines.at(i).c_str());
    }

    return char_lines;
}

List<const char*>& AsciiTexts::get_splash() {
    return splash;
}

List<const char*>& AsciiTexts::get_game_over() {
    return game_over;
}

List<const char*>& AsciiTexts::get_shop() {
    return shop;
}
