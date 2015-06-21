//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Programa para representar un pantallazo del Osciloscopio

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
char titulo[100]="CsI(Tl) + PMT 1901", fich[100], ejex[100]="time (ns)", ejey[100]="Amplitude (V)",ar[100];
Float_t x[N],y[N],datosy[N], area,d,e,f,g,h; 	     		// Datos en canal x e y 
Int_t i,j,k,m,a=1800,b=8000;
char fitf[100]="([0]*exp(-(x-1800)/[1])+[2]*exp(-(x-1800)/[3]))";//)"                        

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);


//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: represent [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y] " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (1 columna) de un fichero ASCII 	   " << "\n";
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
ifstream *in = new ifstream(fich);                              // Abrimos el fichero que se guarda en fich
if(!*in) 							// Si no se puede abrir
	{cout << " ERROR OPENING FILE " <<  fich << endl; 	// Imprime que hay un error
	return 1;						// Salida 1 => error
	}
else    {
	i=0;
	while (!in->eof())					// Mientras no llegue al final
		{
		*in >> datosy[i];  
		//cout << datosy[i] << endl;
		i++;						// Lea el fichero e incremente i
		}
	}
area=0;
for (k=0;k<i-1;k++)
	{
	x[k]=k;
	y[k]=datosy[k];
	area+=y[k];
	}
delete in; 

TGraph *graf1 = new TGraph(k,x,y);
graf1->SetMarkerColor(2);
graf1->SetFillColor(19);
graf1->SetLineColor(2);
graf1->SetLineWidth(1);
graf1->SetMarkerStyle(8);
graf1->SetMarkerSize(0.1);
graf1->SetTitle(titulo);
graf1->GetXaxis()->SetTitle(ejex);
graf1->GetYaxis()->SetTitle(ejey);
graf1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
graf1->GetYaxis()->CenterTitle();
graf1->GetYaxis()->SetTitleOffset(1.3);
graf1->GetYaxis()->SetLabelSize(0.035);
graf1->GetXaxis()->SetLabelSize(0.035);
graf1->Draw("ALP*");
TF1 *f1 = new TF1("f1",fitf,a,b); 

f1->SetParameter(0,20);				
f1->SetParameter(1,500);				
f1->SetParameter(2,10);	
f1->SetParameter(3,2000);	

graf1->Fit("f1","R");
TLegend *legend=new TLegend(0.40,0.75,0.90,0.90,"funcion ajustada");	// Declaración de la leyenda
legend->SetTextFont(72);						// Tipo de fuente de la leyenda
legend->SetTextFont(1);	
legend->SetTextSize(0.025);						// Tamaño de la fuente de la leyenda

d=f1->GetParameter(0);
e=f1->GetParameter(1);
f=f1->GetParameter(2);
g=f1->GetParameter(3);

m=sprintf(ar,"y(x) = %.4f*exp(-x/%.0f)+%.4f*exp(-x/%.0f)",d,e,f,g);//,d,e);	// Introduce una leyenda con datos
legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
legend->Draw();		
//TLegend *legend=new TLegend(0.64,0.61,0.91,0.86);
//gStyle->SetOptFit(11);             		        // Muestro los datos del Fit
//legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

