#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TRint.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>

#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t datos[N],datos1[N],x[N],y[N]; 		      
Float_t integral=0,siga=1.8,sigb=1.8,aux=0;
Int_t i,j,k,l,xini,tim,oldtim,m,m2,m3,a=3500,b=4500,fin,ffi;  
char ar[100],arch[100],arch1[100],arch2[100],title[150],ci[100]="";

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "falta el nombre del archivo a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "espectro [nombre-fichero1](sin extension) [nombre-fichero2](sin extension)" << "\n";
	cout << "[nombre-fichero-final](sin extension)" << "\n";
	cout << "************************************************************************" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: cout << "faltan datos del fit" << "\n"; break;
		case 3: m=sprintf(arch,"%s.mca",argv[1]);
			m3=sprintf(arch2,"%s.mca",argv[2]);
			break;
		
		
		};
	}
ifstream *in = new ifstream(arch);
ofstream *out = new ofstream(arch2);
//ofstream *out = new ofstream("fotopico.txt");
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  arch << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in >> ci;
		if ((strstr(ci,"DATA")!=NULL))	i=0;
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in >> datos[i];                  
	delete in;   
	}


m=sprintf(ar,"DATA");
*out << ar << endl;
for (k=0;k<(N-501);k++)
	{
	aux=(datos[k+500]/8);
	cout << aux << endl;
	if ((datos[k]-Int_t(aux))<0) 
		*out << 0 << endl;
	else
     		*out << (datos[k]-Int_t(datos[k+500]/8)) << endl;
	
	}
for (k=(N-501);k<N;k++)
	{
	*out << 0 << endl;
	}

delete out;
return 0;
}
