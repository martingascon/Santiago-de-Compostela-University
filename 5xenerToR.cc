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
TStyle *MyStyle = new TStyle("Legenda","leyenda");

Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N],mins[5],maxs[5];    
Float_t y3[N],y4[N],y5[N],ey3[N],ey4[N],ey5[N];   

Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N],d,e,f,g,h,o1,o2,o3; 		      
Float_t datosy3[N],datosy4[N],datosy5[N],errory3[N],errory4[N],errory5[N];

Int_t i,j,k,l,xini,tim,oldtim,m,m2,fin;  
char titulo[100]="titulo",fich[100],serie1[4]="P1",serie2[4]="P2",serie3[4]="P3",serie4[4]="P4",serie5[4]="P5";
char fitf[100]="([0]/sqrt(x) )",ar[100];
//char fitf[100]="pol1",ar[100];
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

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
			m=sprintf(serie5,"%s",argv[6]);
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
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i]  >> datosy3[i] >> errory3[i] >> datosy4[i] >> errory4[i] >> datosy5[i] >> errory5[i];  
	 	
	

		i++;
		}
	}

for (k=0;k<i-1;k++)
	{
	
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	y3[k]=datosy3[k];
	y4[k]=datosy4[k];
	y5[k]=datosy5[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	ey3[k]=errory3[k];
	ey4[k]=errory4[k];
	ey5[k]=errory5[k];
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


k=0;
fin=1;
while (fin==1)
		{
		if (y5[k]>0.1)
			{
			mins[4] = x[k];
			fin=0;
			}
		else
			k++;
		}
	fin=1;	
	while (fin!=0)
		{
		if (y5[k]<0.1)
			{
			maxs[4] = x[k-1];
			fin=0;
			}
		else
			k++;
		}


for (j=0;j<5;j++)
	{
	cout << " minimos " <<  mins[j] << endl; 
	cout << " maximos " <<  maxs[j] << endl; 
	}

//**************** Representación  **************

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.
TGraphErrors *gr3 = new TGraphErrors(k,x,y3,ex,ey3);	
TGraphErrors *gr4 = new TGraphErrors(k,x,y4,ex,ey4);	
TGraphErrors *gr5 = new TGraphErrors(k,x,y5,ex,ey5);	


TF1 *f1 = new TF1("f1",fitf,(mins[0]-50),(maxs[0]+50)); 
f1->SetParameter(0,1);	

TF1 *f2 = new TF1("f2",fitf,(mins[1]-50),(maxs[1]+50));
f2->SetParameter(0,1);	

TF1 *f3 = new TF1("f3",fitf,(mins[2]-50),(maxs[2]+50));
f3->SetParameter(0,1);	

TF1 *f4 = new TF1("f4",fitf,(mins[3]-50),(maxs[3]+50));
f4->SetParameter(0,1);	

TF1 *f5 = new TF1("f5",fitf,(mins[4]-50),(maxs[4]+50));
f5->SetParameter(0,1);	


f1->SetLineColor(14);
f2->SetLineColor(2);
f3->SetLineColor(3);
f4->SetLineColor(4);
f5->SetLineColor(43);
f1->SetLineStyle(9);
f2->SetLineStyle(9);
f3->SetLineStyle(9);
f4->SetLineStyle(9);
f5->SetLineStyle(9);

gr1->SetMarkerColor(14);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");		// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(2);
gr2->SetMarkerStyle(22);
gr2->SetMarkerSize(1.5);
gr2->Draw("p");
gr3->SetMarkerColor(3);
gr3->SetMarkerStyle(20);
gr3->SetMarkerSize(1.5);
gr3->Draw("p");
gr4->SetMarkerColor(4);
gr4->SetMarkerStyle(23);
gr4->SetMarkerSize(1.5);
gr4->Draw("p");
gr5->SetMarkerColor(29);
gr5->SetMarkerStyle(16);
gr5->SetMarkerSize(1.7);
gr5->Draw("p");





gr1->Fit("f1","R+");
gr1->SetLineColor(14);
gr1->SetLineStyle(9);

gr2->Fit("f2","R+");
gr2->SetLineColor(2);
gr2->SetLineStyle(9);


gr3->Fit("f3","R+");
gr3->SetLineColor(3);
gr3->SetLineStyle(9);

gr4->Fit("f4","R+");
gr4->SetLineColor(4);
gr4->SetLineStyle(9);

gr5->Fit("f5","R+");
gr5->SetLineColor(43);
gr5->SetLineStyle(9);

TLegend *legend=new TLegend(0.74,0.61,0.89,0.86);	// Declaración de la leyenda
legend->SetTextFont(50);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.03);				// Tamaño de la fuente de la leyenda

legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");
legend->AddEntry(gr3,serie3,"p");
legend->AddEntry(gr4,serie4,"p");
legend->AddEntry(gr5,serie5,"p");

legend->SetFillColor(0);
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda

legend->Draw();	
legend->SetFillColor(0);
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit

legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
