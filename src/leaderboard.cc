#include <fstream>
#include <ranges>
#include <sstream>
#include <set>

#include "leaderboard.h"
using namespace std;

Leaderboard::Leaderboard(const std::size_t max_entries) noexcept
        : max_(max_entries) {}

void Leaderboard::insert(ScoreEntry e) noexcept {
    // TODO: Make sure the number of entries never exceeds the maximum number that was set.
    // Hint: multisets are automatically sorted, so erasing scores should be pretty easy.
    entries_.insert(e);
    if (entries_.size() > max_) {
        auto it = entries_.end();
        --it;
        entries_.erase(it);
    }

}

std::vector<ScoreEntry> Leaderboard::top() const noexcept {
    // TODO
    std::vector<ScoreEntry> result;
     for (const auto& entry : entries_) {
         result.push_back(entry);
     }
    return result;
}

std::size_t Leaderboard::size() const noexcept {
    // TODO
    return entries_.size();
}


bool Leaderboard::save_to_file(const std::string &path) const {
    // TODO
    ofstream file(path);
    if (file.is_open()) {
        for (const auto& entry : entries_) {
            file << entry.player_id << " " << entry.score << endl;
        }
        return true;
    }
    return false;

}

bool Leaderboard::load_from_file(const std::string &path) {
    // TODO
    ifstream file(path);
    if (file.is_open()) {
        entries_.clear();
        int p_id, p_score;
        while (file >> p_id >> p_score) {
            insert({p_id, p_score});
        }
        return true;
    }
    return false;
}
