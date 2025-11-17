#include "GameError.h"

GameError::GameError(const std::string& msg)
    : std::logic_error(msg)
{
}