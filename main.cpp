import <string>;
import <iostream>;
import <cstddef>;

import parser;
import text;
import moth;

int main() {
    std::string line;
    std::size_t line_number{};

    Parser parser;

    while (std::getline(std::cin, line)) {
        ++line_number;
        parser.parse_line(line, line_number);
    }

    return 0;
}
