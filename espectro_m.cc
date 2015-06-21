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


#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N]; 		      
Float_t siga=1.8,sigb=1.8;
Int_t i,k,m,a=1,b=1000,cont=0,fin,ffi,reb=8;  
char ar[100],arch[100],title[150]="",ci[100]="";
//TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
//c->Divide(1,1);
TH1I *H = new TH1I("H",arch,8192,0,8191); 
gROOT->SetStyle("Bold");


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
	x[k]=k;                 
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
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();

TF1 *g2 = new TF1("g2","gaus",a,b);
H->Fit(g2,"R");
do 					// encuentro donde esta la gaussiana con anchura menor a 350 ch
{
	TF1 *g2 = new TF1("g2","gaus",a,b);
	H->Fit(g2,"R+");
	mean = g2->GetParameter(1); 
	sigma = g2->GetParameter(2); 
	cont=cont+1;
	a=a+1000;
	b=b+1000;
	if (b>8000) 
	  	{a=500;b=1500;}
	if (cont==50) sigma=600;
	r = 100*(sigma*2.35/mean); 
}while (r>30);
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);				// derecha y por izquierda a integrar (defecto:1.8)

//c->cd(1);


TF1 *g1 = new TF1("g1","gaus",a,b);
g1->SetLineWidth(4);
g1->SetLineColor(kBlack);

H->Fit(g1,"R+");					// fit del pico del Cesio



mean = g1->GetParameter(1);       			// obtengo el valor x del pico
dmean =g1->GetParError(1);
sigma = g1->GetParameter(2);       			// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);

H->Rebin(reb);
H->Draw();
H->Fit(g1,"R"); 



Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2
chis = g1->GetChisquare();  
ndf= g1->GetNDF();
chiondf=chis/ndf;
cout << "el chis es: " << chis << ", el ndf es: " << ndf << " y el chis/ndf es: " << chiondf  << endl;



TLegend *legend=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend->AddEntry(ar,ar,"p");
legend->Draw();


TLegend *legend2=new TLegend(0.10,0.92,0.52,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();

ofstream *out = new ofstream("centroides.csv",ios::app);
*out << mean << " " << dmean << " " << r << " " << deltar  << endl;

gStyle->SetOptStat(0);   
gStyle->SetOptFit(0);     
//theApp->Run(kTRUE);


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
