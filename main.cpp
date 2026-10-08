#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

static chrono::steady_clock::time_point g_start;

void printArray(const vector<int>& v);
vector<int> randomArray(void);
void startTimer();
void stopTimer();

vector<int> bubbleSort(vector<int> arr);
vector<int> insertionSort(vector<int> arr);
void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right);
void mergeSortHelper(vector<int>& arr, vector<int>& temp, int left, int right);
vector<int> mergeSort(vector<int> arr);
int partition(vector<int>& arr, int low, int high);
void quickSortHelper(vector<int>& arr, int low, int high);
vector<int> quickSort(vector<int> arr);

int main(){

    vector<int> unsorted = randomArray();
    vector<int> bubble;
    vector<int> insertion;
    vector<int> merge;
    vector<int> quick;

    //printArray(unsorted);

    cout << "\n\n";

    
    cout << "==Bubble Sort==\n";
    startTimer();
    bubble = bubbleSort(unsorted);
    stopTimer();
    cout << "\n";
    
    
    
    cout << "==Insertion Sort==\n";
    startTimer();
    insertion = insertionSort(unsorted);
    stopTimer();
    cout << "\n";
    

    
    cout << "==Merge Sort==\n";
    startTimer();
    merge = mergeSort(unsorted);
    stopTimer();
    cout << "\n";

    
    cout << "==Quick Sort==\n";
    startTimer();
    quick = quickSort(unsorted);
    stopTimer();
    cout << "\n";

    return 0;
}

void printArray(const vector<int>& v) {
    cout << '[';
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "]\n";
}

vector<int> randomArray(void){

    int n = -1;
    vector<int> arr;

    do{

        cout << "Enter Array Size: ";
        cin >> n;

    }while(n < 0);

    random_device rd;    
    mt19937 gen(rd());                      
    uniform_int_distribution<int> dist(0, n*10);

    for(int i = 0; i < n; i++){
        arr.push_back(dist(gen));
    }

    return arr;

}

void startTimer() {
    g_start = chrono::steady_clock::now();
}

void stopTimer() {
    auto end = chrono::steady_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(end - g_start).count();
    cout << "Time taken: " << us << " us (" << us / 1000.0 << " ms)\n";
}

//Sorting Algorithm Functions

vector<int> bubbleSort(const vector<int> arr){

    int size = arr.size();

    if(size == 0){
        cout << "Empty Array\n";
        return {};
    }

    vector<int> sorted = arr;

    int tmp;
    bool swapped = 1;
    int pass = 0;

    while(swapped){
        swapped = 0;
        for(int i = 0; i < size- 1 - pass; i++){
            if(sorted[i] > sorted[i+1]){
                tmp = sorted[i];
                sorted[i] = sorted[i+1];
                sorted[i+1] = tmp;
                swapped = 1;
            }
        }
        pass++;
    }

    return sorted;

}

vector<int> insertionSort(const vector<int> arr){

    int size = arr.size();

    if(size == 0){
        cout << "Empty Array\n";
        return {};
    }

    vector<int> sorted = arr;


   for (int i = 1; i < size; ++i) {
        int key = sorted[i];
        int j = i - 1;

        while (j >= 0 && sorted[j] > key) {
            sorted[j + 1] = sorted[j];
            j--;
        }
        sorted[j + 1] = key;
    }


    return sorted;

}

void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;      
    int j = mid + 1;   
    int k = left;


   
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

   
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    
    for (int idx = left; idx <= right; ++idx) {
        arr[idx] = temp[idx];
    }
}

void mergeSortHelper(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) {
        return; 
    }

    int mid = left + (right - left) / 2;

    mergeSortHelper(arr, temp, left, mid);
    mergeSortHelper(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

vector<int> mergeSort(const vector<int> arr){

    int size = arr.size();

    if(size == 0){
        cout << "Empty Array\n";
        return {};
    }

    vector<int> sorted = arr;

    vector<int> temp(size);

    mergeSortHelper(sorted, temp, 0, size - 1);


    return sorted;

}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1; 
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
       
        int p = partition(arr, low, high);

        // Recursively sort elements before & after partition
        quickSortHelper(arr, low, p - 1);
        quickSortHelper(arr, p + 1, high);
    }
}

vector<int> quickSort(const vector<int> arr){

    int size = arr.size();

    if(size == 0){
        cout << "Empty Array\n";
        return {};
    }

    vector<int> sorted = arr;

    quickSortHelper(sorted, 0, size - 1);


    return sorted;

}
