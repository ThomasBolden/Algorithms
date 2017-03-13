/*

Author:     Thomas Bolden
Project:    Sorting Methods

Date:       March 7, 2017

*/

#include <iostream>
using std::cout; using std::cin; using std::endl;
using std::ostream;

#include <iomanip> // not used

#include <cmath> // not used

#include <ctime> // used to seed random number and to time algos
using std::clock_t; using std::clock;

#include <vector>
using std::vector;

#include <string>
using std::string; using std::to_string;
using std::stod; using std::stol;

#include <algorithm>
using std::copy; using std::transform; using std::reverse; 
using std::plus; using std::iter_swap;




// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//
//  List Class with Sorting Methods
//      - TODO: Add heap sort, binary tree sort
//      - TODO: Fix output, doesn't make much sense with
//              the recursive algorithms
//  
//  private:
//      vector<T>   list_           .   
//      size_t      size_           .
//      long        comparisons_    .
//      long        swaps_          .
//      long        loops_          .
//      long        time_           .
//
//  public:
//      void    bubble_sort         .
//      void    selection_sort      .
//      void    insertion_sort      .
//      void    merge_sort          .
//      void    quick_sort          .
//
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

template <typename T>
class List{
public: // attributes
    vector<T> list_;
    string    method_;
    size_t    size_;
    long      comparisons_;
    long      swaps_;
    long      loops_;
    double    time_;

public: // methods
    List(vector<T>&);
    void bubble_sort();
    void selection_sort();
    void insertion_sort();
    void merge_sort(int, int);
    void quick_sort(int, int);
    //friend ostream& operator<<(ostream&, const List<T>& l);
};

//
template <typename T>
List<T>::List(vector<T>& v){
    list_ = v;
    size_ = v.size();
}

// print list
//template <typename T>
//ostream& operator << (ostream& os, const List<T>& l){
//    string to_print;
//    return os;
//}

// currently only supports longs !!!
int main(){
    
    int case_num, list_length, print_list, max_list_size;

    cout << "How large of a list do you want? ";
    cin >> max_list_size;

    cout << "Sorting Method? (1) Bubble, (2) Selection, ";
    cout << endl << "(3) Insertion, (4) Merge, (5) Quick: ";
    cin >> case_num;

    cout << "Would you like to print the sorted list for verification? ";
    cout << endl << "(1) YES, (0) NO: ";
    cin >> print_list;

    string name;

    srand(time(NULL));

    list_length = max_list_size;

    // enable for variable list size
    //list_length = rand() % max_list_size;

    vector<long> list_init;
    // following loop fills the list with random numbers
    for(int i = 0; i < list_length; i++){
        list_init.push_back(rand()%max_list_size);
    }

    List<long> list(list_init);

    switch (case_num){
    
        // bubble sort
        case 1: {
            clock_t begin = clock();
            list.bubble_sort();
            clock_t end = clock();
            list.time_ = double(end - begin) / CLOCKS_PER_SEC;
            break;
        }

        // selection sort
        case 2: {
            clock_t begin = clock();
            list.selection_sort();
            clock_t end = clock();
            list.time_ = double(end - begin) / CLOCKS_PER_SEC;
            break;
        }

        // insertion sort
        case 3: {
            clock_t begin = clock();
            list.insertion_sort();
            clock_t end = clock();
            list.time_ = double(end - begin) / CLOCKS_PER_SEC;
            break;
        }

        // merge sort
        case 4: {
            clock_t begin = clock();
            list.merge_sort(0, list.size_);
            clock_t end = clock();
            list.time_ = double(end - begin) / CLOCKS_PER_SEC;
            break;
        }

        // quick sort
        case 5: {
            clock_t begin = clock();
            list.quick_sort(0, list.size_);
            clock_t end = clock();
            list.time_ = double(end - begin) / CLOCKS_PER_SEC;
            break;
        }

    } // switch

    cout << "To " << list.method_ << " sort the list of length " << list.size_;
    cout << " required... " << endl;
    cout << list.time_ << " seconds," << endl;
    cout << list.loops_ << " passes," << endl;
    cout << list.comparisons_ << " comparisons," << endl;
    cout << "and " << list.swaps_ << " swaps." << endl;
    //cout << "Passes: " << list.loops_ << endl;

    // printing the list for verification purposes
    if(print_list){
        for(int j = 0; j < list.size_; j++){
            cout << list.list_[j] << ' ';
        }
        cout << endl;
    }

    // if I made a friend function to print (haven't yet)
    //cout << list;

    return 0;

}

// Implimentation of the Bubble Sort Algorithm
// with O(n^2) complexity in the worst case
// and  O(n)   complexity in the best case
template <typename T>
void List<T>::bubble_sort(){

    method_ = "bubble";

    for(int loops = 0; loops < size_ - 1; loops++){
        loops_++;
        for(int index = 0; index < size_ - loops - 1; index++){
            comparisons_++;
            if(list_[index] > list_[index+1]){
                swaps_++;
                T temp = list_[index];
                list_[index] = list_[index+1];
                list_[index+1] = temp;
            } // swaps
        } // comparisons
    } // passes

}

// Implimentation of the Selection Sort Algorithm
// with O(n^2) complexity in the worst case
// and  O(n)   complexity in the best case
template <typename T>
void List<T>::selection_sort(){

    method_ = "selection";

    int index_min;

    for(int loops = 0; loops < size_ - 1; loops++){
        loops_++;
        index_min = loops;
        for(int index = loops + 1; index < size_; index++){
            comparisons_++;
            if(list_[index] < list_[index_min]){
                swaps_++;
                T temp = list_[index];
                list_[index] = list_[index_min];
                list_[index_min] = temp;
            } // swaps
        } // comparisons
    } // passes

}

// Implimentation of the Insertion Sort Algorithm
// with O(n^2) complexity in the worst case
// and  O(n)   complexity in the best case
template <typename T>
void List<T>::insertion_sort(){

    method_ = "insertion";

    loops_++;

    for(int loops = 1; loops < size_; loops++){
        comparisons_++;
        int index = loops;
        while(index > 0 && list_[index] < list_[index-1]){
            swaps_++;
            T temp = list_[index];
            list_[index] = list_[index-1];
            list_[index-1] = temp;
            index--;
        } // swaps / "insertions"
    } // comparisons <-- NOT REALLY - FIX REQUIRED!!
      //                 should it be same as swaps + 1 per element?

}

// Implimentation of the Merge Sort Algorithm
// with O(nlogn) complexity in the worst case
// and  O(nlogn) complexity in the best case
template <typename T>
void List<T>::merge_sort(int left, int right){

    method_ = "merge"; // http://quiz.geeksforgeeks.org/merge-sort/

    T temp;

    comparisons_++;
    if(left < right){

        int mid = left + (right - left) / 2; // prevents overflow

        loops_++;
        merge_sort(left, mid);
        merge_sort(mid+1, right);

        vector<T> tempLeft, tempRight;

        int ls = mid - left + 1;
        int rs = right - mid;
        
        for(int l = 0; l < ls; l++){
            swaps_++;
            tempLeft.push_back(list_[left+l]);
        }
        for(int r = 0; r < rs; r++){
            swaps_++;
            tempRight.push_back(list_[mid+r+1]);
        }
        
        int i = 0;
        int j = 0;
        int k = left;
        
        while(i < ls && j < rs){
            comparisons_++;
            if(tempLeft[i] <= tempRight[j]){
                list_[k] = tempLeft[i];
                i++;
            }
            else{
                list_[k] = tempRight[j];
                j++;
            }
            k++;
        }

        // add leftovers
        while(i < ls){
            list_[k] = tempLeft[i];
            i++;
            k++;
        }
        while(j < rs){
            list_[k] = tempRight[j];
            j++;
            k++;
        } 

    }

}

// Implimentation of the Quick Sort Algorithm
// with O(n^2)   complexity in the worst case
// and  O(nlogn) complexity in the best case
template <typename T>
void List<T>::quick_sort(int left, int right){

    method_ = "quick";

    int l = left; 
    int r = right;
    int mid = list_[left + (right - left) / 2]; // prevents overflow
    T temp;
 
    while (l <= r) {
        while (list_[l] < mid){
            l++;
        }
        while (list_[r] > mid){
            r--;
        }
        comparisons_++;
        if (l <= r) {
            swaps_++;
            temp = list_[l];
            list_[l] = list_[r];
            list_[r] = temp;
            l++;
            r--;
        }
    }
 
    // recursive callbacks
    if (left < r){
        loops_++;
        quick_sort(left, r);
    }
    if (l < right){
        loops_++;
        quick_sort(l, right);
    }

}