#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <math.h>

using namespace std;

#define EXP 2.7182
#define TEMPERATURE 10

vector<bitset<5> > vector_cromosomes;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis_range(0, 31);
uniform_int_distribution<> dis_create(1, 4);

void create_p()
{
	int i=2;
	for( ; i>0 ; --i)
		vector_cromosomes.push_back(bitset<5>(dis_range(gen)));
}

void print()
{	
	for(auto &c : vector_cromosomes)
		cout << c << "(" << c.to_ulong() << ")   ";
	cout << endl;
}

void mutate(int index)
{
	vector<int> values = { 0,0,1,1,2,2,3,3,4,4,5,5 };
	vector<float> weights =  {  0.40, 0, 0.30, 0,  0.15, 0, 0.10, 0, 0.05};
	piecewise_constant_distribution<> d(values.begin(), values.end(), weights.begin());
	int pos_mutation = d(gen);
	vector_cromosomes[index][pos_mutation] = !vector_cromosomes[index][pos_mutation];
}

void reproduce(int index)
{
	vector<int> values = { 0,0,1,1,2,2,3,3,4,4,5,5 };
	vector<float> weights =  {  0.40, 0, 0.30, 0,  0.15, 0, 0.10, 0, 0.05};
	piecewise_constant_distribution<> d(values.begin(), values.end(), weights.begin());
	
	int pos_reproduce = d(gen);

	for(int i = 0 ; i<pos_reproduce ;++i)
		vector_cromosomes[index][i] = vector_cromosomes[!index][i];
}

int probability(int A, int B)
{
	float sum = 0.0;
	sum = pow(EXP, A/TEMPERATURE) + pow(EXP, B/TEMPERATURE); 
	vector<float> values = { 0,0,1,1 };
	vector<float> weights =  {  pow(EXP, A/TEMPERATURE)/sum,  0, pow(EXP, B/TEMPERATURE)/sum};

	piecewise_constant_distribution<> d(values.begin(), values.end(), weights.begin());
	int m = d(gen);

	return m;
}

int main()
{
		
	create_p();
	int n_iterations = 100;
	while(--n_iterations)
	{
		int i = probability(vector_cromosomes[0].to_ulong(), vector_cromosomes[1].to_ulong());
		reproduce(i);
		mutate(!i);
		print();
	}
	return 1;
}