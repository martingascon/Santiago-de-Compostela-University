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

#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t mean,sigma,newtrigger, dmean,dsigma,datosy[N],datosx[N],x[N],y[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y";
TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->Divide(1,1);
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: xgraf [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y]     " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (1 columna) de un fichero ASCII donde  " << "\n";
	cout << "la primera columna son los datos del eje Y, mientras que el programa crea " << "\n";
	cout << "los datos del eje X, como números naturales desde 1 hasta numero de datos " << "\n";	
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
			m=sprintf(titulo,"%s",argv[2]);
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			m=sprintf(ejex,"%s",argv[3]);
			break;
		case 6: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			m=sprintf(ejex,"%s",argv[3]);
			m=sprintf(ejey,"%s",argv[4]);
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
		*in >> datosy[i];  
		i++;
		}
	}
for (k=1;k<i;k++)
	{
	x[k]=k;                 
	y[k-1]=datosy[k-1];
	}

TGraph *gr1 = new TGraph(k,x,y);			// Declaración del gráfico.
gr1->SetLineColor(2);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(4);					// Ancho de la linea 0=blanco 1=negro, 2=rojo
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(21);				// Estilo del punto 21 = cuadrado
gr1->SetTitle(titulo);					// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

c->cd(1);						// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AP");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr1->FitPanel();					// Muestra el panel de Fit

TLegend *legend=new TLegend(0.64,0.61,0.99,0.66);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(11);             		        // Muestro los datos del Fit
//legend->Draw();					// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
