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

#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;


int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N],dr; 		      
Float_t siga=2,sigb=2;

Int_t i,k,m,a=1,b=1000,fin,ffi,reb=8;  
char ar[100],arch[100],title[150]="",ci[100]="",res;
TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);

TH1I *H = new TH1I("H",arch,8192,0,8191); 

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
H->SetMarkerSize(0.1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();


TF1 *g2 = new TF1("g2","gaus",a,b);
H->Fit(g2,"R");

mean = g2->GetParameter(1); 
sigma = g2->GetParameter(2); 

a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);




TF1 *fitFcn = new TF1("fitFcn","gaus",a,b);
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);

H->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(1); 
dmean =fitFcn->GetParError(1);
sigma = fitFcn->GetParameter(2);
dsigma =fitFcn->GetParError(2);
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);
fitFcn->SetRange(a,b);					
H->Fit(fitFcn,"R+");					// second try: set start values for some parameters
//H->Fit(fitFcn,"R+");	
//H->Fit(fitFcn,"R+");	
mean = fitFcn->GetParameter(1); 
dmean =fitFcn->GetParError(1);
sigma = fitFcn->GetParameter(2);
dsigma =fitFcn->GetParError(2);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

H->Rebin(reb);
//H->Draw();
H->Fit(fitFcn,"R"); 

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
legend->Draw();


TLegend *legend2=new TLegend(0.10,0.92,0.52,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();

gStyle->SetOptStat(0);    
gStyle->SetOptFit(0);             		        // muestro los datos del Fit


ofstream *out = new ofstream("centroides.csv",ios::app);
*out << mean << " " << dmean << " " << r << " " << deltar  << endl;


cout << "Desea guardar el grafico y sus parámetros (s/n)" << endl;  // PARA GUARDARLO EN UN TREE.
res='s';
//cin >> res;
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

//theApp->Run(kTRUE);
delete theApp;
return 0;
}
