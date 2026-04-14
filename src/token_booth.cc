#include <string>

#include "token_booth.h"

int TokenBooth::buy_tokens(const int cash_cents) noexcept {
    // TODO: A token is worth 100 cents. We keep any extra, so if we get a deposit of 250 cents, the player gets 2
    // tokens, and we keep the "extra" 50 cents.
    // Be sure to increase the booth's number of tokens sold.
    if (cash_cents <= 0) return 0;
    int t = cash_cents / 100;
    tokens_sold_ += t;
    return t;
}

int TokenBooth::tokens_sold() const noexcept {
    // TODO
    return tokens_sold_;
}

const std::string& TokenBooth::location() const noexcept {
    // TODO
    return location_;
}
