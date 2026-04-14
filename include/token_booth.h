#include <utility>

#pragma once

class TokenBooth {
public:
    explicit TokenBooth(std::string location): tokens_sold_(0), location_(std::move(location)) {}
    [[nodiscard]] const std::string& location() const noexcept;
    [[nodiscard]] int buy_tokens(int cash_cents) noexcept; // 1 token per 100 cents
    [[nodiscard]] int tokens_sold() const noexcept;

private:
    int tokens_sold_{0};
    std::string location_;
};
