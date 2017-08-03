//code jam 2015 round 1A problem B
//completed June 19
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void run(int i, ifstream& ifile, ofstream& ofile);
int main(int argc, char** argv){
    if(argc < 3) cout << "Please enter input and output file name" << endl;
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

unsigned long long timeToCustomerServed(unsigned long long t,vector<int>& barbers){
    unsigned long long result = 0;
    for(int i = 0; i < barbers.size(); ++i){
        if(t % barbers[i] == 0){
            result += t/barbers[i];
        }else{
            result += (t/barbers[i]) + 1;
        }
        
    }
    return result;
}

unsigned long binarySearch(unsigned long long N,vector<int>& barbers){
    if(barbers.size() >= N){
        return 0;
    }else{
        unsigned long long max = *max_element(barbers.begin(),barbers.end());
        unsigned long long upper = N*max;
        unsigned long long lower = 0;
        unsigned long long t = (upper + lower)/2;
        unsigned long long served = timeToCustomerServed(t,barbers);
        while(served > N || N - served > barbers.size()){
            if(served > N){
                upper = (lower + upper)/2;
            }else{
                lower = (lower + upper)/2;
            }
            t = (upper + lower)/2;
            served = timeToCustomerServed(t,barbers);
        }
        return t;
    }
}
struct Barber{
    unsigned long long t;
    int id;
    int M;
    Barber(unsigned long long t1,int M, int id):M(M),id(id){
        if(t1 % M == 0){
            t = t1;
        }else{
            t = (t1/M + 1) * M;
        }
    }
};

int simulate(unsigned long long start,vector<int>& barbers,int N){
    int max = *(max_element(barbers.begin(),barbers.end()));
    if(start > max){
        start -= max;
    }else{
        start = 0;
    }
    vector<Barber*> times;
    for(int i = 0; i < barbers.size();++i){
        times.push_back(new Barber(start,barbers[i],i + 1));
    }
    auto comp = [](Barber* i, Barber* j){
        if(i->t == j->t){
            return i->id > j->id;
        }else{
            return i->t > j->t;
        }
    };
    unsigned long long served = timeToCustomerServed(start,barbers);
    make_heap(times.begin(),times.end(),comp);
    Barber* min;
    while(served != N){
        min = times[0];
        pop_heap(times.begin(),times.end(),comp);
        min->t += min->M;
        push_heap(times.begin(),times.end(),comp);
        ++served;
    }
    return min->id;
}

void run(int caseNum, ifstream& ifile, ofstream& ofile){
    int B, N;
    ifile >> B >> N;
    vector<int> barbers;
    for (int j = 0; j < B; j++) {
        int length;
        ifile >> length;
        barbers.push_back(length);
    }
    ofile << "Case #" << caseNum << ": " << simulate(binarySearch(N,barbers),barbers,N) << endl;
}
