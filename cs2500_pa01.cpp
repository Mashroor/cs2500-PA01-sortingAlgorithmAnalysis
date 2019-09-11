/*  Programmer Name: Mashroor Rashid
    Course: CS 2500 - Algorithms Instructor: Matthew Wagner
    Assignment: Programming Assignment 1
    Description: Using C++, Analyze run times and complexities of the following sorting algorithms:
        - Insertion sort
        - Merge sort
        - Selection sort
    A formal report should be written using data gathered from this program.
*/
#include <iostream>
#include <algorithm> 
#include <vector>
#include<chrono>
#include<assert.h> //for Pre and post conditions

using namespace std;
using namespace std::chrono;

// function definitions
void printVec(vector<int> v);
void insertionSort(vector<int>& arr);
void mergeSort(vector<int>& arr, int p, int r);
void merge(vector<int>& arr, int p, int q, int r);
void selectionSort(vector<int>& arr);
void swap(int* x, int* y);
void sortedCheck(vector<int> arr);

int main(){
    string s;
    vector<int> vInsertion;
    vector<int> vMerge;
    vector<int> vSelection;
    // Read input txt file from zsh
    while (cin >> s){
        // while taking input, should throw error if input is NOT an integer
        int temp = std::stoi(s);
        // Store numbers to each vector to run sequentially
        vInsertion.push_back(temp);
        vMerge.push_back(temp);
        vSelection.push_back(temp);
    }
    
    // begin insertion sort
    
    auto startInsertion = high_resolution_clock::now();
    insertionSort(vInsertion);
    auto stopInsertion = high_resolution_clock::now();
    auto durationInsertion = duration_cast<microseconds>(stopInsertion - startInsertion); 
    // Post Check, Is this sorted?
    sortedCheck(vInsertion);
    
    // begin merge sort
    auto startMerge = high_resolution_clock::now();
    mergeSort(vMerge, 0, vMerge.size()-1);
    auto stopMerge = high_resolution_clock::now();
    auto durationMerge = duration_cast<microseconds>(stopMerge - startMerge);
    // Post Check, Is this sorted?
    sortedCheck(vMerge);
    
    // begin selection sort
    auto startSelection = high_resolution_clock::now();
    selectionSort(vSelection);
    auto stopSelection = high_resolution_clock::now();
    auto durationSelection = duration_cast<microseconds>(stopSelection - startSelection);
    // Post Check, Is this sorted?
    sortedCheck(vSelection);

    // report formatted runtimes
 //   printVec(vInsertion);
    cout << "Insertion Sort runtime: " <<  durationInsertion.count() << "ms" << endl;
 //   printVec(vMerge);
    cout << "Merge Sort runtime: " <<  durationMerge.count() << "ms" << endl;
 //   printVec(vSelection);
    cout << "Selection Sort runtime: " <<  durationSelection.count() << "ms" << endl; 

    return 0;
}

// function prototypes ----------//
void printVec(vector<int> v){
    // print vector
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
}

void insertionSort(vector<int> & arr){
    int i = 1, j, key;
    assert(i == 1); // Loop Invariant, init

    for(i = 1; i < arr.size(); i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1]= key;
        assert(arr[i] >= arr[i - 1]); // Loop Invariant, Maint
    }
    assert( i > arr.size()-1); // Loop Invariant, Term
}

void mergeSort(vector<int>& arr, int p, int r){
    if(p < r){
        // divide, calculate middle of arrays
        int q = ((p+r)/2);
        // conquer, recursive calls to mergeSort(), split down to arrays of 1
        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        // combine, merge sorted sub arrays from recursive calls
        merge(arr, p, q, r);
    }
}

void merge(vector<int>& arr, int p, int q, int r){
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q; 
    vector<int> L(n1+1);
    vector<int> R(n2+1);

    for(i = 0; i < n1; i++){
        L[i] = arr[p + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[q + j + 1];
    }
    i = 0;
    j = 0;

    for(k = p; i < n1 && j < n2; k++){
        if(L[i] < R[j]){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
    }
    // combine both subvectors
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void selectionSort(vector<int>& arr){
    int i, j, min_index;
    
    for(i = 0; i < arr.size(); i++){
        min_index = i;
        for(j = i + 1; j < arr.size(); j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[min_index], &arr[i]);
    }
    assert(min_index <= arr[arr.size()-1]); // Loop Invariant, Term
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Post Condition Check
void sortedCheck(vector<int> arr){
    int k = 0;
    for(int i = 0; i < arr.size(); i++){
        assert(arr[k] <= arr[i]);
        k++;
    }
}