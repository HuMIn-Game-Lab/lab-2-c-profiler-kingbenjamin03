#include "Profiler.hpp"
#include "time.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
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
    //std::cout << "ProfilerStats constructor" << std::endl;
    this->sectionName = sectionName;
    count = 1;
    totalTime = 0;
    minTime = DBL_MAX;
    maxTime = 0;
    avgTime = 0;
    fileName = __FILE__;
    functionName = __FUNCTION__;
    lineNumber = __LINE__;
}


Profiler::Profiler(){
    //Profiler* gProfiler = nullptr;
    gProfiler = this;
    startTimes.reserve(100);
    elapsedTimes.reserve(1000000);
    //cout<<"Profiler constructor"<<endl;
}
Profiler::~Profiler(){
    //cout<<"Profiler destructor"<<endl;
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
   //cout << "Entering section: " << sectionName << endl;
    double secondsAtStart = GetCurrentTimeSecond();
    startTimes.emplace_back(sectionName, secondsAtStart);
}
void Profiler::ExitSection(char const* sectionName)
{
    double secondsAtStop = GetCurrentTimeSecond(); // Get the current time when exiting the section
    for(int i = startTimes.size()-1; i>=0; i--)
    {
        if(startTimes.at(i).sectionName == sectionName)
        {
            TimeRecordStart const& currentSection = startTimes.at(i);
            startTimes.erase(startTimes.begin() + i); // Remove the section from the start times vector
            double elapsedTime  = secondsAtStop - currentSection.secondsAtStart;

            TimeRecordStop stop = TimeRecordStop(sectionName, elapsedTime);
            elapsedTimes.push_back(stop);

            if(stats.find(sectionName) == stats.end()) //checks to see if section already is in the map, if not it adds it
            {
                stats[sectionName] = new ProfilerStats(sectionName);
                stats[sectionName]->totalTime = elapsedTime;
                stats[sectionName]->count = 1;
                stats[sectionName]->minTime = elapsedTime;
                stats[sectionName]->maxTime = elapsedTime;

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
            return; // Exit the function after processing the section
        }
    }
   
}


void Profiler::printStats()
{
        std::cout << std::left << std::setw(20) << "Section Name" 
              << std::setw(18) << "Count" 
              << std::setw(18) << "Total Time"
              << std::setw(18) << "Min Time"
              << std::setw(18) << "Max Time"
              << std::setw(18) << "Avg Time"
              << std::endl;
            std::cout << std::string(80, '-') << std::endl;
    for( auto& stat : stats){
            std::cout << std::left << std::setw(20) << stat.first
              << std::setw(18) << stat.second->count 
              << std::setw(18) << stat.second->totalTime
              << std::setw(18) << stat.second->minTime 
              << std::setw(18) << stat.second->maxTime 
              << std::setw(18) << stat.second->totalTime/stat.second->count
              << std::endl;
    }







    // cout<< "Profiler Stats:" << endl;
    // for( auto& stat : stats)
    // {
    //     std::cout << "Section: " << stat.first << ", Count: " << stat.second->count << ", Total Time: " << stat.second->totalTime<<", Min Time: "<<stat.second->minTime<<", Max Time: "<<stat.second->maxTime<<", Avg Time: "<<stat.second->totalTime/stat.second->count
    //     <<", File Name: "<<stat.second->fileName<<", Function Name: " <<stat.second->functionName<<", Line Number: "<<stat.second->lineNumber<<std::endl<<endl;
    // }
}
void Profiler::printStatsToCSV(const char* fileName)
{
    ofstream ProfilerStats("Data/ProfilerStats.csv"); //creates output CSV
    if(ProfilerStats.is_open())
    {
        ProfilerStats << "Section, Count, Total Time, Min Time, Max Time, Avg Time, File Name, Function Name, Line Number\n";
        for( auto& stat : stats)
        {
            ProfilerStats << stat.first << ", " << stat.second->count << ", " << stat.second->totalTime << ", " << stat.second->minTime << ", " << stat.second->maxTime << ", " << stat.second->totalTime/stat.second->count << ", " << stat.second->fileName << ", " << stat.second->functionName << ", " << stat.second->lineNumber << "\n";
        }
        ProfilerStats.close();
    }
    else
    {
        cout << "Unable to open file";
    }

}
void Profiler::printStatsToJSON(const char* fileName)
{
    // Implement JSON output if needed
}


vector<TimeRecordStart> Profiler::getStartTimes(){
    return startTimes;
};
vector<TimeRecordStop> Profiler::getElapsedTimes(){
    return elapsedTimes;
};
map<char const*, ProfilerStats*> Profiler::getStats(){
    return stats;
};