#ifndef FRAME_HPP
#define FRAME_HPP

#include "Widget.hpp"
#include <vector>
#include <memory>

class Frame : public Widget {
public:
    Frame();
    ~Frame();

    void addWidget(std::shared_ptr<Widget> widget);
    virtual void handleEvent(SDL_Event& evt) override;
    virtual void update(float dt) override;
    virtual void render() const override;

private:
    std::vector<std::shared_ptr<Widget>> _widgets;
};

#endif // FRAME_HPP
