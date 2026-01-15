export module text;

export import moth;

import <vector>;
import <memory>;
import <string>;
import <cstddef>;
import <iostream>;

export class Text {
private:
    std::vector<std::unique_ptr<Moth>> moths_;
    std::string text_;

public:
    Text() = default;
    Text(const std::string &text) : text_(text) {}

    void place_moth(std::size_t pos, char kind, uint64_t vitality, std::size_t P) {
        if (kind == CommonMoth::KIND) {
            moths_.push_back(std::make_unique<CommonMoth>(vitality, P, pos));
        } else if (kind == DigitMoth::KIND) {
            moths_.push_back(std::make_unique<DigitMoth>(vitality, P, pos));
        } else if (kind == LetterMoth::KIND) {
            moths_.push_back(std::make_unique<LetterMoth>(vitality, P, pos));
        } else if (kind == FussyMoth::KIND) {
            moths_.push_back(std::make_unique<FussyMoth>(vitality, P, pos));
        }
    }

    void feed(unsigned int cycles) noexcept {
        for (unsigned int i = 0; i < cycles; ++i) {
            for (const auto &moth : moths_) {
                moth->do_action(text_);
            }
        }
    }

    std::size_t get_text_length() const noexcept { return text_.size(); }

    void print_moths() const noexcept {
        for (const auto &moth : moths_) {
            std::cout << *moth;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Text &text);
};

export std::ostream &operator<<(std::ostream &os, const Text &text) {
    os << text.text_ << '\n';
    return os;
}
