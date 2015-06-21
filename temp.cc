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
TStyle *plain = new TStyle("Plain","leyenda");
plain->SetCanvasBorderMode(0);
plain->SetPadBorderMode(0);
plain->SetPadColor(0);
plain->SetCanvasColor(0);
plain->SetTitleColor(0);
plain->SetStatColor(0);
gROOT->SetStyle("Pub");
Float_t datosx[N],datosy[N],errorx[N],errory[N],x[N],y[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y",ar[100];
TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->Divide(1,1);
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


TGraphErrors *gr1 = new TGraphErrors(i-1,datosx,datosy,errorx,errory);	// Declaración del gráfico.
gr1->SetLineColor(1);						// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);						// Ancho de la linea 0=blanco 1=negro, 2=rojo
gr1->SetMarkerColor(2);						// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(21);					// Estilo del punto 21 = cuadrado
//gr1->SetTitle(titulo);					// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle("Temperature (ºC)");			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("Photopeak channel");		// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->SetLabelSize(0.03);
gr1->GetYaxis()->SetLabelSize(0.03);
gr1->GetXaxis()->CenterTitle();					// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();					// Para centrar el titulo del eje x

TF1 *f1 = new TF1("f1","pol1",22,26); 		//*([5]-[3]*exp(-x*[4]))",0,14); 
f1->SetParameter(0,6.5);					// Defino una función TF1 llamada f1 con parametros
f1->SetParameter(1,0.5);						// 0 y 14 son el intervalo sobre el que se define f1
f1->SetParameter(2,0.3);						// Asigno valores a los parametros (numero, valor)
//f1->SetParameter(3,0.1);
//f1->SetParameter(4,0.1);
//f1->SetParameter(5,1);
gr1->Fit("f1","R");						// Hago el Fit en el grafico gr1 de f1 en la region 0 a 14


c->cd(1);							// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AP");						// Pinta el gráfico A:marco P=puntos L=linea C=curva
//gr1->FitPanel();						// Muestra el panel de Fit

TLegend *legend=new TLegend(0.64,0.61,0.99,0.66,"ajuste");	// Declaración de la leyenda
legend->SetTextFont(72);					// Tipo de fuente de la leyenda


//m=sprintf(ar,"(%.1f+%.1f*exp(-x*%.1f))",f1->GetParameter(0),f1->GetParameter(1),f1->GetParameter(2));  									// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");					// Añado entrada a la leyenda
//gStyle->SetStyle("Pub"); 
gStyle->SetOptFit(0);             		        	// Muestro los datos del Fit
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);

//gStyle->SetCanvasBTitle(0);
//legend->Draw();							// Dibujo la leyenda 
theApp->Run(kTRUE);						// Para hacer el ejecutable
delete theApp;
return 0;
}
