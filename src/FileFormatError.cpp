#include "FileFormatError.h"

FileFormatError::FileFormatError(const std::string& filename, int line, const std::string& msg)
    : GameError("Error de formato en '" + filename + "' (linea " + std::to_string(line) + "): " + msg)
{
}
