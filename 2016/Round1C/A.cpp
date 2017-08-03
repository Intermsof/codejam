//codejam 2016 round 1C Problem A
//completed July 21 2017
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    int N;
    ifile >> N;
    int total = 0;
    vector<pair<int, char> > numbers;
    for(int i = 0; i < N; ++i){
        int temp;
        ifile >> temp;
        numbers.push_back(make_pair(temp,(char)(65 + i)));
        total += temp;
    }
    
    string result;
    int exited = 0;
    while(exited != total){
        if(count_if(numbers.begin(),numbers.end(),[&](pair<int, char> i){return i.first == 0;}) == N - 2){
            auto it = max_element(numbers.begin(),numbers.end(),[&](pair<int, char> i, pair<int,char> j){
                return i.first < j.first;
            });
            result += it->second;
            int prev = it->first;
            it->first -= 1;
            
            exited++;
            auto it2 = max_element(numbers.begin(),numbers.end(),[&](pair<int, char> i, pair<int,char> j){
                return i.first < j.first;
            });
            
            if(it2->first == prev && exited != total){
                result += it2->second;
                result += " ";
                it2->first -= 1;
                exited++;
            }else{
                result += " ";
            }
            
        }else{
            auto it = max_element(numbers.begin(),numbers.end(),[&](pair<int, char> i, pair<int,char> j){
                return i.first < j.first;
            });
            result += it->second;
            result += " ";
            it->first -= 1;
            exited++;
        }
    }
    
    ofile << "Case #" << c << ": " << result << endl;
}