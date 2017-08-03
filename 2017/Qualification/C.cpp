//Google Code Jam 2017 Qualification Round Problem 3
//completed May 21 2017
#include <fstream>
#include <iostream>
#include <string>
#include <map>

void run(int caseNum, unsigned long long N, long long K, std::ofstream& ofile);

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cout << "You have not entered an input or output file" << std::endl;
    }
    
    //open input and output files
    std::ifstream ifile(argv[1]);
    std::ofstream ofile(argv[2]);
    
    //get input and pass to run function
    int numTestCases;
    long long N, K;
    ifile >> numTestCases;
    for(int i = 0; i < numTestCases; ++i)
    {
        ifile >> N >> K;
        run(i,N,K,ofile);
    }
    
    ifile.close();
    ofile.close();

}

void run(int caseNum, unsigned long long N, long long K, std::ofstream& ofile)
{
    ofile << "Case #" << caseNum + 1 << ": ";
    
    long long min,max;
    if(N % 2 == 0)
    {
        min = N/2 - 1;
        max = N/2;
    }
    else
    {
        min = N/2;
        max = N/2;
    }
    long long minAmount = 1, maxAmount = 1;
    --K;
    if(K == 0)
    {
        ofile << max << " " << min << std::endl;
        return;
    }
    while(K > 0 && max != 1)
    {

        long long nextMax, nextMin, nextMaxAmount, nextMinAmount;
        nextMax = max/2;
        nextMin = max % 2 == 1 && min == max ? max/2 : max/2 - 1;
        if(max == min){
            nextMaxAmount = 2*maxAmount;
            nextMinAmount = 2*minAmount;
        }
        else if(max % 2 == 0)
        {
            nextMaxAmount = maxAmount;
            nextMinAmount = maxAmount + 2*minAmount;
        }
        else
        {
            nextMaxAmount = maxAmount*2 + minAmount;
            nextMinAmount = minAmount;
        }
        K -= maxAmount;
        if(K <= 0){
            ofile << nextMax << " " << (max % 2 == 0 ? nextMin : nextMax) << std::endl;
            return;
        }
        K -= minAmount;

        if(K <= 0){
            ofile <<  (min % 2 == 0? nextMax : nextMin) << " " << nextMin << std::endl;
            return;
        }
        max = nextMax;
        min = nextMin;
        maxAmount = nextMaxAmount;
        minAmount = nextMinAmount;
    }

    ofile << "0 0" << std::endl;

}
