export module moth;

import <cstdint>;
import <cstddef>;
import <string>;


export class Moth {
    private:
    static constexpr uint8_t MIN_EDIBLE = 33;
    static constexpr uint8_t MAX_EDIBLE = 126;
    static constexpr uint8_t UNEDIBLE_SPACE = 32;
    static constexpr uint64_t MOVE_COST = 10;

    uint64_t vitality_;
    std::size_t P_;
    std::size_t position_;
    

    public:

    Moth(uint64_t vitality, std::size_t P, std::size_t pos) : vitality_(vitality), P_(P), position_(pos) {}
    virtual ~Moth() = default;

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

    virtual void move() noexcept = 0;

    // TODO Finish abstract base class.

};