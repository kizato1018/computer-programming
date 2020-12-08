#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int edge[] = {0,1,2,3,4,5,6,7,8,9};

class cmp {
    bool reverse;
public:
    cmp(const bool& revparam = false) {reverse = revparam;}
    bool operator() (const int& lhs, const int& rhs) const {
        if(reverse) return (edge[lhs] > edge[rhs]);
        else return (edge[lhs] < edge[rhs]);
    }
};

int main() {
    priority_queue<int, vector<int>, cmp> pq;
    for(int i = 0; i < 10; ++i) {
        pq.push(i);
        i = 9 - i;
    }
    for(int i = 0; i < 10; ++i) {
        cout << pq.top() << " ";
        pq.pop();
    }
}
