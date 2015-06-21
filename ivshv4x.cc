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

#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t x[N],ex[N];
Float_t y[N],y2[N],ey[N],ey2[N],mins[5],maxs[5];    
Float_t y3[N],y4[N],ey3[N],ey4[N];   

Float_t datosx[N],errorx[N];
Float_t datosy[N],datosy2[N],errory[N],errory2[N]; 		      
Float_t datosy3[N],datosy4[N],errory3[N],errory4[N];

Int_t i,j,k,m,fin;  
char fich[100],serie1[100]="APD 10x20 No. 1",serie2[100]="APD 10x20 No. 2",serie3[100]="APD 10x20 No. 4",serie4[100]="APD 10x20 No. 5";
char fitf[100]="expo";
//char fitf[100]="pol2";
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,13000,25);      

hr->SetXTitle("High Voltage (V)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Dark current (nA)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: chtohv [FICHERO](sin extens.) [Nom-1ºSer] [Nombre-2ºSer]  " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa representa los datos (2 columna) de un fichero ASCII donde  " << "\n";
	cout << "la primera columna son los datos del eje X, la segunda columna son los    " << "\n";
	cout << "datos del eje Y 							   " << "\n";	
	cout << "									   " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}		
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.txt",argv[1]);
			break;
		case 7: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(serie1,"%s",argv[2]);
			m=sprintf(serie2,"%s",argv[3]);
			m=sprintf(serie3,"%s",argv[4]);
			m=sprintf(serie4,"%s",argv[5]);
			break;
		};
	}
ifstream *in = new ifstream(fich);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  fich << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] >> datosy3[i] >> errory3[i] >> datosy4[i] >> errory4[i];
		i++;
		}
	}

for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	ex[k]=errorx[k];
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	y3[k]=datosy3[k];
	y4[k]=datosy4[k];
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	ey3[k]=errory3[k];
	ey4[k]=errory4[k];
	}
//**************** Calculo del minimo y maximo de cada serie **************
k=0;
fin=1;
while (fin==1)
		{
		if (y[k]>0.1)
			{
			mins[0] = x[k];
			fin=0;
			}
		else
			k++;
		}
	fin=1;	
	while (fin!=0)
		{
		if (y[k]<0.1)
			{
			maxs[0] = x[k-1];
			fin=0;
			}
		else
			k++;
		}

k=0;
fin=1;
while (fin==1)
		{
		if (y2[k]>0.1)
			{
			mins[1] = x[k];
			fin=0;
			}
		else
			k++;
		}
	fin=1;	
	while (fin!=0)
		{
		if (y2[k]<0.1)
			{
			maxs[1] = x[k-1];
			fin=0;
			}
		else
			k++;
		}


k=0;
fin=1;
while (fin==1)
		{
		if (y3[k]>0.1)
			{
			mins[2] = x[k];
			fin=0;
			}
		else
			k++;
		}
	fin=1;	
	while (fin!=0)
		{
		if (y3[k]<0.1)
			{
			maxs[2] = x[k-1];
			fin=0;
			}
		else
			k++;
		}


k=0;
fin=1;
while (fin==1)
		{
		if (y4[k]>0.1)
			{
			mins[3] = x[k];
			fin=0;
			}
		else
			k++;
		}
	fin=1;	
	while (fin!=0)
		{
		if (y4[k]<0.1)
			{
			maxs[3] = x[k-1];
			fin=0;
			}
		else
			k++;
		}




for (j=0;j<4;j++)
	{
	cout << " minimos " <<  mins[j] << endl; 
	cout << " maximos " <<  maxs[j] << endl; 
	}

//**************** Representación  **************

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.
TGraphErrors *gr3 = new TGraphErrors(k,x,y3,ex,ey3);	
TGraphErrors *gr4 = new TGraphErrors(k,x,y4,ex,ey4);	


TF1 *f1 = new TF1("f1",fitf,(mins[0]-4),(maxs[0]+4)); 
TF1 *f2 = new TF1("f2",fitf,(mins[1]-4),(maxs[1]+4));
TF1 *f3 = new TF1("f3",fitf,(mins[2]-4),(maxs[2]+4));
TF1 *f4 = new TF1("f4",fitf,(mins[3]-4),(maxs[3]+4));

f1->SetParameter(0,1);				
f1->SetParameter(1,2000);
f1->SetParameter(2,0.05);
f1->SetParameter(3,-24);

f2->SetParameter(0,1);				
f2->SetParameter(1,2000);
f2->SetParameter(2,0.05);
f2->SetParameter(3,-24);

f3->SetParameter(0,1);				
f3->SetParameter(1,2000);
f3->SetParameter(2,0.05);
f3->SetParameter(3,-24);

f4->SetParameter(0,1);				
f4->SetParameter(1,100);
f4->SetParameter(1,0.1);
f4->SetParameter(4,-24);

f1->SetLineColor(1);
f2->SetLineColor(2);
f3->SetLineColor(3);
f4->SetLineColor(4);


gr1->SetMarkerColor(1);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");		// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(2);
gr2->SetMarkerStyle(21);
gr2->SetMarkerSize(1.5);
gr2->Draw("p");
gr3->SetMarkerColor(3);
gr3->SetMarkerStyle(21);
gr3->SetMarkerSize(1.5);
gr3->Draw("p");
gr4->SetMarkerColor(4);
gr4->SetMarkerStyle(21);
gr4->SetMarkerSize(1.5);
gr4->Draw("p");





gr1->Fit("f1","R+");
gr2->Fit("f2","R+");
gr3->Fit("f3","R+");
gr4->Fit("f4","R+");


TLegend *legend=new TLegend(0.24,0.61,0.51,0.86);	// Declaración de la leyenda
legend->SetTextFont(50);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.03);				// Tamaño de la fuente de la leyenda

legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");
legend->AddEntry(gr3,serie3,"p");
legend->AddEntry(gr4,serie4,"p");

legend->SetFillColor(0);

//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
//legend->SetTextColor(0);
legend->Draw();	
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit

legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
