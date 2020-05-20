#include <iostream>
using namespace std;


// TODO: function template print()
template<typename T>
void print(const T *begin, const T *end) {
    int i = 0;
    while (begin+i != end)
    {
        cout << begin[i] << " ";
        ++i;
    }
    return;
}


// TODO: function template min_element()
template<typename T>
const T *min_element(const T *begin, const T *end) {
    int i = 1;
    int Min = 0;
    while(begin+i != end) {
        if(begin[Min] > begin[i])
            Min = i;
        ++i;
    }
    return begin+Min;
}


int main ()
{
    int i[3] = {3, 1, 2};
    double d[5] = {5.4, 3.2, 1.2, 4.5, 5.6};
    char c[4] = {'S', 'I', 'E', 'C'};

    print(i, i+3); cout << endl;  // T = int
    print(d, d+5); cout << endl;  // T = double
    print(c, c+4); cout << endl;  // T = char

//    print(i, 3); // error!

    cout << *min_element(i, i+3) << endl;
    cout << *min_element(d, d+5) << endl;
    cout << *min_element(c, c+sizeof(c)/sizeof(c[0])) << endl;
}
