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
char titulo[100]="CsI(Tl) + PMT ...",arch[100],fich[100], ejex[100]="Canal", ejey[100]="Amplitud (V)";
Float_t x[N],y[N],datosy[N], area1=0,area2=0; 	     		// Datos en canal x e y 
Int_t i,j,k,m,nini=1,nfin,a=0,l=0,p=0,r=0,ts=0bac;
                         

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
			nfin=atoi(argv[2]);
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			nini=atoi(argv[2]);
			nfin=atoi(argv[3]);
			break;
		case 6: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			m=sprintf(ejex,"%s",argv[3]);
			m=sprintf(ejey,"%s",argv[4]);
			break;
		};
	}
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

for (j=nini;j<(nfin+1);j++) 
{
	m=sprintf(arch,"suma%d.txt",j);  
	ifstream *in = new ifstream(arch);                              // Abrimos el fichero que se guarda en fich
	if(!*in) 							// Si no se puede abrir
		{cout << " ERROR OPENING FILE " <<  fich << endl; 	// Imprime que hay un error
		return 1;						// Salida 1 => error
		}
	else    {
		i=0;
		while (!in->eof())					// Mientras no llegue al final
			{
			*in >> datosy[i];  
			i++;						// Lea el fichero e incremente i
			}
		}
	
	while ((a==0)&&(l<2500))					// Mientras no llegue al final
		{
		if (datosy[l]>(-0.002))  
		l++;						// Lea el fichero e incremente i
		else
		   a=1;
		}
	l=6000;	
	while ((a==0)&&(l<10000))					// Mientras no llegue al final
		{
		if (datosy[l]>(-0.005))  
		l++;						// Lea el fichero e incremente i
		else
		   a=1;
		}

	if (a==0)
		{
		for (k=0;k<i-1;k++)
			{
			x[k]=k;
			if (j==3) {y[k]=datosy[k]/823; area1=area1+y[k];}
			if (j==4) {y[k]=datosy[k]/725;area2=area2+y[k];}
			}
		for (k=0;k<i;k++)
			{
			if ((datosy[k] < (-0.005))&&(r!=1))
				{ts=k-2500;r=1;}
			}
		for (k=1000;k<i;k++)
			{
			if (datosy[k+ts]>0) datosy[k+ts]=0;
			x[k-1000]=x[k-1000]-datosy[k+ts];
			}
		
		p++;
		TGraph *graf1 = new TGraph(k,x,y);
		if (j==nini) graf1->Draw("ALP");
		else graf1->Draw("LP");
		}
	r=0;
	a=0;
	l=0;
	delete in; 
}
//TLegend *legend=new TLegend(0.64,0.61,0.91,0.86);
//gStyle->SetOptFit(11);             		        // Muestro los datos del Fit
//legend->Draw();						// Dibujo la leyenda
cout << area1 << endl;
cout << area2 << endl;
cout << p << endl;
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

