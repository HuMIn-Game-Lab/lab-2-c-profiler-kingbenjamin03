#include "Profiler.hpp"
#include "time.hpp"
#include <iostream>
using namespace std;

Profiler* Profiler::gProfiler = nullptr;

// TimeRecordStart::TimeRecordStart(char const* sectionName)
// {
//     std::cout << "TimeRecordStart constructor" << std::endl;
//     sectionName = sectionName;
//     secondsAtStart = GetCurrentTimeSecond();
// }
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



Profiler::Profiler(){
    //Profiler* gProfiler = nullptr;
    gProfiler = this;
    startTimes.reserve(100);
    elapsedTimes.reserve(1000000);
    cout<<"Profiler constructor"<<endl;
}
Profiler::~Profiler(){
    cout<<"Profiler destructor"<<endl;
    startTimes.clear();
    elapsedTimes.clear();
    stats.clear();
}

void Profiler::ReportSectionTime(char const* sectionName, double elapsedTime)
{
    std::cout << "called ReportSectionTime" << std::endl;
}

void Profiler::calculateStats()
{
    std::cout << "called calculateStats" << std::endl;
}

void Profiler::EnterSection(char const* sectionName)
{
    double secondsAtStart = GetCurrentTimeSecond();
    startTimes.emplace_back(sectionName, secondsAtStart);
}

void Profiler::ExitSection(char const* sectionName)
{

    double secondsAtStop = GetCurrentTimeSecond();
    TimeRecordStart const& currentSection = startTimes.back();

    #if defined (DEBUG_PROFILER)
        //verify the stack isnt empty
        //verify current seciton matches name 
    #endif

    double elapsedTime  = secondsAtStop - currentSection.secondsAtStart;
    ReportSectionTime(sectionName, elapsedTime);
    startTimes.pop_back();
}
void Profiler::printStats()
{
    cout<< "Profiler Stats:" << endl;
    for( auto& stat : stats)
    {
        std::cout << "Section: " << stat.first << " Count: " << stat.second->count << " Total Time: " << stat.second->totalTIme << std::endl;
    }
}