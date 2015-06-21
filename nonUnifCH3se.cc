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
Float_t x[N],y[N],y2[N],y3[N];    
Float_t datosx[N],datosy[N],datosy2[N],datosy3[N],d,e,e2,e3,f,g,h,o1,o2,o3,pra,prb,prc; 		      
Float_t max_a,max_b,min_a,min_b,max_c,min_c,g1,g2,g3; 	

Int_t i,j,k,l,xini,tim,oldtim,m,m1,m2;  
char titulo[100]="titulo",fich[100],serie1[100]="PM1",serie2[100]="PM2",serie3[100]="PM1+PM2";
char fitf[100]="pol1",ar[100],ar2[100],ar3[100];//)"
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,20,8000);      
hr->SetXTitle("Distance from the detector (cm)");	// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Photopeak channel");   	        // Escribe como titulo del eje y lo que hay en ejey
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
		*in >> datosx[i] >> datosy[i] >> datosy2[i] >> datosy3[i] ;  
		i++;
		}
	}
pra=0;prb=0;
max_a=datosy[0];max_b=datosy2[0];
min_a=datosy[0];min_b=datosy2[0];
min_c=datosy3[0];max_c=datosy3[0];
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	y3[k]=datosy3[k];
	if (datosy[k]>max_a) max_a=datosy[k];if (datosy2[k]>max_b) max_b=datosy2[k];if (datosy3[k]>max_c) max_c=datosy3[k];
	if (datosy[k]<min_a) min_a=datosy[k];if (datosy2[k]<min_b) min_b=datosy2[k];if (datosy3[k]<min_c) min_c=datosy3[k];
	pra=pra+datosy[k];
	prb=prb+datosy2[k];
	prc=prc+datosy3[k];

	}
pra=pra/k;
prb=prb/k;
prc=prc/k;

TGraph *gr1 = new TGraph(k,x,y);			// Declaración del gráfico 1.
TGraph *gr2 = new TGraph(k,x,y2);			// Declaración del gráfico 2.
TGraph *gr3 = new TGraph(k,x,y3);

TF1 *f1 = new TF1("f1",fitf,0.5,19); 
f1->SetParameter(0,-0.003);				


TF1 *f2 = new TF1("f2",fitf,0.5,19); 
f2->SetParameter(0,-0.003);				

TF1 *f3 = new TF1("f3",fitf,0.5,19); 
f3->SetParameter(0,-0.003);

gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(kRed);
gr2->SetMarkerStyle(21);
gr2->SetMarkerSize(1.5);
gr2->Draw("p");

gr3->SetMarkerColor(kGreen);
gr3->SetMarkerStyle(23);
gr3->SetMarkerSize(1.5);
gr3->Draw("p");





gr1->Fit("f1","R+");
d=f1->GetParameter(0);
f=f1->GetParError(0);
gr2->Fit("f2","R+");
e=f2->GetParameter(0);
h=f2->GetParError(0);
gr3->Fit("f3","R+");
e2=f3->GetParameter(0);
e3=f3->GetParError(0);


TLegend *legend=new TLegend(0.54,0.71,0.89,0.86);	// Declaración de la leyenda
TLegend *legend2=new TLegend(0.19,0.2,0.57,0.34);

legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");
legend->AddEntry(gr3,serie3,"p");


g1=(max_a-min_a)/pra;
g2=(max_b-min_b)/prb;
g3=(max_c-min_c)/prc;

m=sprintf(ar,"G = (%.1f #pm %.1f) %%",g1*100,0.1);//,d,e);
m1=sprintf(ar2,"G = (%.1f #pm %.1f) %%",g2*100,0.1);//,d,e);
m2=sprintf(ar3,"G = (%.1f #pm %.1f) %%",g3*100,0.1);//,e2,e3);

legend2->AddEntry(gr1,ar,"p");				// Añado entrada a la leyenda
legend2->AddEntry(gr2,ar2,"p");			        // Añado entrada a la leyenda
legend2->AddEntry(gr3,ar3,"p");

gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
legend->Draw();					        // Dibujo la leyenda 1
legend2->Draw();					// Dibujo la leyenda 2
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
