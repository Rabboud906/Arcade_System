#include <string>

#include "player.h"

Player::Player(const int id, std::string name) noexcept
        : id_(id), name_(std::move(name)) {}

int Player::id() const noexcept {
    // TODO
    return id_;
}
const std::string& Player::name() const noexcept {
    // TODO
    return name_;

}

int Player::tokens() const noexcept {
    // TODO
    return tokens_;
}

void Player::add_tokens(const int n) noexcept {
    // TODO
    tokens_ += n;
}

bool Player::spend_tokens(const int n) noexcept {
    // TODO: return true if the player has sufficient tokens to spend.
    // only deduct tokens if the player can actually afford to spend them.
    if (n <= tokens_) {
        tokens_ -= n;
        return true;
    }
    return false;
}

void Player::add_score(const int s) noexcept {
    // TODO
     total_score_ += s;
}

int Player::total_score() const noexcept {
    // TODO
    return total_score_;
}
