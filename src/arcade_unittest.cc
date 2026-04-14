#include <filesystem>

#include <gtest/gtest.h>

#include "arcade.h"
#include "leaderboard.h"
#include "player.h"
#include "puzzle.h"
#include "shooter.h"
#include "token_booth.h"

namespace fs = std::filesystem;

static int score = 0;
static const int TOTAL_POINTS = 100;

TEST(TokenBoothTest, BuyTokensBasic) {
    TokenBooth b("west");
    ASSERT_EQ(b.buy_tokens(0), 0);
    ASSERT_EQ(b.buy_tokens(50), 0);
    ASSERT_EQ(b.buy_tokens(100), 1);
    ASSERT_EQ(b.buy_tokens(250), 2);
    ASSERT_EQ(b.tokens_sold(), 3);
    score += 10;
}

TEST(LeaderboardTest, TopKeepsMax) {
    Leaderboard lb(3);
    ASSERT_EQ(lb.size(), 0);
    lb.insert({1, 10});
    ASSERT_EQ(lb.size(), 1);
    lb.insert({2, 30});
    ASSERT_EQ(lb.size(), 2);
    lb.insert({3, 20});
    ASSERT_EQ(lb.size(), 3);
    lb.insert({4, 40});
    ASSERT_EQ(lb.size(), 3);
    const auto top = lb.top();
    ASSERT_EQ(top.size(), 3);
    ASSERT_EQ(top[0].player_id, 4);
    ASSERT_EQ(top[1].player_id, 2);
    ASSERT_EQ(top[2].player_id, 3);
    score += 10;
}

TEST(LeaderboardTest, SaveLoadFile) {
    Leaderboard lb(5);
    lb.insert({1, 100});
    lb.insert({2, 200});
    const std::string fn = "test_lb.csv";
    ASSERT_TRUE(lb.save_to_file(fn));
    Leaderboard lb2(5);
    ASSERT_TRUE(lb2.load_from_file(fn));
    auto t2 = lb2.top();
    ASSERT_EQ(t2.size(), 2);
    ASSERT_EQ(t2[0].player_id, 2);
    ASSERT_EQ(t2[0].score, 200);
    // cleanup
    std::error_code ec;
    fs::remove(fn, ec);
    score += 20;
}

// Test Fixture for Puzzle and Shooter
class PlayerTest : public ::testing::Test {
protected:
    Player player{1, "TestPlayer"}; // Create a Player with ID 1
};

// Test for Puzzle class
TEST_F(PlayerTest, PuzzlePlay) {
    Puzzle puzzle(1);  // Create a Puzzle instance with ID 1

    ScoreResult result = puzzle.play(player);  // Call the play method
    ASSERT_EQ(player.total_score(), 13);             // Expecting 13 based on the scoring logic
    ASSERT_EQ(result.score, 13);                // Expecting ScoreResult to match
    ASSERT_EQ(result.duration_seconds, 30.0);               // Expecting cost to match
    ASSERT_EQ(result.note, "Solved");         // Expecting message to match
    score += 5;
}

// Test for Shooter class
TEST_F(PlayerTest, ShooterPlay) {
    Shooter shooter(2); // Create a Shooter instance with ID 2

    ScoreResult result = shooter.play(player);  // Call the play method
    ASSERT_EQ(player.total_score(), 37);              // Expecting 37 based on the scoring logic
    ASSERT_EQ(result.score, 37);                 // Expecting ScoreResult to match
    ASSERT_EQ(result.duration_seconds, 12.5);                // Expecting cost to match
    ASSERT_EQ(result.note, "Shot!");          // Expecting message to match
    score += 5;
}

// Test for Player functionality
TEST_F(PlayerTest, PlayerFunctionality) {
    ASSERT_EQ(player.id(), 1);                       // Check player ID
    ASSERT_EQ(player.name(), "TestPlayer");          // Check player name
    ASSERT_EQ(player.tokens(), 0);                    // Initially, player should have 0 tokens

    player.add_tokens(5);                             // Add 5 tokens
    ASSERT_EQ(player.tokens(), 5);                    // Check token count

    ASSERT_TRUE(player.spend_tokens(3));              // Spend 3 tokens; should succeed
    ASSERT_EQ(player.tokens(), 2);                    // Check token count after spending

    ASSERT_FALSE(player.spend_tokens(5));             // Spend 5 tokens; should fail (not enough tokens)
    ASSERT_EQ(player.tokens(), 2);                    // Token count should remain the same

    player.add_score(100);                            // Add score
    ASSERT_EQ(player.total_score(), 100);             // Check total score after adding
    score += 10;
}

class ArcadeTest : public ::testing::Test {
protected:
    Arcade arcade;

    void SetUp() override {
        TokenBooth tb("west");
        arcade.add_token_booth(std::move(tb));
        arcade.add_machine(std::make_unique<Puzzle>(1));
        arcade.add_machine(std::make_unique<Shooter>(2));
    }
};

// Test for registering a player
TEST_F(ArcadeTest, RegisterPlayer) {
    Player &player = arcade.register_player("Alice");
    ASSERT_EQ(player.id(), 1);
    ASSERT_EQ(player.name(), "Alice");

    Player &player2 = arcade.register_player("Bob");
    ASSERT_EQ(player2.id(), 2);
    ASSERT_EQ(player2.name(), "Bob");
    score += 10;
}

// Test for buying tokens
TEST_F(ArcadeTest, BuyTokens) {
    auto &alice = arcade.register_player("Alice");

    auto tb = TokenBooth("west");
    arcade.add_token_booth(tb);

    ASSERT_EQ(arcade.find_token_booth("east"), nullptr);
    auto tb_ptr = arcade.find_token_booth("west");

    ASSERT_EQ(tb_ptr->location(), "west");
    ASSERT_EQ(tb_ptr->tokens_sold(), 0);

    ASSERT_TRUE(arcade.buy_tokens(1, 500, *tb_ptr)); // Alice buys tokens with 500 cents
    ASSERT_EQ(alice.tokens(), 5); // Should have 5 tokens now
    ASSERT_EQ(tb_ptr->tokens_sold(), 5);

    ASSERT_FALSE(arcade.buy_tokens(999, 100, *tb_ptr)); // Invalid player ID
    ASSERT_EQ(tb_ptr->tokens_sold(), 5);  // no tokens sold to invalid player ID
    score += 10;
}

// Test for playing a machine
TEST_F(ArcadeTest, PlayMachine) {
    arcade.register_player("Alice");

    arcade.add_machine(std::make_unique<Puzzle>(1));
    arcade.add_machine(std::make_unique<Shooter>(2));

    // Buy tokens
    auto tb_ptr = arcade.find_token_booth("west");
    arcade.buy_tokens(1, 500, *tb_ptr);

    // Play the puzzle machine
    const auto puzzle_result = arcade.play_machine(1, 1);
    ASSERT_TRUE(puzzle_result.has_value()); // Should successfully play
    ASSERT_EQ(puzzle_result->score, 13);

    // Play the shooter machine
    const auto shooter_result = arcade.play_machine(1, 2);
    ASSERT_TRUE(shooter_result.has_value()); // Should successfully play
    ASSERT_EQ(shooter_result->score, 37);
    score += 10;
}

// Test for invalid machine ID
TEST_F(ArcadeTest, InvalidMachineID) {
    arcade.register_player("Alice");

    // Attempt to play non-existent machine
    const auto result = arcade.play_machine(1, 3); // Invalid machine ID
    ASSERT_FALSE(result.has_value()); // Should return nullopt
    const auto result2 = arcade.play_machine(1, -1); // Invalid machine ID
    ASSERT_FALSE(result2.has_value()); // Should return nullopt
    score += 5;
}

// Test saving and loading leaderboard
TEST_F(ArcadeTest, SaveLoadLeaderboard) {
    const std::string path = "leaderboard_test.csv";
    arcade.register_player("Alice");
    auto tb_ptr = arcade.find_token_booth("west");
    arcade.buy_tokens(1, 500, *tb_ptr); // Buy tokens
    arcade.play_machine(1, 1);  // Play

    ASSERT_TRUE(arcade.save_leaderboard(path)); // Should succeed
    Arcade new_arcade; // Create a new Arcade instance
    ASSERT_TRUE(new_arcade.load_leaderboard(path)); // Load the leaderboard
    ASSERT_EQ(new_arcade.leaderboard().size(), arcade.leaderboard().size()); // Check sizes match after load
    ASSERT_EQ(new_arcade.leaderboard().size(), 1); // Check sizes match after load
    const auto top_player = new_arcade.leaderboard().top()[0];
    ASSERT_EQ(top_player.player_id, 1);
    ASSERT_EQ(top_player.score, 13);
    // cleanup
    std::error_code ec;
    fs::remove(path, ec);
    score += 5;
}

class ScorePrinter : public ::testing::Environment {
public:
    void TearDown() override {
        std::cout << "\nYour unit test score is " << score << " out of " << TOTAL_POINTS << std::endl;
    }
};

::testing::Environment *const scorePrinterEnv =
        ::testing::AddGlobalTestEnvironment(new ScorePrinter);
