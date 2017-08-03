#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>

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
    int cN, jN, cTime = 720, jTime = 720;
    ifile >> cN >> jN;
    vector<int* > C;
    vector<int* > J;
    for(int i = 0 ; i < cN; ++i){
        int start,end;
        ifile >> start >> end;
        int* x = new int[3]; 
        x[0] = start;
        x[1] = end;
        x[2] = 0;
        C.push_back(x);
        cTime -= end - start;
    }
    for(int i = 0 ; i < jN; ++i){
        int start,end;
        ifile >> start >> end;
        int* x = new int[3]; 
        x[0] = start;
        x[1] = end;
        x[2] = 0;
        J.push_back(x);
        jTime -= end - start;
    }
    sort(C.begin(),C.end(),[](int *i, int *j){
        return i[0] < j[0];
    });
    sort(J.begin(),J.end(),[](int *i, int *j){
        return i[0] < j[0];
    });

    for(int i = 0; i < C.size(); ++i){
        if(i == C.size() - 1){
            if(C[i][1] > C[0][0]){
                C[i][2] = 1440 - C[i][1] + C[0][0];
            
            }else{
                C[i][2] = C[0][0] - C[i][1];
            }
        }else{
            C[i][2] = C[i + 1][0] - C[i][1]; 
        }
    }
    
    for(int i = 0; i < J.size(); ++i){
        if(i == J.size() - 1){
            if(J[i][1] > J[0][0]){
                J[i][2] = 1440 - J[i][1] + J[0][0];
            
            }else{
                J[i][2] = J[0][0] - J[i][1];
            }
        }else{
            J[i][2] = J[i + 1][0] - J[i][1]; 
        }
    }
    
    sort(C.begin(),C.end(),[](int *i, int *j){
        return i[2] < j[2];
    });
    sort(J.begin(),J.end(),[](int *i, int *j){
        return i[2] < j[2];
    });
    
    int removedC = 0;
    for(int i = 0; i < C.size(); ++i){
         
        if(C[i][2] <= cTime){
            bool conflict = false;
            for(int j = 0; j < J.size(); ++j){
                if(C[i][1] + C[i][2] > 1440){
                    if(J[j][0] >= C[i][1] || J[j][0] < (C[i][1] + C[i][2]) % 1440){
                        conflict = true;
                    }
                }else{
                    if(J[j][0] >= C[i][1] && J[j][0] < (C[i][1] + C[i][2])){
                        conflict = true;
                    }
                }
                
            }
            if(!conflict){
                removedC++;
                cTime -= C[i][2];
            }
        }else{
            break;
        }
    }
    
    int removedJ = 0;
    for(int i = 0; i < J.size(); ++i){
        if(J[i][2] <= jTime){
            bool conflict = false;
            for(int j = 0; j < C.size(); ++j){
                if(J[i][1] + J[i][2] > 1440){
                    if(C[j][0] >= J[i][1] || C[j][0] < ((J[i][1] + J[i][2]) % 1440) ){
                        conflict = true;
                    }
                }else{
                    if(C[j][0] >= J[i][1] && C[j][0] < (J[i][1] + J[i][2])){
                        conflict = true;
                    }
                }
            }
            if(!conflict){
                removedJ++;
                jTime -= J[i][2];
            }
        }else{
            break;
        }
    }
    
    int res1 = C.size() - removedC,res2 = J.size() - removedJ;
    ofile << "Case #" << c << ": " << 
        2*(res1 > res2? res1 : res2) << endl;
    for(int i = 0; i < C.size();++i){
        delete[] C[i];
    }
    for(int i = 0; i < J.size();++i){
        delete[] J[i];
    }
}