#include <iostream>
#include <deque> 
using namespace std;
#include <vector>
#include <algorithm>

void printKMax(int arr[], int n, int k) {
    deque<int> deq;

    for ( int i = 0; i < n; ++i )
    {
        int value = arr[i];

        while (!deq.empty() && value > deq.back())
            deq.pop_back();

        deq.push_back(value);

        if (i >= k && deq.front() == arr[i - k] )
            deq.pop_front();

        if ( i >= k - 1)
        {
            if (i >= k)
                cout << " ";

            cout << deq.front();
        }        
    }
    cout << endl;
}

/*
int main() {

    int t;
    cin >> t;
    while (t>0) {
        int n, k;
        cin >> n >> k;
        int i;
        vector<int> arr;
        arr.resize(n);
        for (i = 0; i<n; i++)
            cin >> arr[i];
        printKMax(arr.data(), n, k);
        t--;
    }
    return 0;
}*/