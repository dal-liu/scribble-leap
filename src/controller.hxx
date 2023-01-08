#pragma once

#include "model.hxx"
#include "view.hxx"
#include <ge211.hxx>

/* Things to do:
 * draw: should just be calling view_
 * initial_window_dimensions: should just call view_
 * initial_window_title: should just call view_ title
 * onMouseUp: should shoot a bullet, draw it using view
 * onMouseMove: should aim to where mouse is aiming
 * onFrame: just call model onFrame
 * onKey: movement handled by a and d will call model function that flips velocity
 */

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller(Model&);
    void on_frame(double dt) override;
    void on_key_down(ge211::Key) override;
    void on_key_up(ge211::Key) override;

protected:
    void draw(ge211::Sprite_set& set) override;
    Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
};
