#include<bits/stdc++.h>
using namespace std;

struct grid
{
	int value;
	vector<int> mayNum;
};

grid matrix[25][25] = { 0 };
int N;
vector<pair<int, int>> emptyPos;
int emptyNum = 0;

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
		matrix[0][i].value = inputs[i];
	for (int i = 1; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j].value;
}
void printMatrix()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << matrix[i][j].value << " ";
		}
		cout << endl;
	}
}
int getBlcok(int row, int col)
{
	int n = sqrt(N);
	int r = row / n;
	int c = col / n;
	return r * n + c;
}
void getNum(int row, int col, vector<int> rowVec, vector<int> colVec, vector<int> blockVec)
{
	bool rowNum[25] = { false };
	bool colNum[25] = { false };
	bool blockNum[25] = { false };

	for (int i = 0; i < rowVec.size(); i++)
		rowNum[rowVec[i] - 1] = true;
	for (int i = 0; i < colVec.size(); i++)
		colNum[colVec[i] - 1] = true;
	for (int i = 0; i < blockVec.size(); i++)
		blockNum[blockVec[i] - 1] = true;

	for (int i = 0; i < N; i++)
		if (rowNum[i] && colNum[i] && blockNum[i])
			matrix[row][col].mayNum.push_back(i + 1);
}
void check()
{
	vector<int> rowVec[25];
	vector<int> colVec[25];
	vector<int> blockVec[25];

	//row
	for (int i = 0; i < N; i++)
	{
		bool checkRow[25] = { false };
		for (int j = 0; j < N; j++)
		{
			int value = matrix[i][j].value - 1;
			if (value < 0)
				continue;
			checkRow[value] = true;
		}
		for (int j = 0; j < N; j++)
		{
			if (!checkRow[j])
				rowVec[i].push_back(j + 1);
		}
	}
	//colume
	for (int j = 0; j < N; j++)
	{
		bool checkCol[25] = { false };
		for (int i = 0; i < N; i++)
		{
			int value = matrix[i][j].value - 1;
			if (value < 0)
				continue;
			checkCol[value] = true;
		}
		for (int i = 0; i < N; i++)
		{
			if (!checkCol[i])
				colVec[j].push_back(i + 1);
		}
	}
	// block
	for (int block = 0; block < N; block++)
	{
		int n = sqrt(N);
		bool check[25] = { false };
		int rowStart = (block / n) * n;
		int colStart = (block % n) * n;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int value = matrix[i + rowStart][j + colStart].value - 1;
				if (value < 0)
					continue;
				check[value] = true;
			}
		}
		for (int i = 0; i < N; i++)
		{
			if (!check[i])
				blockVec[block].push_back(i + 1);
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (matrix[i][j].value == 0)
			{
				emptyNum++;
				emptyPos.push_back(pair<int, int>(i, j));
				int b = getBlcok(i, j);
				getNum(i, j, rowVec[i], colVec[j], blockVec[b]);
			}
	sort(emptyPos.begin(), emptyPos.end(), [](pair<int, int> pos1, pair<int, int>pos2) {return matrix[pos1.first][pos1.second].mayNum.size() < matrix[pos2.first][pos2.second].mayNum.size(); });
}
void findAns(int index, int emptyNum, vector<pair<int, int>> emptyPos, int& times)
{
	if (index == emptyNum)
	{
		printMatrix();
		times++;
		return;
	}
	int row = emptyPos[index].first;
	int col = emptyPos[index].second;
	int block = getBlcok(row, col);

	if (matrix[row][col].mayNum.size() == 0)	return;

	for (int i = 0; i < matrix[row][col].mayNum.size(); i++)
	{
		int val = matrix[row][col].mayNum[i];
		vector<int>::iterator iter;
		vector<pair<int, int>> delPos;
		for (int j = 0; j < N; j++)
		{
			if (matrix[row][j].value == 0)
			{
				iter = find(matrix[row][j].mayNum.begin(), matrix[row][j].mayNum.end(), val);
				if (iter != matrix[row][j].mayNum.end())
				{
					delPos.push_back(pair<int, int>(row, j));
					matrix[row][j].mayNum.erase(iter);
				}
					
			}
		}
		for (int i = 0; i < N; i++)
		{
			if (matrix[i][col].value == 0)
			{
				iter = find(matrix[i][col].mayNum.begin(), matrix[i][col].mayNum.end(), val);
				if (iter != matrix[i][col].mayNum.end())
				{
					delPos.push_back(pair<int, int>(i, col));
					matrix[i][col].mayNum.erase(iter);
				}
			}
		}
		int n = sqrt(N);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (matrix[block+i][block+j].value == 0)
				{
					iter = find(matrix[block + i][block + j].mayNum.begin(), matrix[block + i][block + j].mayNum.end(), val);
					if (iter != matrix[block + i][block + j].mayNum.end())
					{
						delPos.push_back(pair<int, int>(block + i, block + j));
						matrix[block + i][block + j].mayNum.erase(iter);
					}
				}
			}
		}

		matrix[row][col].value = val;
		findAns(index + 1, emptyNum, emptyPos, times);
		matrix[row][col].value = 0;

		for (int i = 0; i < delPos.size(); i++)
		{
			matrix[delPos[i].first][delPos[i].second].mayNum.push_back(val);
		}
	}
}
int main()
{
	int times = 0;
	inputMatrix();
	puts("-------------------");
	printMatrix();
	check();
	findAns(0, emptyNum, emptyPos, times);
	return 0;
}