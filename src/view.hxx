#pragma once

#include "model.hxx"
#include <string>

// Set background color to white (if time change to like yellowish white) can be done by
//  " assign the protected member variable Abstract_game::background_color from the draw(Sprite_set&)
//      or on_start() functions"
//  MAIN FUNCTIO: TO DO: draw
//  draw: paddles: asks model for random position of paddles and puts paddle there
//  charcter: check sprite state? and display according to velocity direction and mousePressed?
//  monssters: display at position given by model (dont display once killed)
//  bullets: display at position given by model (dont display either 1. once of screen 2. hit monster)
using Dimensions = ge211::Dims<int>;

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;
    ge211::Rectangle_sprite const platform_sprite_;
    ge211::Rectangle_sprite const player_sprite_;
    ge211::Rectangle_sprite const monster_sprite_;
    ge211::Circle_sprite const bullet_sprite_;
    ge211::Font sans_ {"sans.ttf", 20};
    ge211::Font sans_big_ {"sans.ttf", 60};
    ge211::Text_sprite score_sprite_;
    ge211::Text_sprite game_over_sprite_;

    void draw_score_(ge211::Sprite_set& set);
    void draw_game_over_(ge211::Sprite_set& set);
};


