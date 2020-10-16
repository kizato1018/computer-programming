#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Matrix{
public:
    Matrix() : row_num_(0), col_num_(0), non_zero_(0) {}
    Matrix(const Matrix &m) : row_num_(m.row_num_), col_num_(m.col_num_), non_zero_(m.non_zero_), data_(m.data_) {}
    Matrix& operator = (const Matrix&);
    Matrix operator + (const Matrix&);
    Matrix operator * (const Matrix&);
    
    int Row_num() const {return row_num_;}
    int Col_num() const {return col_num_;}
    int Non_zero() const {return non_zero_;}
    void Create();
    Matrix Transpose() const;
    void Submatrix(const bool [], const bool []);
    Matrix Pow(int) const;
    void Show();
    
private:
    int row_num_;
    int col_num_;
    int non_zero_;
    vector<array<int, 3> > data_;
    void Sort();
};
map<string, Matrix> M;

void Matrix::Sort() {
    sort(data_.begin(), data_.end(), [](const array<int, 3> a, const array<int, 3> b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); } );
}

Matrix& Matrix::operator = (const Matrix& m) {
    row_num_ = m.row_num_;
    col_num_ = m.col_num_;
    non_zero_ = m.non_zero_;
    data_ = m.data_;
    return *this;
}

Matrix Matrix::operator + (const Matrix& m) {
    Matrix tmp(*this);
    auto it = tmp.data_.begin();
    auto end = tmp.data_.end();
    vector<array<int, 3> > vtmp;
    for(auto mit = m.data_.begin(); mit != m.data_.end(); ++mit) {
        while(it+1 != end && (*it)[0] < (*mit)[0]) ++it;
        while(it+1 != end && (*it)[0] == (*mit)[0] && (*it)[1] < (*mit)[1]) ++it;
        if((*it)[0] == (*mit)[0] && (*it)[1] == (*mit)[1]) {
            (*it)[2] += (*mit)[2];
        }
        else {
            vtmp.push_back(*mit);
            ++tmp.non_zero_;
        }
        
    }
    for(auto i = vtmp.begin(); i != vtmp.end(); ++i) {
        tmp.data_.push_back(*i);
    }
    tmp.Sort();
    return tmp;
}

Matrix Matrix::operator * (const Matrix& m) {
    Matrix result, m2(m.Transpose());
    result.row_num_ = row_num_;
    result.col_num_ = m2.row_num_;
    auto rstart = data_.begin();
    auto rend = rstart;
    while(rstart != data_.end()) {
        while(rend != data_.end() && (*(rend))[0] == (*rstart)[0]) ++rend;
        int cur_c = 0;
        int sum = 0;
        for(auto cit = m2.data_.begin(); cit != m2.data_.end(); ++cit) {
            for(auto rit = rstart; rit != rend; ++rit) {
                if((*cit)[0] != cur_c) {
                    if(sum != 0) {
                        result.data_.push_back({(*rstart)[0], cur_c, sum});
                        auto p = result.data_.back();
                    }
                    cur_c = (*cit)[0];
                    sum = 0;
                }
                if((*rit)[1] < (*cit)[1]) continue;
                else if((*rit)[1] > (*cit)[1]) break;
                else {
                    sum += (*rit)[2] * (*cit)[2];
                    break;
                }
            }
        }
        if(sum != 0) {
            result.data_.push_back({(*rstart)[0], cur_c, sum});
            auto p = result.data_.back();
        }

        rstart = rend;
    }
    result.non_zero_ = result.data_.size();
    
    return result;
}

void Matrix::Create() {
    cout << "how many rows: ";
    cin >> row_num_;
    cout << "how many columns: ";
    cin >> col_num_;
    cout << "how many non-zero elements: ";
    cin >> non_zero_;
    cout << "enter the elements (format: 0 0 0):" << endl;
    for(int i = 0; i < non_zero_; ++i) {
        array<int, 3> data;
        cin >> data[0] >> data[1] >> data[2];
        data_.push_back(data);
    }
    Sort();
    return;
}

void Matrix::Submatrix (const bool row[], const bool col[]) {
    auto it = data_.begin();
    for(int i = 0; i < row_num_; ++i) {
        if(!row[i]) continue;
        for(int j = 0; j < col_num_; ++j) {
            if(!col[j]) continue;
            while((*it)[0] < i) ++it;
            while((*it)[0] == i && (*it)[1] < j) ++it;
            if((*it)[0] == i && (*it)[1] == j)
                cout << (*it)[2] << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    return;
}

void Matrix::Show() {
    auto it = data_.begin();
    for(int i = 0; i < row_num_; ++i) {
        for(int j = 0; j < col_num_; ++j) {
            if(it != data_.end() && (*it)[0] == i && (*it)[1] == j) {
                cout << (*it)[2] << " ";
                ++it;
            }
            else
                cout << "0 ";
        }
        cout << endl;
    }
    return;
}

Matrix Matrix::Transpose() const { 
    Matrix tmp(*this);
    int index[col_num_+1] = {0};
    int i = 0;
    int cnt = 0;
    for(auto it : data_) 
        ++index[it[1]+1];
    for(int i = 0; i < col_num_; ++i) {
        index[i] += cnt;
        cnt = index[i];
    }
    for(auto it = data_.begin(); it != data_.end(); ++it) {
        tmp.data_[index[(*it)[1]]] = {(*it)[1], (*it)[0], (*it)[2]};
        ++index[(*it)[1]];
    }
    swap(tmp.col_num_, tmp.row_num_);
    return tmp;
}

Matrix Matrix::Pow(int n) const {
    Matrix result, base(*this);
    bool first = true;
    while(n) {
        if(n%2) {
            if(first) {
                result = base;
                first = false;
            }
            else 
                result = result * base;
        }
        base = base * base;
        n /= 2;
    }
    result.non_zero_ = result.data_.size();
    return result;
}

void New_Matrix() {
    string name;
    cout << "Enter matrix name." << endl;
    cin >> name;
    Matrix m;
    m.Create();
    M[name] = Matrix(m);
    M[name].Show();
    return;
}


void Show() {
    string name;
    cout << "Enter matrix name." << endl;
    cin >> name;

    if(M.find(name) != M.end())
        M[name].Show();
    else
        cout << "no this matrix." << endl;
    return;
}

void Transpose() {
    string name;
    cout << "Enter matrix name." << endl;
    cin >> name;
    if(M.find(name) != M.end()) {
        M[name] = M[name].Transpose();
        M[name].Show();
    }
    else
        cout << "no this matrix." << endl;
    return;
}

void Submatrix() {
    string name;
    cout << "Enter matrix name." << endl;
    cin >> name;
    int rn;
    int cn;
    int r;
    int c;
    bool row[M[name].Row_num()] = {0};
    bool col[M[name].Col_num()] = {0};
    while(1) {
        cout << "How many row in submatrix: ";
        cin >> rn;
        if(rn <= M[name].Row_num()) break;
        cout << "Error! submatrix's row can't bigger original matrix." << endl;
    }
    while(1) {
        cout << "How many column in submatrix: ";
        cin >> cn;
        if(cn <= M[name].Row_num()) break;
        cout << "Error! submatrix's column can't bigger original matrix." << endl;
    }
    cout << "Enter row index 0~" << M[name].Row_num()-1 << ": ";
    for(int i = 0; i < rn; ++i) {
        int r;
        while(1) {
            cin >> r;
            if(r < 0 || r >= M[name].Row_num()) {
                cout << "Error! out of range!" << endl;
            }
            else if(row[r]) {
                cout << "Error! Can't enter reapeat number." << endl;
            }
            else break;
        }
        row[r] = true;
    }
    cout << "Enter column index 0~" << M[name].Col_num()-1 << ": ";
    for(int i = 0; i < cn; ++i) {
        int c;
        while(1) {
            cin >> c;
            if(c < 0 || c >= M[name].Col_num()) {
                cout << "Error! out of range!" << endl;
            }
            else if(col[c]) {
                cout << "Error! Can't enter reapeat number." << endl;
            }
            else break;
        }
        col[c] = true;
    }
    M[name].Submatrix(row, col);
    return;
}

void Add() {
    string m1, m2 ,result;
    cout << "Enter M1 name: ";
    cin >> m1;
    cout << "Enter M2 name: ";
    cin >> m2;
    cout << "Enter result name: ";
    cin >> result;
    if(M[m1].Row_num() != M[m2].Row_num() || M[m1].Col_num() != M[m2].Col_num()) {
        cout << "Error! Incompatible matrices." << endl;
        return; 
    }
    M[result] = (M[m1] + M[m2]);
    M[result].Show();
    return;
}

void Mult() {
    string m1, m2 ,result;
    cout << "Enter M1 name: ";
    cin >> m1;
    cout << "Enter M2 name: ";
    cin >> m2;
    if(M[m1].Col_num() != M[m2].Row_num()) {
        cout << "Error! Incompatible matrices." << endl;
        return; 
    }
    cout << "Enter result name: ";
    cin >> result;
    M[result] = (M[m1] * M[m2]);
    M[result].Show();
    return;
}

void Pow() {
    string m1,result;
    int n;
    cout << "Enter M1 name: ";
    cin >> m1;
    if(M[m1].Col_num() != M[m1].Row_num()) {
        cout << "Error! Incompatible matrices." << endl;
        return; 
    }
    cout << "n = ";
    cin >> n;
    cout << "Enter result name: ";
    cin >> result;
    M[result] = M[m1].Pow(n);
    M[result].Show();
    return;
}

void ListMatrix() {
    printf("Matrices List:\n");
    for(auto it = M.begin(); it != M.end(); ++it)
        printf("%s %d %d %d\n", (*it).first.c_str(), (*it).second.Row_num(), (*it).second.Col_num(), (*it).second.Non_zero());
    return;
}

int main() {
    bool exit = false;
    while(!exit) {
        int c;
        cout << "1) Enetr Matrix" << endl;
        cout << "2) show Matrix" << endl;
        cout << "3) Transpose Matrix" << endl;
        cout << "4) Show Submatrix" << endl;
        cout << "5) Matrix addition" << endl;
        cout << "6) Matrix multiplication" << endl;
        cout << "7) Matrix power" << endl;
        cout << "0) exit" << endl;
        cin >> c;
        switch (c) {
        case 1:
            New_Matrix();
            break;
        case 2:
            ListMatrix();
            Show();
            break;
        case 3:
            ListMatrix();
            Transpose();
            break;
        case 4:
            ListMatrix();
            Submatrix();
            break;
        case 5:
            ListMatrix();
            Add();
            break;
        case 6:
            ListMatrix();
            Mult();
            break;
        case 7:
            ListMatrix();
            Pow();
            break;
        case 0:
            exit = true;
            break;
        default:
            cout << "Error! No this option!" << endl;
            break;
        }
    }
    return 0;
}
/*
Apple
5
9
11
4 8 11
2 7 7
4 6 5
0 2 1
1 2 10
2 1 2
3 4 3
1 5 4
2 3 6
4 0 8
0 6 9


   0  1  2  3  4  5  6  7  8
----------------------------
0| 0  0  1  0  0  0  9  0  0
1| 0  0 10  0  0  4  0  0  0
2| 0  2  0  6  0  0  0  7  0
3| 0  0  0  0  3  0  0  0  0
4| 8  0  0  0  0  0  5  0 11


M1
3 5 4
0 0 1
1 0 2
0 1 3
2 2 -1

1  3  0  0  0
2  0  0  0  0
0  0 -1  0  0

M2
3 5 4
2 2 10
0 0 2
1 4 8
1 0 -3

2  0  0  0  0
-3  0  0  0  8
0  0 10  0  0




*/