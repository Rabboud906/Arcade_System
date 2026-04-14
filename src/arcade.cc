
#include "arcade.h"
#include "token_booth.h"
#include <fstream>
#include <utility>

using namespace std;

Player& Arcade::register_player(string name) {
    // TODO
    //Create a player with a given name. Remember to increment the next player ID tracker we keep.
    int id = next_player_id_;
    Player player(id, std::move(name));
    players_.emplace(id, player);
    ++next_player_id_;
    return players_.at(id);

}

int Arcade::add_machine(std::unique_ptr<Machine> m) noexcept {
    // TODO
    // Add the machine to our collection of machines.
    // Remember to increment the next machine ID tracker we keep.
    // Hint: move ownership of the machine to the collection of machines.
    int id = next_machine_id_++;
    machines_.push_back(std::move(m));
    return id;
}

void Arcade::add_token_booth(TokenBooth booth) noexcept {
    // TODO
    token_booths.push_back(std::move(booth));

}

TokenBooth* Arcade::find_token_booth(const std::string& location) noexcept {
    // TODO: find a token booth with the given location. return the first one we find in our collection of booths.
    // If we can't find a token booth at the given location, return nullptr.
    for ( auto& token_booth: token_booths ) {
        if ( token_booth.location() == location ) {
            return &token_booth;
        }
    }
    return nullptr;
}



bool Arcade::buy_tokens(const int player_id, const int cash_cents, TokenBooth& booth) noexcept {
    // TODO: find the player by their ID and have them buy tokens at the given booth.
    // Remember to add the tokens to the player.

    auto player_it = players_.find(player_id); // return an iterator to a pair if found where <player_int, Player object>
    if (player_it == players_.end()) {
        return false;
    }
    int i = booth.buy_tokens(cash_cents);
    player_it -> second.add_tokens(i);
    return true;


}

std::optional<ScoreResult> Arcade::play_machine(const int player_id, const int machine_id) noexcept {
    // TODO:
    // 1. Find the player by their ID. return std::nullopt if unable to do so.
    // 2. Return std::nullopt if machine ID is invalid.
    // 3. If the player is unable to spend the machine's token cost, return std::nullopt.
    // 4. Get the score result by having the player play the machine.
    // 5. Insert the player ID and score into the leaderboard.
    auto player_it = players_.find(player_id);
    if (player_it == players_.end()) {
        return std::nullopt;
    }
    Machine* machine = nullptr;
    for ( auto& m : machines_ ) {
        if (m->id() == machine_id) {
            machine = m.get();
            break;
        }
    }
    if (machine == nullptr) {
        return std::nullopt;
    }
    Player player = player_it->second;
    ScoreResult result = machine->play(player);
    board_.insert({player_id,result.score});
    return result;

}

const Leaderboard& Arcade::leaderboard() const noexcept {
    return board_;
}

bool Arcade::save_leaderboard(std::string const& path) const {
    // TODO
    bool r = board_.save_to_file(path);
    return r;

}

bool Arcade::load_leaderboard(std::string const& path) {
    // TODO
    bool r = board_.load_from_file(path);
    return r;
}
