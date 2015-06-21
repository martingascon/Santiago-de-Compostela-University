//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa los datos (5 columnas) 
#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TGraphErrors.h>
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

#define N 57000 
				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Int_t i,k,j,m,fin;  
char fich[100],serie1[100]="serie 1",serie2[100]="serie 2",ar[100],ar2[100];
Float_t a,b,c,d;    
Float_t y[N],datosy[N]; 		      
Float_t x[N],datosx[N];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: chtohv [FICHERO](sin extens.) [Nom-1ºSer] [Nombre-2ºSer]  " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (2 columna) de un fichero ASCII donde  " << "\n";
	cout << "la primera columna son los datos del eje X, la segunda columna son los    " << "\n";
	cout << "datos del eje Y 							   " << "\n";	
	cout << "									   " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.txt",argv[1]);
			break;
		case 3: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(serie1,"%s",argv[2]);
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(serie1,"%s",argv[2]);
			m=sprintf(serie2,"%s",argv[3]);
			break;
		};
	}
ifstream *in = new ifstream(fich);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  fich << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		*in >> datosx[i] >> datosy[i];  
		i++;
		}
	}


for (k=0;k<i-1;k++)
	{
	 datosx[k] = k;         
	}

j=0;

TH1F *gr1 = new TH1F("H",fich,53180,1,53180); 
for (k=0;k<i-1;k++)
	{
	if ((datosy[k]>18.0)&&(datosy[k]<25.0)) 	
		{		
		x[j] = datosx[k];         
		y[j] = datosy[k];
		//cout << x[j] << " " << y[j] << endl;
		gr1->SetBinContent(((int)x[j]),y[j]);		
		j++;		
		cout << j << " " << x[j] << endl;
		}
	}
cout << j << " " << i << endl;
k=0;
fin=1;

Float_t minx,maxx,miny,maxy;
minx = x[0]; maxx = x[0]; miny = y[0]; maxy = y[0];

for (k=1;k<(j-1);k++)	{if (minx> x[k]) minx= x[k];}
for (k=1;k<(j-1);k++)	{if (maxx< x[k]) maxx= x[k];}
for (k=1;k<(j-1);k++)	{if (miny> y[k]) miny= y[k];}
for (k=1;k<(j-1);k++)	{if (maxy< y[k]) maxy= y[k];}

cout << miny << " " << maxy << endl;

   
gr1->SetXTitle("time (s)");		// Escribe como titulo del eje x lo que hay en ejex
gr1->SetYTitle("Temperature (^{o}C)");   		// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
gr1->GetXaxis()->SetLabelColor(1);			
gr1->GetYaxis()->SetLabelColor(1);
gr1->Draw();



theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
