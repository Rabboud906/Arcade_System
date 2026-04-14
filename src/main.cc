#include <iostream>
#include <memory>

#include "arcade.h"
#include "player.h"
#include "puzzle.h"
#include "shooter.h"
#include "token_booth.h"

int main() {
    Arcade arcade;

    // Register players
    Player& a = arcade.register_player("Alice");
    Player& b = arcade.register_player("Bob");

    // Add machines
    arcade.add_machine(std::make_unique<Shooter>(1));
    arcade.add_machine(std::make_unique<Puzzle>(2));

    auto tb = TokenBooth("north");
    // Give tokens
    arcade.buy_tokens(a.id(), 500, tb); // 5 tokens
    arcade.buy_tokens(b.id(), 300, tb); // 3 tokens

    // Plays
    auto r1 = arcade.play_machine(a.id(), 1);
    std::cout << "Alice played Shooter -> score: " << r1->score << " note: " << r1->note << "\n";

    auto r2 = arcade.play_machine(b.id(), 2);
    std::cout << "Bob played Puzzle -> score: " << r2->score << " note: " << r2->note << "\n";

    // Show leaderboard
    auto top = arcade.leaderboard().top();
    std::cout << "Leaderboard:\n";
    for (auto const& e : top) {
        std::cout << "  player " << e.player_id << " : " << e.score << "\n";
    }

    return 0;
}
