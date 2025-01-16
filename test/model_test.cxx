#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//

TEST_CASE("Move left")
{
    Model model;
    model.set_direction({-1, 0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    model.map_[{2, 0}] = 10;
    model.move_tiles();
    CHECK(model.map_[{0, 0}] == 10);
}

TEST_CASE("Move right")
{
    Model model;
    model.set_direction({1, 0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    model.map_[{0, 0}] = 10;
    model.move_tiles();
    CHECK(model.map_[{3, 0}] == 10);
}

TEST_CASE("Move up")
{
    Model model;
    model.set_direction({0, -1});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    model.map_[{1, 3}] = 8;
    model.move_tiles();
    CHECK(model.map_[{1, 0}] == 8);
}

TEST_CASE("Move down")
{
    Model model;
    model.set_direction({0, 1});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    model.map_[{2, 0}] = 16;
    model.map_[{2, 2}] = 8;
    model.move_tiles();
    CHECK(model.map_[{2, 3}] == 8);
    CHECK(model.map_[{2, 2}] == 16);

}

TEST_CASE("Addition")
{
    Model model;
    model.set_direction({-1, 0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    model.map_[{1, 0}] = 2;
    model.map_[{2, 0}] = 2;
    model.move_tiles();
    CHECK(model.map_[{0, 0}] == 4);
}

TEST_CASE("Game Over")
{
    Model model;
    model.set_direction({-1, 0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model.map_[{i, j}] = 0;
        }
    }
    CHECK(!model.game_over_);
    bool emptyboard = model.is_board_full();
    CHECK(!emptyboard);

    // row 1
    model.map_[{0, 0}] = 1;
    model.map_[{1, 0}] = 3;
    model.map_[{2, 0}] = 5;
    model.map_[{3, 0}] = 7;
    // row 2
    model.map_[{0, 1}] = 9;
    model.map_[{1, 1}] = 11;
    model.map_[{2, 1}] = 13;
    model.map_[{3, 1}] = 15;
    // row 3
    model.map_[{0, 2}] = 17;
    model.map_[{1, 2}] = 19;
    model.map_[{2, 2}] = 21;
    model.map_[{3, 2}] = 23;
    // row 4
    model.map_[{0, 3}] = 25;
    model.map_[{1, 3}] = 27;
    model.map_[{2, 3}] = 29;
    model.map_[{3, 3}] = 31;
    bool is_full = model.is_board_full();
    CHECK(is_full);

    model.set_direction({-1, 0});
    model.move_tiles();
    model.set_direction({1, 0});
    model.move_tiles();
    model.set_direction({0, 1});
    model.move_tiles();
    model.set_direction({0, -1});
    model.move_tiles();

    CHECK(model.game_over_);
}
