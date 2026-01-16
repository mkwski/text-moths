export module text_set;

export import text;

import <unordered_map>;
import <cstddef>;
import <string>;
import <iostream>;
import <cstdint>;

// Manages texts indexed by number and their moth colonies.
export class TextSet {
private:
    std::unordered_map<std::size_t, Text> texts_;

public:
    TextSet() = default;

    void add_text(std::size_t text_num, const std::string &text) noexcept {
        texts_[text_num] = Text(text);
    }

    // Does not check if the text number exists!
    void delete_text(std::size_t text_num) { texts_.erase(text_num); }

    // Does not check if the text number exists! It has to be done prior to
    // calling this method.
    void add_moth(std::size_t text_num, std::size_t pos, char kind,
                  uint64_t vitality, std::size_t P) {
        texts_[text_num].place_moth(pos, kind, vitality, P);
    }

    // Checks whether a text with the given number exists.
    bool text_num_exists(std::size_t text_num) const noexcept {
        if (texts_.contains(text_num))
            return true;
        return false;
    }

    // Does not check if the text number exists!
    void print_text(std::size_t text_num) const {
        std::cout << texts_.at(text_num);
    }

    // Does not check if the text number exists!
    void print_moths(std::size_t text_num) const {
        texts_.at(text_num).print_moths();
    }

    // Does not check if the text number exists!
    std::size_t get_text_length(std::size_t text_num) const {
        return texts_.at(text_num).get_text_length();
    }

    // Does not check if the text number exists!
    void feed(std::size_t text_num, unsigned int cycles) noexcept {
        texts_[text_num].feed(cycles);
    }
};
