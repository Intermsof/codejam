#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Horse{
	int K;
	int S;
	double t;
	Horse(int k, int s, int& D):K(k),S(s){
		t = (double)(D - K)/(double)S;
	}
};
struct Comp{
	bool operator()(Horse* i, Horse* j){
		return i->K < j->K;
	}
};
void run(int caseNum, std::ofstream& ofile, std::vector<Horse*> horses, int D);
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
		int D, N;
		ifile >> D >> N;
		std::vector<Horse*> horses;
		for(int j = 0; j < N; ++j){
			int k, s;
			ifile >> k >> s;
			horses.push_back(new Horse(k,s,D));
		}
		run(i,ofile,horses,D);
	}

	ifile.close();
	ofile.close();
	return 0;
}

void run(int caseNum, std::ofstream& ofile, std::vector<Horse*> horses, int D){
	Comp mycomp;
	std::sort(horses.begin(), horses.end(),mycomp);
	Horse* jamCausingHorse = horses[0];
	for(unsigned i = 1; i < horses.size(); ++i){
		if(horses[i]->t > jamCausingHorse->t){
			jamCausingHorse = horses[i];
		}
	}
	double result = ((double)D)/((double)(jamCausingHorse->t));
	ofile << "Case #" << caseNum + 1 << ": " << std::setprecision(20) << result << std::endl;
}