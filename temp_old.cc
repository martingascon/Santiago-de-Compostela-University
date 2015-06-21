//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
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


#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t datosx[N],datosy[N],errorx[N],errory[N],x[N],y[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2,fin=1;;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y",ar[100];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);




//TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
//c->Divide(1,1);
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: xerrgraf [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y]  " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (2 columnas) de un fichero ASCII donde " << "\n";
	cout << "la primera y segunda columnas son los datos y la tercera y cuarta columnas" << "\n";
	cout << "son los errores del eje x y del eje y respectivamente			   " << "\n";
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
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i];  
		i++;
		}
	}



Float_t minx,maxx,miny,maxy;
minx = x[0]; maxx = x[0]; miny = y[0]; maxy = y[0];

for (k=1;k<(i-1);k++)	{if (minx> x[k]) minx= x[k];}
for (k=1;k<(i-1);k++)	{if (maxx< x[k]) maxx= x[k];}
for (k=1;k<(i-1);k++)	{if (miny> y[k]) miny= y[k];}
for (k=1;k<(i-1);k++)	{if (maxy< y[k]) maxy= y[k];}


TH1F *hr = c1->DrawFrame((minx-10),(miny-1),(maxx+10),(maxy+1));      
hr->SetXTitle("Temperature ({^0}C)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Photopeak channel");   	// Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);




TGraphErrors *gr1 = new TGraphErrors(k,datosx,datosy,errorx,errory);	



char fitf[100]="pol1";
TF1 *f1 = new TF1("f1",fitf,(minx-0.3),(maxx+0.3)); 
f1->SetParameter(0,1);						// Defino una función TF1 llamada f1 con parametros
f1->SetParameter(1,1);						// 0 y 14 son el intervalo sobre el que se define f1
f1->SetLineColor(kBlue);

gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");							// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr1->Fit("f1","R+");
gr1->SetLineColor(kBlue);
//gr1->Fit("f1","R");						// Hago el Fit en el grafico gr1 de f1 en la region 0 a 14


//c->cd(1);							// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AP");						// Pinta el gráfico A:marco P=puntos L=linea C=curva
//gr1->FitPanel();						// Muestra el panel de Fit


TLegend *legend=new TLegend(0.50,0.81,0.86,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
m=sprintf(ar,"#DeltaG/#DeltaT  = -2.8 % / ^{o}C"); 
legend->AddEntry(gr1,ar,"p");
legend->Draw();	


gStyle->SetOptFit(0);     

//gStyle->SetCanvasBTitle(0);
legend->Draw();							// Dibujo la leyenda 
theApp->Run(kTRUE);						// Para hacer el ejecutable
delete theApp;
return 0;
}
