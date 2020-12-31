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

#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long long

#define measure(content) { \
	long long start = PerformanceCounter(); \
	content; \
	long long finish = PerformanceCounter(); \
	long long frequency = PerformanceFrequency(); \
	double elapsedMilliseconds = ((finish - start) * 1000.0) / frequency; \
	print("Time: " << elapsedMilliseconds << "ms"); \
} \
