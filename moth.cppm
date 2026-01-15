export module moth;

import <cstdint>;
import <cstddef>;
import <string>;
import <ostream>;
import <cctype>;


export class Moth {
    protected:
    static constexpr char MIN_EDIBLE = static_cast<char>(33);
    static constexpr char MAX_EDIBLE = static_cast<char>(126);
    static constexpr char UNEDIBLE_SPACE = static_cast<char>(32);
    static constexpr uint64_t MOVE_COST = 10;

    uint64_t vitality_;
    std::size_t P_;
    std::size_t position_;
    bool is_active_;
    char kind_;

    virtual bool can_eat(char character) const noexcept {
        if (MIN_EDIBLE <= character && character <= MAX_EDIBLE) return true;
        return false;
    }

    void eat(std::string &text) noexcept {
        char cur_char = text[position_];
        if (!can_eat(cur_char)) {
            if (cur_char == UNEDIBLE_SPACE) {
                uint64_t space = static_cast<uint64_t>(UNEDIBLE_SPACE);
                vitality_ = vitality_ >= space ? vitality_ - space : 0;
            }
        }
        else {
            vitality_ += cur_char;
            text[position_] = UNEDIBLE_SPACE;
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
    static constexpr char KIND = '*';
    CommonMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '*') {}
};

export class LetterMoth : public Moth {
    private:

    std::size_t next_move_size() noexcept override {
        return P_;
    }

    bool can_eat(char character) const noexcept override {
        if (std::isalpha(static_cast<unsigned char>(character))) {
            return true;
        }
        return false;
    }

    public:
    static constexpr char KIND = 'A';
    LetterMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, 'A') {}

};

export class DigitMoth : public Moth {
    private:

    std::size_t next_move_size() noexcept override {
        return P_;
    }

    bool can_eat(char character) const noexcept override {
        if (std::isdigit(static_cast<unsigned char>(character))) {
            return true;
        }
        return false;
    }

    public:
    static constexpr char KIND = '1';
    DigitMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '1') {}

};

export class FussyMoth : public Moth {
    private:

    std::size_t last_move_size_;

    std::size_t next_move_size() noexcept override {
        return last_move_size_ = (last_move_size_ % P_) + 1;
    }

    bool can_eat(char character) const noexcept override {
        if (
            !(std::isalnum(static_cast<unsigned char>(character)))
            && 
            (MIN_EDIBLE <= character && character <= MAX_EDIBLE)
        ) {
            return true;
        }
        return false;
    }

    public:
    static constexpr char KIND = '!';
    FussyMoth(uint64_t vitality, std::size_t P, std::size_t pos) : Moth(vitality, P, pos, '!'), last_move_size_(0) {}
};