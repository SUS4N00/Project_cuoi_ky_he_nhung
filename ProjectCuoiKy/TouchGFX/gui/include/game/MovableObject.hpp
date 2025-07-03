#pragma once
#include <game/Entity.hpp>
#include <touchgfx/Drawable.hpp>

struct MovableObject {
    game::Entity* entity;
    touchgfx::Drawable* container;
    int x, y;
};
