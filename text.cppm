export module text;

export import moth;

import <vector>;
import <memory>;
import <string>;
import <cstddef>;
import <iostream>;

// Holds a text and the moths currently feeding on it.
export class Text {
private:
    std::vector<std::unique_ptr<Moth>> moths_;
    std::string text_;

public:
    Text() = default;
    Text(const std::string &text) : text_(text) {}

    // Creates and places a moth of the given kind at position.
    void place_moth(std::size_t pos, char kind, uint64_t vitality,
                    std::size_t P) {
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

    // Runs the given number of feeding cycles.
    void feed(unsigned int cycles) noexcept {
        for (unsigned int i = 0; i < cycles; ++i) {
            for (const auto &moth : moths_) {
                moth->do_action(text_);
            }
        }
    }

    std::size_t get_text_length() const noexcept { return text_.size(); }

    // Prints moths in insertion order.
    void print_moths() const noexcept {
        for (const auto &moth : moths_) {
            std::cout << *moth;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Text &text);
};

// Prints the current text state.
export std::ostream &operator<<(std::ostream &os, const Text &text) {
    os << text.text_ << '\n';
    return os;
}
