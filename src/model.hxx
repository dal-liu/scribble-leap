#pragma once

#include <ge211.hxx>
#include <player.hxx>
#include <game_config.hxx>
#include <monster.hxx>
#include <vector>

class Model
{
public:
    // PUBLIC FIELDS
    Game_config cfg;
    std::vector<Platform> platforms;
    Player player;
    Monster monster;
    double timeA;
    int score;
    // PUBLIC FUNCTIONS
    // model constructor
    explicit Model(Game_config const& cfg = Game_config());

    // advance frame
    void on_frame(double);
    // scene shift algorithm
    void shift_scene(double);
    // generate new platforms
    void generate_platforms();
    // spawn monster
    void spawn_monster();
    // destroy old platforms
    void destroy_all();

private:
    int scene_velocity_;
    bool scene_shifting_;
};


/* Bullets: need a shoot function, so when MOUSE is clicked then bullet will be
    shot in direction of CURSOR mouse part will be in controller. Need a function
    in model to check if bullet shot will hit monster?) */

/* Jumping: Is constant so have a onFrame function? Which will just check  */


