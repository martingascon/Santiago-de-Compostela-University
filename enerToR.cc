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
#include <strings.h>

#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N],d,e,f,g,h,o1,o2,o3,pra,prb; 	
Float_t datosx22[N],datosy22[N],datosy22[N],errorx22[N],errory222[N],errory222[N];

Float_t x2[N],y22[N],y222[N],ex2[N],ey22[N],ey222[N];
Int_t i,j,k,l,xini,tim,oldtim,m,m1,m2;  
char titulo[100]="titulo",fich[100],fich2[100],serie1[100]="serie 1",serie2[100]="serie 2";
char fitf[100]="([0]+[1]/sqrt(x) )",ar[100],ar2[100];//)"
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,1500,35);      
hr->SetXTitle("Energy photon (keV)");	// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);



//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: nonUnif [FICHERO](sin extens.) [Nom-1ºSer] [Nombre-2ºSer]  " << "\n";
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
			m=sprintf(fich2,"%s.txt",argv[2]);
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
		*in >> datosx[i] >> errorx[i] >> datosy2[i] >> errory2[i] >> datosy[i] >> errory[i] ;  
		i++;
		}
	}

pra=0;prb=0;
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}


TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);	
TF1 *f1 = new TF1("f1",fitf,50,1400); 
f1->SetParameter(0,3);				
f1->SetParameter(1,1);
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr1->Fit("f1","R+");
d=f1->GetParameter(0);
f=f1->GetParError(0);

TLegend *legend=new TLegend(0.54,0.71,0.89,0.86);	// Declaración de la leyenda
TLegend *legend2=new TLegend(0.19,0.2,0.57,0.34);
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
m=sprintf(ar,"#delta = (%.2f #pm %.2f) %%",d*100,f*100);//,d,e);
legend2->AddEntry(gr1,ar,"p");				// Añado entrada a la leyenda
legend->Draw();	

if (argc==3)
	{
	ifstream *in2 = new ifstream(fich2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  fich2 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in2->eof())
			{
			*in >> datosx22[i] >> errorx22[i] >> datosy22[i] >> errory22[i] >> datosy222[i] >> errory222[i] ;  
			i++;
			}
		}
	

	pra=0;prb=0;
	for (k=0;k<i-1;k++)
		{
		x2[k]=datosx22[k];         
		y2[k]=datosy22[k];
		y22[k]=datosy22[k];
		ex22[k]=errorx22[k];   
		y222[k]=datosy222[k];
		ey222[k]=errory222[k];
		}

	TGraphErrors *gr2 = new TGraphErrors(k,x2,y222,ex22,ey222);			// Declaración del gráfico 2.
	TF1 *f2 = new TF1("f2",fitf,50,1400); 
	f2->SetParameter(0,3);				
	f2->SetParameter(1,1);
	gr2->SetMarkerColor(kBlue);
	gr2->SetMarkerStyle(21);
	gr2->SetMarkerSize(1.5);
	gr2->Draw("p");
	gr2->Fit("f2","R+");
	e=f2->GetParameter(0);
	h=f2->GetParError(0);

	legend->AddEntry(gr2,serie2,"p");
	m1=sprintf(ar2,"#delta = (%.2f #pm %.2f) %%",e*100,h*100);//,d,e);
	legend2->AddEntry(gr2,ar2,"p");
	legend2->Draw();
	}

gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
