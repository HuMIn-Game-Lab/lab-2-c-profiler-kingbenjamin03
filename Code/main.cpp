#include <iostream>
#include <cstdlib>
#include "Profiler.hpp"
using namespace std;

int main()
{
    TimeRecordStart trs("main");
    cout<<trs.secondsAtStart<<endl;
    cout<<"Hello World!"<<endl;
    return 0;
}
