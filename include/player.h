#pragma once

#include <string>

class Player {
public:
    Player() = default;
    Player(int id, std::string name) noexcept;

    [[nodiscard]] int id() const noexcept;
    [[nodiscard]] const std::string& name() const noexcept;

    [[nodiscard]] int tokens() const noexcept;
    void add_tokens(int n) noexcept;
    bool spend_tokens(int n) noexcept;

    void add_score(int s) noexcept;
    [[nodiscard]] int total_score() const noexcept;

private:
    int id_{0};
    std::string name_;
    int tokens_{0};
    int total_score_{0};
};
