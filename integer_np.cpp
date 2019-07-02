#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

vector<long> numbers;
vector< vector<bool> > memo;

long dp(int i, long capacity) {
	if (i >= numbers.size())
		return -INF;
	if (capacity < 0)
		return -INF;

	if (memo[i][capacity] != -INF)
		return memo[i][capacity];

	long with =  1 + dp(i + 1, capacity - numbers[i]);
	long without = dp(i + 1, capacity);
	
	if (with > without)
		return memo[i][capacity] = with;
	else 
		return memo[i][capacity] = without; 
} 

long iterative_dp(long n, long capacity) {

	memo.assign(capacity + 1, vector<bool>());	
	memo[0].assign(n + 1, true);
		
	for (int i = 1; i < memo.size(); ++i) {
		memo[i].assign(n + 1, 0);
		memo[i][0] = true;
	}
	memo[0][0] = false;

	for (int i = 1; i < capacity; ++i) {
		for (int j = 1; j < n; ++j) {
			if(i - numbers[j] >= 0)
				memo[i][j] = memo[i][j-1] || memo[i - numbers[j]][j - 1];
			else
				memo[i][j] = memo[i][j-1];
		}
	}
	cout << memo[capacity].size() << endl;
//		<< memo[capacity][1].size() << endl;


	return memo[capacity][n];
}

int main() {
	long n, sum = 0, x;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x;
		numbers.push_back(x);
		sum += x;
	}

	long capacity = sum/2;

	long res = iterative_dp(n, capacity);
	cout << res << endl;
	return 0;	
}
