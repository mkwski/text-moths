export module parser;

import <iostream>;
import <regex>;
import <cstddef>;
import <string>;
import <cstdint>;

import text_set;

namespace detail {

constexpr std::string_view TEXT_REGEX_PATTERN = R"(^TEXT (\d+) ([!-~]+)$)";
constexpr std::string_view MOTH_REGEX_PATTERN =
    R"(^MOTH (\d+) (\d+) ([*A1!]) ([1-9]\d*) ([1-9]\d?)$)";
constexpr std::string_view FEED_REGEX_PATTERN = R"(^FEED (\d+) ([1-9]\d*)$)";
constexpr std::string_view PRINTM_REGEX_PATTERN = R"(^PRINTM (\d+)$)";
constexpr std::string_view PRINTT_REGEX_PATTERN = R"(^PRINTT (\d+)$)";
constexpr std::string_view DELETE_REGEX_PATTERN = R"(^DELETE (\d+)$)";

} // namespace detail

export class Parser {

private:
    inline static const std::regex text_regex_{detail::TEXT_REGEX_PATTERN.data()};
    inline static const std::regex moth_regex_{detail::MOTH_REGEX_PATTERN.data()};
    inline static const std::regex feed_regex_{detail::FEED_REGEX_PATTERN.data()};
    inline static const std::regex printm_regex_{detail::PRINTM_REGEX_PATTERN.data()};
    inline static const std::regex printt_regex_{detail::PRINTT_REGEX_PATTERN.data()};
    inline static const std::regex delete_regex_{detail::DELETE_REGEX_PATTERN.data()};

    TextSet text_set_;

    void print_error(std::size_t line_number) const noexcept {
        std::cerr << "ERROR " << line_number << '\n';
    }

    bool parse_text(const std::smatch &match, std::size_t line_number) {
        std::cout << "text command" << '\n';
        std::size_t text_num = std::stoull(match[1].str());
        if (text_set_.text_num_exists(text_num)) return false;
        std::string text = match[2].str();
        text_set_.add_text(text_num, text);
        return true;
    }

    bool parse_moth(const std::smatch &match, std::size_t line_number) {
        std::cout << "moth command" << '\n';
        
        std::size_t text_num = std::stoull(match[1].str());
        if (!text_set_.text_num_exists(text_num)) return false;
        std::size_t pos = std::stoull(match[2].str());
        if (pos >= text_set_.get_text_length(text_num)) return false;
        char kind = match[3].str()[0];
        uint64_t vitality = std::stoull(match[4].str());
        std::size_t P = std::stoull(match[5].str());
        if (P < 1 || P > 99) return false;
        text_set_.add_moth(text_num, pos, kind, vitality, P);

        return true;
    }

    bool parse_feed(const std::smatch &match, std::size_t line_number) {
        std::cout << "feed command" << '\n';
        
        std::size_t text_num = std::stoull(match[1].str());
        if (!text_set_.text_num_exists(text_num)) return false;
        unsigned int cycles = std::stoul(match[2].str());
        text_set_.feed(text_num, cycles);

        return true;
    }

    bool parse_printm(const std::smatch &match, std::size_t line_number) {
        std::cout << "printm command" << '\n';
        
        std::size_t text_num = std::stoull(match[1].str());
        if (!text_set_.text_num_exists(text_num)) return false;
        text_set_.print_moths(text_num);

        return true;
    }

    bool parse_printt(const std::smatch &match, std::size_t line_number) {
        std::cout << "printt command" << '\n';
        
        std::size_t text_num = std::stoull(match[1].str());
        if (!text_set_.text_num_exists(text_num)) return false;
        text_set_.print_text(text_num);

        return true;
    }

    bool parse_delete(const std::smatch &match, std::size_t line_number) {
        std::cout << "delete command" << '\n';
        
        std::size_t text_num = std::stoull(match[1].str());
        if (!text_set_.text_num_exists(text_num)) return false;
        text_set_.delete_text(text_num);

        return true;
    }

public:
    Parser() = default;

    bool parse_line(const std::string &line, std::size_t line_number) {
        if (line.empty()) {
            print_error(line_number);
            return false;
        }

        std::smatch match;

        bool parse_result = true;

        if (std::regex_match(line, match, text_regex_)) {
            parse_result = parse_text(match, line_number);
        }
        if (std::regex_match(line, match, moth_regex_)) {
            parse_result = parse_moth(match, line_number);
        }
        if (std::regex_match(line, match, feed_regex_)) {
            parse_result = parse_feed(match, line_number);
        }
        if (std::regex_match(line, match, printm_regex_)) {
            parse_result = parse_printm(match, line_number);
        }
        if (std::regex_match(line, match, printt_regex_)) {
            parse_result = parse_printt(match, line_number);
        }
        if (std::regex_match(line, match, delete_regex_)) {
            parse_result = parse_delete(match, line_number);
        }
        if (parse_result) return true;

        print_error(line_number);
        return false;
    }
};
