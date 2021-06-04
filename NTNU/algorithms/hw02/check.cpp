#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 200000

using namespace std;

int Sort(int arr[], int n) {
    bool sorted = false;
    int counter = 0;
    while(!sorted) {
        sorted = true;
        for(int i = 0; i < n-2; i++) {
            if(arr[i] > arr[i+2]) {
                sorted = false;
                reverse(arr+i, arr+i+3);
                counter++;
            }
        }
    }
    cout << counter;
    return counter;
}

int main() {
    int n;
    int arr[N] = {};
    int cnt, ans;
    bool flag = true, correct = false;
    string s;
    cin >> n;
    cout << n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> s;
    cin >> cnt;
    ans = Sort(arr, n);
    for(int i = 0; i < n-1; i++)
        if(arr[i] > arr[i+1])
            flag = false;
    if((s == "Yes" && flag == true) || (s == "No" && flag == false)) {
        if(ans == cnt) {
            correct = true;
        }
    }
    if(correct) cout << "Accept" << endl;
    else cout << "Wrong Answer" << endl;
}