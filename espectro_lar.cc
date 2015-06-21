//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa un espectro mca
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TRint.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>
#include <TMath.h>
#include <TRandom.h>

#define N 16384				       // Número máximo de Datos por Canal
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N]; 		      
Float_t siga=1.8,sigb=1.8;
Int_t i,k,m,a=1,b=1000,cont=0,fin,ffi,reb=8;  
char ar[100],arch[100],title[150]="",ci[100]="";
TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
c->Divide(1,1);
TH1I *H = new TH1I("H",arch,2500,0,2500); 
gROOT->SetStyle("Bold");

TRandom q;
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Falta el nombre del archivo a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "espectro [nombre-fichero] [canal-ini-fit] [canal-fin-fit]" << "\n";
	cout << "[sigmas a izq] [sigmas a derecha]" << "\n";
	cout << "************************************************************************" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch,"%s.mca",argv[1]);
			break;
		case 3: m=sprintf(arch,"%s.mca",argv[1]);
			reb=atoi(argv[2]);
			break;
		case 4: m=sprintf(arch,"%s.mca",argv[1]);
			fin=atoi(argv[2]);ffi=atoi(argv[3]);
			a=fin;b=ffi;
			
			break;
			
		case 5: {
			m=sprintf(arch,"%s.mca",argv[1]);
			reb=atoi(argv[2]);
			fin=atoi(argv[3]);ffi=atoi(argv[4]);
			a=fin;b=ffi;
			break;
			}
		case 6: {
			m=sprintf(arch,"%s.mca",argv[1]);
			fin=atoi(argv[2]);ffi=atoi(argv[3]);
			a=fin;b=ffi;
			siga=atof(argv[4]);sigb=atof(argv[5]);
			cout << sigb  << siga <<endl;
			break;
			}
		};
	}
cout << arch << endl;
ifstream *in = new ifstream(arch);

if(!*in) 
	{cout << " ERROR OPENING FILE " <<  arch << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in >> ci;
		//if ((strstr(ci,"LIVE_TIME")!=NULL))  strcpy(livetime,ci);
		//if ((strstr(ci,"START_TIME")!=NULL))  strcpy(starttime,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in;   
	}
for (k=0;k<N;k++)
	{
	x[k]=0.150103*(k+(q.Uniform(1)-0.5))+0.422616;                 
	y[k]=datos[k];
	H->Fill(x[k],y[k]);
	}
//m2=sprintf(title,"%s ",argv[1]);
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Energy (keV)");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();

//c->cd(1);

//H->Rebin(reb);
H->Draw();



gStyle->SetOptStat(0);   
gStyle->SetOptFit(0);     
theApp->Run(kTRUE);


/*
cout << "Desea guardar el grafico y sus parámetros (s/n)" << endl;
cin >> res[0];
if (res==1)
	{
TFile *fichroot=new TFile("../espectros.root","UPDATE");		// abre un fichero root
TTree *tree = new TTree("tree","signals");		// crea un Tree
tree->Branch("espectro","TH1I",&H,32000,0);		// crea una rama del tree
tree->Branch("photopeak",&mean,"mean/F");
//tree->Branch("photopeakerr",&dmean,"dmean/F");
tree->Fill();
tree->Write(); 
H->Write(argv[1]);
fichroot->Close();
	
	}
cout << "res es " << res[0] << endl;*/
delete theApp;
return 0;
}
