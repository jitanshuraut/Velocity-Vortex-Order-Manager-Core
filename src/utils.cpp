#include "utils.hpp"
#include <cstdlib>

std::string getEnvVariable(const std::string& varName) {
    const char* val = std::getenv(varName.c_str());
    if (val == nullptr) {
        return "";
    }
    return std::string(val);
}