#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <n> " << " <k> "<< endl;
		return 1;

    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    double com = 1;
    if(k>0)
    {
        for(int i=1;i<=k;i++)
        {
            int c1 = n+1-i;
            com*=(double)c1/(double)i;    
        }
    } 
    cout << n <<"choose" << k << "=" << com <<endl;

    return 0;
}