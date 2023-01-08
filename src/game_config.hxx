#pragma once

#include <ge211.hxx>

class Game_config
{
public:
    Game_config();

    ge211::Dims<int> scene_dims;
    ge211::Dims<int> platform_dims;
    int half_side;
    int max_velocity;
    ge211::Dims<int> monster_velocity;
    int bullet_size;
    ge211::Dims<int> bullet_velocity;
};
