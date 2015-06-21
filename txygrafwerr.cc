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
Float_t x[N],y[N],y2[N],y3[N],y4[N],ex[N],ey[N],ey2[N],ey3[N],ey4[N];    
Float_t datosx[N],datosy[N],datosy2[N],datosy3[N],datosy4[N],errorx[N],errory[N],errory2[N],errory3[N],errory4[N],d,e,f,g,h,o1,o2,o3; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y";
char fitf[100]="([0]+[1]*exp(-x*[2]))",ar[100];//)" 
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,420,10000);      // draw a frame to define the range
//hr->SetTitle("Eficiencia cuantica de los fotomultiplicadores");	// Escribe como título del grafico lo que hay en titulo
hr->SetXTitle("time (s)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");      // Escribe como titulo del eje y lo que hay en ejey
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
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] >> datosy3[i] >> errory3[i] >> datosy4[i] >> errory4[i];  
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
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	ey3[k]=errory3[k];
	ey4[k]=errory4[k];


	}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.
TGraphErrors *gr3 = new TGraphErrors(k,x,y3,ex,ey3);			// Declaración del gráfico 3.
TGraphErrors *gr4 = new TGraphErrors(k,x,y4,ex,ey4);			// Declaración del gráfico 4.

TF1 *f1 = new TF1("f1",fitf,330,420); 
f1->SetParameter(0,10);				
f1->SetParameter(1,-29);
f1->SetParameter(2,0.1);
//f1->SetParameter(3,-307);
//f1->SetParameter(4,0.1);

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
gr4->SetMarkerColor(kBlue);
gr4->SetMarkerStyle(20);
gr4->SetMarkerSize(1.5);
gr4->Draw("p");
//gr1->SetLineStyle(1);
//gr2->SetLineStyle(2);
//gr3->SetLineStyle(3);
//gr4->SetLineStyle(4);
gr1->Fit("f1","R+");
TF1 *f2 = new TF1("f2",fitf,330,420); 
f2->SetParameter(0,10);				
f2->SetParameter(1,-29);
f2->SetParameter(2,0.1);
//f2->SetParameter(3,-307);
//f2->SetParameter(4,0.1);
gr2->Fit("f2","R+");
TF1 *f3 = new TF1("f3",fitf,330,420);
f3->SetParameter(0,10);				
f3->SetParameter(1,-29);
f3->SetParameter(2,0.1);
//f3->SetParameter(3,-307);
//f3->SetParameter(4,0.1);
gr3->Fit("f1","R+");
d=f1->GetParameter(0);
e=f1->GetParameter(1);
f=f1->GetParameter(2);
g=f1->GetParameter(3);
h=f1->GetParameter(4);
m=sprintf(ar,"y(x) = %.1f+%.1f*exp(-x*%.1f)+%.1f/exp(-x*%.1f))",d,e,f,g,h);//,d,e);

TLegend *legend=new TLegend(0.54,0.61,0.91,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1," CsI(Tl) 1 cm","p");
legend->AddEntry(gr2," CsI(Tl) 5 cm","p");
legend->AddEntry(gr3," CsI(Tl) 10 cm","p");
legend->AddEntry(gr4," CsI(Tl) 20 cm","p");
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
o1= d*exp(390*e)-d*exp(370*e);
o2= d*exp(380*e)+f;
o3= (o1/(float)o2)/20.0*100;
m=sprintf(ar,"%.4f",o3);
//legend->AddEntry(ar,ar,"p");
//legend->Draw();	
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit

legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
