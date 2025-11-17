#pragma once
#include "GameError.h"
#include <string>

class FileFormatError : public GameError {
public:
    FileFormatError(const std::string& filename, int line, const std::string& msg);
};