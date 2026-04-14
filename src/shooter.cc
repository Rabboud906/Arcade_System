#include "shooter.h"

Shooter::Shooter(const int id) noexcept : Machine(id, "Shooter", 2) {}

ScoreResult Shooter::play(Player& p) {
    // TODO
    // As sort of a PRNG (to make testing easier), have the score be the player's ID multiplied by 37 and then modulo
    // 1000.
    // Add the score to that player.
    // Return a result that consists of the score, a duration of 12.5 seconds, and a note of "Shot!".
    ScoreResult r;
    r.score = (p.id() * 37) % 1000;
    p.add_score(r.score);
    r.duration_seconds = 12.5;
    r.note = "Shot!";

    return r;
}

