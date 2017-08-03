#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath> 

struct Pancake{
	long R;
	long H;
	long RH;
	int loc;
	Pancake(long r, long h): R(r),H(h),RH(r*h){}
};
struct CompMul
{
	bool operator()(Pancake* i, Pancake* j){
		if(i->RH == j->RH){
			return i->R < j->R;
		}
		return i->RH < j->RH;
	}
};
struct CompRad
{
	bool operator()(Pancake* i, Pancake* j){
		if(i->R == j->R){
			return i->RH < j->RH;
		}
		return i->R < j->R;
	}
};
void run(int caseNum, std::ofstream& ofile,std::vector<Pancake*>& pancakes, int K);
int main(int argc, char** argv){
	if(argc < 3){
		std::cout << "You did not enter an input file or output file name" << std::endl;
		return 1;
	}
	int numTestCases;
	std::ifstream ifile(argv[1]);
	std::ofstream ofile(argv[2]);
	ifile >> numTestCases;
	for(int i = 0; i < numTestCases; ++i){
		int N,K;
		ifile >> N >> K;
		std::vector<Pancake*> pancakes;
		for(int j = 0; j < N; ++j){
			long r, h;
			ifile >> r >> h;
			pancakes.push_back(new Pancake(r,h));
		}
		run(i,ofile,pancakes,K);
	}

	ifile.close();
	ofile.close();
	return 0;
}

void run(int caseNum, std::ofstream& ofile,std::vector<Pancake*>& pancakes,int K){
	std::vector<Pancake*> listTwo(pancakes);
	std::sort(pancakes.begin(),pancakes.end(),CompMul());
	std::sort(listTwo.begin(),listTwo.end(),CompRad());
	for(unsigned i = 0; i < pancakes.size(); ++i){
		pancakes[i]->loc = i;
	}
	Pancake* bottom = listTwo[listTwo.size() - 1];
	int i = 0;
	bool sumMethod = true;
	if(bottom->loc < (int)pancakes.size() - K){
		//search for the most optimal bottom pancake that isn't in the largest set
		for(i = 1; listTwo[listTwo.size() - 1 - i]->loc < (int)pancakes.size() - K; ++i){
			if(2*(listTwo[listTwo.size() - 1 - i]->RH) + 
				(listTwo[listTwo.size() - 1 - i]->R)*(listTwo[listTwo.size() - 1 - i]->R) > 
				2*(bottom->RH) + (bottom->R)*(bottom->R)){
				bottom = listTwo[listTwo.size() - 1 - i];
			}
		}
		//bottom is the one in the largest set
		if(2*(bottom->RH) + (bottom->R)*(bottom->R) < 
			(listTwo[listTwo.size() - 1 - i]->R)*(listTwo[listTwo.size() - 1 - i]->R) 
			+ 2*(pancakes[pancakes.size() - K]->RH) ){

			bottom = listTwo[listTwo.size() - 1 - i];
		}else{
			sumMethod = false;
		}
	}

	double result = M_PI*bottom->R*bottom->R;
	int index = sumMethod ? K : K - 1;
	for(int i = 0; i < index; ++i){
		result += M_PI*2*pancakes[pancakes.size() - i - 1]->RH;
	}
	if(!sumMethod){
		result += M_PI*2*bottom->RH;
	}

	ofile << "Case #" << caseNum + 1 << ": " << std::setprecision(25) << result << std::endl;
	for(unsigned i = 0; i < pancakes.size(); ++i){
		delete pancakes[i];
	}	
	
}