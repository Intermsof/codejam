//Google Code Jam 2017 Qualification Round Problem 2
//Completed April 7 2017
#include <fstream>
#include <string>
#include <iostream>
#include <deque>


void run(std::string& s, std::ofstream& ofile, int caseNum);
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
    for(int i = 0; i < numOfTestCases; i++){
    	ifile >> s;
    	run(s,ofile,i+1);
    }

    ifile.close();
    ofile.close();
    return 0;
}

void run(std::string& s, std::ofstream& ofile, int caseNum){
    ofile << "Case #" << caseNum << ": ";
    std::deque<bool> sameChecker;
    for(int i = 0; i < (int)(s.size() - 1); i++){
        if(s[i] == s[i+1]){
            sameChecker.push_back(true);
        }
        else if (s[i] < s[i + 1]){
            sameChecker.push_back(false);            
        }
        else{
            s[i] = (char)(((s[i] - '0') + 47));
            for(int i2 = i + 1; i2 < (int)s.size(); i2++){
                s[i2] = '9';
            }
            if(!sameChecker.empty() && sameChecker.back()){
                sameChecker.pop_back();
                i = i - 2;
            }
        }
    }

    std::string result = "";
    bool start = false;
    for(int i = 0; i < (int)s.size(); i++){
        if (!start && s[i] != '0'){
            start = true;
            result += s[i];
        }
        else if(start){
            result += s[i];
        }
    }

    ofile << result << std::endl;
    return;
}