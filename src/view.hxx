#pragma once

#include "model.hxx"
#include <array>

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);
    using Dimensions = ge211::Dims<int>;
    View::Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;


private:
    Model const& model_;
    ge211::Rectangle_sprite const tile_sprite;
    ge211::Font font {"sans.ttf", 30};
    ge211::Font text_font {"sans.ttf", 80};
    std::array<std::array<ge211::Text_sprite, 4>, 4> value_sprites_;
    ge211::Text_sprite game_over_sprite;

};