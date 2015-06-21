//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa los datos (5 columnas) 
#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRint.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>

#define N 40				       // max data number
using namespace std;

int main(int argc, char **argv)
{
//********************************** variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t x[16][N],y[16][N],ex[16][N],ey[16][N],ap0[16],ap1[16];
Float_t datosx,datosy,errorx,errory; 		      
Int_t i[16],color[16]={2,4,8,6,7,9,11,21,31,41,50,51,65,71,85,91};
Int_t k,l,m,aux=1,max=0; 
TGraphErrors *gr[16];  TF1 *f[16]; TLegend  *leg;
char fich[100], func[100], serie[12];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,4090,7250);      
hr->SetXTitle("Total energy peak (channels)");		// Escribe como titulo del e[1]++e x lo que hay en e[1]++ex
hr->SetYTitle("Energy (keV)");   	        // Escribe como titulo del e[1]++e y lo que hay en e[1]++ey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del e[1]++e x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del e[1]++e x	
hr->GetXaxis()->SetLabelColor(1);		
hr->GetYaxis()->SetLabelColor(1);

for (k=0;k<N;k++)
	for (l=0;l<16;l++)
	 	{
		x[l][k]=0; y[l][k]=0; ex[l][k]=0; ey[l][k]=0;		
		}

for (l=0;l<16;l++)
	 {
		ap0[l]=0; ap1[l]=0;		
	}
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: nombre-programa [FICHERO](sin extens.)                    " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}		
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.txt",argv[1]);
			break;
		};
	}
ifstream *in = new ifstream(fich);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  fich << endl; 
	return 1;
	}
else    {
	for (k=0;k<16;k++) 	i[k]=0;
	while (aux!=0)
	   {
	   *in >> aux >> datosx >> errorx >> datosy >> errory;
	   switch (aux)		
		{
		case 1: {x[0][i[0]]=datosx; ex[0][i[0]]=errorx; y[0][i[0]]=datosy; ey[0][i[0]]=errory; 	i[0]++; max=aux; break;}
		case 2: {x[1][i[1]]=datosx; ex[1][i[1]]=errorx; y[1][i[1]]=datosy; ey[1][i[1]]=errory;	i[1]++; max=aux; break;}
		case 3: {x[2][i[2]]=datosx; ex[2][i[2]]=errorx; y[2][i[2]]=datosy; ey[2][i[2]]=errory;	i[2]++; max=aux; break;}
		case 4: {x[3][i[3]]=datosx; ex[3][i[3]]=errorx; y[3][i[3]]=datosy; ey[3][i[3]]=errory; 	i[3]++; max=aux; break;}
		case 5: {x[4][i[4]]=datosx; ex[4][i[4]]=errorx; y[4][i[4]]=datosy; ey[4][i[4]]=errory; 	i[4]++; max=aux; break;}
		case 6: {x[5][i[5]]=datosx; ex[5][i[5]]=errorx; y[5][i[5]]=datosy; ey[5][i[5]]=errory;	i[5]++; max=aux; break;}
		case 7: {x[6][i[6]]=datosx; ex[6][i[6]]=errorx; y[6][i[6]]=datosy; ey[6][i[6]]=errory;	i[6]++; max=aux; break;}
		case 8: {x[7][i[7]]=datosx; ex[7][i[7]]=errorx; y[7][i[7]]=datosy; ey[7][i[7]]=errory; 	i[7]++; max=aux; break;}		
		case 9: {x[8][i[8]]=datosx; ex[8][i[8]]=errorx; y[8][i[8]]=datosy; ey[8][i[8]]=errory;	i[8]++; max=aux; break;}
		case 10:{x[9][i[9]]=datosx; ex[9][i[9]]=errorx; y[9][i[9]]=datosy; ey[9][i[9]]=errory; 	i[9]++; max=aux; break;}	
		case 11: {x[10][i[10]]=datosx; ex[10][i[10]]=errorx; y[10][i[10]]=datosy; ey[10][i[10]]=errory; i[10]++; max=aux; break;}
		case 12: {x[11][i[11]]=datosx; ex[11][i[11]]=errorx; y[11][i[11]]=datosy; ey[11][i[11]]=errory;	i[11]++; max=aux; break;}
		case 13: {x[12][i[12]]=datosx; ex[12][i[12]]=errorx; y[12][i[12]]=datosy; ey[12][i[12]]=errory;	i[12]++; max=aux; break;}
		case 14: {x[13][i[13]]=datosx; ex[13][i[13]]=errorx; y[13][i[13]]=datosy; ey[13][i[13]]=errory; i[13]++; max=aux; break;}
		case 15: {x[14][i[14]]=datosx; ex[14][i[14]]=errorx; y[14][i[14]]=datosy; ey[14][i[14]]=errory; i[14]++; max=aux; break;}
		case 16: {x[15][i[15]]=datosx; ex[15][i[15]]=errorx; y[15][i[15]]=datosy; ey[15][i[15]]=errory;	i[15]++; max=aux; break;}
		case 0: {break;}
		}
	   }
	}


//**************** Representación  **************
leg =new TLegend(0.74,0.21,0.83,0.56);			// Declaración de la leyenda
leg->SetTextFont(50);					// Tipo de fuente de la leyenda
leg->SetTextSize(0.025);					// Tamaño de la fuente de la leyenda
leg->SetFillColor(0);


for (m=0;m<max;m++)
	{
	l=sprintf(func,"f%d",m);
	f[m] =  new TF1(func,"pol1",10,6500);
	f[m]->SetParameter(0,1);
	f[m]->SetParameter(1,0.001);
	f[m]->SetParameter(2,0.0001);
	f[m]->SetLineColor(color[m]);
	f[m]->SetLineStyle(1);
	gr[m]=  new TGraphErrors(i[m],x[m],y[m],ex[m],ey[m]);
	gr[m]->SetMarkerColor(color[m]);
	gr[m]->SetMarkerStyle(23);
	gr[m]->SetMarkerSize(1.2);
	gr[m]->Draw("P");				// A:frame P=dots L=lines C=curve
	gr[m]->Fit(func,"R+");
	gr[m]->SetLineColor(color[m]);
	gr[m]->SetLineStyle(1);
	gr[m]->Fit(func,"R");
	ap0[m] = f[m]->GetParameter(1); 	
	ap1[m] = f[m]->GetParameter(0); 	
	l=sprintf(serie,"Detector %d",m+1);
	leg->AddEntry(gr[m],serie,"p");
	}

leg->Draw();	
gStyle->SetOptFit(0);
cout << "********************************************************************" <<endl;
for (l=0;l<16;l++) 
	cout << ap0[l] << ",";
cout <<endl;
for (l=0;l<16;l++) 
	cout << ap1[l] << ",";

cout << "********************************************************************" <<endl;
theApp->Run(kTRUE);					// Para hacer el e[1]++ecutable
delete theApp;
return 0;
}



