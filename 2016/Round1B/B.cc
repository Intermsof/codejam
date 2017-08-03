//Codejam 2016 Round 1B Problem B
//Completed June 12 2017
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;
void run(int c, ifstream& ifile, ofstream& ofile);
bool subProblem(string &small, string &large, int index, int option = 0);
void makeEqual(string &s1, string &s2, int index);
int breakTie(string &s1, string &s2, int i);
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
    string s1,s2;
    ifile >>s1>>s2;
    bool first = true,s1L;
    int i = 0;
    for(; i < s1.size(); ++i){
        if(first){
            if(s1[i] != s2[i] && !(s1[i] == '?' || s2[i] == '?')){
                if(s1[i] > s2[i]){
                    int absDiff = abs(s1[i] - s2[i]);
                    if(absDiff < 5){
                        makeEqual(s1,s2,i - 1);
                        s1L = false;
                    }else if(absDiff > 5){
                        if(subProblem(s1,s2,i - 1)){
                            s1L = true;
                        }else{
                            s1L = false;
                        }
                    }else{
                        int cases = breakTie(s1,s2,i);
                        if(cases == 0){
                            if(subProblem(s1,s2,i - 1,1)){
                                s1L = true;
                            }else{
                                s1L = false;
                            }
                        }else if(cases == 1){
                            if(subProblem(s1,s2,i - 1)){
                                s1L = true;
                            }else{
                                s1L = false;
                            }
                        }else{
                            makeEqual(s1,s2,i - 1);
                            s1L = false;
                        }
                    }
                }else{
                    int absDiff = abs(s1[i] - s2[i]);
                    if(absDiff < 5){
                        makeEqual(s1,s2,i - 1);
                        s1L = true;
                    }else if(absDiff > 5){
                        if(subProblem(s2,s1,i - 1)){
                            s1L = false;
                        }else{
                            s1L = true;
                        }
                    }else{
                        int cases = breakTie(s1,s2,i);
                        if(cases == 0){
                            if(subProblem(s2,s1,i - 1,1)){
                                s1L = false;
                            }else{
                                s1L = true;
                            }
                        }else if(cases == 1){
                            makeEqual(s1,s2,i - 1);
                            s1L = true;
                        }else{
                            if(subProblem(s2,s1,i - 1)){
                                s1L = false;
                            }else{
                                s1L = true;
                            }
                        }
                    }
                }
                
                first = false;
                break;
            }
        }
    }
    if(first){
        makeEqual(s1,s2,s1.size() - 1);
    }else{
        for(i = i + 1;i < s1.size(); ++i){
            if(s1L){
                if(s1[i] == '?') s1[i] = '9';
                if(s2[i] == '?') s2[i] = '0';
            }else{
                if(s1[i] == '?') s1[i] = '0';
                if(s2[i] == '?') s2[i] = '9';
            }
        }
    }
    
    ofile << "Case #" << c << ": " << s1 << " " << s2 << endl;
}

bool subProblem(string &small, string &large, int index, int option){
    if(index < 0){
        return false;
    }else if(small[index] == large[index] && small[index] != '?'){
        makeEqual(small,large,index);
        return false;
    }else if(small[index] == '?' && large[index] == '?'){
        if(subProblem(small,large,index - 1,1)){
            small[index] = '9';
            large[index] = '0';
            return true;
        }else{
            if(option == 0){
                small[index] = '0';
                large[index] = '1';
                return true;
            }else{
                small[index] = '0';
                large[index] = '0';
                return false;
            }
        }
    }else if(small[index] == '?'){
        
        if(large[index] == '0'){
            if(subProblem(small,large,index - 1,option)){
                small[index] = '9';
                return true;
            }else{
                small[index] = '0';
                return false;
            }
        }else{
            makeEqual(small,large,index - 1);
            small[index] = (char)((int)large[index] - 1);
            return true;
        }
    }else if(large[index] == '?'){
        if(small[index] == '9'){
            if(subProblem(small,large,index - 1,option)){
                large[index] = '0';
                return true;
            }else{
                large[index] = '9';
                return false;
            }
        }else{
            if(option == 0){
                makeEqual(small,large,index - 1);
                large[index] = (char)((int)small[index] + 1);
                return true;
            }else{
                makeEqual(small,large,index);
                return false;
            }
            
        }
    }
}

void makeEqual(string &s1, string &s2, int index){
    for(int i = 0; i <= index; ++i){
        if(s1[i] == '?' && s2[i] == '?'){
            s1[i] = '0';
            s2[i] = '0';
        }else if(s1[i] == '?'){
            s1[i] = s2[i];
        }else if(s2[i] == '?'){
            s2[i] = s1[i];
        }
    }
}

int breakTie(string &s1, string &s2, int i){
    string sub1,sub2 = "1",sub3 = "1",sub4;
    for(int j = i + 1; j < s1.size(); ++j){
        if(s1[j] == '?'){
            sub1 += '9';
            sub3 += '0';
        }else{
            sub1 += s1[j];
            sub3 += s1[j];
        }
        if(s2[j] == '?'){
            sub2 += '0';
            sub4 += '9';
        }else{
            sub2 += s2[j];
            sub4 += s2[j];
        }
    }
    if(i + 1 == s1.size()){
        sub1 = "1";
        sub4 = "1";
    }
    long long one,two,three,four;
    stringstream ss;
    ss << sub1 << " " << sub2 << " " << sub3 << " " << sub4;
    ss >> one >> two >> three >> four;
    long long diff1 = two - one,diff2 = three - four;
    if(diff1 == diff2){
        return 0;
    }else if(diff1 < diff2){
        return 1;
    }else{
        return 2;
    }
}