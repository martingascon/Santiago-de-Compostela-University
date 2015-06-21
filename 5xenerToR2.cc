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

#define N 20				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t d,e,f,g,h,o1,o2,o3; 		      

Float_t x1[N],y1[N],y2[N],x2[N],x3[N],y3[N];    
Float_t x4[N],y4[N],x5[N],y5[N];   






Float_t a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20;
Int_t i,j,k,l,xini,tim,oldtim,m,m2,fin;  
char titulo[100]="titulo",fich[100],serie1[4]="P1",serie2[4]="P2",serie3[4]="P3",serie4[4]="P4",serie5[4]="P5";
char fitf[100]="([0]+[1]/sqrt(x) )",ar[100];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,1500,25);      

hr->SetXTitle("Photon energy (keV)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);		
hr->GetYaxis()->SetLabelColor(1);
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

switch (i)
		{
	case 0: 
*in >> x1[0] >> x1[1] >> x1[2] >> x1[3] >> x1[4] >> x1[5] >> x1[6] >> x1[7] >> x1[8] >> x1[9] >> x1[10] >> x1[11] >> x1[12] >> x1[13] >> x1[14] >> x1[15] >> x1[16] >> x1[17] >> x1[18] >> x1[19];
*in >> y1[0] >> y1[1] >> y1[2] >> y1[3] >> y1[4] >> y1[5] >> y1[6] >> y1[7] >> y1[8] >> y1[9] >> y1[10] >> y1[11] >> y1[12] >> y1[13] >> y1[14] >> y1[15] >> y1[16] >> y1[17] >> y1[18] >> y1[19];
	case 1: 
*in >> x2[0] >> x2[1] >> x2[2] >> x2[3] >> x2[4] >> x2[5] >> x2[6] >> x2[7] >> x2[8] >> x2[9] >> x2[10] >> x2[11] >> x2[12] >> x2[13] >> x2[14] >> x2[15] >> x2[16] >> x2[17] >> x2[18] >> x2[19];
*in >> y2[0] >> y2[1] >> y2[2] >> y2[3] >> y2[4] >> y2[5] >> y2[6] >> y2[7] >> y2[8] >> y2[9] >> y2[10] >> y2[11] >> y2[12] >> y2[13] >> y2[14] >> y2[15] >> y2[16] >> y2[17] >> y2[18] >> y2[19];
	case 2: 
*in >> x3[0] >> x3[1] >> x3[2] >> x3[3] >> x3[4] >> x3[5] >> x3[6] >> x3[7] >> x3[8] >> x3[9] >> x3[10] >> x3[11] >> x3[12] >> x3[13] >> x3[14] >> x3[15] >> x3[16] >> x3[17] >> x3[18] >> x3[19];
*in >> y3[0] >> y3[1] >> y3[2] >> y3[3] >> y3[4] >> y3[5] >> y3[6] >> y3[7] >> y3[8] >> y3[9] >> y3[10] >> y3[11] >> y3[12] >> y3[13] >> y3[14] >> y3[15] >> y3[16] >> y3[17] >> y3[18] >> y3[19];
	case 3: 
*in >> x4[0] >> x4[1] >> x4[2] >> x4[3] >> x4[4] >> x4[5] >> x4[6] >> x4[7] >> x4[8] >> x4[9] >> x4[10] >> x4[11] >> x4[12] >> x4[13] >> x4[14] >> x4[15] >> x4[16] >> x4[17] >> x4[18] >> x4[19];
*in >> y4[0] >> y4[1] >> y4[2] >> y4[3] >> y4[4] >> y4[5] >> y4[6] >> y4[7] >> y4[8] >> y4[9] >> y4[10] >> y4[11] >> y4[12] >> y4[13] >> y4[14] >> y4[15] >> y4[16] >> y4[17] >> y4[18] >> y4[19];
		};

i++;

		}
	}

//**************** Representación  **************

TGraph *gr1 = new TGraph(20,x1,y1);			// Declaración del gráfico 1.
TGraph *gr2 = new TGraph(20,x2,y2);			// Declaración del gráfico 2.
TGraph *gr3 = new TGraph(20,x3,y3);	
TGraph *gr4 = new TGraph(20,x4,y4);		


TF1 *f1 = new TF1("f1",fitf,500,1400); 
f1->SetParameter(0,1);	
f1->SetParameter(1,2);	
//f1->SetParameter(2,1);	
TF1 *f2 = new TF1("f2",fitf,500,1400);
f2->SetParameter(0,1);	
f2->SetParameter(1,2);	
//f2->SetParameter(2,1);
TF1 *f3 = new TF1("f3",fitf,500,1400);
f3->SetParameter(0,1);	
f3->SetParameter(1,2);	
//f3->SetParameter(2,1);
TF1 *f4 = new TF1("f4",fitf,500,1400);
f4->SetParameter(0,1);	
f4->SetParameter(1,2);	
//f4->SetParameter(2,1);


f1->SetLineColor(14);
f2->SetLineColor(2);
f3->SetLineColor(3);
f4->SetLineColor(4);
f1->SetLineStyle(9);
f2->SetLineStyle(9);
f3->SetLineStyle(9);
f4->SetLineStyle(9);


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


TLegend *legend=new TLegend(0.74,0.61,0.89,0.86);	// Declaración de la leyenda
legend->SetTextFont(50);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.03);				// Tamaño de la fuente de la leyenda

legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");
legend->AddEntry(gr3,serie3,"p");
legend->AddEntry(gr4,serie4,"p");


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
