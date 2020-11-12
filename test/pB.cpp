#include <bits/stdc++.h>

using namespace std;

struct Block{
    bool fill;
    int value;
    int pos_cnt;
    bool pos_num[25];
}matrix[25][25];
int N;

void inputMatrix()
{
	int num;
	vector<int> inputs;
	cin >> num;
	inputs.push_back(num);
	while (cin.get() != '\n')
	{
		cin >> num;
		inputs.push_back(num);
	}
	N = inputs.size();
	for (int i = 0; i < N; i++)
		matrix[0][i] = inputs[i];
	for (int i = 1; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> matrix[i][j].value;
            matrix[i][j].fill = true;
        }
}

int main() {

}