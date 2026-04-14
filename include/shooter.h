#pragma once

#include "machine.h"

class Shooter : public Machine {
public:
    explicit Shooter(int id) noexcept;
    ScoreResult play(Player& p) override;
};
