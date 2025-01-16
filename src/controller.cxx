#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::left()) {
        model_.set_direction(ge211::Dims<int> {-1, 0});
        // moving left
    }
    if (key == ge211::Key::right()) {
        model_.set_direction(ge211::Dims<int> {1, 0});
        // moving right
    }
    if (key == ge211::Key::up()) {
        model_.set_direction(ge211::Dims<int>{0, -1});
        // moving up (negative y)
    }
    if (key == ge211::Key::down()) {
        model_.set_direction(ge211::Dims<int>{0, 1});
        // moving down (positive y)
    }
    model_.move_tiles();

}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();

}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}