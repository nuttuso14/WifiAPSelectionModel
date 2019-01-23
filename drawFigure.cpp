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
    ifstream myfile ("result.txt");
    vector<string> lineitems;
    vector<vector<string>> data; 

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
            lineitems.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "new method"<<endl;

    for(string  s : lineitems)
    {
        vector<string> str;
        //string a = "scott>=tiger>=mushroom";
        string delimiter = ",";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            str.push_back(token);
            //cout <<"Token:"<< token << endl;
            s.erase(0, pos + delimiter.length());
        }
       // cout <<"Hello:" << s << endl;
        str.push_back(s);
        data.push_back(str);

    }
    int i = 0;
    for(vector<string> datum : data)
    {
        cout << "datum:"<<datum.size()<<endl;

        cout << (i+1)<<"-th line"<<endl;
        for(string ss: datum)
        {
            cout << ss <<endl;
        }
        i++;
    }
    cout << "data: " << data.size() <<endl;
    return 0;
}