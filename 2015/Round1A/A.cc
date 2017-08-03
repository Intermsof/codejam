//Codejam 2015 Round 1A Problem A
//Completed June 7 2017
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char** argv) {
    if(argc < 3) cout << "Please enter an input and output file name" << endl;
    else{
        ifstream ifile(argv[1]);
        ofstream ofile(argv[2]);
        
        int T;
        ifile >> T;
        for (int i = 0; i < T; i++) {
            int N;
            ifile >> N;
            vector<int> terms;
            for (int j = 0; j < N; j++) {
                int value;
                ifile >> value;
                terms.push_back(value);
            }
            ofile << "Case #" << i + 1 << ": ";
            //first way of computing
            int decreased = 0;
            int prev = 0;
            for (auto j : terms) {
                if(j < prev){
                    decreased += (prev - j);
                }
                prev = j;
            }
            ofile << decreased << " ";
            //second way of computing
            vector<int> decList;
            for (int j = 1; j < terms.size(); j++) {
                decList.push_back(terms[j - 1] - terms[j]);
            }
            
            sort(decList.begin(),decList.end());

            int maxDecrease = decList[decList.size() - 1];
          
            decreased = 0;
            for (int j = 0; j < terms.size() - 1; j++) {
                decreased += terms[j] < maxDecrease ? terms[j] : maxDecrease;
            }
            
            ofile << decreased << endl;

            
        }
        ifile.close();
	    ofile.close();
    }
}
