#pragma once
#include "day.hpp"

class DayFactory {
public:
	using TCreateMethod = unique_ptr<Day>(*)();
	DayFactory() = delete;

	static bool Register(const string name, TCreateMethod funcCreate);
	static unique_ptr<Day> Create(const string& name);

private:
	static map<string, TCreateMethod> s_methods;
};


map<string, DayFactory::TCreateMethod> DayFactory::s_methods;

bool DayFactory::Register(const string name, TCreateMethod funcCreate) {
    if (auto it = s_methods.find(name); it == s_methods.end()) {
        s_methods[name] = funcCreate;
        return true;
    }

    return false;
}

unique_ptr<Day> DayFactory::Create(const string& name) {
    if (auto it = s_methods.find(name); it != s_methods.end()) {
        return it->second(); // call the createFunc
    }

    return nullptr;
}
