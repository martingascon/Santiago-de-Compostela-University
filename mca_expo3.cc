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


#define N 8192				       // Número máximo de Datos por Canal
using namespace std;


Float_t Resol(TF1 *g1);
Double_t Background(Double_t *x, Double_t *par);
Double_t Signal(Double_t *x, Double_t *par);
Double_t fitFunction(Double_t *x, Double_t *par);
 



// Calculate the resolution
Float_t Resol(TF1 *g1)
{ 
Float_t mean,sigma,r;
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
sigma = g1->GetParameter(2);       			// obtengo el sigma
r = 100*(sigma*2.35/mean);       			// calculo la resolución
return r;
}

// Exponential background function
Double_t Background(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}

// The signal function: a gaussian
Double_t Signal(Double_t *x, Double_t *par)
{  Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}
// Combined background + signal
Double_t fitFunction(Double_t *x, Double_t *par)
{  Double_t tot = Background(x,par) + Signal(x,&par[2]);
   return tot;
}

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t i,k,m,a=1,b=1000,cont=0,fin,ffi,reb;  
Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N],siga=1.8,sigb=1.8,res1,res2; 		      
Float_t integral=0;
char ar[100],arch[100],title[150]="",ci[100]="";
TH1I *H = new TH1I("H",arch,1024,0,1024); 

gROOT->SetStyle("Bold");


//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Syntax error" << "\n";
	cout << "*************************************************************************" << "\n";
	cout << "mca_lineal [file-name] [ch-ini-fit] [ch-fin-fit] [sigm-left] [sigm-right]" << "\n";
	cout << "*************************************************************************" << "\n";
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
TH1I *h2 = (TH1I*)H->Clone("h2");                 

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


TF1 *fitFcn = new TF1("fitFcn",fitFunction,a,b,5);
fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);	
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);
H->Fit(fitFcn,"QR");
H->Fit(fitFcn,"QR");
H->Fit(fitFcn,"QR");
//////////////////////////////////////////////////////////////////////////////////////// calculo de la resolución
Float_t max=0,xmax=0,hmax=0,le=0,ri=0,val=0;
max = fitFcn->GetMaximum(a,b);			
xmax=fitFcn->GetMaximumX(a,b);	
hmax=max/2;
cout << hmax << " " << xmax << endl;
val=fitFcn->Eval(xmax);
for (k=(Int_t)xmax;k<b;k++)
	{
	val=fitFcn->Eval(k);
	if (val<hmax) 
		{ri=k;k=b;}
	}
val=fitFcn->Eval(xmax);
for (k=(Int_t)xmax;k>a;k--)
	{
	val=fitFcn->Eval(k);
	if (val<hmax) 
		{le=k;k=a;}
	}
mean = xmax;
sigma=(ri-le)/2.35;					
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);
//////////////////////////////////////////////////////////////////////////////////////// 



reb=8-cont*2;
H->Rebin(reb);
H->Draw();
H->Fit(fitFcn,"QR"); 



Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2 y rebinin
chis = fitFcn->GetChisquare();  
ndf= fitFcn->GetNDF();
chiondf=chis/ndf;
cout << " E.R. after rebining." << endl;
cout << "*******************************************************************" << endl;
cout << " Chi square: " << chis << ", ndf: " << ndf << " chis/ndf: " << chiondf  << endl;
cout << " Rebining: x"<< cont*2 << endl;
cout << " Energy Resolution: "<< r << "+" << deltar << endl;
cout << " Mean: "<< mean << "+" << dmean << endl;
cout << " Integral: "<< integral  << endl;
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
