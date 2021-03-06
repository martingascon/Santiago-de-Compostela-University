//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa un espectro mca con un ajuste gaussiano. 

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


Float_t Resol(TF1 *g1);

 
// calculate the resolution
Float_t Resol(TF1 *g1)
{ 
Float_t mean,sigma,r;
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
sigma = g1->GetParameter(2);       			// obtengo el sigma
r = 100*(sigma*2.35/mean);       			// calculo la resolución
return r;
}

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t i,k,m,a=1,b=1000,cont=0,fin,ffi,reb;  
Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N],siga=1.8,sigb=1.8,res1,res2; 		      
Int_t integral=0;
char ar[100],arch[100],title[150]="",ci[100]="";
TH1I *H = new TH1I("H",arch,8192,0,8191); 

gROOT->SetStyle("Bold");


//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Syntax error" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "gaus [nombre-fichero] [ch-ini-fit] [ch-fin-fit] [sigm-left] [sigm-right]" << "\n";
	cout << "************************************************************************" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch,"%s.mca",argv[1]); break;
		case 3: m=sprintf(arch,"%s.mca",argv[1]);
			reb=atoi(argv[2]);break;
		case 4: m=sprintf(arch,"%s.mca",argv[1]);
			fin=atoi(argv[2]);ffi=atoi(argv[3]);
			a=fin;b=ffi;break;
		case 5: {m=sprintf(arch,"%s.mca",argv[1]);
			reb=atoi(argv[2]);
			fin=atoi(argv[3]);ffi=atoi(argv[4]);
			a=fin;b=ffi;break;}
		case 6: {m=sprintf(arch,"%s.mca",argv[1]);
			fin=atoi(argv[2]);ffi=atoi(argv[3]);
			a=fin;b=ffi;
			siga=atof(argv[4]);sigb=atof(argv[5]);
			cout << sigb  << siga <<endl; break;}
		};

	}
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
integral=H->Integral(a,b);

TF1 *g2 = new TF1("g2","gaus",a,b);
TH1I *h2 = (TH1I*)H->Clone("h2");                     // esto sirve para localizar el pico de 662keV de Cs137 

Int_t final=0;
do 
{	H->Fit(g2,"QR");
	res1=Resol(g2);
	h2->Rebin(2);
	h2->Fit(g2,"QR");
	res2=Resol(g2);
	cout <<  res1 << "-> "; 
	if (res1>res2) 
		{
		 
		H=h2;
		cont++;
		}
	else
		final=1;
}
while ((final==0)&&(cont<6));

mean = g2->GetParameter(1);       			// obtengo el valor x del pico
sigma = g2->GetParameter(2);       			// obtengo el sigma
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);				// derecha y por izquierda a integrar (defecto:1.8)

cout << a << " " << b << endl;
TF1 *g1 = new TF1("g1","gaus",a,b);
g1->SetLineWidth(4);
g1->SetLineColor(kBlack);

H->Fit(g1,"QR");H->Fit(g1,"QR");H->Fit(g1,"QR");
					// fit del pico del Cesio
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
dmean =g1->GetParError(1);
sigma = g1->GetParameter(2);       			// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);
reb=8-cont*2;

H->Rebin(reb);

H->Draw();
H->Fit(g1,"QR"); 



Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2 y rebinin
chis = g1->GetChisquare();  
ndf= g1->GetNDF();
chiondf=chis/ndf;
cout << " E.R. after rebining." << endl;
cout << "*******************************************************************" << endl;
cout << " Chi square: " << chis << ", ndf: " << ndf << " chis/ndf: " << chiondf  << endl;
cout << " Rebining: x"<< cont*2 << endl;
cout << " Energy Resolution: "<< r << "+" << deltar << endl;
cout << " Mean: "<< mean << "+" << dmean << endl;
cout << " Integral: "<< integral << endl;
cout << "*******************************************************************" << endl;


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
