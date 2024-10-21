#include "Profiler.hpp"
#include "time.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

Profiler* Profiler::gProfiler = nullptr;


TimeRecordStart::~TimeRecordStart()
{

}


TimeRecordStop::TimeRecordStop(char const* sectionName, double secondsAtStop)
{
    this->sectionName = sectionName;
    this->elapsedTime = secondsAtStop;
}
TimeRecordStop::TimeRecordStop(char const* sectionName, double elapsedTime, int lineNumber, const char* fileName, const char* functionName)
{
    this->sectionName = sectionName;
    this->elapsedTime = elapsedTime;
    this->lineNumber = lineNumber;
    this->fileName = fileName;
    this->funcitonName = functionName;

}
TimeRecordStop::~TimeRecordStop(){}


ProfilerStats::ProfilerStats(char const* sectionName)
{
    std::cout << "ProfilerStats constructor" << std::endl;
    this->sectionName = sectionName;
    count = 1;
    totalTime = 0;
    minTime = DBL_MAX;
    maxTime = 0;
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
    TimeRecordStart const& currentSection = startTimes.back(); //grabs the last section form vector of start times 

    #if defined (DEBUG_PROFILER)
        //verify the stack isnt empty
        //verify current seciton matches name 
    #endif

    double elapsedTime  = secondsAtStop - currentSection.secondsAtStart;
    TimeRecordStop stop = TimeRecordStop(sectionName, elapsedTime);
    elapsedTimes.push_back(stop);
    //ReportSectionTime(sectionName, elapsedTime);
    if(stats.find(sectionName) == stats.end())
    {
        stats[sectionName] = new ProfilerStats(sectionName);

    }
    else{
    stats[sectionName]->count++;
    stats[sectionName]->totalTime += elapsedTime;
    if(stats[sectionName]->minTime > elapsedTime || stats[sectionName]->minTime == 0)
    {
        stats[sectionName]->minTime = elapsedTime;
    }
    if(stats[sectionName]->maxTime < elapsedTime)
    {
        stats[sectionName]->maxTime = elapsedTime;
    }
    }
}
void Profiler::printStats()
{
    cout<< "Profiler Stats:" << endl;
    for( auto& stat : stats)
    {
        std::cout << "Section: " << stat.first << ", Count: " << stat.second->count << ", Total Time: " << stat.second->totalTime << std::endl;
    }
}