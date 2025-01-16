#include "view.hxx"
#include <iostream>

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
using Position = ge211::Posn<int>;

static Color const tilecolor {255, 147, 190}; // pink
static Color const white {255, 255, 255}; // white
static Color const black {0, 0, 0}; // black
static Color const red {199, 0, 57}; // red


View::View(Model const& model)
        : model_(model),
          tile_sprite({100, 100}, tilecolor),
          game_over_sprite("Game Over", text_font)

{ }

View::Dimensions
View::initial_window_dimensions() const
{
    Dimensions dims = {430, 430};
    return dims;
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "2048";
}

void
View::draw(Sprite_set& set)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = i * 110;
            int y = j * 110;

            set.add_sprite(tile_sprite, {x, y}, 2);

            if (model_.map_.at({i, j}) != 0) {
                // std::cout << tile.second << " ";
                Position text_pos = {x + 30, y + 10};
                ge211::Text_sprite::Builder word_builder(font);
                word_builder << model_.map_.at({i, j});

                value_sprites_[i][j].reconfigure(word_builder);
                set.add_sprite(value_sprites_[i][j], text_pos, 4);
            }
        }
    }

    if (model_.game_over_) {
        Position game_over_pos = {10, 125};
        set.add_sprite(game_over_sprite, game_over_pos, 5);
    }



    // for (const auto& tile : model_.map_) {
    //     Position pos = tile.first; // position
    //     // std::string value = std::to_string(tile.second);
    //     int x = pos.x * 110;
    //     int y = pos.y * 110;
    //
    //     set.add_sprite(tile_sprite, {x, y}, 2);
    //
    //     if (tile.second != 0) {
    //         std::cout << tile.second << " ";
    //         Position text_pos = {x + 25, y - 25};
    //         ge211::Text_sprite::Builder word_builder(font);
    //         word_builder << tile.second;
    //         value_sprite_.reconfigure(word_builder);
    //         set.add_sprite(value_sprite_, text_pos, 4);
    //     }
    // }
    // std::cout << std::endl;
}
