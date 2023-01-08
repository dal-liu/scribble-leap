#pragma once

#include <ge211.hxx>
#include <game_config.hxx>

using Position = ge211::Posn<float>;
using Velocity = ge211::Dims<int>;
using Platform = ge211::Rect<int>;

class Player
{
public:
    // player constructor
    Player(Game_config const&);
    // gets the coordinates of the top left corner of player
    Position top_left() const;
    // creates a new player after being moved
    Player next(double dt);
    // getter function for velocity
    Velocity get_velocity();
    // sets y component of velocity to 0
    void set_velocity_zero();
    // returns whether player is alive
    bool is_alive() const;
    // returns if the player's center passes the middle of the screen
    bool in_middle();
    // returns whether player hits a platform
    bool hits_platform(Platform const&);
    // adds acceleration due to gravity
    void decrease_velocity();
    // jump
    void jump();
    // move left
    void move_left();
    // move right
    void move_right();
    // stop moving
    void stop_moving();
    // returns if player's center goes past the bottom
    bool hits_bottom();
    // returns if the player's center goes past the left side
    bool hits_left();
    // returns if the player's center goes past the right side
    bool hits_right();
    // wrap from left to right
    void wrap_left();
    // wrap from right to left
    void wrap_right();
    // Kill player
    void kill();
    // FOR TESTING
    Position get_center();
    void set_center(Position);
    void set_velocity(Velocity);

private:
    // private fields
    int half_side_;
    Position center_;
    Velocity velocity_;
    bool alive_;
    int max_velocity_height_;
};

