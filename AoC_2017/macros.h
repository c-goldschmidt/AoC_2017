#pragma once

#define DAY(className) class className : public Day {\
public:\
	virtual void part1() override;\
	virtual void part2() override;\
\
	static unique_ptr<Day> CreateMethod() {\
		return make_unique<className>();\
	}\
\
	static string GetFactoryName() { return #className; }\
private:\
	static bool s_registered; \
};\
\
bool className::s_registered = DayFactory::Register(className::GetFactoryName(), className::CreateMethod);\

#define print(x) cout << x << endl
#define printResult(x) cout << "Result: " << x << endl