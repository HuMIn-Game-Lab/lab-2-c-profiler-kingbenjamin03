#include "Profiler.hpp"
#include "time.hpp"
#include <iostream>
using namespace std;

TimeRecordStart::TimeRecordStart(char const* sectionName)
{
    std::cout << "TimeRecordStart constructor" << std::endl;
    sectionName = sectionName;
    secondsAtStart = GetCurrentTimeSecond();
}
TimeRecordStart::~TimeRecordStart()
{
    std::cout << "TimeRecordStart destructor" << std::endl;
}
TimeRecordStop::TimeRecordStop(char const* sectionName, double secondsAtStop)
{
    std::cout << "TimeRecordStop constructor" << std::endl;
}
TimeRecordStop::TimeRecordStop(char const* sectionName, double elapsedTime, int lineNumber, const char* fileName, const char* functionName)
{
    std::cout << "TimeRecordStop constructor" << std::endl;
}
TimeRecordStop::~TimeRecordStop()
{
    std::cout << "TimeRecordStop destructor" << std::endl;
}


Profiler::Profiler()
{
    std::cout << "Profiler constructor" << std::endl;
}
Profiler::~Profiler()
{
    std::cout << "Profiler destructor" << std::endl;
}
