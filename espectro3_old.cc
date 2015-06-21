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

#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t mean,sigma,newtrigger, dmean,dsigma,deltar,r,datos[N],datos2[N],x[N],y[N]; 		      
Float_t integral=0,siga=1.8,sigb=1.8;
Int_t i,j,k,l,xini,tim,oldtim,m,m2,a=1,b=1000,cont=0,fin,ffi,tru=0,reb=8,aux=0,bin=0;  
char ar[100],arch[100],arch2[100],title[150],ci[100]="",livetime[100]="",stabin2ascrttime[100]="";
gROOT->SetStyle("Bold"); 

TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
c->Divide(1,1);
TH1I *H = new TH1I("H",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch2,8192,0,8191); 

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
			m=sprintf(arch2,"%s.mca",argv[2]);
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
		//if ((strstr(ci,"LIVE_TIME")!=NULL))  strcpy(livetime,ci);
		//if ((strstr(ci,"START_TIME")!=NULL))  strcpy(starttime,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in2 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in2 >> datos2[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in2;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos2[k];
	H2->Fill(x[k],y[k]);
	}

m2=sprintf(title,"%s ",argv[1]);
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(1);
H->SetMarkerStyle(8);
H->SetMarkerSize(0.1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();


TF1 *g2 = new TF1("g2","gaus",a,b);
H->Fit(g2,"R");



a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);				// derecha y por izquierda a integrar (defecto:1.8)

c->cd(1);


TF1 *g1 = new TF1("g1","gaus",a,b);
//H->Rebin(reb);
H->Fit(g1,"R+"); 					// fit del pico del Cesio
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
dmean =g1->GetParError(1);
sigma = g1->GetParameter(2);       			// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);
H->Rebin(reb);
H2->Rebin(reb);

H->Fit(g1,"R"); 
TLegend *legend=new TLegend(0.64,0.61,0.99,0.66);
legend->SetTextFont(72);
legend->SetTextSize(0.04);


legend->SetTextSize(0.02);
legend->SetTextColor(2);

m=sprintf(ar,"R(canberra) = (%2.2f #pm %2.2f) %%",4.84,0.08);  
legend->AddEntry(ar,ar,"l");

m=sprintf(ar,"R(cremat) = (%2.2f #pm %2.2f) %%",5.30,0.09);  

legend->AddEntry(ar,ar,"l");
H->SetMarkerColor(1);
H2->SetMarkerColor(2);

TLegend *legend2 =new TLegend(0.64,0.31,0.99,0.46);
legend2->SetTextFont(72);
legend2->SetTextSize(0.02);
legend2->AddEntry("PMT","h2","p3");
legend2->AddEntry("APD","h3","p4");

H->Draw();
H2->Draw("same");
gStyle->SetOptFit(0);             		        // muestro los datos del Fit
legend->Draw();
legend->SetTextColor(0);
legend2->Draw();
theApp->Run(kTRUE);
delete theApp;
return 0;
}
