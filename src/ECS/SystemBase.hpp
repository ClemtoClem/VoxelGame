#ifndef SYSTEM_BASE_HPP
#define SYSTEM_BASE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <SDL2/SDL.h>

class Manager;

// Base class for Systems
class SystemBase {
protected:
    int priority;
    std::shared_ptr<Manager> manager;

public:
    SystemBase(std::shared_ptr<Manager> manager, int p) : priority(p), manager(manager) {}
    virtual ~SystemBase() = default;

    int getPriority() const { return priority; }

    virtual void preUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) = 0;
    virtual void update(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) = 0;
    virtual void postUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) = 0;
};

#endif // SYSTEM_BASE_HPP
