export module parser;

import <iostream>;
import <regex>;
import <cstddef>;

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

    void print_error(std::size_t line_number) const noexcept {
        std::cerr << "ERROR " << line_number << '\n';
    }

    bool parse_text(const std::smatch &match, std::size_t line_number) {
        std::cout << "text command" << '\n';
        // TODO:: implement
        return false;
    }

    bool parse_moth(const std::smatch &match, std::size_t line_number) {
        std::cout << "moth command" << '\n';
        // TODO:: implement
        return false;
    }

    bool parse_feed(const std::smatch &match, std::size_t line_number) {
        std::cout << "feed command" << '\n';
        // TODO:: implement
        return false;
    }

    bool parse_printm(const std::smatch &match, std::size_t line_number) {
        std::cout << "printm command" << '\n';
        // TODO:: implement
        return false;
    }

    bool parse_printt(const std::smatch &match, std::size_t line_number) {
        std::cout << "printt command" << '\n';
        // TODO:: implement
        return false;
    }

    bool parse_delete(const std::smatch &match, std::size_t line_number) {
        std::cout << "delete command" << '\n';
        // TODO:: implement
        return false;
    }

public:
    Parser() = default;

    bool parse_line(const std::string &line, std::size_t line_number) {
        if (line.empty()) {
            print_error(line_number);
            return false;
        }

        std::smatch match;

        if (std::regex_match(line, match, text_regex_)) {
            return parse_text(match, line_number);
        }
        if (std::regex_match(line, match, moth_regex_)) {
            return parse_moth(match, line_number);
        }
        if (std::regex_match(line, match, feed_regex_)) {
            return parse_feed(match, line_number);
        }
        if (std::regex_match(line, match, printm_regex_)) {
            return parse_printm(match, line_number);
        }
        if (std::regex_match(line, match, printt_regex_)) {
            return parse_printt(match, line_number);
        }
        if (std::regex_match(line, match, delete_regex_)) {
            return parse_delete(match, line_number);
        }

        print_error(line_number);
        return false;
    }
};
