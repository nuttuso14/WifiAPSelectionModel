#include <iostream>
#include <cstdio>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> // setprecision
#include <vector>

using namespace std;

class WifiData{
    int q_ap,n_shape;
    double lambda,eti_k,simprob, mathprob;
    string error;
    public:
    void setQ_AP(int n){
        q_ap = n;
    }
    void setN_shape(int n){
        n_shape = n;
    }
    void setEti_K(double n){
        eti_k = n;
    }
    void setLamda(double n){
        lambda = n;
    }
    void setSim_prob(double n){
        simprob = n;
    }
    void setM_prob(double n){
        mathprob = n;
    }
    void setError(string n){
        error = n;
    }
    


    int getQ_AP(){
        return q_ap;
    }
    int getN_shape(){
        return n_shape;
    }
    double getEti_k(){
        return eti_k;
    }
    double getLamda(){
        return lambda;
    }
    double getSim_prob(){
        return simprob;
    }
    double getM_prob(){
        return mathprob;
    }
     double getMean(){
        return (double)(n_shape/lambda);
    }

    string getError(){
        return error;
    }

};

class DataFigure{

    int n_sim,n_ap,k;
    double etl;
    vector<WifiData> wifi;
    public:
    void setN_sim(int n)
    {
        n_sim = n;
    }
    void setN_AP(int n)
    {
        n_ap = n;
    }
    void setK(int n)
    {
        k = n;
    }
    void setETL(double n){
        etl = n;
    }

    void setWifiData(vector<WifiData> wf){
        wifi = wf;
    }

    int getN_sim()
    {
        return n_sim;
    }
    int getN_AP()
    {
        return n_ap;
    }
    int getK()
    {
        return k;
    }
    double getEtl(){
        return etl;
    }

    vector<WifiData> getWifiData(){
        return wifi;
    } 

};

int selectMinIndex(vector<WifiData> wf){
    int i=0;
    double temp = wf[0].getMean();
    int x=0;
    for(WifiData w:wf)
    {
        if(w.getMean()<temp){
            temp = w.getMean();
            //i = w.getQ_AP();
            i = x;
        }
        x++;
    }

    if(i==0) //every expected download time is same
    {
        double pmax = wf[0].getSim_prob();
        int y = 0;
        for(WifiData w:wf)
        {
            if(w.getSim_prob()>pmax){
                pmax = w.getSim_prob();
                //i = w.getQ_AP();
                i = y;
            }
            y++;
        }
    }

    return i;
}

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

    //cout << "new method"<<endl;

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
    
    
    /*
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
    cout << "data: " << data.size() <<endl;*/

    vector<DataFigure> figs;
    for(vector<string> datum : data)
    {
        vector<WifiData> wifis;
        DataFigure df; 
        df.setN_sim(stoi(datum[0]));   
        df.setN_AP(stoi(datum[1]));
        df.setK(stoi(datum[2]));
        df.setETL(stod(datum[datum.size()-1]));

        int mathdata[df.getN_AP()]={0};
        int init = 3+(df.getN_AP()*2);

        mathdata[0]= init;
        for(int i=1;i<df.getN_AP();i++){
            mathdata[i]=init +(i*4);
           // cout << mathdata[i]<<endl;
        }

        int r=0;
        for(int i=3;i<3+df.getN_AP();i++){
            WifiData wifi;
            wifi.setQ_AP((r+1));
            wifi.setN_shape(stoi(datum[i]));
            wifi.setLamda(stof(datum[i+df.getN_AP()]));
            wifi.setEti_K(stof(datum[mathdata[r]]));
            wifi.setSim_prob(stof(datum[mathdata[r]+1]));
            wifi.setM_prob(stof(datum[mathdata[r]+2]));
            wifi.setError(datum[mathdata[r]+3]);
            //wifi.setSim_prob(stof(datum[]));
            r++;
            wifis.push_back(wifi);
        }


        df.setWifiData(wifis);
        figs.push_back(df);
    }
   // cout << "figs:"<< figs.size()<<endl;
    int i=0;
    ofstream outfile;
    outfile.open("figure.txt",ios_base::app);
 

    for(DataFigure dd: figs)
    {
       /* cout << "line"<<(i+1)<<":"<<endl;
        for(WifiData dt:dd.getWifiData())
        {
            cout <<dt.getQ_AP()<<","<< dt.getN_shape()<< "," <<dt.getLamda()<< "," <<dt.getSim_prob()<< "," <<dt.getM_prob()<< "," <<dt.getError()<<","<<dt.getMean() <<endl;
            
        }
        cout << "Expected min download time:" << (selectMinIndex(dd.getWifiData())+1)<<endl;*/
        vector<WifiData> dt = dd.getWifiData();
        int x = selectMinIndex(dt);
        
        string content;

        stringstream prob1,mprob1;
		prob1 << fixed << setprecision(4) << dt[x].getSim_prob();
		mprob1 << fixed << setprecision(4) << dt[x].getM_prob();

        content = to_string(dd.getN_sim()) +"," + to_string(dd.getN_AP()) + "," + to_string(dd.getK()) +"," \
                  + to_string(dt[x].getQ_AP()) +"," + to_string(dt[x].getMean())+","  + to_string(dt[x].getEti_k())+ "," \
                  + prob1.str() +","+ mprob1.str() +","+ dt[x].getError()+","+ to_string(dd.getEtl());
        i++;
        outfile << content <<"\n"; 
    }

    //outfile << content <<"\n"; 
    outfile.close();
    cout << "write successfully, see figure.txt" <<endl;
    return 0;
}