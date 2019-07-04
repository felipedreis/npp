#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

typedef std::chrono::high_resolution_clock CLOCK;
typedef std::chrono::duration<float> fsec;

vector<long> numbers;
vector< vector<bool> > memo;

long iterative_dp(long n, long capacity) {

	memo.assign(capacity + 1, vector<bool>());	
	memo[0].assign(n + 1, true);
		
	for (int i = 1; i < memo.size(); ++i) {
		memo[i].assign(n + 1, false);
	}

	for (int i = 1; i <= capacity; ++i) {
		for (int j = 1; j <= n; ++j) {
			if(i - numbers[j] >= 0)
				memo[i][j] = memo[i][j-1] || memo[i - numbers[j]][j - 1];
			else
				memo[i][j] = memo[i][j-1];
		}
	}

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
	auto start = CLOCK::now();
	long res = iterative_dp(n, capacity);
	auto end = CLOCK::now();

	fsec elapsed = end - start;

	cout << elapsed.count() << endl;
	return 0;	
}
