#include <iostream>
#include <string>

using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    int n = stoi(argv[1]);
    unsigned long long  frac = 1;
    if(n==0||n==1)
    {
        frac = 1;
    }
    else
    {

        for(int i=1;i<=n;i++)
        {
            frac*=i;
        }
    }
    cout << n <<"!="<<frac; 

    return 0;
}
