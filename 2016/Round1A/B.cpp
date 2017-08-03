//code jam 2016 Round 1A Problem B
//completed July 21 2017
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;
void run(int c, ifstream& ifile, ofstream& ofile);
void place(pair<vector<int>,vector<int> >& intersection, vector<vector<int> >& grid, int index, int N);

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
    //get info
    int N;
    ifile >> N;
    vector<vector<int> > lists;
    int totalLists = 2*N - 1;
    for(int i = 0; i < totalLists; ++i){
        vector<int> temp;
        for(int j = 0; j < N; ++j){
            int height;
            ifile >> height;
            temp.push_back(height);
            
        }
        lists.push_back(temp);
    }
    
    
    //sort
    vector<pair<vector<int>,vector<int> > > sorted;
    int missingIntersection = -1;
    for(int i = 0; i < N; ++i){
        int index = missingIntersection == -1? 2*i : 2*i - 1;
        sort(lists.begin(),lists.end(),[&](vector<int> j, vector<int> k){
            return j[i] < k[i];
        });
        if((missingIntersection == -1 && index + 1 == lists.size()) || lists[index][i] != lists[index + 1][i]){
            vector<int> temp(N,-1);
            sorted.push_back(make_pair(lists[index],temp));
            missingIntersection = i;
        }else{
            sorted.push_back(make_pair(lists[index],lists[index + 1]));
        }
    }
    
    
    //make grid
    vector<vector<int> > grid(N);
    for(int i = 0; i < N; ++i){
        vector<int> temp(N,-1);
        grid[i] = temp;
    }
    set<int> placed;
    deque<int> myQ;
    for(int i = 0; i < N; ++i){
        myQ.push_back(i);
    }
    //solve
    while(placed.size() != N - 1){
        int next = myQ.front();
        myQ.pop_front();
        if(placed.find(next) == placed.end() && next != missingIntersection){
            place(sorted[next],grid,next,N);
            placed.insert(next);
            for(int i = 0; i < N; ++i){
                if(sorted[next].first[i] != sorted[next].second[i] 
                    && placed.find(i) == placed.end()){
                    myQ.push_front(i);    
                }
            }
        }
    }
    
    grid[missingIntersection][missingIntersection] = sorted[missingIntersection].first[missingIntersection];
    ofile << "Case #" << c << ": ";
    for(int i = 0; i < N; ++i){
        if(grid[missingIntersection][i] != sorted[missingIntersection].first[i]){
            for(int j = 0; j < N; ++j){
                ofile << grid[missingIntersection][j];
                if(j != N - 1){
                    ofile << " ";
                }
            }
            ofile << endl;
            return;
        }
    }
    
    for(int j = 0; j < N; ++j){
        ofile << grid[j][missingIntersection];
        if(j != N - 1){
            ofile << " ";
        }
    }
    ofile << endl;
}

void place(pair<vector<int>,vector<int> >& intersection, vector<vector<int> >& grid, int index, int N){
    for(int i = 0; i < N; ++i){
        if(grid[index][i] != grid[i][index]){
            if(intersection.first[i] == grid[index][i]){
                for(int j = 0; j < N; ++j){
                    grid[index][j] = intersection.first[j];
                    grid[j][index] = intersection.second[j];
                }
            }else{
                for(int j = 0; j < N; ++j){
                    grid[index][j] = intersection.second[j];
                    grid[j][index] = intersection.first[j];
                }
            }
            return;
        }
    }
    for(int j = 0; j < N; ++j){
        grid[index][j] = intersection.first[j];
        grid[j][index] = intersection.second[j];
    }
}
