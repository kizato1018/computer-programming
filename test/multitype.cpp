#include <iostream>
using namespace std;

template <typename T>

struct Node {
    Node();
    Node(T d): data(d) {}
    T data;
    Node* next;
    Node* prev;
};

template <typename TL>
class Linklist {
public:
    Linklist():head(nullptr) {}
    void push_back(TL data);
    void Show();
private:
    Node <TL>* head;
};

template <typename TL>
void Linklist<TL>::Show() {
    if(head == nullptr) return;
    Node <TL>* cur = head;
    do {
        cout << cur->data << " ";
        cur = cur->next;
    }while(cur != head);
    cout << endl;
    return;
}

template <typename TL>
void Linklist<TL>::push_back(TL data) {
    Node <TL> *tmp = new Node<TL>(data);
    if(head == nullptr) {
        head = tmp; 
        head->next = head;
        head->prev = head;
    }
    else {
        head->prev->next = tmp;
        tmp->prev = head->prev;
        head->prev = tmp;
        tmp->next = head;
    }
}



int main() {
    Linklist <int> l_int;
    Linklist <char> l_ch;
    for(int i = 0; i < 10; ++i) {
        l_int.push_back(i);
        l_ch.push_back(i+'A');
    }
    l_int.Show();
    l_ch.Show();

}