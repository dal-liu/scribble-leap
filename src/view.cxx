#include "view.hxx"
#include "model.hxx"

using Sprite_set = ge211::Sprite_set;

static ge211::Color const platform_color {0, 102, 0};
static ge211::Color const player_color {182, 212, 51};
static ge211::Color const monster_color {200, 0, 23};
static ge211::Color const bullet_color {0, 0, 255};

View::View(Model const& model)
        : model_(model),
          platform_sprite_(model_.cfg.platform_dims, platform_color),
          player_sprite_({model_.cfg.platform_dims.width / 2,
                          model_.cfg.platform_dims.width / 2}, player_color),
          monster_sprite_({model_.cfg.platform_dims.width / 2,
                           model_.cfg.platform_dims.width / 2}, monster_color),
          bullet_sprite_(model_.cfg.bullet_size, bullet_color),
          score_sprite_(),
          game_over_sprite_()
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    draw_score_(set);

    for (Platform platform: model_.platforms) {
        set.add_sprite(platform_sprite_, {platform.x, platform.y}, 0);
    }

    set.add_sprite(player_sprite_, model_.player.top_left().into<int>(), 2);
    if (model_.monster.is_alive()) {
        set.add_sprite(monster_sprite_,
                       model_.monster.top_left().into<int>(),
                       1);
    }
    if (!model_.player.is_alive()) {
        draw_game_over_(set);
    }
}

Dimensions
View::initial_window_dimensions() const
{
    return {model_.cfg.scene_dims.width, model_.cfg.scene_dims.height};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Scribble Leap";
}

void
View::draw_score_(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder score_builder(sans_);
    score_builder.color(ge211::Color(0, 0, 0)) << model_.score;
    score_sprite_.reconfigure(score_builder);
    int score_padding = model_.cfg.scene_dims.width -
                        score_sprite_.dimensions().width - 10;
    set.add_sprite(score_sprite_, {score_padding, 0});
}

void
View::draw_game_over_(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder game_over_builder(sans_big_);
    game_over_builder.color(ge211::Color(0, 0, 0)) << "GAME OVER";
    game_over_sprite_.reconfigure(game_over_builder);
    set.add_sprite(game_over_sprite_,
                   {model_.cfg.scene_dims.width / 2 - game_over_sprite_
                                                              .dimensions()
                                                              .width / 2,
                    model_.cfg.scene_dims.height / 2 -
                    game_over_sprite_.dimensions().height / 2},
                   3);
}
