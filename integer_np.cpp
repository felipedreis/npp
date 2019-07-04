#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

typedef std::chrono::high_resolution_clock CLOCK;
typedef std::chrono::duration<float> fsec;

vector<long> numbers;
vector< vector<int> > memo;
vector<int> setA, setB;

long dp(int i, long capacity) {
    printf("%d, %d\n", i, capacity);
    if (capacity < 0)
        return INF;
    if(i == numbers.size())
        return capacity;
        
    memo[i][capacity] = min(dp(i + 1, abs(capacity - numbers[i])), dp(i + 1,capacity));
    
    return memo[i][capacity];
}

long iterative_dp(long n, long capacity) {
    printf("%d\n", capacity);
	memo.assign(n + 1, vector<int>());	
	memo[n].assign(capacity + 1, 0);
	for (int i = 0; i <= capacity; ++i) {
		memo[n][i] = i;
	}
	for (int i = 0; i < n; ++i) {
		memo[i].assign(capacity + 1, 0);
	}

	for (int i = n - 1; i >= 0; --i) {
		for (int j = capacity; j >= 1; --j) {
			memo[i][j] = min(memo[i + 1][j],memo[i + 1][abs(j - numbers[i])]);
			
		}
	}
	
	int currentCap = capacity;
	for (int i = 0; i < n; ++i){
	    if(memo[i][currentCap] != memo[i + 1][currentCap]){
	        ans.push_back(numbers[i]);
	        currentCap -= numbers[i];
	    }
	}

	return memo[0][capacity];
}

int main() {
	long n, sum = 0, x;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x;
		numbers.push_back(x);
		sum += x;
	}
	long capacity = ceil(sum/2.0);

	auto start = CLOCK::now();
	long res = iterative_dp(n, capacity);
	auto end = CLOCK::now();

	fsec elapsed = end - start;
	
    sort(ans.begin(), ans.end());
    
	cout << n << " " << res << ", " << elapsed.count() << endl;
	
	for (auto i : ans) {
	    cout << i << " ";
	}
	cout << endl;
	return 0;	
}
