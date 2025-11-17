#pragma once
#include "GameError.h"
#include <string>

class SDLError : public GameError {
public:
    SDLError(const std::string& msg);
};

