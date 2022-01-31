// ---------------------- Soriting Techniques ------------------------- 
// --Bubble sort      --> [ Comparison based sorts -> takes O(n^2) time -> Adaptive ]  
// --Insertion sort   --> [ Comparison based sorts -> takes O(n^2) time -> Adaptive ]
// --Selection sort   --> [ Comparison based sorts -> takes O(n^2) time -> Non-Adaptive ] 
// --Heap sort        --> [ Comparison based sorts -> takes O(nlogn) time ] 
// --Merge sort       --> [ Comparison based sorts -> takes O(nlogn) time ]
// --Quick sort       --> [ Comparison based sorts -> takes Worst case(already sorted) : O(n^2) | Best case : O(nlogn) | Avg case : O(nlogn) time ] 
// --Tree sort        --> [ Comparison based sorts -> takes O(nlogn) time ]
// --Shell sort       --> [ Comparison based sorts -> takes O(n^(3/2)) time ] 
// --Count sort       --> [ Index based sorts -> takes O(n) time but consumes more space ]
// --Bucket / Bin sort--> [ Index based sorts -> takes O(n) time but consumes more space ]
// --Radix sort       --> [ Index based sorts -> takes O(n) time but consumes more space ]

#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h> // All STL libs
using namespace std ;

class node { // -- For Bucket Sort --
    public :
    int value ;
    node *next ;
};

class Sort {
    public:
    // -- Sort Methods --
    void BubbleSort(vector<int> Arr) ;
    void InsertionSort(vector<int> Arr) ;
    void SelectionSort(vector<int> Arr) ;
    void Quicksort(vector<int> &Arr) ;
    void QuickSort(vector<int> &Arr, int low, int high) ;
    void Merge(vector<int> &A, int low, int mid, int high) ;
    void MergeSort_iterative(vector<int> Arr) ;
    void MergeSort_recursive(vector<int> &Arr, int low, int high) ;
    void CountSort(vector<int> &Arr) ;
    void BinOrBucketSort(vector<int> &Arr) ;
    void Insert(node **ptrbins, int idx) ;
    int  Delete(node **ptrbins, int idx) ;
    int  countDigits(long long int x) ;
    int  getBinIndex(int x, int idx) ;
    void InsertRadix(node **ptrbins, int value, int idx) ;
    void RadixSort(vector<int> &Arr) ;
    
    // -- Helper Methods --
    int partition(vector<int> &Arr, int low, int high) ;
    
    void Display(vector<int> Arr) ;
};

void Sort::BubbleSort(vector<int> Arr) {
    cout<<"Before Bubble Sorting : ";
    Display(Arr) ;
    int len = Arr.size() ;
    for (int pass = 0 ; pass < len - 1 ; pass++) {
        int flag = 0 ;
        for (int i = 0 ; i < len - pass - 1 ; i++) {
            if (Arr[i] > Arr[i+1]) {
                int temp = Arr[i] ;
                Arr[i] = Arr[i+1] ;
                Arr[i+1] = temp ;
                flag = 1 ;
             }
        }
        if (flag == 0) { break ; }
    }
    cout<<"After Bubble Sorting : ";
    Display(Arr) ;
}

void Sort::InsertionSort(vector<int> Arr) {
    cout<<"Before Insert Sorting : ";
    Display(Arr) ;
    // ---------- Procedure I ---------- Made Adaptive (used flag)
    // for (int pass = 1 ; pass < Arr.size() ; pass++) {
    //     int flag = 0 ;
    //     for (int i = pass ; i >= 1 ; i--) {
    //         if (Arr[i] < Arr[i-1]) {
    //             int temp = Arr[i] ;
    //             Arr[i] = Arr[i-1] ;
    //             Arr[i-1] = temp ;
    //             flag = 1 ;
    //         }
    //         if (flag == 0) {
    //             break ;
    //         }
    //     }
    // }
    
    //---------- Procedure II ---------- self Adaptive (no flag)
    for (int i=1; i<Arr.size(); i++){
        int j = i-1;
        int x = Arr[i];
        while (j>-1 && Arr[j] > x) { Arr[j+1] = Arr[j]; j--; }
        Arr[j+1] = x;
    }
    
    cout<<"After Insert Sorting : ";
    Display(Arr) ;
}

void Sort::SelectionSort(vector<int> Arr) {
    cout<<"Before Selection Sorting : ";
    Display(Arr) ;
    for (int pass = 0 ; pass < Arr.size() ; pass++) {
        int i, j;
        for (i = j = pass ; j < Arr.size() ; j++) {
            if (Arr[j] < Arr[i]) {
                i = j ;
            }
        }
        int temp = Arr[i] ;
        Arr[i] = Arr[pass] ;
        Arr[pass] = temp ;
    }
    cout<<"After Selection Sorting : ";
    Display(Arr) ;
}

void Sort::Quicksort(vector<int> &Arr) {
    cout<<"Before Quick Sorting : ";
    Display(Arr) ;
    QuickSort(Arr,0,Arr.size()-1) ;
    cout<<"After Quick Sorting : ";
    Display(Arr) ;
}

void Sort::QuickSort(vector<int> &Arr, int low, int high) {
    if (low < high) {
        int j = partition(Arr,low,high) ;
        QuickSort(Arr,low,j) ;
        QuickSort(Arr,j+1,high) ;
    }
}

void Sort::MergeSort_recursive(vector<int> &Arr, int low, int high) {
    if (low < high) {  
        int mid = (low + high) / 2 ;
        MergeSort_recursive( Arr, low, mid ) ;
        MergeSort_recursive( Arr, mid+1, high ) ;
        Merge( Arr, low, mid, high ) ;
    }
}

void Sort::MergeSort_iterative(vector<int> Arr) {
    cout<<"Before Merge Sorting : ";
    Display(Arr) ;
    int n = Arr.size() ;
    int p , i , low , mid , high ;
    for (p = 2 ; p <= n ; p *= 2) {
        for (i = 0 ; i+p-1 < n ; i += p) {
            low = i ;
            high = i + p - 1 ;
            mid = (low + high) / 2 ;
            Merge( Arr , low , mid , high ) ;
        }
    }
    if (p/2 < n) { Merge( Arr , 0 , p/2-1 , n-1 ); };
    cout<<"After Merge Sorting : ";
    Display(Arr) ;
}

void Sort::Merge(vector<int> &A, int low, int mid, int high) {
    //------ Extra space for storage ------
    vector<int> Merged(A.size()) ;
    int i, j, k;
    i = k = low ; 
    j = mid + 1 ;
    
    //------ comparing and Inserting ------
    while(i<=mid && j<=high) { A[i] < A[j] ? Merged[k++] = A[i++] : Merged[k++] = A[j++] ; }
    
    //------ Inserting left elements in either list ,if any ------
    for (; i <=  mid ; i++) { Merged[k++] = A[i] ; } ;
    for (; j <= high ; j++) { Merged[k++] = A[j] ; } ;
    
    //------ copying from Merged to A ------
    for (int p = low ; p <= high ; p++) { A[p] = Merged[p] ; }
}

void Sort::CountSort(vector<int> &Arr) {
    cout<<"Before Count Sorting : ";
    Display(Arr) ;
    
    int curMax = Arr[0] ;
    for (int i = 1 ; i < Arr.size() ; i++) { if (curMax <= Arr[i]) { curMax = Arr[i]; } }
    
    vector<int> count(curMax+1,0) ; // -- count array --
    for (int i = 0 ; i < Arr.size() ; i++) { count[Arr[i]]++ ; }

    int i = 0 , j = 0 ;
    while (i < count.size()) {
        if (count[i] > 0) { Arr[j++] = i; count[i]--; }
        else { i++; }
    }
    
    cout<<"After count Sorting : ";
    Display(Arr) ;
}

// ---------- Bucket Sort ----------
void Sort::Insert(node **ptrbins , int idx ) {
    node *temp = new node ;
    temp -> value = idx ;
    temp -> next = nullptr ;
    if (ptrbins[idx] == nullptr) {
        ptrbins[idx] = temp ;
    }else{
        node *P = ptrbins[idx] ;
        while (P -> next != nullptr) { P = P -> next ; }
        P->next = temp ;
    }
}

int Sort::Delete(node **ptrbins , int idx) {
    node *P = ptrbins[idx] ;
    ptrbins[idx] = ptrbins[idx] -> next ;
    int x = P -> value ;
    delete P ;
    return x ;
}

void Sort::BinOrBucketSort(vector<int> &Arr) {
    cout<<"\nBefore Bin/Bucket Sorting : ";
    Display(Arr) ;
    
    int curMax = Arr[0] ;
    for (int i = 1 ; i < Arr.size() ; i++) { if (curMax <= Arr[i]){ curMax = Arr[i]; } }
    
    node **Bins ;
    Bins = new node* [curMax + 1] ;
    
    for (int i = 0 ; i < curMax+1 ; i++) { 
        Bins[i] = nullptr ;   // -- Bins array all indices initialised with null --
    }
   
    for (int i = 0 ; i < Arr.size() ; i++) { Insert(Bins,Arr[i]) ; }
    
    // ---------- Testing ----------
    // node *p = new node ;
    // p -> value = 10 ;
    // p -> next = new node ;
    // p -> next -> value = 20 ;
    // p -> next -> next = nullptr ;
    // // Bins[4] = p ;
    // Bins[3] = p ;
    // for(node *p = Bins[3] ; p != nullptr ; p = p -> next) { cout<<p->value<<" "; }
    
    int i = 0 , j = 0 ;
    while (i < curMax+1) {
        while (Bins[i] != nullptr) { Arr[j++] = Delete(Bins,i); }
        i++ ;
    }
    cout<<"After Bin/Bucket Sorting : ";
    Display(Arr) ;
}

// ---------- Radix Sort ----------
void Sort::InsertRadix(node **ptrbins, int value, int idx) {
    node *temp = new node ;
    temp -> value = value ;
    temp -> next = nullptr ;
    if (ptrbins[idx] == nullptr) {
        ptrbins[idx] = temp ;
    }else{
        node *P = ptrbins[idx] ;
        while (P -> next != nullptr) { P = P -> next ; }
        P->next = temp ;
    }
}


void Sort::RadixSort(vector<int> &Arr) {
    cout<<"\nBefore Radix Sorting : ";
    Display(Arr) ;
    
    int curMax = Arr[0] ;
    for (int i = 1 ; i < Arr.size() ; i++) { if (curMax <= Arr[i]){ curMax = Arr[i]; } }
    
    int maxDigits = countDigits(curMax) ;
    
    node **Bins ;
    Bins = new node* [10] ; // Array of pointers to node of size 10 (Radix of decimal)
    
    for (int i = 0 ; i < 10 ; i++) { 
        Bins[i] = nullptr ;   // -- Bins array all indices initialised with null --
    }
    
    for (int pass = 0 ; pass < maxDigits ; pass++) { 
        for (int i = 0 ; i < Arr.size() ; i++) {
            int binIndex = getBinIndex(Arr[i],pass) ;
            InsertRadix(Bins,Arr[i],binIndex) ;
        }
        
        int i = 0;
        int j = 0;
        while (i < 10) {
            while (Bins[i] != nullptr) {
                Arr[j++] = Delete(Bins,i) ;
            }
            i++ ;
        }
        for (int k = 0 ; k < 10 ; k++) { 
            Bins[k] = nullptr ;   // -- Bins array all indices initialised with null --
        }
    }
    delete [] Bins ;
    
    cout<<"After Radix Sorting : ";
    Display(Arr) ;
}

// ---------- Helper Methods ----------
int Sort::partition(vector<int> &Arr, int low, int high) {
    int pivot = Arr[low] ;
    int i = low , j = high ;
    do {
        do{ i++; } while( Arr[i] <= pivot ) ;
        do{ j--; } while( Arr[j] >  pivot ) ;
        if (i < j) {
            int temp = Arr[i] ;
            Arr[i] = Arr[j] ;
            Arr[j] = temp ;
        }
    }while(i < j);
    
    int t = Arr[low] ;
    Arr[low] = Arr[j] ;
    Arr[j] = t ;
    
    return j ; // partitioning index
}

int Sort::countDigits(long long int x) {
    if (x/10 == 0) 
        return 1 ;
    return 1 + countDigits(x/10) ;
}

int Sort::getBinIndex(int x, int idx){
    return (int)(x / pow(10, idx)) % 10;
}

void Sort::Display(vector<int> Arr) {
    for (int i = 0 ; i < Arr.size() ; i++) {
        cout<<Arr[i]<<"  ";
    }cout<<endl;
}

int main(void) {
    Sort S ;
    
    vector<int> Arr1{7,5,2,1,8} ;
    vector<int> Arr2{7,50,20,10,80,5,90} ;
    vector<int> Arr3{7,50,20,10,80,5,90} ;
    vector<int> Arr4{7,50,20,10,80,5,90} ;
    vector<int> Arr5{7,50,20,10,80,5,90} ;
    
    S.BubbleSort(Arr1) ; cout<<endl;
    S.InsertionSort(Arr1) ; cout<<endl;
    S.SelectionSort(Arr1) ; cout<<endl;
    S.Quicksort(Arr2) ; cout<<endl;
    S.MergeSort_iterative(Arr1) ; cout<<endl;
    S.CountSort(Arr3) ; cout<<endl;
    
    cout<<"Before MergeSort recursive Sorting : ";
    S.Display(Arr4) ;
    S.MergeSort_recursive(Arr4,0,Arr4.size()-1) ;
    cout<<"After MergeSort recursive Sorting : ";
    S.Display(Arr4) ;
    
    S.BinOrBucketSort(Arr1) ;
    S.RadixSort(Arr5);
    
    return 0 ;
}























