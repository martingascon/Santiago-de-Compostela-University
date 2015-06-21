//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa 1,2 o 3 espectros  

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
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

Float_t mean,sigma, dmean,dsigma,deltar,r,datos[N],datos2[N],datos3[N],x[N],y[N]; 		      
Float_t siga=1.8,sigb=1.8,sup1=0,sup2=0,sup3=0;
Int_t i,k,m,m2,a=1,b=1000,fin,ffi,reb=8;  
char arch[100],arch2[100],arch3[100],title[150],ci[100]="";
gROOT->SetStyle("Bold"); 

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
Double_t xbins[9] ;

TH1I *H1 = new TH1I("H",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch2,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch3,8192,0,8191); 

TH1I *H1m = new TH1I("H1m",arch,1024,0,1023); 
TH1I *H2m = new TH1I("H2m",arch2,1024,0,1023); 
TH1I *H3m = new TH1I("H3m",arch3,1024,0,1023); 


H1m->GetXaxis()->SetLabelColor(1);		
H1m->GetYaxis()->SetLabelColor(1);
H1->GetXaxis()->SetLabelColor(1);		
H1->GetYaxis()->SetLabelColor(1);


//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Falta el nombre del archivo a representar" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch,"%s.mca",argv[1]);
			break;
		case 3: m=sprintf(arch,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			break;
		case 4: m=sprintf(arch,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			m=sprintf(arch3,"%s.mca",argv[3]);		
			break;
		case 5: m=sprintf(arch,"%s.mca",argv[1]);
			reb=atoi(argv[2]);
			fin=atoi(argv[3]);ffi=atoi(argv[4]);
			a=fin;b=ffi;
			break;
		case 6: m=sprintf(arch,"%s.mca",argv[1]);
			fin=atoi(argv[2]);ffi=atoi(argv[3]);
			a=fin;b=ffi;
			siga=atof(argv[4]);sigb=atof(argv[5]);
			cout << sigb  << siga <<endl;
			break;
			
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
			if (argc==4) *in >> ci;
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
	H1->Fill(x[k],y[k]);
	}

cout << arch2 << endl;
ifstream *in2 = new ifstream(arch2);

if(!*in2) 
	{cout << " ERROR OPENING FILE " <<  arch2 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in2 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==4) *in2 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		{*in2 >> datos2[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
		}
	delete in2;   
	}


for (k=0;k<N;k++)
	{
	x[k]=k; 
	y[k]=datos2[i];	
	H2->Fill(x[k],y[k]);
	}

cout << arch3 << endl;
ifstream *in3 = new ifstream(arch3);
if(!*in3) 
	{cout << " ERROR OPENING FILE " <<  arch3 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in3 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			//if (argc==4) *in3 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		{
		*in3 >> datos3[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
		}
	delete in3;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos3[k];
	H3->Fill(x[k],y[k]);
	}



//m2=sprintf(title,"%s ",argv[1]);
H1->SetMarkerColor(2);
H1->SetFillColor(0);
H1->SetLineColor(2);
H1->SetLineWidth(1);
H1->SetMarkerStyle(8);
H1->SetMarkerSize(0.1);


H1->SetTitle(title);
H1->GetXaxis()->SetTitle("Channel");
H1->GetYaxis()->SetTitle(" Counts ");
H1->GetXaxis()->CenterTitle();
H1->GetYaxis()->CenterTitle();


H2->SetMarkerColor(4);
H2->SetFillColor(4);
H2->SetLineColor(4);
H2->SetMarkerStyle(8);
H2->SetLineWidth(1);
H2->SetMarkerSize(0.1);


H3->SetMarkerColor(kGreen+3);
H3->SetFillColor(0);
H3->SetLineColor(kGreen+3);
H3->SetMarkerStyle(8);
H3->SetLineWidth(1);
H3->SetMarkerSize(0.1);
/*

TF1 *g2 = new TF1("g2","gaus",a,b);
H1->Fit(g2,"R");



a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);				// derecha y por izquierda a integrar (defecto:1.8)

c->cd(1);


TF1 *g1 = new TF1("g1","gaus",a,b);
//H->Rebin(reb);
H1->Fit(g1,"R+"); 					// fit del pico del Cesio
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
dmean =g1->GetParError(1);
sigma = g1->GetParameter(2);       			// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);


*/
//H1->Rebin(8);   
//H2->Rebin(2); 
//H3->Rebin(18); 


/*for (k=1;k<1025;k++)
	{
sup1 = H->GetBinContent(k);         
H1m->SetBinContent(k,sup1);  
sup2 = H2->GetBinContent(k);         
H2m->SetBinContent(k,sup2);  
sup3 = H3->GetBinContent(k);         
H3m->SetBinContent(k,sup3);  
	}*/


//H1->Fit(g1,"R"); 
TLegend *legend=new TLegend(0.64,0.61,0.99,0.76);
legend->AddEntry(H1,"A","l");
legend->AddEntry(H2,"B","l");
legend->AddEntry(H3,"C","l");


legend->SetTextFont(72);
legend->SetTextSize(0.04);
legend->SetTextColor(1);
legend->SetFillColor(0);

//m=sprintf(ar,"R(canberra) = (%2.2f #pm %2.2f) %%",4.84,0.08);  
//legend->AddEntry(ar,ar,"l");

//m=sprintf(ar,"R(cremat) = (%2.2f #pm %2.2f) %%",5.30,0.09);  

//legend->AddEntry(ar,ar,"l");
//H->SetMarkerColor(1);
//H2->SetMarkerColor(2);

//TLegend *legend2 =new TLegend(0.64,0.31,0.99,0.46);
//legend2->SetTextFont(72);
//legend2->SetTextSize(0.02);
//legend2->AddEntry("PMT","h2","p3");
//legend2->AddEntry("APD","h3","p4");


H1->Draw();
H2->Draw("same");
H3->Draw("same");


gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);  
gStyle->SetOptFit(0);             		        // muestro los datos 
legend->Draw();
legend->SetFillColor(0);

theApp->Run(kTRUE);
delete theApp;
return 0;
}
