//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************

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
Float_t mean,sigma,newtrigger, dmean,dsigma,datosy[N],datosy2[N],datosx[N],x[N],y[N],y2[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0);
c1->GetFrame()->SetBorderSize(1);    

//TH1F *hr = c1->DrawFrame(0,0,10000,500);          // draw a frame to define the range
//hr->SetTitle("Espectro de emision de CsI(Tl) ");	// Escribe como título del grafico lo que hay en titulo
//hr->SetXTitle("Longitud de onda (nm)");		// Escribe como titulo del eje x lo que hay en ejex
//hr->SetYTitle("Produccion de luz (fotones/(MeV.nm)) ");// Escribe como titulo del eje y lo que hay en ejey
//hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
//hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: xygraf [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y]    " << "\n";
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
		*in >> datosx[i] >> datosy[i] >> datosy2[i];  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	}

TGraph *gr1 = new TGraph(k,x,y);			// Declaración del gráfico 1.
TGraph *gr2 = new TGraph(k,x,y2);			// Declaración del gráfico 2.


  				
gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(21);
gr1->GetXaxis()->SetLabelSize(0.03);			
gr1->GetYaxis()->SetLabelSize(0.03);	
//gr1->SetTitle("titulo ");				// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle("Amplifier Gain");			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("Photopeak channel");			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();
gr1->Draw("ALP");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(kRed);
gr2->SetMarkerStyle(20);
gr2->Draw("CP");
//gr1->FitPanel();					// Muestra el panel de Fit
TLatex *t = new TLatex();				// Leyenda en cada una de las graficas
   t->SetNDC();
   t->SetTextFont(62);
   t->SetTextColor(36);
   t->SetTextSize(0.08);
   t->SetTextAlign(12);
   t->SetTextSize(0.045);
   t->SetTextColor(kBlue);
   t->DrawLatex(0.20,0.85,"CsI(Tl) - La");
   t->SetTextColor(kRed);
   t->DrawLatex(0.6,0.85,"CsI(Tl) - SG");


TLegend *legend=new TLegend(0.64,0.61,0.99,0.66);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
//legend->Draw();					// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
