//code jam 2016 Round 1A Problem A
//completed Jun 19 2017
#include <fstream>
#include <iostream>
#include <string>
#include <list>
using namespace std;
void run(int c, ifstream& ifile, ofstream& ofile);
int main(int argc, char** argv) {
    if(argc < 3) cout << "Please enter an input and output file name" << endl;
    else{
        ifstream ifile(argv[1]);
        ofstream ofile(argv[2]);
        int T;
        ifile >> T;
        for (int i = 0; i < T; i++) {
            run(i + 1,ifile,ofile);
        }
        ifile.close();
	    ofile.close();
    }
}
void run(int c, ifstream& ifile, ofstream& ofile){
    string s;
    ifile >> s;
    list<char> result;
    result.push_back(s[0]);
    for(int i = 1; i < s.size(); ++i){
        if(s[i] >= result.front()){
            result.push_front(s[i]);
        }else{
            result.push_back(s[i]);
        }
    }
    ofile << "Case #" << c << ": ";
    for (auto i : result) {
        ofile << i;
    }
    ofile << endl;
}
