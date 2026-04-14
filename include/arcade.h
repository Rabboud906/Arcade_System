#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

#include "leaderboard.h"
#include "machine.h"
#include "player.h"
#include "token_booth.h"

class Arcade {
public:
    Arcade() = default;

    Player& register_player(std::string name);                 // returns reference to created player
    int add_machine(std::unique_ptr<Machine> m) noexcept;
    void add_token_booth(TokenBooth booth) noexcept;
    [[nodiscard]] TokenBooth* find_token_booth(const std::string& location) noexcept;
    bool buy_tokens(int player_id, int cash_cents, TokenBooth& token) noexcept;
    std::optional<ScoreResult> play_machine(int player_id, int machine_id) noexcept;


    const Leaderboard& leaderboard() const noexcept;

    // persistence helpers
    bool save_leaderboard(std::string const& path) const;
    bool load_leaderboard(std::string const& path);

private:
    std::unordered_map<int, Player> players_;
    std::vector<std::unique_ptr<Machine>> machines_;
    std::vector<TokenBooth> token_booths;
    Leaderboard board_{10};
    int next_player_id_{1};
    int next_machine_id_ = 1;
};
