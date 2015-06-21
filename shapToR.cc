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

#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N],d,e,f,g,h,o1,o2,o3; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],serie1[100]="serie 1",serie2[100]="serie 2";
char fitf[100]="([0]+[1]*exp(x*[2])+[3]*exp(-x*[4]))",ar[100];//)" 
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: timeToR [FICHERO](sin extens.) [Nom-1ºSer] [Nombre-2ºSer]  " << "\n";
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
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}


Float_t minx,maxx,miny,maxy;
minx = x[0]; maxx = x[0]; miny = y[0]; maxy = y[0];

for (k=1;k<(i-1);k++)	{if (minx> x[k]) minx= x[k];}
for (k=1;k<(i-1);k++)	{if (maxx< x[k]) maxx= x[k];}
for (k=1;k<(i-1);k++)	{if (miny> y[k]) miny= y[k];}
for (k=1;k<(i-1);k++)	{if (maxy< y[k]) maxy= y[k];}

TH1F *hr = c1->DrawFrame((minx-10),(miny-1),(maxx+10),(maxy+1));  

hr->SetXTitle("Shaping time (#mus)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);	






TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.

TF1 *f1 = new TF1("f1",fitf,0.3,14); 
f1->SetParameter(0,6);				
f1->SetParameter(1,-30);
f1->SetParameter(2,0.01);
f1->SetParameter(3,-3);
f1->SetParameter(4,0.01);

TF1 *f2 = new TF1("f2",fitf,0.3,14); 
f2->SetParameter(0,10);				
f2->SetParameter(1,-29);
f2->SetParameter(2,0.001);
f2->SetParameter(3,-3);
f2->SetParameter(4,0.1);


f1->SetLineColor(kBlue);
f2->SetLineColor(kRed);

gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(kRed);
gr2->SetMarkerStyle(21);
gr2->SetMarkerSize(1.5);
gr2->Draw("p");


gr1->Fit("f1","R+");
gr2->Fit("f2","R+");



TLegend *legend=new TLegend(0.54,0.61,0.91,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");

//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda

legend->Draw();	
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit

legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
