#include "Profiler.hpp"
#include "time.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include <cmath>
using namespace std;
using namespace nlohmann;

Profiler* Profiler::gProfiler = nullptr;

#define exitSection(sectionName) gProfiler->ExitSection(sectionName, __FILE__, __FUNCTION__, __LINE__)
#define enterSection(sectionName) gProfiler->EnterSection(sectionName)
//^^using macros to call the global profile, so that i can grab line numb, file name, and function name^^

#define PrintStats() gProfiler->printStats()
#define PrintStatsToCSV(fileName) gProfiler->printStatsToCSV(fileName)
#define PrintStatsToJSON(fileName) gProfiler->printStatsToJSON(fileName)



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


ProfilerStats::ProfilerStats(char const* sectionName, const char* fileName, const char* functionName, int lineNumber)
{
    this->sectionName = sectionName;
    count = 1;
    totalTime = 0;
    minTime = DBL_MAX;
    maxTime = 0;
    avgTime = 0;
    this->fileName = fileName;
    this->functionName = functionName;
    this->lineNumber = lineNumber;
}


Profiler::Profiler(){
    gProfiler = this;
    startTimes.reserve(100);
    elapsedTimes.reserve(1000000);
}
Profiler::~Profiler(){
    startTimes.clear();
    elapsedTimes.clear();
    stats.clear();
}


void Profiler::EnterSection(char const* sectionName)
{
    double secondsAtStart = GetCurrentTimeSecond();
    startTimes.emplace_back(sectionName, secondsAtStart);
}
void Profiler::ExitSection(char const* sectionName, char const* file, char const* function, int line) 
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
                stats[sectionName] = new ProfilerStats(sectionName,file, function, line);
                stats[sectionName]->totalTime = elapsedTime;
                stats[sectionName]->count = 1;
                stats[sectionName]->minTime = elapsedTime;
                stats[sectionName]->maxTime = elapsedTime;
                stats[sectionName]->sumSquaredTime = elapsedTime * elapsedTime;

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
                stats[sectionName]->sumSquaredTime += elapsedTime * elapsedTime;
            }
            return; // Exit the function 
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
              << std::setw(18) << "Standard Deviation"
              << std::endl;
            std::cout << std::string(130, '-') << std::endl;
    for( auto& stat : stats){
            double variance = (stat.second->sumSquaredTime / stat.second->count) - (stat.second->avgTime * stat.second->avgTime);
            stat.second->sumSquaredTime = sqrt(variance);
            std::cout << std::left << std::setw(20) << stat.first
              << std::setw(18) << stat.second->count 
              << std::setw(18) << stat.second->totalTime
              << std::setw(18) << stat.second->minTime 
              << std::setw(18) << stat.second->maxTime 
              << std::setw(18) << stat.second->totalTime/stat.second->count
              <<std::setw(18)<<stat.second->sumSquaredTime
              << std::endl;
    }
}
void Profiler::printStatsToCSV(const char* fileName)
{
    ofstream ProfilerStats("Data/ProfilerStats.csv"); //creates output CSV
    if(ProfilerStats.is_open())
    {
        ProfilerStats << "Section, Count, Total Time, Min Time, Max Time, Avg Time, File Name, Function Name, Line Number, Standard Deviation\n";
        for( auto& stat : stats)
        {
            ProfilerStats << stat.first << ", " << stat.second->count << ", " << stat.second->totalTime << ", " << stat.second->minTime << ", " << stat.second->maxTime << ", " << stat.second->totalTime/stat.second->count << ", " << stat.second->fileName << ", " << stat.second->functionName << ", " << stat.second->lineNumber<<", "<<stat.second->sumSquaredTime << "\n";
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
    
    ordered_json ProfilerStatsJson;

    for( auto& stat : stats)
    {
        ordered_json sectionJson;
        sectionJson["Section"] = stat.first;
        sectionJson["Count"] = stat.second->count;
        sectionJson["Total Time"] = stat.second->totalTime;
        sectionJson["Min Time"] = stat.second->minTime;
        sectionJson["Max Time"] = stat.second->maxTime;
        sectionJson["Avg Time"] = stat.second->totalTime/stat.second->count;
        sectionJson["File Name"] = stat.second->fileName;
        sectionJson["Function Name"] = stat.second->functionName;
        sectionJson["Line Number"] = stat.second->lineNumber;
        sectionJson["Standard Deviation"] = stat.second->sumSquaredTime;
        ProfilerStatsJson.push_back(sectionJson); // Add the section JSON to the main JSON array
    }

    ofstream file("Data/ProfilerStats.json");
    file<<ProfilerStatsJson.dump(4); 
    file.close();
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