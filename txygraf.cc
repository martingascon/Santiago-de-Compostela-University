//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa los datos (5 columnas) 
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

#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t x[N],y[N],y2[N],y3[N],y4[N]; 		      
Float_t datosx[N],datosy[N],datosy2[N],datosy3[N],datosy4[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

TH1F *hr = c1->DrawFrame(340,500,420,8000);      // draw a frame to define the range
hr->SetTitle("Eficiencia cuantica de los fotomultiplicadores");	// Escribe como título del grafico lo que hay en titulo
hr->SetXTitle("Longitud de onda (nm)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("QE (%) ");      // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: xygraf [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y]    " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (5 columna) de un fichero ASCII donde  " << "\n";
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
		*in >> datosx[i] >> datosy[i] >> datosy2[i] >> datosy3[i] >> datosy4[i];  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	y3[k]=datosy3[k];
	y4[k]=datosy4[k];
	}

TGraph *gr1 = new TGraph(k,x,y);			// Declaración del gráfico 1.
TGraph *gr2 = new TGraph(k,x,y2);			// Declaración del gráfico 2.
TGraph *gr3 = new TGraph(k,x,y3);			// Declaración del gráfico 3.
TGraph *gr4 = new TGraph(k,x,y4);			// Declaración del gráfico 4.

//gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(1);
gr1->SetMarkerSize(0.7);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
//gr2->SetMarkerColor(kRed);
gr2->SetMarkerStyle(2);
gr2->SetMarkerSize(0.7);
gr2->Draw("p");
//gr3->SetMarkerColor(kGreen);
gr3->SetMarkerStyle(3);
gr3->SetMarkerSize(0.7);
gr3->Draw("p");
//gr4->SetMarkerColor(kYellow);
gr4->SetMarkerStyle(4);
gr4->SetMarkerSize(0.7);
gr4->Draw("p");
//gr1->SetLineStyle(1);
//gr2->SetLineStyle(2);
//gr3->SetLineStyle(3);
//gr4->SetLineStyle(4);

TLegend *legend=new TLegend(0.64,0.61,0.91,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1," XP1901","p");
legend->AddEntry(gr2," XP1912","p");
legend->AddEntry(gr3," XP1918","p");
legend->AddEntry(gr4," XP3102","p");
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(11);             		        // Muestro los datos del Fit
legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
