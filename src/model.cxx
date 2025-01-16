#include "model.hxx"
#include <stdlib.h>
#include <iostream>

Model::Model()
    :
        game_over_(false),
        game_updated_clickright(false),
        game_updated_clickleft(false),
        game_updated_clickup(false),
        game_updated_clickdown(false),
        dir_(0, 0)

{
    initialgame();
}



void
Model::set_direction(ge211::Dims<int> new_dir)
{
    dir_ = new_dir;
}

void
Model::move_tiles()
{

    // right
    if (dir_ == ge211::Dims<int> {1, 0}) {
        game_updated_clickright = false;
        for (int j = 0; j <= 3; j++) {
            for (int i = 2; i >= 0; i--) {

                if (map_[{i, j}] != 0) { // not empty
                    int n = i;
                    while (n < 3) {
                        if (map_[{n + 1, j}] == 0) {
                            map_[{n + 1, j}] = map_[{n, j}];
                            map_[{n, j}] = 0;
                            game_updated_clickright = true;
                            n++;
                        }
                        else if (map_[{n + 1, j}] == map_[{n, j}]) {
                            ge211::Posn<int> pos1 = {n + 1, j};
                            ge211::Posn<int> pos2 = {n, j};
                            if (map_[pos1] == map_[pos2]) {
                                std::cout << pos1 << "," << pos2 << std::endl;
                                map_[pos1] = map_[pos1] * 2;
                                delete_tile({pos2});
                                game_updated_clickright = true;
                                n++;
                            }
                            break;
                        }
                        else {
                            break;
                        }

                    }
                }
            }
        }
    }
    // left
    if (dir_ == ge211::Dims<int> {-1, 0}) {
        game_updated_clickleft = false;
        for (int j = 0; j <= 3; j++) {
            for (int i = 1; i <= 3; i++) {
                if (map_[{i, j}] != 0) { // not empty
                    int n = i;
                    while (n > 0) {
                        if (map_[{n - 1, j}] == 0) {
                            map_[{n - 1, j}] = map_[{n, j}];
                            map_[{n, j}] = 0;
                            game_updated_clickleft = true;
                            n--;
                        }
                        else if (map_[{n - 1, j}] == map_[{n, j}]) {
                            ge211::Posn<int> pos1 = {n - 1, j};
                            ge211::Posn<int> pos2 = {n, j};
                            if (map_[pos1] == map_[pos2]) {
                                map_[pos1] = map_[pos1] * 2;
                                delete_tile(pos2);
                                game_updated_clickleft = true;
                                n--;
                            }
                            break;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
    }
    // up
    if (dir_ == ge211::Dims<int> {0, -1}) {
        game_updated_clickup = false;
        for (int i = 0; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (map_[{i, j}] != 0) { // not empty
                    int n = j;
                    while (n > 0) {
                        if (map_[{i, n - 1}] == 0) {
                            map_[{i, n - 1}] = map_[{i, n}];
                            map_[{i, n}] = 0;
                            game_updated_clickup = true;
                            n--;
                        } else if (map_[{i, n}] == map_[{i, n - 1}]) {
                            ge211::Posn<int> pos1 = {i, n - 1};
                            ge211::Posn<int> pos2 = {i, n};
                            if (map_[pos1] == map_[pos2]) {
                                map_[pos1] = map_[pos1] * 2;
                                delete_tile(pos2);
                                game_updated_clickup = true;
                                n--;
                            }
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    if (dir_ == ge211::Dims<int> {0, 1}) {
        game_updated_clickdown = false;
        for (int i = 0; i <= 3; i++) {
            for (int j = 2; j >= 0; j--) {
                if (map_[{i, j}] != 0) { // not empty
                    int n = j;
                    while (n < 3) {
                        if (map_[{i, n + 1}] == 0) {
                            map_[{i, n + 1}] = map_[{i, n}];
                            map_[{i, n}] = 0;
                            game_updated_clickdown = true;
                            n++;
                        } else if (map_[{i, n}] == map_[{i, n + 1}]) {
                            ge211::Posn<int> pos1 = {i, n + 1};
                            ge211::Posn<int> pos2 = {i, n};
                            if (map_[pos1] == map_[pos2]) {
                                map_[pos1] = map_[pos1] * 2;
                                delete_tile(pos2);
                                game_updated_clickdown = true;
                                n++;
                            }
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }


        // if direction is right, start with rightmost side, if there is a tile
        // on its right then tiles cant shift to right
        // check column to the left iterating through each row (top to bottom),
        // iterate
        // through each column to the left
        // check for each that is there an empty space to the right, if not,
        // can't move to the right
        // to the right
        // check through each column
        // if something is already there, can't move, but if its the same value,
        // update rightmost tile to added value and then delete previous spot

        // boolean game_update
        // boolean defined for were tiles moved, if true, game continues
        // or if merge occurred game continues boolean = true, or if 2048 is found
        // if at any point boolean of move_tiles = false (if any tiles moved, set
        // = true)
        // at the end of the move_tiles, if its false, no update --> then game is
        // over

        check_2048();
        game_over_ = !game_updated_clickright && !game_updated_clickleft &&
                      !game_updated_clickup && !game_updated_clickdown;

        generate_newtile();

        }


bool
Model::is_board_full()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map_[{i, j}] == 0) {
                return false;
            }
        }
    }
    return true;
}

void
Model::generate_newtile()
{
    // generate random positions for initial 2 tiles between 0 and 3
    if (!is_board_full()) {
        for (;;) {
            int x = rand() % 4;
            int y = rand() % 4;
            if (map_[{x, y}] == 0) {
                int prob1 = 1 + (rand() % 10); // gen random # 1-10
                if (prob1 <= 9) {
                    map_[{x, y}] = 2; // assign 2 or 4
                } else {
                    map_[{x, y}] = 4;
                }
                game_over_ = false;
                break;
            }
        }
    }
}

    // check if map_[{x, y}] is empty
    // if its empty, value = 0
    // if not empty, value is != 0
    // if not empty, generate random positions again and check again
    // do this until you find a position that is empty
    // then use the code logic below to assign either a 2 or 4 value to that
    // position

void
Model::check_2048()
{
    if (!game_over_) {
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 3; j++) {
                if (map_[{i, j}] == 2048) {
                    game_over_ = true;
                }
            }
        }
    }
}


void
Model::merge_tiles(ge211::Posn<int> pos1, ge211::Posn<int> pos2)
{
    // merge tile would add the tiles
    // if moving right, start with most right tile
    // check positions, farther tile
    // update farther tile to be the sum
    // delete other tile (set = 0?)
    if (map_[pos1] == map_[pos2]) {
        std::cout << pos1 << "," << pos2 << std::endl;
        map_[pos1] = map_[pos1] * 2;
        delete_tile({pos2});
    }
}

void
Model::delete_tile(ge211::Posn<int> pos)
{
    map_[{pos}] = 0; // = 0 --> empty
}

void
Model::initialgame()
{
    // go through each row each column, set each value to 0 (empty)
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            map_[{i, j}] = 0;
        }
    }
// generate random positions for initial 2 tiles between 0 and 3
    int x1 = rand() % 4;
    int y1 = rand() % 4;
    int x2 = rand() % 4;
    int y2 = rand() % 4;
    // generate random values for initial 2 tiles between 1 and 10
    int prob1 = 1 + (rand() % 10);
    // tile 1
    if (prob1 == 10) {
        map_[{x1, y1}] = 4;
    }
    else {
        map_[{x1, y1}] = 2;
    }

    int prob2 = 1 + (rand() % 10);
    if (prob2 == 10) {
        map_[{x2, y2}] = 4;
    }
    else {
        map_[{x2, y2}] = 2;
    }
    // generate 4 random integers between 0, 3
    // map_[{int 1, int2}]
    // map_[{int 3, int4}]
}