#include "monster.hxx"

Monster::Monster(Game_config const& cfg)
        : cfg(cfg),
          half_side_(cfg.half_side),
          center_(cfg.scene_dims.width / 2, half_side_),
          velocity_(cfg.monster_velocity),
          alive_(false)
{ }

void
Monster::reset()
{
    center_.x = cfg.scene_dims.width / 2;
    center_.y = half_side_;
}

Position
Monster::top_left() const
{
    return {center_.x - half_side_, center_.y - half_side_};
}

Monster
Monster::next(double dt)
{
    Monster result(*this);

    result.center_.x += velocity_.width * dt;
    result.center_.y += velocity_.height * dt;
    return result;
}

Velocity
Monster::get_velocity()
{
    return velocity_;
}

void
Monster::set_velocity(Velocity velocity)
{
    velocity_ = velocity;
}

bool
Monster::is_alive() const
{
    return alive_;
}

void
Monster::rev_alive()
{
    alive_ = !alive_;
    center_.y = -18;
}

bool
Monster::hits_player(Player const& player)
{
    if (!alive_) {
        return false;
    }
    // Checks collision on x-axis
    if (center_.x + half_side_ < player.top_left().x ||
        center_.x - half_side_ > player.top_left().x + (2 * half_side_)) {
        return false;
    }
    // Checks collision on y-axis
    if (center_.y + half_side_ < player.top_left().y ||
        center_.y - half_side_ > player.top_left().y + (2 * half_side_)) {
        return false;
    }
    // if all conditions are met, then return true
    return true;
}


bool
Monster::hits_bottom()
{
    return center_.y > cfg.scene_dims.height;
}

bool
Monster::hits_left()
{
    return center_.x < 0;
}

bool
Monster::hits_right()
{
    return center_.x > cfg.scene_dims.width;
}

void
Monster::add_monster_y(int y)
{
    center_.y += y;
}