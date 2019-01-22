#include <iostream>
#include <cstdio>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // setprecision
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    string line;
    ifstream myfile ("result2.txt");
    vector<string> vs;

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
            vs.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "new method"<<endl;
    int i=0;
    for(string  s : vs)
    {

        cout << "Round:"<< (i+1) << '\n';
        //string a = "scott>=tiger>=mushroom";
        string delimiter = ",";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            cout <<"Token:"<< token << endl;
            s.erase(0, pos + delimiter.length());
        }
        cout <<"Hello:" << s << endl;
        i++;
    }
    return 0;
}