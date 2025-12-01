#pragma once
#include <SDL3/SDL.h>
class EventHandler
{
public:
    virtual ~EventHandler() = default;
    // Devuelve true si el oyente ha "consumido" el evento (no debe seguir propagándose).
    virtual void handleEvent(const SDL_Event& event) = 0;
};

