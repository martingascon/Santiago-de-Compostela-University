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
#include <TGraph.h>
#include <TH2.h>
#include <TH2F.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TMath.h>


#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;



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
Int_t i,k,m,a1=5500,a2=6500,b1=5500,b2=6500,c1=5500,c2=6500,d1=5500,d2=6500,fin,ffi,reb=8;  
char ar[100],ar2[100],arch1[100],arch2[100],arch3[100],arch4[100],ci[100]="",titulo[100]="Titulo del grafico";

TCanvas *c = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TH1I *H1 = new TH1I("H1",arch1,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch2,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch3,8192,0,8191); 
TH1I *H4 = new TH1I("H4",arch4,8192,0,8191); 

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Error de ejecución							" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch1,"%s.mca",argv[1]);
			break;
		case 3: m=sprintf(arch1,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			break;
		case 4: m=sprintf(arch1,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			m=sprintf(arch3,"%s.mca",argv[3]);
			break;
			
		case 5: {
			m=sprintf(arch1,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			m=sprintf(arch3,"%s.mca",argv[3]);
			m=sprintf(arch4,"%s.mca",argv[4]);
			break;
			}
		case 13: {
			m=sprintf(arch1,"%s.mca",argv[1]);
			m=sprintf(arch2,"%s.mca",argv[2]);
			m=sprintf(arch3,"%s.mca",argv[3]);
			m=sprintf(arch4,"%s.mca",argv[4]);
			a1=atoi(argv[5]);a2=atoi(argv[6]);
			b1=atoi(argv[7]);b2=atoi(argv[8]);
			c1=atoi(argv[9]);c2=atoi(argv[10]);
			d1=atoi(argv[11]);d2=atoi(argv[12]);
			break;
			}
		};
	}
cout << arch1 << endl;
ifstream *in1 = new ifstream(arch1);
ifstream *in2 = new ifstream(arch2);
ifstream *in3 = new ifstream(arch3);
ifstream *in4 = new ifstream(arch4);


cout << a1 << " " << a2 << " " <<  b1 << " " << b2 << " " << c1 << " " << c2 << " " <<  d1 << " " << d2 << endl;




//************************************************************************************ lectura de fich 1
if(!*in1) 
	{cout << " ERROR OPENING FILE " <<  arch1 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in1 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in1 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in1 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in1;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H1->Fill(x[k],y[k]);
	}
//************************************************************************************ lectura de fich 2
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
			if (argc==3) *in2 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in2 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in2;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H2->Fill(x[k],y[k]);
	}

//************************************************************************************ lectura de fich 3
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
			if (argc==3) *in3 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in3 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in3;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H3->Fill(x[k],y[k]);
	}

//************************************************************************************ lectura de fich 4
if(!*in4) 
	{cout << " ERROR OPENING FILE " <<  arch4 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in4 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in4 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in4 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in4;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H4->Fill(x[k],y[k]);
	}

c->Divide(2,2);

H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle("CH1");   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); //H1->Rebin(8); 
c->cd(1);


TF1 *fitFcn = new TF1("fitFcn",fitFunction,a1,a2,5);
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);
fitFcn->SetParameters(5,-0.001,1,(a1+a2)/2,100);		// par4 = width, par5 = peak
H1->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
a1=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
a2=Int_t(mean+sigb*sigma);
fitFcn->SetRange(a1,a2);					
H1->Fit(fitFcn,"R+");					// second try: set start values for some parameters
//H1->Fit(fitFcn,"R+");	
//H1->Fit(fitFcn,"R+");	

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

H1->Rebin(reb);
H1->Draw();
H1->Fit(fitFcn,"R"); 

TLegend *legend=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
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

//************************************************************************************************************************* histo2 
H2->SetMarkerColor(7);   H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle("CH2");  
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); 
c->cd(2);



fitFcn->SetParameters(5,-0.001,1,(b1+b2)/2,100);		// par4 = width, par5 = peak
H2->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
b1=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b2=Int_t(mean+sigb*sigma);
fitFcn->SetRange(b1,b2);					
H2->Fit(fitFcn,"R+");					// second try: set start values for some parameters
//H2->Fit(fitFcn,"R+");	
//H2->Fit(fitFcn,"R+");	

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

H2->Rebin(reb);
H2->Draw();
H2->Fit(fitFcn,"R"); 

TLegend *legend3=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend3->SetTextFont(72);
legend3->SetTextSize(0.04);
m=sprintf(ar2,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend3->AddEntry(ar2,ar2,"p");
legend3->SetFillColor(0);
legend3->Draw();

TLegend *legend4=new TLegend(0.10,0.92,0.52,0.97);
legend4->SetTextFont(72);
legend4->SetTextSize(0.04);
m=sprintf(ar2,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend4->AddEntry(ar2,ar2,"p");
legend4->SetFillColor(0);
legend4->Draw();


//************************************************************************************************************************* histo3 
H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle("CH3");   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); 
c->cd(3); 


fitFcn->SetParameters(5,-0.001,1,(c1+c2)/2,100);		// par4 = width, par5 = peak
H3->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
c1=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
c2=Int_t(mean+sigb*sigma);
fitFcn->SetRange(c1,c2);					
H3->Fit(fitFcn,"R+");					// second try: set start values for some parameters
//H3->Fit(fitFcn,"R+");	
//H3->Fit(fitFcn,"R+");	

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

H3->Rebin(reb);
H3->Draw();
H3->Fit(fitFcn,"R"); 

TLegend *legend5=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend5->SetTextFont(72);
legend5->SetTextSize(0.04);
m=sprintf(ar2,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend5->AddEntry(ar2,ar2,"p");
legend5->SetFillColor(0);
legend5->Draw();

TLegend *legend6=new TLegend(0.10,0.92,0.52,0.97);
legend6->SetTextFont(72);
legend6->SetTextSize(0.04);
m=sprintf(ar2,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend6->AddEntry(ar2,ar2,"p");
legend6->SetFillColor(0);
legend6->Draw();

//************************************************************************************************************************* histo4
H4->SetMarkerColor(7);  H4->SetFillColor(0);  H4->SetLineColor(2);  H4->SetLineWidth(1);  H4->SetMarkerStyle(8); H4->SetMarkerSize(1);  H4->SetTitle("CH4");   
H4->GetXaxis()->SetTitle("Channel");         H4->GetYaxis()->SetTitle(" Counts "); H4->GetXaxis()->CenterTitle(); H4->GetYaxis()->CenterTitle(); 
c->cd(4); 

fitFcn->SetParameters(5,-0.001,1,(d1+d2)/2,100);		// par4 = width, par5 = peak
H4->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
d1=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
d2=Int_t(mean+sigb*sigma);
fitFcn->SetRange(d1,d2);					
H4->Fit(fitFcn,"R+");					// second try: set start values for some parameters
//H4->Fit(fitFcn,"R+");	
//H4->Fit(fitFcn,"R+");	

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

H4->Rebin(reb);
H4->Draw();
H4->Fit(fitFcn,"R"); 

TLegend *legend7=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend7->SetTextFont(72);
legend7->SetTextSize(0.04);
m=sprintf(ar2,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend7->AddEntry(ar2,ar2,"p");
legend7->SetFillColor(0);
legend7->Draw();

TLegend *legend8=new TLegend(0.10,0.92,0.52,0.97);
legend8->SetTextFont(72);
legend8->SetTextSize(0.04);
m=sprintf(ar2,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend8->AddEntry(ar2,ar2,"p");
legend8->SetFillColor(0);
legend8->Draw();

c->cd(0);

theApp->Run(kTRUE);
delete theApp;
return 0;
}
