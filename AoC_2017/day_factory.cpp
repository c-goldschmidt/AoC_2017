#include "day_factory.h"

map<string, DayFactory::TCreateMethod> DayFactory::s_methods;

bool DayFactory::Register(const string name, TCreateMethod funcCreate) {
    std::cout << name << std::endl;
    std::cout << s_methods.size() << std::endl;
    
    if (auto it = s_methods.find(name); it == s_methods.end()) {
        s_methods[name] = funcCreate;
        return true;
    }

    std::cout << "could not register: " << name;
    return false;
}

unique_ptr<Day> DayFactory::Create(const string& name) {
    if (auto it = s_methods.find(name); it != s_methods.end()) {
        return it->second(); // call the createFunc
    }

    std::cout << "class not found: " << name;
    return nullptr;
}
