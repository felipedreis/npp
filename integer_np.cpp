#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

typedef std::chrono::high_resolution_clock CLOCK;
typedef std::chrono::duration<float> fsec;

vector<long> numbers;
vector< vector<int> > memo;
vector<int> setA, setB;
int sumA = 0, sumB = 0;

/**
long dp(int i, long capacity) {
    if (capacity < 0)
        return INF;
    if(i == numbers.size())
        return capacity;
        
    memo[i][capacity] = min(dp(i + 1, abs(capacity - numbers[i])), dp(i + 1,capacity));
    
    return memo[i][capacity];
}
**/

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
	        setA.push_back(numbers[i]);
	        currentCap -= numbers[i];
	    } else {
	        setB.push_back(numbers[i]);
	    }
	}

	return memo[0][capacity];
}

int main(int argc, char ** argv) {
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
	
	cout << n << " " << res << ", " << elapsed.count() << endl;
	
	string ansfile(argv[1]);
	ansfile = "int_" + ansfile + "_pd.out";
	fstream f(ansfile, fstream::out);
	
    sort(setA.begin(), setA.end());
    sort(setB.begin(), setB.end());
	
	f << setA.size() << " " << sumA << endl; 
	for (auto i : setA) {
	    f << i << " ";
	}
	f << endl;
	
	f << setB.size() << " " << sumB << endl; 
	for (auto i : setB) {
	    f << i << " ";
	}
	
	f << endl;
	return 0;	
}
