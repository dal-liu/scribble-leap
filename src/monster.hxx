#pragma once

#include <ge211.hxx>
#include <game_config.hxx>
#include "player.hxx"

using Position = ge211::Posn<float>;
using Velocity = ge211::Dims<int>;
using Platform = ge211::Rect<int>;

class Monster
{
public:
    Game_config cfg;
    // returns if the monster's center goes past bottom
    bool hits_bottom();
    // returns if the player's center goes past the left side
    bool hits_left();
    // returns if the player's center goes past the right side
    bool hits_right();
    // player constructor
    Monster(Game_config const&);
    // gets the coordinates of the top left corner of monster
    Position top_left() const;
    // creates a new player after being moved
    Monster next(double dt);
    // returns whether monster is alive
    bool is_alive() const;
    // reverse monster life
    void rev_alive();
    // Sets velocity of monster
    void set_velocity(Velocity velocity);
    // Gets velocity of monster
    Velocity get_velocity();
    // Checks if monster is hit by player
    bool hits_player(Player const& player);
    // sets the monster's y value
    void add_monster_y(int);
    // Monster position rest
    void reset();

private:
    // private fields
    int half_side_;
    Position center_;
    Velocity velocity_;
    bool alive_;
};

