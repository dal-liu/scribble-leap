#include "controller.hxx"

Controller::Controller(Model& model)
        : model_(model),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    ge211::Abstract_game::background_color = {253,246,227};
    view_.draw(set);
}

Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::code('a') || key == ge211::Key::left()) {
        model_.player.move_left();
    }
    if (key == ge211::Key::code('d') || key == ge211::Key::right()) {
        model_.player.move_right();
    }
}

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code('a') || key == ge211::Key::left() ||
        key == ge211::Key::code('d') || key == ge211::Key::right()) {
        model_.player.stop_moving();
    }
}

