#pragma once

#include <string>
#include <utility>
#include "player.h"

struct ScoreResult {
    int score{};
    double duration_seconds{};
    std::string note;
};

class Machine {
public:
    Machine(int id, std::string name, int cost) noexcept;



    virtual ~Machine() = default;

    [[nodiscard]] int id() const noexcept;
    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] int play_cost() const noexcept;

    virtual ScoreResult play(Player& player) = 0;

    Machine(Machine&&) = default;
    Machine& operator=(Machine&&) = delete;
    Machine(const Machine&) = delete;
    Machine& operator=(const Machine&) = delete;

private:
    int id_;
    std::string name_;
    int cost_;
};
