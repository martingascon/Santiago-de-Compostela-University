//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa los datos n series en formato como el ejemplo. Debe terminar en 0
//	
//	nro serie     x1   deltax1     y1   deltay1
//  ej.     1          1905    	1	173	1
//	    1          1906	1	173 	1
//	    2 	       2340	1	173	1 	
//	    0		0	0	0	0

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

#define N 1				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t x1[N],x2[N],x3[N],x4[N],ex1[N],ex2[N],ex3[N],ex4[N];
Float_t y1[N],y2[N],y3[N],y4[N],ey1[N],ey2[N],ey3[N],ey4[N];   
Float_t datosx[N],datosy[N],errorx[N],errory[N]; 		      

Int_t i,j,k,l,m,aux=1;  
char fich[100]="pol1",serie1[12]="det. 1",serie2[12]="det. 2",serie3[12]="det. 3",serie4[12]="det. 4";
//char fitf[100]="([0]+x*[1]+[2]*exp(x*[3]))";

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,3000,250);      

hr->SetXTitle("Channels");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy (keV)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);		
hr->GetYaxis()->SetLabelColor(1);


for (k=0;k<40;k++)			// inicializar variables
	{
	x1[k]=0;x2[k]=0;x3[k]=0;x4[k]=0;ex1[k]=0;ex2[k]=0;ex3[k]=0;ex4[k]=0; 
	y1[k]=0;y2[k]=0;y3[k]=0;y4[k]=0;ey1[k]=0;ey2[k]=0;ey3[k]=0;ey4[k]=0; 
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
	i=j=k=l=0;

	//*in >> aux >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i];
	while (aux!=0)
	   {
	     *in >> aux >> datosx[0] >> errorx[0] >> datosy[0] >> errory[0];
	     
	 switch (aux)		
		{
		case 1: {x1[i]=datosx[0];ex1[i]=errorx[0];y1[i]=datosy[0];ey1[i]=errory[0];
			i++;				
			break;}
		case 2: {x2[j]=datosx[0];ex2[j]=errorx[0];y2[j]=datosy[0];ey2[j]=errory[0];
			j++;
			break;}
		case 3: {x3[k]=datosx[0];ex3[k]=errorx[0];y3[k]=datosy[0];ey3[k]=errory[0];
			k++;
			break;}
		case 4: {x4[l]=datosx[0];ex4[l]=errorx[0];y4[l]=datosy[0];ey4[l]=errory[0];
			l++;
			break;}
		case 0: {break;}
		}
	   
	   }
	}


//**************** Representación  **************



TGraphErrors *gr1 = new TGraphErrors(3,x1,y1,ex1,ey1);			// Declaración del gráfico 1.
TGraphErrors *gr2 = new TGraphErrors(3,x2,y2,ex2,ey2);			// Declaración del gráfico 2.
TGraphErrors *gr3 = new TGraphErrors(3,x3,y3,ex3,ey3);	
TGraphErrors *gr4 = new TGraphErrors(3,x4,y4,ex4,ey4);	
/*
TF1 *f1 = new TF1("f1","([0]+x*[1])",500,1600); 
TF1 *f2 = new TF1("f2","([0]+x*[1])",500,1600);
TF1 *f3 = new TF1("f3","([0]+x*[1])",500,1600);
TF1 *f4 = new TF1("f4","([0]+x*[1])",500,1600);	

f1->SetParameter(0,-2.1);				
f1->SetParameter(1,0.07);
f2->SetParameter(0,-2.1);				
f2->SetParameter(1,0.07);
f3->SetParameter(0,-2.1);				
f3->SetParameter(1,0.07);
f4->SetParameter(0,-2.1);				
f4->SetParameter(1,0.07);



TF1 *f1 = new TF1("f1","([0]+[1]*x+[2]*exp(x*[3]))",600,2500); 
TF1 *f2 = new TF1("f2","([0]+[1]*x+[2]*exp(x*[3]))",600,2500);
TF1 *f3 = new TF1("f3","([0]+[1]*x+[2]*exp(x*[3]))",600,2500);
TF1 *f4 = new TF1("f4","([0]+[1]*x+[2]*exp(x*[3]))",600,2500);

TF1 *f1 = new TF1("f1","([0]+[1]*x+[2]*log(x*[3]))",1,2500); 
TF1 *f2 = new TF1("f2","([0]+[1]*x+[2]*log(x*[3]))",1,2500);
TF1 *f3 = new TF1("f3","([0]+[1]*x+[2]*log(x*[3]))",1,2500);
TF1 *f4 = new TF1("f4","([0]+[1]*x+[2]*log(x*[3]))",1,2500);

TF1 *f1 = new TF1("f1","([0]*log(x*[1]))",-10,2500); 
TF1 *f2 = new TF1("f2","([0]*log(x*[1]))",-10,2500);
TF1 *f3 = new TF1("f3","([0]*log(x*[1]))",-10,2500);
TF1 *f4 = new TF1("f4","([0]*log(x*[1]))",-10,2500);

TF1 *f1 = new TF1("f1","pol1",10,2500); 
TF1 *f2 = new TF1("f2","pol1",10,2500);
TF1 *f3 = new TF1("f3","pol1",10,2500);
TF1 *f4 = new TF1("f4","pol1",10,2500);




*/
TF1 *f1 = new TF1("f1","pol1",0,600); 
TF1 *f2 = new TF1("f2","pol1",0,600);
TF1 *f3 = new TF1("f3","pol1",0,600);
TF1 *f4 = new TF1("f4","pol1",0,600);


/*
f1->SetParameter(0,1);
f1->SetParameter(1,0.001);
f1->SetParameter(2,0.0001);
f2->SetParameter(0,1);
f2->SetParameter(1,0.001);
f2->SetParameter(2,0.0001);
f3->SetParameter(0,1);
f3->SetParameter(1,0.001);
f3->SetParameter(2,0.0001);
f4->SetParameter(0,1);
f4->SetParameter(1,0.001);
f4->SetParameter(2,0.0001);


f1->SetParameter(0,1);				
f1->SetParameter(1,0.07);
f1->SetParameter(2,120);
f1->SetParameter(3,0.001);
f2->SetParameter(0,1);				
f2->SetParameter(1,0.07);
f2->SetParameter(2,120);
f2->SetParameter(3,0.001);
f3->SetParameter(0,1);				
f3->SetParameter(1,0.07);
f3->SetParameter(2,120);
f3->SetParameter(3,0.001);
f4->SetParameter(0,1);				
f4->SetParameter(1,0.07);
f4->SetParameter(2,120);
f4->SetParameter(3,0.001);
*/
f1->SetLineColor(2);
f2->SetLineColor(3);
f3->SetLineColor(4);
f4->SetLineColor(6);

f1->SetLineStyle(1);
f2->SetLineStyle(1);
f3->SetLineStyle(1);
f4->SetLineStyle(1);


gr1->SetMarkerColor(2);
gr1->SetMarkerStyle(23);
gr1->SetMarkerSize(1.2);
gr1->Draw("P");		// Pinta el gráfico A:marco P=puntos L=linea C=curva
gr2->SetMarkerColor(3);
gr2->SetMarkerStyle(23);
gr2->SetMarkerSize(1.2);
gr2->Draw("P");
gr3->SetMarkerColor(4);
gr3->SetMarkerStyle(23);
gr3->SetMarkerSize(1.2);
gr3->Draw("P");
gr4->SetMarkerColor(6);
gr4->SetMarkerStyle(23);
gr4->SetMarkerSize(1.2);
gr4->Draw("P");


gr1->Fit("f1","R+");
gr1->SetLineColor(2);
gr1->SetLineStyle(1);
gr1->Fit("f1","R");

gr2->Fit("f2","R+");
gr2->SetLineColor(3);
gr2->SetLineStyle(1);
gr2->Fit("f2","R");

gr3->Fit("f3","R+");
gr3->SetLineColor(4);
gr3->SetLineStyle(1);
gr3->Fit("f3","R");

gr4->Fit("f4","R");
gr4->SetLineColor(6);
gr4->SetLineStyle(1);

TLegend *legend=new TLegend(0.74,0.61,0.89,0.86);	// Declaración de la leyenda
legend->SetTextFont(50);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.03);				// Tamaño de la fuente de la leyenda

legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");
legend->AddEntry(gr3,serie3,"p");
legend->AddEntry(gr4,serie4,"p");

legend->SetFillColor(0);

legend->Draw();	
legend->SetFillColor(0);
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(11);             		        // Muestro los datos del Fit

legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}



