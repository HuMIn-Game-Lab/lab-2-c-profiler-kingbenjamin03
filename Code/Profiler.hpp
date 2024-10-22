#pragma once //does all that macro stuff to make sure there isnt an endless loop of headers 
#include <cfloat>
#include <vector>
#include <map>
using namespace std;

#define exitSection(sectionName) gProfiler->ExitSection(sectionName, __FILE__, __FUNCTION__, __LINE__)
#define enterSection(sectionName) gProfiler->EnterSection(sectionName)
#define PrintStats() gProfiler->printStats()
#define PrintStatsToCSV(fileName) gProfiler->printStatsToCSV(fileName)
#define PrintStatsToJSON(fileName) gProfiler->printStatsToJSON(fileName)

class TimeRecordStart{
    public:
            TimeRecordStart(const char* sectionName, double secondsAtStart)
        : sectionName(sectionName), secondsAtStart(secondsAtStart) {}
        ~TimeRecordStart();

        char const* sectionName;
        double secondsAtStart;
};

class TimeRecordStop{
    public:
        TimeRecordStop(char const* sectionName, double secondsAtStop);
        TimeRecordStop(char const* sectionName, double elapsedTime, int lineNumber, const char* fileName, const char* functionName);
        ~TimeRecordStop();

        char const* sectionName;
        int callCount;
        double elapsedTime;
        int lineNumber;
        const char* fileName;
        const char* funcitonName;

        
};

class ProfilerStats{
    public:
        ProfilerStats(char const* sectionName, const char* fileName, const char* functionName, int lineNumber);
        ~ProfilerStats();

        char const* sectionName;
        int count;
        double totalTime;
        double minTime;
        double maxTime;
        double avgTime;
        const char* fileName;
        const char* functionName;
        int lineNumber;
};

class Profiler{
    public:
        Profiler();
        ~Profiler();

        void EnterSection(char const* sectionName);
        void ExitSection(char const* sectionName, const char* file, const char* function, int line);
        void printStats();
        void printStatsToCSV(const char* fileName);
        void printStatsToJSON(const char* fileName);
        vector<TimeRecordStart> getStartTimes();
        vector<TimeRecordStop> getElapsedTimes();
        map<char const*, ProfilerStats*> getStats();
        static Profiler* gProfiler;

    private:
        void ReportSectionTime(char const* sectionName, double elapsedTime);
        void ReportSectionTime(char const* sectionName, double elapsedTime, int lineNumber, const char* fileName, const char* functionName);
        map<char const*, ProfilerStats*> stats;
        vector<TimeRecordStart> startTimes;
        vector<TimeRecordStop> elapsedTimes;
        
};