#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // setprecision
#include <vector>

using namespace std;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class ErlangDistribution {
	int shape;
	double lamda;
	private:
		double calculatePI(){
			double U = 1;
		//	cout <<"sss:" <<shape <<"\n";
        	for(int i=0;i<shape;i++){
            	U*=((double) rand() / (RAND_MAX));
            //	cout << "PI"<< U <<"\n";
        	}
        //	free(&t);
        	return U;
		}
	public:
    ErlangDistribution ();
	ErlangDistribution (int,double);
	double generateRandomNumber(){
		double U = calculatePI();
		if(U==0){
			do{
				U = calculatePI();
			}while(U==0);
		}
        return (-1/lamda)*log(U);
    }
    int getShape(){
    	return shape;
	}
	int getLamda(){
    	return lamda;
	}
	
};

class Polynomial{
	double coefficeint;
	int t_degree;
	public:
	Polynomial(double,int);
	double getCoefficient(){
		return coefficeint;
	}
	int getDegree(){
		return t_degree;
	}
	void setCoefficient(double a){
		coefficeint = a;
	}
	void setDegree(int b){
		t_degree = b;
	}
};

ErlangDistribution::ErlangDistribution () {
	//time_t t;
	//srand((unsigned) time(&t)+rand());
}

ErlangDistribution::ErlangDistribution (int a, double b) {
	shape = a;
	lamda = b;
	time_t t;
	srand((unsigned) time(&t)+rand());
}

Polynomial::Polynomial(double a,int b){
	coefficeint = a;
	t_degree = b;
}

int findMinIndex(double list[],int size){
	int index = 0;
	double min=list[0];
//	int size = sizeof(list)/sizeof(*list);
//	cout << size << "\n";
	
    for(int i=1;i<size;i++){
    	//cout << "r";
        /*if(list[i-1]>list[i]){
            index = i;
        }*/
		if(min>list[i]){
			index = i;
			min = list[i];
		}
    }
	return index;


	
}

void printStatiscalRecord(double ti[],int minindex,int type){
	switch(type){
		case 0:
			cout << "=============== Statistical Record ===============" <<endl;
			cout <<"t1"<<setw(10)<<"t2"<<setw(10)<<"t3"<<setw(20)<<"min(t1,t2,t3)"<<setw(13)<<"The best AP"<<endl;
			cout << "=============== Statistical Record ===============" <<endl;
			break;
		case 1:
			//cout << ti[0]<<fixed<<setprecision(4)<<setw(10)<<left<<ti[1]<<fixed<<setprecision(4)<<setw(10)<<left<<ti[2]<<fixed<<setprecision(4)<<setw(10)<<left<<minindex<<endl;
			

			
			cout <<setw(10)<<left<<ti[0]<<fixed<<setprecision(4)<<setw(10)<<left<<ti[1]<<fixed<<setprecision(4)
				 <<setw(10)<<left<<ti[2]<<fixed<<setprecision(4)<<setw(15)<<left<<ti[minindex]<<fixed<<setprecision(4)<<(minindex+1)<<endl;
			break;
		default:	
			break;
	}
}

/*unsigned long int nCr(int n,int r){
	return (r==0||n==r)?1:nCr(n-1,r)+nCr(n-1,r-1);
}*/

double fractorial(int n){

	double  frac = 1;
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
	
	return frac;
}

unsigned long long int nCr(int n,int r){

    unsigned long long int  com = 1;

	if(r==0||r==n){
		return 1;
	}
	else{
  		for(int i=1;i<=r;i++)
        {
            int c1 = n+1-i;
			
            com*=((double)c1/(double)i);
			//cout<< "C1="<<c1 <<" com="<<com <<"C1/i="<<(c1/i) <<endl;    
        }
		return com;
	}
}

int* initvalue(int arr[],int value,int size){
	
	if(size>0){
		for(int i=0;i<size;i++){
			arr[i] = value;
		}
	}
	return arr;

}


double getProbValue(ErlangDistribution lists[],int i,int k,int size){

	//cout << "welcome to new model" << endl;
	double pi=1;

    if(size>0){
        
        // detemine which APs will be considered
        int indexCj[size-1]  ={0};
		int index = 0;
		for(int x=0;x<size;x++){
			if(i!=x)
			{
				//cout << "helloooo" <<endl;
				indexCj[index] = x;
				index++;
			}			
		}


        // initial all APs 
        ErlangDistribution er[size];

        er[0] = lists[i];
		double sumlamda =er[0].getLamda();
        
        for(int n=0;n<index;n++)
        {
            er[n+1] = lists[indexCj[n]];
			sumlamda += er[n+1].getLamda();
        }

        //generate Cj ......
        int upperbound = 0;
        for(int i=1;i<size;i++){
		   upperbound+=((k*er[i].getShape())-1);
        }
		upperbound = upperbound+1;
       // cout << "there are Cj="<<upperbound <<endl;

		vector<vector<Polynomial>> poly;

		// collect each h(t)
		for(int n=1;n<size;n++){
			int nKn = ((k*er[n].getShape())-1);
			vector<Polynomial> arr;
			for(int j=0;j<=nKn;j++){
				double res = (double)pow(er[n].getLamda(),j)/(double)fractorial(j);
				Polynomial pl(res,j);
				arr.push_back(pl);
			}
			poly.push_back(arr);
		}

		// initial some cj
		vector<Polynomial> cj; 
	//	cout << "ddd" << endl;
		int indicateCj[upperbound];
		fill_n(indicateCj,upperbound,-1);
	//	cout << "hhhhh" << endl;
		vector<Polynomial> firstpoly = poly[0];
		for(int i=0;i<firstpoly.size();i++)
		{
			cj.push_back(firstpoly[i]);
			indicateCj[firstpoly[i].getDegree()] = i;
		}
		//cout << "first cj.size =" << cj.size() << ",,"<<upperbound <<endl;

		for(int i=1;i<poly.size();i++)
		{	
			//cout << "i="<<i <<endl;
			vector<Polynomial> Mj; 
			vector<Polynomial> nextpoly = poly[i];
			int indicateMj[upperbound];
			fill_n(indicateMj,upperbound,-1);
			
			int ti=1;
			int indexMj = 0;
			for(int x=0;x<cj.size();x++)
			{
		
				double ci = 0;
				
				for(int j=0;j<nextpoly.size();j++)
				{
	
					ci = (cj[x].getCoefficient()*nextpoly[j].getCoefficient());
					ti = cj[x].getDegree()+nextpoly[j].getDegree();
					//cout << "ti="<<ti<<endl;
					Polynomial poi(ci,ti);

					// store in mj
					if(indicateMj[ti]==-1) // no index in desried t_degree
					{
						indicateMj[ti]=indexMj;
						Mj.push_back(poi);
						indexMj++;
					}
					else{
						Mj[indicateMj[ti]].setCoefficient(Mj[indicateMj[ti]].getCoefficient()+poi.getCoefficient());
					}
				}
			}

			//update cj by mj
			int insertCj = cj.size();
			//cout << "Mj.size =" << Mj.size() << endl;
			for(int m=0;m<Mj.size();m++)
			{
			
				if(indicateCj[Mj[m].getDegree()]==-1)
				{
					cj.push_back(Mj[m]);
					indicateCj[Mj[m].getDegree()]=insertCj;
					insertCj++;
				}
				else
				{
					//update

					cj[indicateCj[Mj[m].getDegree()]].setCoefficient(Mj[m].getCoefficient());

				}

			}

		}

		
		
		double p=0;
		for(int j=0;j<cj.size();j++)
		{
			double c21 = fractorial((k*er[0].getShape())+j-1);
			double c22 = pow(sumlamda,(k*er[0].getShape())+j);
			double c2=double((cj[j].getCoefficient()*c21)/c22);
			p+=c2;
		}
		//cout << "h(t)="<<p<<endl;
		double o11 = pow(er[0].getLamda(),(k*er[0].getShape()));
		double o12 = fractorial((k*(er[0].getShape()))-1);
		double o1 = o11/o12;
		pi*=(o1*p);

    }
    else{
        pi=-1;
    }


	return pi;
}

int main(int argc, char *argv[]) {
	
	if (argc < 8) {
		cerr << "Usage: " << argv[0] << " <SIM_ROUND> " <<" <Num_AP>" << " <ROUND_TRIP> " << " <N1> "  	<< " <N2> " << " ... " << " <LAMDA1> " << " <LAMDA2> " << " ... " << endl;
		return 1;
	}
	
	
	/* initial variable */
	int NSimulation = atoi(argv[1]);
	int N_AP = atoi(argv[2]);
	int K=atoi(argv[3]);

	int wifi_para = (argc-1)-3;

	if(double(wifi_para/N_AP)!=2){
		cerr << "Enter Parameters : <N1> <N2> ... <LAMDA1> <LAMDA2>" <<endl;
		return 1;
	}

	int Ni[N_AP];
	int LAMDAs[N_AP];
	for(int i=0;i<N_AP;i++)
	{
		Ni[i]=atoi(argv[4+i]);
		LAMDAs[i]=atoi(argv[4+N_AP+i]);
	}

	/* print all setting values*/

	cout << "================ Settings ================\n";
	cout << "N_SIMULATION =" << NSimulation <<"\n";
	cout << "N_WIFI_AP =" << N_AP <<"\n";
	cout << "ROUND_TRIP =" << K <<"\n";
	for(int i=0;i<N_AP;i++)
	{
		cout << "N"<<(i+1)<<" =" << Ni[i] <<"\n";
	}

	for(int i=0;i<N_AP;i++)
	{
		cout << "LAMDA"<<(i+1)<<" =" << LAMDAs[i] <<"\n";
	}

	
	ErlangDistribution es[N_AP]; // generate random variable

	for(int i=0;i<N_AP;i++){
		ErlangDistribution e (Ni[i],LAMDAs[i]);
		es[i]= e;
	}

	int count [N_AP] = {0};
	double probAP [N_AP]={0};
	double timerecord[N_AP]={0};
	double ETi_k[N_AP]={0};
	double sum_tl = 0;
	double etl = 0;
	double ti=0;
	
	cout << "================ Simulation ================\n";

	// simulation part 
	for(int x=0;x<NSimulation;x++){
		double t[N_AP]={0};
		int minindex = -1;

		// generate all ping value
		for(int i=0;i<N_AP;i++){
			ti=0;
			for(int j=0;j<K;j++){
				ti+= es[i].generateRandomNumber();
			}
			t[i]=ti;
			timerecord[i]=ti;
			//cout << "t["<<i<<"]="<<t[i]<<"\n";
		}
		
		//string stat;
		minindex = findMinIndex(t,N_AP); // the best AP

		count[minindex]+=1; 
		sum_tl+=t[minindex];
		//statfile << stat <<"\n"; 
	}


	for(int i=0;i<N_AP;i++){
		double p=0;
		cout << "count[" << i <<"]="<<count[i] <<"\n";
		probAP[i] = (double)count[i]/(double)NSimulation;
	}

	for(int i=0;i<N_AP;i++){
		ETi_k[i] = (double)(timerecord[i]/NSimulation);
		cout << "E[T"<<i<<"_(K)]="<<ETi_k[i] <<"\n";
	}

	etl = (double)sum_tl/(double)NSimulation; 
	cout << "E[tl]="<<etl<<endl;

	double psimsum=0;
	for(int i=0;i<N_AP;i++){
		cout <<"prob[AP"<<i<<"]=" <<fixed<<setprecision(8) <<probAP[i]<<"\n";
		psimsum += probAP[i];
	}
	cout << "Sum of P =" << psimsum <<endl;
	
	 
	cout << "================ Math Anaysis ================\n";
	
	double Mprob[N_AP]={0};
	double p2 = 0,psum =0;
    for(int i=0;i<N_AP;i++){

		// new function
		p2 = getProbValue(es, i,K,N_AP);

        Mprob[i]=p2;
        cout << "P[AP"<<i<<" is the best]="<<fixed<<setprecision(8)<<p2<<"\n";
        psum+=p2;

    }
    cout << "sum of P = " << psum << endl;
    string content;
	content = to_string(NSimulation)+","+to_string(N_AP)+","+to_string(K);
	
	 for(int i=0;i<N_AP;i++){
		content+=","+to_string(Ni[i]); 
	 }
	  for(int i=0;i<N_AP;i++){
		content+=","+to_string(LAMDAs[i]); 
	 }

	
	
    for(int i=0;i<N_AP;i++){

        double diff = abs(probAP[i] - Mprob[i]);
        double xtrue = (Mprob[i]!=0)?Mprob[i]:probAP[i];
        double percent = (Mprob[i]==probAP[i])?0:(diff/xtrue)*100;

		double pi = 3.14159265359;
		stringstream prob1,mprob1;
		prob1 << fixed << setprecision(4) << probAP[i];
		mprob1 << fixed << setprecision(4) << Mprob[i];

    	content+=","+ to_string(ETi_k[i])+ ","+prob1.str()+","+mprob1.str()+","+to_string(percent)+"%";

	}
    /* 
    for(int i=0;i<N_AP;i++){
    	content+=","+to_string(Mprob[i]);
	}*/
    
	content +=","+ to_string(etl);

	ofstream outfile;
    outfile.open("result.txt",ios_base::app);
    outfile << content <<"\n"; 
    outfile.close();


	return 0;
}

