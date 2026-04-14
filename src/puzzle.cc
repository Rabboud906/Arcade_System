#include "puzzle.h"

Puzzle::Puzzle(const int id) noexcept : Machine(id, "Puzzle", 1) {}

ScoreResult Puzzle::play(Player& p) {
    // TODO
    // As sort of a PRNG (to make testing easier), have the score be the player's ID multiplied by 13 and then modulo
    // 500.
    // Add the score to that player.
    // Return a result that consists of the score, a duration of 30.0 seconds, and a note of "Solved".
    ScoreResult r;
    r.score = p.id() * 13 % 500;
    p.add_score(r.score);
    r.duration_seconds = 30;
    r.note = "Solved";

    return r;
}
