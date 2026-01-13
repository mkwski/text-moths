import <string>;
import <iostream>;

import parser;

int main() {
    std::string line;
    size_t line_number{};

    Parser parser;

    while (std::getline(std::cin, line)) {
        ++line_number;
        parser.parse_line(line, line_number);
    }

    return 0;
}
