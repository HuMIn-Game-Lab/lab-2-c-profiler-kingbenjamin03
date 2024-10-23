#include <iostream>
#include <cstdlib>
#include <thread>
#include <queue>
#include "Profiler.hpp"
using namespace std;

Profiler* gProfiler = new Profiler();

void test1(){

vector<int> unsortedVector;
//enterSection("interweaveTest");
for(int i = 0; i < 1000; i++){
    //enterSection("Array1");
    unsortedVector.push_back(rand() % 1000);
    //exitSection("Array1");
}
    bool swapped;
    int n = unsortedVector.size();
    
    // Outer loop: keeps iterating until the vector is sorted
    enterSection("BubbleSort1");
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            //enterSection("InnerLoop");
            if (unsortedVector[i] > unsortedVector[i + 1]) {
                // Swap adjacent elements if they are in the wrong order
                std::swap(unsortedVector[i], unsortedVector[i + 1]);
                swapped = true;
            }
            //exitSection("InnerLoop");
            
        }
        //exitSection("interweaveTest");
        n--;  // Reduce the range to optimize since the largest element gets placed at the end in each pass
    } while (swapped); 
    
    exitSection("BubbleSort1");

};
void test2(){
//enterSection("interweaveTest2");

    vector<int> unsortedVector;

    for(int i = 0; i < 1000; i++){
       //enterSection("Array2");
        unsortedVector.push_back(rand() % 1000);
        //exitSection("Array2");
    }
    
    
    enterSection("BubbleSort2");
    int n = unsortedVector.size();
        for (int i = 0; i < n; i++) {  // Outer loop
        for (int j = 0; j < n - 1; j++) {  // Inner loop
            //nterSection("InnerLoop2");
            // Compare adjacent elements and swap if out of order
            if (unsortedVector[j] > unsortedVector[j + 1]) {
                std::swap(unsortedVector[j], unsortedVector[j + 1]);
            }
            //exitSection("InnerLoop2");
        }
        //exitSection("interweaveTest2");
        // Even when sorted, this algorithm does not optimize by stopping early
    }
    exitSection("BubbleSort2");
}
void test3(){
    for(int i = 0; i<10; i++){
        enterSection("Test3");
        //cout<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        exitSection("Test3");
    }
    
}
void test4()
{
    enterSection("Test4");
    enterSection("Test4.1");
    int x = 2;
    if (x == 23) {
        exitSection("Test4");
    }
    else {
        exitSection("Test4.1");
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    exitSection("Test4");
    exitSection("Test4.1");
}

void DFSUtil(int vertex, vector<bool> &visited, const vector<int> adj[]) {
    // Mark the current vertex as visited and print it
    enterSection("DFS Test");
    visited[vertex] = true;
    //cout << vertex << " ";

    // Recur for all adjacent vertices that have not been visited
    for (int adjVertex : adj[vertex]) {
       // enterSection("DFSUtil");
        if (!visited[adjVertex]) {
            DFSUtil(adjVertex, visited, adj);
        }
        //exitSection("DFSUtil");
        exitSection("DFS Test");
    }
}
void DFS(int startVertex, const vector<int> adj[], int numVertices) {
    // Create a boolean array to mark visited vertices
    
    vector<bool> visited(numVertices, false);
    //cout << "DFS Traversal starting from vertex " << startVertex << ": ";
    DFSUtil(startVertex, visited, adj);
    //cout << endl;
    
}
void selectionSort1(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        swap(arr[i], arr[min_idx]);
    }
}
void selectionSort2(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {

        int min_idx = i;

        // Iterate through the entire array instead of just the unsorted portion
        for (int j = 0; j < n; ++j) {  // Start from 0, inefficient
            if (arr[j] < arr[min_idx]) {
                min_idx = j; 
            }
        }

        // Always perform the swap, even if it's unnecessary
        swap(arr[i], arr[min_idx]);  // Always swap, inefficient
    }
}



void test5(){
    int numVertices = 5;

    // Create an adjacency list using an array of vectors
    vector<int> adj[numVertices];

    // Add edges to the graph
    adj[0].push_back(1);
    adj[0].push_back(4);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[4].push_back(3);

    
    // Perform DFS traversal starting from vertex 0
    DFS(0, adj, numVertices);
    
}
void sleepTest()
{
    for(int i = 0; i < 10; i++){
    enterSection("SleepTestShort");
    enterSection("SleepTestLong");
    this_thread::sleep_for(chrono::milliseconds(200));
    exitSection("SleepTestShort");
    this_thread::sleep_for(chrono::milliseconds(200));
    exitSection("SleepTestLong");
    }

}
void test6(){
    vector<int> unsortedVector;
    for(int i = 0; i < 1000; i++){
        unsortedVector.push_back(rand() % 1000);
    }
    enterSection("SelectionSort1");
    selectionSort1(unsortedVector);
    exitSection("SelectionSort1");

}
void test7(){
    vector<int> unsortedVector;
    for(int i = 0; i < 1000; i++){
        unsortedVector.push_back(rand() % 1000);
    }
    enterSection("SelectionSort2");
    selectionSort2(unsortedVector);
    exitSection("SelectionSort2");
}
int main()
{
for(int i = 0;i<1000; i++){
     test1(); //efficient bubble sort
     test2(); //ineffeicient bubble sort
     //test3(); //test3 runs for 1 second
     //test4(); //test4 interweaving test
     //test5(); //DFS test
     test6(); //selection sort test
     test7(); //inefficient selection sort
}
sleepTest(); //sleep test has interweaving as well. not in loop becasue it would run for 2 seconds 1000 times which would take 33.33 minutes 

PrintStats();
PrintStatsToCSV("ProfilerStats.csv");

    return 0;
}