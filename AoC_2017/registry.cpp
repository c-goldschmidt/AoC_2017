#include "registry.hpp"

std::unordered_map<std::string, Registry::create_f*>& Registry::registry()
{
    static std::unordered_map<std::string, Registry::create_f*> impl;
    return impl;
}