#pragma once

#include <set>
#include <vector>
#include <optional>
#include <string>

struct ScoreEntry {
    int player_id{};
    int score{};

    bool operator<(const ScoreEntry& o) const noexcept {
        if (score != o.score) return score > o.score; // higher first
        return player_id < o.player_id;
    }
};

class Leaderboard {
public:
    explicit Leaderboard(std::size_t max_entries = 10) noexcept;

    void insert(ScoreEntry e) noexcept;
    [[nodiscard]] std::vector<ScoreEntry> top() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

    // Persistence: save/load CSV "player_id,score\n"
    [[nodiscard]] bool save_to_file(std::string const& path) const;
    bool load_from_file(std::string const& path);

private:
    std::size_t max_;
    std::multiset<ScoreEntry> entries_;
};
