//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa un espectro mca
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
#include <TRandom.h>
#include <ctime>

#define N 8192 				       // Número máximo de Datos por Canal
using namespace std;
//ofstream *out = new ofstream("resulta.txt");  


int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t Ampli,mean2, mean,sigma, dmean,dsigma,deltar,r,datos[N],x[N],y[N],siga=1.8,sigb=1.8,dmin=0,fmin=0,rmin=0; 		      
Float_t Despla, Factor,ndf=0,chis=0,chiondf=0,ndf2=0,chis2=0,chiondf_old=0,chiondf_new=0,dif,r1,r2,r3, temp=1,ener=0;

Int_t i,k,m,m2,a=1,b=1000,cont=0,fin,ffi,reb=8,entries=0;  
char ar[100],arch[100],title[150],ci[100]="";

//TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
//c->Divide(1,1);
TH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 
TH1I *Hs = new TH1I("Hs",arch,8192,0,8191); 

gROOT->SetStyle("Pub");
TRandom g;

ofstream archivo;  // objeto de la clase ofstream

archivo.open("resulta.txt", ios::app);

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
	H1->Fill(x[k],y[k]);
	}
m2=sprintf(title,"%s ",argv[1]);
H1->SetMarkerColor(7);
H1->SetFillColor(19);
H1->SetLineColor(2);
H1->SetLineWidth(1);
H1->SetMarkerStyle(8);
H1->SetMarkerSize(1);
H1->SetTitle(title);
H1->GetXaxis()->SetTitle("Channel");
H1->GetYaxis()->SetTitle(" Counts ");
H1->GetXaxis()->CenterTitle();
H1->GetYaxis()->CenterTitle();

Hs->SetLineColor(3);



TF1 *g1b = new TF1("g1b","gaus",a,b);
H1->Fit(g1b,"RN");
do 							// encuentro donde esta la gaussiana con anchura menor a 350 ch
{
	TF1 *g1b = new TF1("g1b","gaus",a,b);
	H1->Fit(g1b,"RN");
	mean = g1b->GetParameter(1); 
	sigma = g1b->GetParameter(2); 
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
TF1 *gs = new TF1("gs","gaus",a,b);
TF1 *g3 = new TF1("g3","gaus",a,b);

//H->Rebin(reb);
H1->Fit(g1,"RN"); 						// fit del pico del Cesio
Ampli= g1->GetParameter(0); 
mean = g1->GetParameter(1);       				// obtengo el valor x del pico
dmean = g1->GetParError(1);
sigma = g1->GetParameter(2);       				// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        				// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);
////H1->Rebin(reb);H3->Rebin(reb);Hs->Rebin(reb);H2->Rebin(reb);	// Hago rebining x8 para todos

H1->Fit(g1,"RN"); 						// Hago el fit de H1
chis = g1->GetChisquare();  
ndf= g1->GetNDF();
chiondf=chis/ndf;
cout << "el chis es: " << chis << ", el ndf es: " << ndf << " y el chis/ndf es: " << chiondf  << endl;

entries=H1->Integral(H1->FindBin(mean-3*sigma),H1->FindBin(mean+3*sigma));// cout << "entries: " << entries  << endl;
Despla=220;
Factor=0.1;
dif = 1;
chiondf_old=chiondf;						//guardo en chiondf_old el chiondf
H2 = (TH1I*)H1->Clone("H2");					// Hago un clon de H1 en H2 y trabajo con el.
do
{
	mean2 = mean-Despla;  					//cout << "mean2: " << mean2  << endl;
	gs->SetParameter(0,Ampli); 				// pongo los parametros de la
	gs->SetParameter(1,mean2); 				// función gs que sirve para fitear el histo 
 	gs->SetParameter(2,sigma); 				// suplementario	
	Hs->Reset();						// reseteo el histo suplementario (gauss pequeña)
	Hs->FillRandom("gs",entries);				// lleno el histo suplementario (gauss pequeña)
	Hs->Add(Hs,Hs,0,Factor);				// lo reescalo
	g3->SetParameter(0,Ampli); 				// pongo los parametros de la
	g3->SetParameter(1,mean); 				// función g3 que sirve para fitear el histo 
 	g3->SetParameter(2,sigma); 				// final H3 = H2 - Hs
	H3->Reset();						// reseteo el histo H3
	H3->Add(H2,Hs,1,-1);					// creo el histo H3 
	H3->Fit(g3,"RQN+"); 					// fiteo el histo final H3

	mean = g3->GetParameter(1);       			// obtengo el valor x del pico
	dmean = g3->GetParError(1);
	sigma = g3->GetParameter(2);       			// obtengo el sigma
	dsigma =g3->GetParError(2);
	r = 100*(sigma*2.35/mean);        			// calculo la resolución  cout << "Energy Resolution =: " << r << endl;

	chis2 = g3->GetChisquare();  				// obtengo chi2 de H3
	ndf2= g3->GetNDF();
	chiondf_new=chis2/ndf2; 					// calculo el chiondf_new de la nueva función....	
	cout << "el chis2 es: " << chis2 << ", el ndf2 es: " << ndf2 << " y el chis2/ndf es: " << chiondf_new  << endl;
	dif = chiondf_old-chiondf_new;  				cout << "La diferencia es: " << dif << endl;
	r1=g.Rndm();r2=g.Rndm();				// tiro dos numero random r2 signo, r1 entre 0 y 1
	//ener=TMath::Exp(dif/temp);				// defino la variable energía que es ener>1 si dif>0 y <1 si dif<0
	r1=r1*2-1;						//cout << "ener es: " << ener << endl;
	r2=r2*2-1;						//	cout << "r1 es: " << r1 << endl;
	Despla=200+r1*50;					// el desplazamiento 150 se le suman un nro. entre 5 y -5
	Factor=0.045+r2/25;					// el factor se le suma un numero entre -0.01 y 0.01 
	cout << "DESPLA es: " << Despla << endl;
	cout << "Factor es: " << Factor << endl;
	
	if (dif>0)						// esto implica que el chis2 es menor que el anterior, lo descarto?
		{						// depende de si cumple una condición no lo descarto
		chiondf_old=chiondf_new;
		dmin=Despla;
		rmin=r;
		fmin=Factor;		
		
		//r3=g.Rndm(); 					// tiro un random para ver si lo acepto o no.
		//cout << "r3 es: " << r3 << endl;		
		//chiondf_new=chiondf_old;			// guardo en chiondf_new el chiondf_old 		
		//if (ener>r3) 					// si la energía es mayor que el random vale tambien...
			//{
			//H2->Reset();				// reseteo H2 
			//H2 = (TH1I*)H3->Clone("H2");		// pongo en H2 lo que había en H3
			//}
		}
cont=cont+1;
if ((cont%500)==0) temp=temp/2;
cout << "********************"<< endl;
cout << "chi2: " <<  chiondf_old <<	endl;
cout << "dmin: " <<  dmin <<	endl;
cout << "rmin: " <<  rmin <<	endl;
cout << "fmin: " <<  fmin <<	endl;
cout << "		      " <<  endl;
}while ((cont%10000)!=0);                // numero de eventos

//while ((chiondf_old-chiondf_new)<0.001);
archivo << "chi2: " <<  chiondf_old << "   dmin: " <<  dmin <<	"    rmin: " <<  rmin << "     fmin: " <<  fmin <<	endl;

archivo.close();

/*
H2->Draw();   // Para correr un script con varios archivos comentar desde aqui hasta theAPP

Hs->Draw("same");
H3->Draw("same");

H2->Fit(g3,"R+"); 
mean = g3->GetParameter(1);       			// obtengo el valor x del pico
dmean = g3->GetParError(1);
sigma = g3->GetParameter(2);       			// obtengo el sigma
dsigma =g3->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);

TLegend *legend=new TLegend(0.55,0.44,0.88,0.49);
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar);  
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);


TLegend *legend2=new TLegend(0.47,0.71,0.88,0.76);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.0f #pm %2.1f) %%",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);

*/

//H->Draw();
//gStyle->SetOptFit(111);     
//legend->Draw();
//legend2->Draw();

//theApp->Run(kTRUE); 
delete theApp;
}
