#include "SDLError.h"
#include "SDL3/SDL.h"

SDLError::SDLError(const std::string& msg)
    : GameError(msg + " " + SDL_GetError())
{
}
