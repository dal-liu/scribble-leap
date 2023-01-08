#include "player.hxx"

Player::Player(Game_config const& cfg)
        : half_side_(cfg.half_side),
          center_(cfg.scene_dims.width / 2, cfg.scene_dims.height - half_side_),
          velocity_(0, -cfg.max_velocity),
          alive_(true),
          max_velocity_height_(cfg.max_velocity)
{ }

Position
Player::top_left() const
{
    return {center_.x - half_side_, center_.y - half_side_};
}

Player
Player::next(double dt)
{
    Player result(*this);
    result.center_.x += velocity_.width * dt;
    // make sure the center doesn't pass the screen midpoint
    result.center_.y = result.center_.y + velocity_.height * dt < 360 ? 360 :
                       result.center_.y + velocity_.height * dt;
    return result;
}

Velocity
Player::get_velocity()
{
    return velocity_;
}

void
Player::set_velocity_zero()
{
    velocity_.height = 0;
}

bool
Player::is_alive() const
{
    return alive_;
}

bool
Player::in_middle()
{
    return center_.y <= 360;
}

bool
Player::hits_platform(Platform const& platform)
{
    // character must not be travelling up before jumping
    if (velocity_.height < 0 || !alive_) {
        return false;
    }
    // character must be within bounds of the platform width
    if (center_.x + half_side_ < platform.x ||
        center_.x - half_side_ > platform.x + platform.width) {
        return false;
    }
    // character must be within bounds of the platform height
    if (center_.y + half_side_ < platform.y ||
        center_.y + half_side_ / 2 > platform.y + platform.height) {
        return false;
    }
    // if all conditions are met, then return true
    return true;
}

void
Player::decrease_velocity()
{
    if (velocity_.height < max_velocity_height_) {
        velocity_.height += 20;
    }
}

void
Player::jump()
{
    velocity_.height = -max_velocity_height_;
}

void
Player::move_left()
{
    velocity_.width = -400;
}

void
Player::move_right()
{
    velocity_.width = 400;
}

void
Player::stop_moving()
{
    velocity_.width = 0;
}

void
Player::wrap_left()
{
    center_.x = 405;
}

void
Player::wrap_right()
{
    center_.x = 0;
}

bool
Player::hits_bottom()
{
    return center_.y > 720;
}

bool
Player::hits_left()
{
    return center_.x < 0;
}

bool
Player::hits_right()
{
    return center_.x > 405;
}

void
Player::kill()
{
    alive_ = false;
}

Position
Player::get_center()
{
    return center_;
}

void
Player::set_center(Position position)
{
    center_ = position;
}

void
Player::set_velocity(Velocity velocity)
{
    velocity_ = velocity;
}