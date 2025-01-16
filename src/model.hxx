#pragma once

#include <ge211.hxx>
#include <unordered_map>

class Model
{
public:
    Model(); // constructor

    void set_direction(ge211::Dims<int>); // update field direction of swipe
    void move_tiles(); // move tiles

    void merge_tiles(ge211::Posn<int> pos1, ge211::Posn<int> pos2);
    void initialgame();
    void delete_tile(ge211::Posn<int> pos);
    void generate_newtile();
    bool is_board_full();

    void check_2048();

    bool game_over_;
    bool game_updated_clickright;
    bool game_updated_clickleft;
    bool game_updated_clickup;
    bool game_updated_clickdown;


    ge211::Dims<int> dir_;
    std::unordered_map<ge211::Posn<int>, int> map_;
};