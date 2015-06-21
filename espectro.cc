#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TFile.h>
#include <TObject.h>
#include <TRint.h>
#include <TH1.h>
#include <TH1I.h>
#include <TSpectrum.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>
#include <TMath.h>
#include <TTree.h>
#include <TRandom.h>
#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;

/*
class espectro : public TObject {


public: 
  Float_t mean;
  Float_t dmean;
  Float_t r;
  Float_t deltar;
  Float_t tam;
  Float_t volt;
  Float_t gana;
  Float_t shap;
  Float_t fech;
  Float_t atime;
 // void Fill(  Float_t smean,  Float_t sdmean,   Float_t sr,   Float_t sdeltar,   Float_t stam,  Float_t svolt,  Float_t sgana,   Float_t sshap,   Float_t sfech,   Float_t satime);

void Fill(Float_t smean,  Float_t sdmean,   Float_t sr,   Float_t sdeltar,   Float_t stam,  Float_t svolt,  Float_t sgana,   Float_t sshap,   Float_t sfech,   Float_t satime);
  { mean=smean; dmean=sdmean; r=sr; deltar=sdeltar; tam=stam; volt=svolt; gana=sgana; shap=sshap; fech=sfech; atime=satime; return;	};
ClassDef(espectro,1)
};	

*/

Double_t Background(Double_t *x, Double_t *par);
Double_t Signal(Double_t *x, Double_t *par);
Double_t fitFunction(Double_t *x, Double_t *par);
 
// linear background function
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

Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N],dr; 		      
Float_t siga=2,sigb=2;

Int_t i,k,m,a=1,b=1000,fin,ffi,reb=8;  
char ar[100],arch[100],title[150]="",ci[100]="",res;
TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
TH1F *H = new TH1F("H",arch,8192,-9.7740,1196.44); 
TRandom q;

gROOT->SetStyle("Bold"); 
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Falta el nombre del archivo a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "espectro2 fichero(sin ext.) [canal-ini-fit] [canal-fin-fit]"              << "\n";
	cout << "[sigmas a izq] [sigmas a derecha]"                                        << "\n";
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
	x[k]=(((float)k)*0.14726-9.77740);       
	y[k]=datos[k];
	H->Fill(x[k],y[k]);
	}

//+(q.Uniform(1)-0.5)
//m2=sprintf(title,"%s ",argv[1]);
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(0.1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();

TF1 *fitFcn = new TF1("fitFcn",fitFunction,a,b,5);
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);

/*
TH1I *h2 = (TH1I*)H->Clone("h2");                     // esto sirve para localizar el pico de 662keV de Cs137 
TSpectrum *s = new TSpectrum(1);
Int_t nfound = s->Search(H,1,"new");
Float_t *xpeaks = s->GetPositionX();
Float_t xp = xpeaks[0];
cout << xp << endl;
a= int(xp - xp/10);
b= int(xp + xp/10);
*/
/*

fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);		// par4 = width, par5 = peak
H->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);
fitFcn->SetRange(a,b);					
H->Fit(fitFcn,"R+");					// second try: set start values for some parameters
H->Fit(fitFcn,"R+");	
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);
H->Fit(fitFcn,"R+");	

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;
*/
//H->Rebin(reb);
H->Draw();
//H->Fit(fitFcn,"R"); 


Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2
chis = fitFcn->GetChisquare();  
ndf= fitFcn->GetNDF();
chiondf=chis/ndf;
cout << "el chis es: " << chis << ", el ndf es: " << ndf << " y el chis/ndf es: " << chiondf  << endl;

TLegend *legend=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend->AddEntry(ar,ar,"p");
//legend->Draw();


TLegend *legend2=new TLegend(0.10,0.92,0.52,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
//legend2->Draw();

gStyle->SetOptStat(0);    
gStyle->SetOptFit(0);             		        // muestro los datos del Fit

/*
ofstream *out = new ofstream("centroides.csv",ios::app);
*out << mean << " " << dmean << endl;
*/
/*
cout << "Desea guardar el grafico y sus parámetros (s/n)" << endl;  // PARA GUARDARLO EN UN TREE.
//res='n';
cin >> res;
if (res=='s'||res=='y')
	{
	Float_t meanr,dmeanr,meanw,dmeanw,rr,drr,rw,drw;
	char *sepa,*tama,*voltaje,*gain,*shp,*fch,*acq;
	Float_t tam,volt,gana,shap,fech,atime,tamr,voltr,ganar,shapr,fechr,atimer,tamw,voltw,ganaw,shapw,fechw,atimew;	
	Float_t x[N],y[N];
	char canvasName[100];
	strcpy(canvasName,argv[1]);
	sepa= strtok(argv[1],"_ V_ g us s"); k=0;
	while (sepa != NULL)
		{
		if (k==0) tama=sepa;                		
		if (k==1) voltaje=sepa;   
		if (k==2) gain=sepa;
		if (k==3) shp=sepa;
		if (k==4) fch=sepa;
		if (k==5) acq=sepa;
		sepa = strtok(NULL,"V_ g_ us s");
		k++;
		}
	tam=atof(tama); volt=atof(voltaje); gana=atof(gain); shap=atof(shp); atime=atof(acq);
	cout << "tamaño: " << tam <<  " voltaje: " << volt  <<   " ganancia: " << gana  << " shap: " << shap << " acq time: " << atime <<  endl;
	//if ((strstr(ci,"block")!=NULL))	i=0;             0_390V_124g8_4us_101008_15s_6V0_1

	//espectro *sp = new espectro();
	//sp->Fill();
	TFile *fichroot=new TFile("espectros.root","UPDATE");		// abre un fichero root
	TTree *tree =(TTree*)fichroot->Get("tree");
	if (tree==NULL) 
		{
		TTree *tree = new TTree("tree","signals");
		//tree->Branch("espectro",&sp,16000,99);

		tree->Branch("photopeak",&mean,"mean/F");
		tree->Branch("photopeakerr",&dmean,"dmean/F");
		tree->Branch("resolution",&r,"r/F");
		tree->Branch("deltar",&dr,"dr/F");
		tree->Branch("tamano",&tam,"tam/F");
		tree->Branch("voltaje",&volt,"volt/F");
		tree->Branch("ganancia",&gana,"gana/F");
		tree->Branch("shaping",&shap,"shap/F");
		tree->Branch("fecha",&fech,"fech/F");
		tree->Branch("acqtime",&atime,"atime/F");
		tree->Fill();
		tree->Write("tree");
		
		}
	else
		{
		//TTree *tree2 = tree->CloneTree();

		TTree *tree2 = new TTree("tree2","signals");
		tree->SetBranchAddress("photopeak",&meanr);
		tree->SetBranchAddress("photopeakerr",&dmeanr);
		tree->SetBranchAddress("resolution",&rr);
		tree->SetBranchAddress("deltar",&drr);
		tree->SetBranchAddress("tamano",&tamr);		
		tree->SetBranchAddress("voltaje",&voltr);
		tree->SetBranchAddress("ganancia",&ganar);
		tree->SetBranchAddress("shaping",&shapr);
		tree->SetBranchAddress("fecha",&fechr);
		tree->SetBranchAddress("acqtime",&atimer);
		Int_t nentries=tree->GetEntries();
		tree2->Branch("photopeak",&meanw,"mean/F");
		tree2->Branch("photopeakerr",&dmeanw,"dmean/F");
		tree2->Branch("resolution",&rw,"r/F");
		tree2->Branch("deltar",&drw,"dr/F");
		tree2->Branch("tamano",&tamw,"tam/F");
		tree2->Branch("voltaje",&voltw,"volt/F");
		tree2->Branch("ganancia",&ganaw,"gana/F");
		tree2->Branch("shaping",&shapw,"shap/F");
		tree2->Branch("fecha",&fechw,"fech/F");
		tree2->Branch("acqtime",&atimew,"atime/F");	
		for (Int_t j=0;j<nentries;j++)
			{
			tree->GetEntry(j);
			meanw=meanr;
			dmeanw=dmeanr;
			rw=rr;
			drw=drr;
			tamw=tamr;
			voltw=voltr;
			ganaw=ganar;
			shapw=shapr;
			atimew=atimer;
			tree2->Fill();
			}
		meanw=mean;
		dmeanw=dmean;
		rw=r;
		drw=dr;
		tamw=tam;
		voltw=volt;
		ganaw=gana;
		shapw=shap;
		atimew=atime;
		tree->Delete("all");
		tree2->Fill();
		tree2->Write("tree");
		}
	H->Write(argv[1]);
	gStyle->SetOptStat(0); 
	c->Write(canvasName);
	fichroot->Close();
	
	}
*/
theApp->Run(kTRUE);
delete theApp;
return 0;
}
