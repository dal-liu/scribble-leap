#include "model.hxx"
#include <catch.hxx>

Game_config const config;

// These tests should demonstrate your functional requirements.
//

/* Tests to see if player is correctly falling
with acceleration due to "gravity" being taken
into consideration */
TEST_CASE("player moving")
{
    Model m(config);
    m.platforms.clear();
    ge211::Posn<float> expected_position{202, 702};
    CHECK(m.player.get_center() == expected_position);

    m.on_frame(0);
    expected_position = {202, 702};
    CHECK(m.player.get_center() == expected_position);

    m.on_frame(0.5);
    expected_position = {202, 360};
    CHECK(m.player.get_center() == expected_position);

    m.on_frame(10);
    expected_position = {202, 360};
    CHECK(m.player.get_center() == expected_position);
}

/* Tests to see if player jump is working as it should
i.e. if player jump on platform is correctly changing
veloctiy */
TEST_CASE("player jumping")
{
    Model m(config);
    m.platforms.clear();
    m.platforms.push_back(ge211::Rect<int>(100, 500, 100, 20));
    m.player.set_center({150, 450});
    m.player.set_velocity({0, 25});

    m.on_frame(1);
    ge211::Dims<int> expected_velocity{0, 45};
    CHECK(m.player.get_velocity() == expected_velocity);

    m.on_frame(1);
    expected_velocity = {0, -750};
    CHECK(m.player.get_velocity() == expected_velocity);
}

/* Tests to see player wrapping when hitting sides
Player should have position center wrapped to other end
i.e. if hits left (pos = {< 0, y}) then pos should become
(pos = {405, y + motion}) */
TEST_CASE("player hits scene")
{
    Model m(config);
    m.platforms.clear();

    // Hits left side
    m.player.set_center({-1,100});
    m.on_frame(1);
    ge211::Posn<float> center = {405, 360};
    CHECK(m.player.get_center() == center);

    // Hits right sie
    m.player.set_center({406,100});
    m.on_frame(1);
    center = {0, 360};
    CHECK(m.player.get_center() == center);

    // Hits bottom and dies
    m.player.set_center({200, 721});
    m.on_frame(1);
    CHECK(!m.player.is_alive());

}

/* Checks to see collision detection between player
and monster. Monster hitting player should kill player
monster when not overlapping with player should
not kill player */
TEST_CASE("player collides with monster")
{
    Model m(config);
    m.platforms.clear();

    if(!m.monster.is_alive()) {
        m.monster.rev_alive();
    }

    m.monster.add_monster_y(100);

    m.player.set_center({202 , 70});
    m.on_frame(1);
    CHECK(!m.player.is_alive());

    // Missing monster y

    Model m2(config);
    m2.platforms.clear();

    if(!m2.monster.is_alive()) {
        m2.monster.rev_alive();
    }

    m2.player.set_center({202 , 150});
    m2.on_frame(1);
    CHECK(m2.player.is_alive());

    // Missing monster x

    Model m3(config);
    m3.platforms.clear();

    if(!m3.monster.is_alive()) {
        m3.monster.rev_alive();
    }

    m3.player.set_center({400 , 70});
    m3.on_frame(1);
    CHECK(m3.player.is_alive());

}

/* Checks to see how monster interacts with scene. When monster hits bottom
 it should die, when it hits sides, the velocity should reverse. */
TEST_CASE("monster collisions")
{
    // Monster hits bottom
    Model m(config);
    m.platforms.clear();

    if(!m.monster.is_alive()) {
        m.monster.rev_alive();
    }

    m.monster.add_monster_y(800);

    m.on_frame(1);
    CHECK(!m.monster.is_alive());

    // Monster hits left

    Model m2(config);
    m2.platforms.clear();
    m2.player.set_velocity({0, 0});
    m2.player.set_center({0, 0});

    if(!m2.monster.is_alive()) {
        m2.monster.rev_alive();
    }

    // Hits right with current monster speed impl = 150
    m2.on_frame(2);
    // Need to update once more to actually detect that right side was hit
    m2.on_frame(0.1);
    CHECK(m2.monster.get_velocity().width == -150);
    CHECK(m2.monster.get_velocity().height == 0);

    // Monster hits right


    Model m3(config);
    m3.platforms.clear();
    m3.player.set_velocity({0, 0});
    m3.player.set_center({0, 0});
    m3.monster.set_velocity({-150, 0});

    if(!m3.monster.is_alive()) {
        m3.monster.rev_alive();
    }

    // Hits left with current monster speed impl = -150
    m3.on_frame(2);
    // Left side hit want velocity to swap
    m3.on_frame(0.1);
    CHECK(m3.monster.get_velocity().width == 150);
    CHECK(m3.monster.get_velocity().height == 0);
}