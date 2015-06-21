//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Programa para sumar archivos

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TRint.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>

#define N 10000 				        // Número máximo de Datos 

using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Leye","leyenda");
char titulo[100]="CsI(Tl) + PMT ...", fich[100], ejex[100]="Canal", ejey[100]="Amplitud (V)";
Float_t x[N],y[N],datosy[N], area; 	     		// Datos en canal x e y 
Int_t i,j,k,m,nfin,nini;
char arch[100],arch1[100];                         
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: sumar [FICHERO](sin extens.) [inicial] [final]            " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa suma los datos (1 columna) de n ficheros ASCII y los escribe" << "\n";
	cout << "en un fichero llamado Suma " 		   				     <<	"\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
		case 3: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			nini=atoi(argv[2]);
			nfin=atoi(argv[3]);
			break;
		case 6: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA"  << endl;
			break;
		};
	}
for (i=0;i<N;i++)
	{
	x[i]=0;
	}
for (j=nini;j<(nfin+1);j++) 
	{
	m=sprintf(arch,"backup_%d.txt",j);  
	ifstream *in = new ifstream(arch);
	if(!*in) 							// Si no se puede abrir
		{cout << " ERROR OPENING FILE " <<  fich << endl; 	// Imprime que hay un error
		return 1;						// Salida 1 => error
		}
	else    {
		i=0;
		while (!in->eof())					// Mientras no llegue al final
			{
			*in >> datosy[i];  
			i++;						// Lea el fichero e incremente i
			}
		}
	for (k=0;k<i;k++)
		{
		x[k]=x[k]+datosy[k];
		}
	delete in; 
	}



ofstream *out = new ofstream("suma");
for (k=0;k<N;k++)
	{
	*out << x[k] << endl;
	}
delete out;


theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

