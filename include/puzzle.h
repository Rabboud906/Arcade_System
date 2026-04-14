#pragma once

#include "machine.h"

class Puzzle : public Machine {
public:
    explicit Puzzle(int id) noexcept;
    ScoreResult play(Player& p) override;
};
