#include <bits/stdc++.h>

using namespace std;

int main() {
	int guess;
	int Max = 11, Min = -1;
	bool honest = true;
	while(cin >> guess && guess) {
		string s, buffer;
		getline(cin, buffer);
		getline(cin, s);
		//printf("%d %d\n", Min, Max);
		if(s == "too high") {
			//printf("h\n");
			if(guess < Min) honest = false;
			else Max = min(Max, guess);
			//else Max = guess;
		}
		else if(s == "too low") {
			//printf("l\n");
			if(guess > Max) honest = false;
			else Min = max(Min, guess);
			//else Min = guess;
		}
		else if(s == "right on") {
			//printf("r\n");
			if(guess >= Max || guess <= Min) honest = false;
			if(honest)
				printf("Stan may be honest\n");
			else
				printf("Stan is dishonest\n");
			Max = 11;
			Min = -1;
			honest = true;
		}
	}
}