#include "model.hxx"

using Platform = ge211::Rect<int>;


Model::Model(Game_config const& cfg)
        : cfg(cfg),
          player(cfg),
          monster(cfg),
          score(0),
          scene_velocity_(0),
          scene_shifting_(false)
{
    // Places 10 paddles/platforms randomly
    for (int i = 0; i < 720; i += 72) {
        platforms.push_back(Platform(rand() % (cfg.scene_dims.width - cfg
                                             .platform_dims.width),
                                     i,
                                     cfg.platform_dims.width,
                                     cfg.platform_dims.height));
    }
}

void
Model::on_frame(double dt)
{
    if (player.is_alive()) {
        if (player.hits_left()) {
            player.wrap_left();
        } else if (player.hits_right()) {
            player.wrap_right();
        }

        if (player.hits_bottom()) {
            player.kill();
        }

        generate_platforms();

        spawn_monster();

        // Kill player if hits monster
        if (monster.hits_player(player)) {
            player.kill();
        }
        // Reverse monster velocity if hits sides
        if (monster.hits_left() || monster.hits_right()) {
            monster.set_velocity(-monster.get_velocity());
        }

        // Update monster if alive
        if (monster.is_alive()) {
            monster = monster.next(dt);
        }

        shift_scene(dt);
        player = player.next(dt);
        destroy_all();
    }
}

void
Model::shift_scene(double dt)
{
    // conditions to check:
    // 1. when player hits the midpoint when it's still moving
    // 2. when the scene hasn't stopped moving
    // 3. when both the scene and player aren't moving
    if (player.in_middle()) {
        score++;
        if (player.get_velocity().height != 0) {
            // if player is still moving, the scene starts shifting
            scene_velocity_ = -player.get_velocity().height;
            player.set_velocity_zero();
            scene_shifting_ = true;
        }
        // if scene isn't moving either, then the scene is no longer shifting
        if (scene_velocity_ == 0) {
            scene_shifting_ = false;
        }
        // if player isn't moving and scene is still moving, then continue
        // shifting
    }

    if (scene_shifting_) {
        // loop through all platforms and change their y positions by a constant
        for (size_t i = 0; i < platforms.size(); i++) {
            platforms[i].y += scene_velocity_ * dt;
        }
        if (monster.is_alive()) {
            monster.add_monster_y(scene_velocity_ * dt);
        }
        // scene deceleration
        scene_velocity_ = scene_velocity_ < 20 ? 0 : scene_velocity_ - 20;
    } else {
        // normal jumping behavior
        player.decrease_velocity();
        for (size_t i = 0; i < platforms.size(); i++) {
            if (player.hits_platform(platforms[i])) {
                player.jump();
            }
        }
    }
}

void
Model::generate_platforms()
{
    if (score % 20 == 0) {
        platforms.push_back(Platform(
                rand() % (cfg.scene_dims.width - cfg.platform_dims.width), -18,
                cfg.platform_dims.width,
                cfg.platform_dims.height));
    }
}

void
Model::spawn_monster()
{
    if (score % 200 == 0 && rand() % 3 == 0 && !monster.is_alive()) {
        monster.rev_alive();
        monster.reset();
    }
}

void
Model::destroy_all()
{
    for (std::vector<Platform>::iterator it = platforms.begin();
         it != platforms.end();) {
        if (it->y > cfg.scene_dims.height) {
            it = platforms.erase(it);
        } else {
            ++it;
        }
    }

    if (monster.hits_bottom()) {
        monster.rev_alive();
    }
}