#ifndef GUI_HPP
#define GUI_HPP

#include "Widget.hpp"
#include <vector>
#include <memory>

class GUI {
public:
    GUI();
    ~GUI();

    void reset();
    void addWidget(std::shared_ptr<Widget> widget);
    void handleEvent(SDL_Event& evt);
    void update(float dt);
    void render() const;

private:
    void disableProjection() const;
    void enableProjection() const;

    std::vector<std::shared_ptr<Widget>> _widgets;

    int _screenWidth;
    int _screenHeight;
};

#endif // GUI_HPP
