#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TFile.h>
#include <TObject.h>
#include <TGraphErrors.h>
#include <TRint.h>
#include <TH1.h>
#include <TFrame.h>
#include <TH1I.h>
#include <TSpectrum.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TBrowser.h>
#include <TMath.h>
#include <TTree.h>
#include <strings.h>


#define N 8192 			
using namespace std;


int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);



Int_t m,k,i,fin,ent;
char arch[100];

//TH1I *H = new TH1I("H",arch,8192,0,8191); 
gROOT->SetStyle("Bold"); 
TFile *fichroot=new TFile("espectros.root","READ");		// abre un fichero root

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);


//*********************************** Cuerpo del programa   *************************************
if (argc<1){
	cout << "Falta el nombre del grafico a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "browser [nombre-grafico] 						 " << "\n";
	cout << "									 " << "\n";
	cout << "************************************************************************" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch,"%s",argv[1]);
			break;
		case 3: cout << "Demasiados parámetros" << "\n";
			break;
		case 4: cout << "Demasiados parámetros" << "\n";
			break;
		case 5: cout << "Demasiados parámetros" << "\n";
			break;
		case 6: cout << "Demasiados parámetros" << "\n"; 
			break;
			
		};
	}

gStyle->SetOptStat(0); 
TBrowser *br=new TBrowser("br",fichroot);
TTree *tree =(TTree*)fichroot->Get("tree");
  
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N],a1,a2,a3; 
for (i=0;i<N;i++) ex[N]=1;
 


if (((strcmp(arch,"chGToR"))==0) ||((strcmp(arch,"chGtoR"))==0))      ///**********************************************************************    chGToR   
{
	tree->SetBranchAddress("resolution",&a1);		// CARGO LAS RAMAS DEL TREE
	tree->SetBranchAddress("voltaje",&a2);
	tree->SetBranchAddress("deltar",&a3);
	ent=tree->GetEntries();
	for (i=0;i<ent;i++)					// METO LOS VALORES EN MIS VARIABLES
		{
		tree->GetEntry(i);
		x[i]=a2;
		y[i]=a1;
		ex[i]=a3;
		}
	for (i=0;i<(ent/2);i++)                        		     // HAGO EL PROMEDIO
		{
		x[i]=x[i*2];
	 	y[i]=(y[2*i]+y[2*i+1])/2;
		}
	k=0;
	fin=1;
	i=ent/2;
	Float_t minx,maxx,miny,maxy;				        // BUSCO EL MÁXIMO Y EL MINIMO
	minx = x[0]; maxx = x[0]; miny = y[0]; maxy = y[0];
	for (k=0;k<(i-1);k++)	{if (minx> x[k]) minx= x[k];}
	for (k=0;k<(i-1);k++)	{if (maxx< x[k]) maxx= x[k];}
	for (k=0;k<(i-1);k++)	{if (miny> y[k]) miny= y[k];}
	for (k=0;k<(i-1);k++)	{if (maxy< y[k]) maxy= y[k];}
	
	TH1F *hr = c1->DrawFrame((minx-10),(miny-1),(maxx+10),(maxy+1));      // DEFINO EL HISTOGRAMA  
	hr->SetXTitle("High Voltage (V)");		// Escribe como titulo del eje x lo que hay en ejex
	hr->SetYTitle("Energy resolution (%)");   	// Escribe como titulo del eje y lo que hay en ejey
	hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
	hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
	hr->GetXaxis()->SetLabelColor(1);			
	hr->GetYaxis()->SetLabelColor(1);

	char fitf[100]="pol2";						//FUNCIÓN A AJUSTAR y PARAMETROS
	TF1 *f1 = new TF1("f1",fitf,(minx-4),(maxx+5)); 		// DECLARO LA FUNCION PARA FITEAR
	f1->SetLineColor(kBlue);

	//TF1 *f2 = new TF1("f2",fitf,(minx-4),(maxx+5)); 


	TGraphErrors *gr1 = new TGraphErrors(ent/2,x,y,ex,ey);			// Declaración del gráfico 1.
	gr1->SetMarkerColor(kBlue);
	gr1->SetMarkerStyle(22);
	gr1->SetMarkerSize(1.5);
	gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
	gr1->Fit("f1","R+");
	gr1->SetLineColor(kBlue);

	//TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.

}
if (((strcmp(arch,"timeToR"))==0) ||((strcmp(arch,"timetoR"))==0))      ///**********************************************************************       timeToR  
	{
	tree->SetBranchAddress("resolution",&a1);		// CARGO LAS RAMAS DEL TREE
	tree->SetBranchAddress("acqtime",&a2);
	tree->SetBranchAddress("deltar",&a3);
	ent=tree->GetEntries();
	for (i=0;i<ent;i++)					// METO LOS VALORES EN MIS VARIABLES
		{
		tree->GetEntry(i);
		x[i]=a2;
		y[i]=a1;
		ey[i]=a3;
		}

	for (i=0;i<(ent/2);i++)                        		     // HAGO EL PROMEDIO
		{
		x[i]=x[i*2];
	 	y[i]=(y[2*i]+y[2*i+1])/2;
		}

	k=0;
	fin=1;
	i=ent/2;
	Float_t minx,maxx,miny,maxy;				        // BUSCO EL MÁXIMO Y EL MINIMO
	minx = x[0]; maxx = x[0]; miny = y[0]; maxy = y[0];
	for (k=0;k<(ent/2);k++)	{if (minx> x[k]) minx= x[k];}
	for (k=0;k<(ent/2);k++)	{if (maxx< x[k]) maxx= x[k];}
	for (k=0;k<(ent/2);k++)	{if (miny> y[k]) miny= y[k];}
	for (k=0;k<(ent/2);k++)	{if (maxy< y[k]) maxy= y[k];}


	TH1F *hr = c1->DrawFrame((minx-10),(miny-1),(maxx+10),(maxy+1));         // DEFINO EL HISTOGRAMA     
	hr->SetXTitle("Acq. time (s)");			// Escribe como titulo del eje x lo que hay en ejex
	hr->SetYTitle("Energy resolution (%)");   	// Escribe como titulo del eje y lo que hay en ejey
	hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
	hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
	hr->GetXaxis()->SetLabelColor(1);			
	hr->GetYaxis()->SetLabelColor(1);

	char fitf2[100]="([0]+[1]*exp(x*[2])+[3]*exp(-x*[4]))";		//FUNCIÓN A AJUSTAR y PARAMETROS
	TF1 *f1 = new TF1("f1",fitf2,(minx-4),(maxx+15));  		// DECLARO LA FUNCION PARA FITEAR
	f1->SetParameter(0,10);				
	f1->SetParameter(1,-3);
	f1->SetParameter(2,0.0001);
	f1->SetParameter(3,3);
	f1->SetParameter(4,0.1);
	f1->SetLineColor(kBlue);

	//TF1 *f2 = new TF1("f2",fitf2,(minx-4),(maxx+5)); 



	TGraphErrors *gr1 = new TGraphErrors(ent/2,x,y,ex,ey);			// Declaración del gráfico 1.
	gr1->SetMarkerColor(kBlue);
	gr1->SetMarkerStyle(22);
	gr1->SetMarkerSize(1.5);
	gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
	gr1->Fit("f1","R+");
	gr1->SetLineColor(kBlue);

	//TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.



	
	


}
//tree->Draw("photopeak:photopeakerr","","")

//c->Write(argv[1]);
//fichroot->Close();


theApp->Run(kTRUE);
//delete theApp;
return 0;
}
