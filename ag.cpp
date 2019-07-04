#include <bits/stdc++.h>
using namespace std;

#define POP_SIZE 150
#define MUTATION_RATE 0.1
#define CROSSOVER_RATE 0.8
#define OFFSPRING_SIZE (POP_SIZE * CROSSOVER_RATE)
#define MAX_ITERATIONS 1000

typedef vector<bool> chromossome;

typedef uniform_int_distribution<int> UIDist;
typedef uniform_real_distribution<double> UDDist;

default_random_engine gen;

struct individual {
	chromossome genes;
	long fit;
};

struct ind_comparator{
    bool operator()(individual a, individual b) {
        return b.fit < a.fit;
    }
};

ind_comparator comparator;

typedef vector<individual> population;

UIDist rndInt;
UIDist rndPop(0, POP_SIZE - 1);
UDDist uniform(0, 1);

population pop;
vector<long> numbers;
vector<long> fitness;
int IND_SIZE;

long objective_function(const chromossome& c) {
	long A, B;
	A = B = 0;	
	for (int i = 0; i < IND_SIZE; ++i) {
		if (c[i])
			A += numbers[i];
		else
			B += numbers[i];
	}

	return abs(A - B);
}

void mutation(individual& ind) {
	for (int i = 0; i < IND_SIZE; ++i)
		if ((1 - uniform(gen)) <= MUTATION_RATE) 
			ind.genes[i] = !ind.genes[i];
	ind.fit = objective_function(ind.genes);
}

pair<individual, individual> crossover(const individual& ind1, const individual& ind2) {
	int part = rndInt(gen);
    if (part > IND_SIZE)
        throw "FUCK";
	chromossome f1, f2;
	//f1.assign(IND_SIZE, 0);
	//f2.assign(IND_SIZE, 0);
	cout << "SIZEEEEE1 " << ind1.genes.size() << endl;
	cout << "SIZEEEEE2 " << ind2.genes.size() << endl;
	for	(int i = 0; i < part; ++i) {
		f1.push_back(ind1.genes[i]); //[i] = ind1.genes[i];
		f2.push_back(ind2.genes[i]); //[i] = ind2.genes[i];
	}

	for (int i = part; i < IND_SIZE; ++i) {
		f1.push_back(ind2.genes[i]);//[i] = ind2.genes[i];
		f2.push_back(ind1.genes[i]);//[i] = ind1.genes[i];
	}
	individual son1 = {f1, 0};
	individual son2 = {f2, 0};

	return make_pair(son1, son2);
}

individual select(const vector<individual>& pop) {
	individual best = pop.front();
	individual selected;
	do {
		selected = pop[rndPop(gen)];
	} while(uniform(gen) >= selected.fit/(double)best.fit);

	return selected;
}

individual initialize() {
	chromossome c;
	c.assign(IND_SIZE, 0);
	for (int i = 0; i < IND_SIZE; ++i) {
		if (uniform(gen) > 0.5) 
			c[i] = true;
		else
			c[i] = false;
	}

	individual ind = {c, objective_function(c)};
	return ind;
}

individual AG() {
	pop.clear();
	
	for (int i = 0; i < POP_SIZE; ++i)
		pop.push_back(initialize());

	sort(pop.begin(), pop.end(), comparator);
	int it = 0;
	while(it < MAX_ITERATIONS) {
		for (int i = 0; i < OFFSPRING_SIZE; ++i) {
			individual father1 = select(pop), father2 = select(pop);
			pair<individual, individual> offspring = crossover(father1, father2);
		    mutation(offspring.first);
		    mutation(offspring.second);
		    
			pop.push_back(offspring.first);
			pop.push_back(offspring.second);
		}

		sort(pop.begin(), pop.end(), comparator);
		pop.resize(POP_SIZE);
		it++;
	}

	return pop.front();
}

int main() {
	int n,x;
		
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	gen = default_random_engine(seed);
    uniform(gen);
	cin >> n;

	for (int i = 0; i < n; ++i){
		cin >> x;
		numbers.push_back(x);
	} 

	IND_SIZE = n;
	rndInt = UIDist(0, IND_SIZE);

	individual best = AG();
	cout << best.fit << endl;
	return 0;
}
