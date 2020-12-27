#pragma once

#include <memory>
#include <unordered_map>
#include <string>

struct Registry {
    virtual ~Registry() = default;

    using create_f = std::unique_ptr<Registry>();

    static void registrate(std::string const& name, create_f* fp) {
        registry()[name] = fp;
    }

    static std::unique_ptr<Registry> instantiate(std::string const& name) {
        auto it = registry().find(name);
        return it == registry().end() ? nullptr : (it->second)();
    }

    template <typename T>
    struct Registrar {
        explicit Registrar(std::string const& name) {
            Base::registrate(name, &T::create);
        }
    };

private:
    static std::unordered_map<std::string, create_f*>& registry();
};