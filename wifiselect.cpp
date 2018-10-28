#include <iostream>
#include <cstdio>
#include <time.h> 
#include <math.h>
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
        return (-1/lamda)*log(calculatePI());
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

double getProbValueHardCode(ErlangDistribution lists[],int i,int k,int size){
	
	// this function use only n1=n2=n3=3
	//cout << endl<<"this function use only n1=n2=n3=3" << endl;
	//cout << "============================================="<<endl;
	double pi=1;
	if(size>0)
	{
	//try to generate cj
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

		//cout << "find P[AP"<<i<<"]=min("<<"t"<<indexCj[0]<<",t"<<indexCj[1]<<")"<<endl;
		/*for(int y=0;y<2;y++){
			cout << " =" <<indexCj[y] << endl;
		}*/


		ErlangDistribution eri = lists[i];
		ErlangDistribution erm1 = lists[indexCj[0]]; //Ap2
		ErlangDistribution erm2 = lists[indexCj[1]]; //Ap3

		//cout << "lamda"<<indexCj[0]<<"="<<erm1.getLamda() << " , lamda"<<indexCj[1]<<"="<<erm2.getLamda()<<endl; 

		double c[5]={0};
		
		c[0]=1;
		c[1]=erm1.getLamda()+erm2.getLamda();
		c[2]=((double)((pow(erm1.getLamda(),2)/2)))+(erm1.getLamda()*erm2.getLamda())+((double)((pow(erm2.getLamda(),2)/2)));
		c[3]=(double)(((erm1.getLamda()*pow(erm2.getLamda(),2))+(pow(erm1.getLamda(),2)*erm2.getLamda()))/2);
		c[4]=double(pow(erm1.getLamda(),2)*pow(erm2.getLamda(),2)/4);

		/*c[0]=1;
		c[1]=erm1.getLamda()+erm2.getLamda();
		c[2]=((double)((pow(erm1.getLamda(),2))))+(erm1.getLamda()*erm2.getLamda())+((double)((pow(erm2.getLamda(),2))));
		c[3]=(double)(((erm1.getLamda()*pow(erm2.getLamda(),2))+(pow(erm1.getLamda(),2)*erm2.getLamda())));
		c[4]=double(pow(erm1.getLamda(),2)*pow(erm2.getLamda(),2));*/



		double p=0;
		for(int j=0;j<5;j++)
		{
			double c21 = fractorial((k*eri.getShape())+j-1);
			double c22 = pow(eri.getLamda()+erm1.getLamda()+erm2.getLamda(),(k*eri.getShape())+j);
		//	double c2=((double)(c[j]/fractorial(j)))*c21;
			double c2=double((c[j]*c21)/c22);
			//cout << "c2=" << c2 <<endl;
			//cout <<"c"<<j<<"="<<c[j]<< " (k"<<i<<"+j-1)!=("<<eri.getShape()+j-1<<")!="<<c21<< " cj*(k+j-1)!="<<c2<<endl;
			p+=c2;
		}
		//cout << "h(t)="<<p<<endl;
		double o11 = pow(eri.getLamda(),(k*eri.getShape()));
		double o12 = fractorial((k*(eri.getShape()))-1);
		double o1 = o11/o12;
		//cout << "lamda"<<i<<"^k"<<i<<"="<<eri.getLamda()<<"^"<<eri.getShape()<<"="<<o11<<" (k"<<i<<"-1)!="<<"("<<((eri.getShape())-1)<<")!="<<o12<<" (lamda"<<i<<"^k"<<i<<")/(k"<<i<<"-1)!="<<o1<<endl;
		//cout << "o1=" << o1 << endl;
		pi*=(o1*p);
		//cout <<endl<< "((lamda"<<i<<"^k"<<i<<")/(k"<<i<<"-1)!)*h(t)="<<pi<<endl;

	}
	else{
		pi = -1;
	}
	return pi;
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

        //cout << "find P[AP"<<i<<"]=min("<<"t"<<indexCj[0]<<",t"<<indexCj[1]<<")"<<endl;

        // initial all APs 
        ErlangDistribution er[size];

        er[0] = lists[i];
		double sumlamda =er[0].getLamda();
        
        for(int n=0;n<index;n++)
        {
            er[n+1] = lists[indexCj[n]];
			sumlamda += er[n+1].getLamda();
        }

        /*for(int x=0;x<size;x++)
        {
            cout << "n="<<er[x].getShape()<< " lamda=" << er[x].getLamda() <<endl;
        }*/

        //generate Cj ......
        int upperbound = 0;
        for(int i=1;i<size;i++){
           // cout << "k =" << k << " n="<< er[i].getShape() << endl;
           // upperbound *= ((k*er[i].getShape())-1);
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

		//print
		/*cout << "poly size = "<< poly.size() << endl;
		for(int i=0;i<poly.size();i++){
			cout << "the " << (i+1) << "th "<<endl;
			cout << "=============================" <<endl;
			vector<Polynomial> arr = poly[i];
			cout << "arr size ="<< arr.size() << endl;
			for(int j=0;j<arr.size();j++)
			{
				Polynomial pl = arr[j];
				cout << "arr["<<j<<"]="<<pl.getCoefficient() << ", degree: t^" << pl.getDegree() <<endl;
			}
			cout << "=============================" <<endl;
		}*/

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

			/*for(int k=0;k<Mj.size();k++)
			{
				cout << "Mj["<<k<<"]="<<Mj[k].getCoefficient() << " degree:"<< Mj[k].getDegree() << endl ;
			}*/	

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

					//cj[indicateCj[Mj[m].getDegree()]].setCoefficient(Mj[indicateCj[Mj[m].getDegree()]].getCoefficient());
				//	cout<< "hhhh:" << cj[indicateCj[Mj[m].getDegree()]].getCoefficient()<<endl;
				}
				//cout<< "kkkk"<<endl;
			}

		}

		//cout << "last cj.size =" << cj.size() <<endl;
		
		
		double p=0;
		for(int j=0;j<cj.size();j++)
		{
			double c21 = fractorial((k*er[0].getShape())+j-1);
			double c22 = pow(sumlamda,(k*er[0].getShape())+j);
		//	double c2=((double)(c[j]/fractorial(j)))*c21;
			double c2=double((cj[j].getCoefficient()*c21)/c22);
			//cout << "sumlamda="<< sumlamda <<" ,c2=" << c2 <<endl;
			//cout <<"c"<<j<<"="<<cj[j].getCoefficient()<< " (k"<<i<<"+j-1)!=("<<(k*er[0].getShape())+j-1<<")!="<<c21<< " cj*(k+j-1)!="<<c2<<endl;
			p+=c2;
		}
		//cout << "h(t)="<<p<<endl;
		double o11 = pow(er[0].getLamda(),(k*er[0].getShape()));
		double o12 = fractorial((k*(er[0].getShape()))-1);
		double o1 = o11/o12;
		//cout << "lamda"<<i<<"^k"<<i<<"="<<eri.getLamda()<<"^"<<eri.getShape()<<"="<<o11<<" (k"<<i<<"-1)!="<<"("<<((eri.getShape())-1)<<")!="<<o12<<" (lamda"<<i<<"^k"<<i<<")/(k"<<i<<"-1)!="<<o1<<endl;
		//cout << "o1=" << o1 << endl;
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
		cerr << "Enter Parameters : <N1> <N2> ... <LAMDA1> <LAMDA2>";
		return 1;
	}

	int Ni[N_AP];
	int LAMDAs[N_AP];
	for(int i=0;i<N_AP;i++)
	{
		Ni[i]=atoi(argv[4+i]);
		LAMDAs[i]=atoi(argv[4+N_AP+i]);
	}

	/*int n1=atoi(argv[3]);
	int n2=atoi(argv[4]);
	int n3=atoi(argv[5]);
	double lamda1=atof(argv[6]);
	double lamda2=atof(argv[7]);
	double lamda3=atof(argv[8]);*/
	
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

	/*
	cout << "================ Settings ================\n";
	cout << "N_SIMULATION =" << NSimulation <<"\n";
	cout << "ROUND_TRIP =" << K <<"\n";
	cout << "N1 =" << n1 <<"\n";
	cout << "N2 =" << n2 <<"\n";
	cout << "N3 =" << n3 <<"\n";
	cout << "LAMDA1 =" << lamda1 <<"\n";
	cout << "LAMDA2 =" << lamda2 <<"\n";
	cout << "LAMDA3 =" << lamda3 <<"\n";*/
	
	ErlangDistribution es[N_AP]; // generate random variable

	for(int i=0;i<N_AP;i++){
		ErlangDistribution e (Ni[i],LAMDAs[i]);
		es[i]= e;
	}

/*
	ErlangDistribution e1 (n1,lamda1);
	ErlangDistribution e2 (n2,lamda2);
	ErlangDistribution e3 (n3,lamda3); */
	
	
	//ErlangDistribution es [] = {ei};
	
	//int count [] = {0,0,0};
	//int table[N_AP][N_AP] ={{0,0,0},{0,0,0},{0,0,0}};
	//double proptable[N_AP][N_AP] ={{0,0,0},{0,0,0},{0,0,0}};
	//double probAP []={0,0,0};
	//double timerecord[NSimulation][N_AP] ={0};
	//double conditionalTable[N_AP][N_AP] ={0};

	int count [N_AP] = {0};
	double probAP [N_AP]={0};
	
	
	double ti=0;
	
	cout << "================ Simulation ================\n";
	//ofstream statfile;
	//statfile.open("stat.txt");
	//printStatiscalRecord(NULL,-1,0);

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
		//	timerecord[x][i]=ti;
			//cout << "t["<<i<<"]="<<t[i]<<"\n";
		}
		
		//count which one won the competitor e.g., 0>1 0>2 1>0......
		/*for(int xx=0;xx<N_AP;xx++){
			for(int yy=0;yy<N_AP;yy++){
				if(xx!=yy){
					if(t[xx]<t[yy]){
						table[xx][yy]+=1;
					}
				}
			}
		}*/



		//string stat;
		minindex = findMinIndex(t,N_AP); // the best AP
		//printStatiscalRecord(t,minindex,1);
		//stat+= to_string(t[0])+","+to_string(t[1])+","+to_string(t[2])+","+to_string(t[minindex])+","+to_string(minindex); // write to text file
		count[minindex]+=1; 
		//statfile << stat <<"\n"; 
	}
	//statfile.close();
	
	/*for(int i=0;i<NSimulation;i++){
		for(int j=0;j<N_AP;j++){
			cout <<timerecord[i][j] <<","; 
		}
		cout<<endl;
	}*/

	for(int i=0;i<N_AP;i++){
		double p=0;
		cout << "count[" << i <<"]="<<count[i] <<"\n";
		probAP[i] = (double)count[i]/(double)NSimulation;
	}
	double psimsum=0;
	for(int i=0;i<N_AP;i++){
		cout <<"prob[AP"<<i<<"]=" <<fixed<<setprecision(8) <<probAP[i]<<"\n";
		psimsum += probAP[i];
	}
	cout << "Sum of P =" << psimsum <<endl;
//	cout << "============== Table ============" <<endl;

/*	for(int i=0;i<N_AP;i++){
		for(int j=0;j<N_AP;j++){
			if(i!=j){
				cout <<"count["<<i<<"<"<<j<<"]="<<table[i][j]<<endl;
			}
			proptable[i][j] = (double)table[i][j]/NSimulation;
		}

	}
	double ptableSum=0;
	double ptable=1;*/
//	cout << "============== Prob Table ==============" <<endl;
/*	for(int i=0;i<N_AP;i++){
		ptable=1;
		for(int j=0;j<N_AP;j++){
			if(i!=j){
				cout <<"P["<<i<<"<"<<j<<"]="<<proptable[i][j]<<endl;
				ptable*=proptable[i][j];
			}

		}
		cout << "P[AP"<<i<<" is the best]="<<ptable<<endl;
		ptableSum+=ptable;
	}

	cout << "Sum of P="<<ptableSum<<endl;
*/

	cout << "================ Math Anaysis ================\n";

	double Mprob[N_AP]={0};
	double p2 = 0,psum =0;
    for(int i=0;i<N_AP;i++){
      //  APSelection ap = aps.get(i);
       // ap.simM = ap.getProbValue(ers, i, K); 
       // aps.set(i, ap);
       // System.out.println("P[AP"+(i+1)+"]="+aps.get(i).simM);

	    // old function
        //p2 = getProbValue(es, i, K,3);

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
    	content+=","+to_string(probAP[i]);
	}
    
    for(int i=0;i<N_AP;i++){
    	content+=","+to_string(Mprob[i]);
	}
    
	ofstream outfile;
    outfile.open("result.txt",ios_base::app);
    outfile << content <<"\n"; 
    outfile.close();


	return 0;
}

