#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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

class UnicornPlacer{
public:
    int R,Y,B;
    char justUsed;
    char first;
    UnicornPlacer(int R,int Y, int B):
        R(R),Y(Y),B(B){}
        
    char getFirst(){
        if(R == B && B == Y){
            --R;
            justUsed = 'R';
            first = 'R';
            return 'R';
        }else if(B == R){
            if(Y > B){
                --Y;
                justUsed = 'Y';
                first = 'Y';
                return 'Y';
            }else{
                --R;
                justUsed = 'R';
                first = 'R';
                return 'R';
            }
        }else if(Y == R){
            if(B > Y){
                --B;
                justUsed = 'B';
                first = 'B';
                return 'B';
            }else{
                --R;
                justUsed = 'R';
                first = 'R';
                return 'R';
            }
        }else if(B == Y){
            if(R > B){
                --R;
                justUsed = 'R';
                first = 'R';
                return 'R';
            }else{
                --Y;
                justUsed = 'Y';
                first = 'Y';
                return 'Y';
            }
        }else if(B > R && B > Y){
            --B;
            justUsed = 'B';
            first = 'B';
            return 'B';
        }else if(R > Y && R > B){
            --R;
            justUsed = 'R';
            first = 'R';
            return 'R';
        }else{
            --Y;
            justUsed = 'Y';
            first = 'Y';
            return 'Y';
        }
    }
    char getNext(){
        if(!checkPossible()){
            return '1';
        }
        if(justUsed == 'R'){
            if(Y == B){
                if(first == 'Y'){
                    --Y;
                    justUsed = 'Y';
                    return 'Y';
                }else{
                    --B;
                    justUsed = 'B';
                    return 'B';
                }
            }else if(Y > B){
                --Y;
                justUsed = 'Y';
                return 'Y';
            }else{
                --B;
                justUsed = 'B';
                return 'B';
            }
        }else if(justUsed == 'Y'){
            if(R == B){
                if(first == 'R'){
                    --R;
                    justUsed = 'R';
                    return 'R';
                }else{
                    --B;
                    justUsed = 'B';
                    return 'B';
                }
            }else if(R > B){
                --R;
                justUsed = 'R';
                return 'R';
            }else{
                --B;
                justUsed = 'B';
                return 'B';
            }
        }else{
            if(Y == R){
                if(first == 'Y'){
                    --Y;
                    justUsed = 'Y';
                    return 'Y';
                }else{
                    --R;
                    justUsed = 'R';
                    return 'R';
                }
            }else if(Y > R){
                --Y;
                justUsed = 'Y';
                return 'Y';
            }else{
                --R;
                justUsed = 'R';
                return 'R';
            }
        }
    }
    bool checkPossible(){
        if(R + Y + B == 1){
            if(R == 1 && first == 'R'){
                return false;
            }
            if(Y == 1 && first == 'Y'){
                return false;
            }
            if(B == 1 && first == 'B'){
                return false;
            }
        }
        if(justUsed == 'R'){
            if(B == 0 && Y == 0){
                return false;
            }
        }else if(justUsed == 'Y'){
            if(B == 0 && R == 0){
                return false;
            }
        }else{
            if(Y == 0 && R == 0){
                return false;
            }
        }
        return true;
    }
    bool hasMore(){
        return !(R + Y + B == 0);
    }
};

void run(int c, ifstream& ifile, ofstream& ofile){
    int N, R, O, Y, G, B, V;
    ifile >> N >> R >> O >> Y >> G >> B >> V;
    if(c == 47) cout << R << " " << O << " " << Y << " " << G << " " << B << " " << V << endl;
    ofile << "Case #" << c << ": ";
    if(G != 0 && R == G + 1){
        if(Y == 0 && B == 0 && O == 0 && V == 0){
            ofile << "IMPOSSIBLE" << endl;
            return;
        }
    }else if(O != 0 && B == O + 1){
        if(Y == 0 && R == 0 && G == 0 && V == 0){
            ofile << "IMPOSSIBLE" << endl;
            return;
        }
    }else if(V != 0 && V + 1 == Y){
        if(R == 0 && B == 0 && O == 0 && G == 0){
            ofile << "IMPOSSIBLE" << endl;
            return;
        }
    }
    
    if(G != 0 && R == G){
        if(Y == 0 && B == 0 && O == 0 && V == 0){
            while(G != 0){
                ofile << "RG";
                --G;
            }
            ofile << endl;
        }else{
            ofile << "IMPOSSIBLE" << endl;
        }
    }else if(O != 0 && B == O){
        if(Y == 0 && R == 0 && G == 0 && V == 0){
            while(Y != 0){
                ofile << "BO";
                --Y;
            }
            ofile << endl;
        }else{
            ofile << "IMPOSSIBLE" << endl;
        }
    }else if(V != 0 && V == Y){
        if(R == 0 && B == 0 && O == 0 && G == 0){
            while(V != 0){
                ofile << "YV";
                --V;
            }
            ofile << endl;
        }else{
            ofile << "IMPOSSIBLE"  << endl;
        }
    }else if(O > B || V > Y || G > R){
        ofile << "IMPOSSIBLE"  << endl;
    }else{
        string result;
        UnicornPlacer myUnicornPlacer(R-G,Y-V,B-O);
        char firstChar = myUnicornPlacer.getFirst();
        if(firstChar == 'R'){
            while(G != 0){
                result += "RG";
                --G;
            }
            result += 'R';
        }else if(firstChar == 'Y'){
            while(V != 0){
                result += "YV";
                --V;
            }
            result += 'Y';
        }else if(firstChar == 'B'){
            while(O != 0){
                result += "BO";
                --O;
            }
            result += 'B';
        }
        while(myUnicornPlacer.hasMore()){
            char next = myUnicornPlacer.getNext();
            if(c == 46)cout << next << endl;
            if(next == '1'){
                ofile << "IMPOSSIBLE" << endl;
                return;
            }
            if(next == 'R' && G != 0){
                while(G != 0){
                    result += "RG";
                    --G;
                }
                result += 'R';
            }else if(next == 'Y' && V != 0){
                while(V != 0){
                    result += "YV";
                    --V;
                }
                result += 'Y';
            }else if(next == 'B' && O != 0){
                while(O != 0){
                    result += "BO";
                    --O;
                }
                result += 'B';
            }else{
                result += next;
            }
        }
        ofile << result << endl;
    }
    
}