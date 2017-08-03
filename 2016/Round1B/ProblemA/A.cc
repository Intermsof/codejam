//Codejam 2016 Round 1B Problem A
//Completed June 9 2017
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <string>

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
    }
}
void run(int c, ifstream& ifile, ofstream& ofile){
    string s;
    ifile >> s;
    unordered_map<char,int> myMap;
    
    for (auto i : s) {
        if(i == 'Z')
            myMap['Z'] += 1;
        if(i == 'W')
            myMap['W'] += 1;
        if(i == 'U')
            myMap['U'] += 1;
        if(i == 'X')
            myMap['X'] += 1;
        if(i == 'G')
            myMap['G'] += 1;
        if(i == 'H')
            myMap['H'] += 1;
        if(i == 'I')
            myMap['I'] += 1;
        if(i == 'S')
            myMap['S'] += 1;
        if(i == 'V')
            myMap['V'] += 1;
        if(i == 'N')
            myMap['N'] += 1;
    }
    
    ofile << "Case #" << c << ": " << 
        string (myMap['Z'],  '0' ) << 
        string (myMap['N'] - (myMap['S'] - myMap['X']) - 2*(myMap['I'] - myMap['G'] - 2*myMap['X'] - myMap['V']  + myMap['S']),'1') <<
        string (myMap['W'],  '2' ) <<
        string (myMap['H'] - myMap['G'],  '3' ) <<
        string (myMap['U'],  '4' ) <<
        string (myMap['V'] - myMap['S'] + myMap['X'],  '5' ) <<
        string (myMap['X'],  '6' ) <<
        string (myMap['S'] - myMap['X'],  '7' ) <<
        string (myMap['G'],  '8' ) <<
        string (myMap['I'] - myMap['G'] - 2*myMap['X'] - myMap['V']  + myMap['S'],'9') << endl;
    
}
