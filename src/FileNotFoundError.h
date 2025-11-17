#pragma once
#include "GameError.h"
#include <string>

class FileNotFoundError : public GameError {
public:
    FileNotFoundError(const std::string& filename);
};
