//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TRint.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>

#define N 10000				       // Número máximo de Datos 
#define Z 1700 		       			       // Número Pulsos 

using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t mean,sigma,newtrigger, dmean,dsigma,datosy[N],datosx[N],x[N],y[N]; 		      
Float_t XINCR=2.0E-10, PT_OFF=0 , XZERO=-9.5E-7,YMULT=8.0E-4  , YZERO=0.0E0  ,YOFF=7.3E1 ;
Int_t i,j,k,l,xini,aux=0,oldtim,m,m2,fin=1,ffi=1,m3;  
char arch[100],arch1[100],fich[100],dummy[7];

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela)M.Gascón.*******    " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "MODO DE USO: bin2asc [FICHERO](sin extens.) 		          	   " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa transforma de un fichero binario a N ficheros ascii.        " << "\n";
	cout << "y los crea en la carpeta datos con el nombre backup(i).txt 		   " << "\n";
	cout << "									   " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.bin",argv[1]);
			break;
		};
	

	ifstream *in = new ifstream(fich,ios::in | ios::binary);
	if(!*in) 
		{cout << " ERROR OPENING FILE " <<  fich << endl; 
		return 1;
		}
	else    {
 		/*m3=sprintf(arch1,"header.bin");
		ifstream *in = new ifstream(arch1);
		if(!*in) 
			{cout << " ERROR OPENING FILE " <<  arch1 << endl; 
			return 1;
			}
		i=0;
			while (i==0)
				{
				in->read(dummy,1);  
				if (dummy[0]=='#')
					{
					//cout << dummy << endl;
					in->read(dummy,6);  
					i=1;
					}
				}
		*/
		for (j=0;j<Z;j++) 
			{	
			m=sprintf(arch,"ConvertRPC_D_04_GSI_4400_dobleC1_10nF_560_470_10_Plomo%d.txt",j);  
			ofstream *out = new ofstream(arch);
			i=0;
			while (i==0)
				{
				in->read(dummy,1);  
				if (dummy[0]=='#')
					{
					//cout << dummy << endl;
					in->read(dummy,6);  
					i=1;
					}
				}
			//cout << dummy << endl;
			Char_t *buf = new Char_t[N];
			in->read(buf,N);
			for(i=0;i<N;i++)
    				{
     		 		datosx[i]=XZERO+XINCR*(N-PT_OFF);
     				aux = *(buf+i);
     			 	datosy[i]=YZERO+YMULT*(aux-YOFF);
		 		if (i==0) {*out << XZERO <<endl;
					   *out << XINCR <<endl;}
					 
				else
				    *out << datosy[i-1] <<endl; 
				}
			*out << datosy[i] << endl;
			in->read(dummy,1);  
			delete out;
			}
  		}
	
	}
}

