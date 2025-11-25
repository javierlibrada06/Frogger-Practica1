#pragma once
#include <stdexcept>
#include <string>

class GameError : public std::logic_error {
public:
    GameError(const std::string& msg);
    virtual ~GameError() = default;
};
