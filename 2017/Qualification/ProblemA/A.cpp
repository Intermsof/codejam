//Google Code Jam 2017 Qualification Round Problem 1
//Completed April 7 2017
#include <fstream>
#include <string>
#include <iostream>


void run(std::string& s, int k, std::ofstream& ofile, int caseNum);
int main(int argc, char* argv[]){
    if(argc < 3) {
        std::cerr << "Please specify a file input and output name" << std::endl;
        return 1;
    }

    std::ifstream ifile(argv[1]);
    std::ofstream ofile(argv[2]);

    int numOfTestCases;

    ifile >> numOfTestCases;

    std::string s;
    int k;
    for(int i = 0; i < numOfTestCases; i++){
    	ifile >> s >> k;
    	run(s,k,ofile,i+1);
    }

    ifile.close();
    ofile.close();
    return 0;
}

void run(std::string& s, int k, std::ofstream& ofile, int caseNum){
	ofile << "Case #" << caseNum << ": ";
	int result = 0;
	for(int i = 0; i < (int)(s.size() - k + 1); i++){
		if(s[i] == '-'){
			result += 1;
			s[i] = '+';
			for(int i2 = 1; i2 < k; i2++){
				if(s[i + i2] == '-'){
					s[i + i2] = '+';
				}
				else{
					s[i + i2] = '-';
				}
			}
		}
	}
	for(int i = 0; i < (int)s.size(); i++){
		if(s[i] != '+'){
			ofile << "IMPOSSIBLE" << std::endl;
			return;
		}
	}

	ofile << result << std::endl;
	return;
}
