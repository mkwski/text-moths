export module moth;

import <cstdint>;
import <cstddef>;
import <string>;
import <ostream>;


export class Moth {
    protected:
    static constexpr uint8_t MIN_EDIBLE = 33;
    static constexpr uint8_t MAX_EDIBLE = 126;
    static constexpr uint8_t UNEDIBLE_SPACE = 32;
    static constexpr uint64_t MOVE_COST = 10;

    uint64_t vitality_;
    std::size_t P_;
    std::size_t position_;
    bool is_active_;
    char kind_;

    virtual bool can_eat(uint8_t character) const noexcept {
        if (MIN_EDIBLE <= character && character <= MAX_EDIBLE) return true;
        return false;
    }

    void eat(std::string &text) noexcept {
        uint8_t cur_char = static_cast<uint8_t>(text[position_]);
        if (!can_eat(cur_char)) {
            // TODO: Ask if the moth loses vitality on other chars than the space.
            if (cur_char == UNEDIBLE_SPACE) {
                vitality_ = vitality_ >= UNEDIBLE_SPACE ? vitality_ - UNEDIBLE_SPACE : 0;
            }
        }
        else {
            vitality_ += cur_char;
            text[position_] = static_cast<char>(UNEDIBLE_SPACE);
        }
    }

    virtual std::size_t next_move_size() noexcept = 0;

    public:

    Moth(uint64_t vitality, std::size_t P, std::size_t pos, char kind) : vitality_(vitality), P_(P), position_(pos), is_active_(true), kind_(kind) {}
    virtual ~Moth() = default;

    void do_action(std::string &text) {
        if (!is_active_) return;
        std::size_t n = text.size();
        std::size_t next_move = next_move_size();

        uint64_t needed_vitality = static_cast<uint64_t>(next_move) * MOVE_COST;
        if (vitality_ < needed_vitality) {
            vitality_ = 0;
            is_active_ = false;
            return;
        }
        vitality_ -= needed_vitality;

        position_ = (position_ + next_move) % n;
        eat(text);
    }

    friend std::ostream& operator<<(std::ostream& os, const Moth& moth);

};

export std::ostream& operator<<(std::ostream& os, const Moth& moth) {
    os << moth.kind_ << ' ' << moth.P_ << ' ' << moth.position_ << ' ' << moth.vitality_ << '\n';
    return os;
}

export class CommonMoth : public Moth {
    private:
    std::size_t next_move_size() noexcept override {
        return P_;
    }

    public:
    CommonMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '*') {}
};

export class LetterMoth : public Moth {
    private:

    static constexpr uint8_t FIRST_LOWERCASE_LETTER = static_cast<uint8_t>('a');
    static constexpr uint8_t LAST_LOWERCASE_LETTER = static_cast<uint8_t>('z');
    static constexpr uint8_t FIRST_UPPERCASE_LETTER = static_cast<uint8_t>('A');
    static constexpr uint8_t LAST_UPPERCASE_LETTER = static_cast<uint8_t>('Z');

    std::size_t next_move_size() noexcept override {
        return P_;
    }

    bool can_eat(uint8_t character) const noexcept override {
        if (
            (FIRST_LOWERCASE_LETTER <= character && character <= LAST_LOWERCASE_LETTER)
            ||
            (FIRST_UPPERCASE_LETTER <= character && character <= LAST_UPPERCASE_LETTER)
        ) {
            return true;
        }
        return false;
    }

    public:
    LetterMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, 'A') {}

};

export class DigitMoth : public Moth {
    private:
    static constexpr uint8_t FIRST_DIGIT = static_cast<uint8_t>('0');
    static constexpr uint8_t LAST_DIGIT = static_cast<uint8_t>('9');

    std::size_t next_move_size() noexcept override {
        return P_;
    }

    bool can_eat(uint8_t character) const noexcept override {
        if (
            (FIRST_DIGIT <= character && character <= LAST_DIGIT)
        ) {
            return true;
        }
        return false;
    }

    public:
    DigitMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '1') {}

};

export class FussyMoth : public Moth {
    private:
    static constexpr uint8_t FIRST_LOWERCASE_LETTER = static_cast<uint8_t>('a');
    static constexpr uint8_t LAST_LOWERCASE_LETTER = static_cast<uint8_t>('z');
    static constexpr uint8_t FIRST_UPPERCASE_LETTER = static_cast<uint8_t>('A');
    static constexpr uint8_t LAST_UPPERCASE_LETTER = static_cast<uint8_t>('Z');
    static constexpr uint8_t FIRST_DIGIT = static_cast<uint8_t>('0');
    static constexpr uint8_t LAST_DIGIT = static_cast<uint8_t>('9');

    std::size_t last_move_size_;

    std::size_t next_move_size() noexcept override {
        return last_move_size_ = (last_move_size_ % P_) + 1;
    }

    bool can_eat(uint8_t character) const noexcept override {
        if (
            !(FIRST_DIGIT <= character && character <= LAST_DIGIT)
            &&
            !(FIRST_LOWERCASE_LETTER <= character && character <= LAST_LOWERCASE_LETTER)
            &&
            !(FIRST_UPPERCASE_LETTER <= character && character <= LAST_UPPERCASE_LETTER)
            && 
            (MIN_EDIBLE <= character && character <= MAX_EDIBLE)
        ) {
            return true;
        }
        return false;
    }

    public:
    FussyMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '!'), last_move_size_(0) {}
};