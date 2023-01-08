#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims(405, 720),
          platform_dims(75, 18),
          half_side(18),
          max_velocity(750),
          monster_velocity({150, 0}),
          bullet_size(5),
    bullet_velocity({0, -1000})
{ }