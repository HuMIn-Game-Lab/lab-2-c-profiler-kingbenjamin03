#include <iostream>
#include <cstdlib>
#include "Profiler.hpp"
using namespace std;



void test1(){
    //gProfiler->EnterSection("test1");
    vector<int> test;
    for(int i = 0; i < 1000000; i++){
        test.push_back(i);
    }
    //gProfiler->ExitSection("test1");

};


int main()
{
    // TimeRecordStart* trs = new TimeRecordStart("main");
    // cout << trs->secondsAtStart << endl;
    // delete trs;
    // TimeRecordStop* trs2 = new TimeRecordStop("main", 1.0);
    // cout << trs2->elapsedTime << endl;
    // delete trs2;
    
    Profiler* p = new Profiler();
    p->EnterSection("mTest");
    vector<int> test;
    for(int i = 0; i < 1000; i++){
        p->EnterSection("iTest");
        test.push_back(i);
        for(int j = 0; j <1000; j++){
            p->EnterSection("jTest");
            test.push_back(j);
            p->ExitSection("jTest");
        }
        p->ExitSection("iTest");
    }
    p->ExitSection("mTest");
    p->printStats();




    delete p;
    






    return 0;
}