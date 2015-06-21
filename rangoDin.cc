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
#include <TGaxis.h>


#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Int_t i,k,m; 
char fich[100],serie1[100]="Titulo Serie1",serie2[100]="Titulo Serie2";
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N],mins1,maxs1,mins2,maxs2;    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N]; 		      
char fitf[100]="([0]/sqrt([1]*x)+[2] )";
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
gPad->SetLogy();
gPad->SetLogx();
TH1F *hr = c1->DrawFrame(200,0.1,5000000,67);      

hr->SetXTitle("Neh");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->SetTitleSize(0.04);	
hr->GetXaxis()->SetLabelSize(0.04);	
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
//hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	

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
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(serie1,"%s",argv[2]);
			m=sprintf(serie2,"%s",argv[3]);
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
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}

mins1=x[0];maxs1=x[k];cout << mins1 << "\n";cout << maxs1 << "\n";
mins2=x[0];maxs2=x[k];

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
//TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.

TF1 *f1 = new TF1("f1",fitf,100,10000000); 
//TF1 *f2 = new TF1("f2",fitf,200,460); 
f1->SetParameter(0,1);	
f1->SetParameter(1,2);	
f1->SetParameter(2,0.01);	
 
 TGaxis *axis5 = new TGaxis(200,0.2,2*1e6,0.2,0.041,200,510,"G");
  axis5->SetName("axis5");
  axis5->SetLabelSize(0.04);
  //axis5->SetTextFont(72);
  axis5->SetTitle("Photon Energy (MeV)");
  axis5->SetTitleOffset(-0.6);
  axis5->SetTitleSize(0.04);
  axis5->CenterTitle();
  axis5->Draw();

 TGaxis *axis6 = new TGaxis(200,100,2000000,100,0,12,510,"");
  axis6->SetName("axis6");
 axis6->SetLabelSize(0.04);
   axis6->SetTitleSize(0.04);
 // axis6->SetTextFont(72);
  axis6->SetTitleOffset(-0.5);
  axis6->SetTitle("Preamp. pulse height [V]");
  axis6->CenterTitle();
  axis6->Draw();


gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
//gr2->SetMarkerColor(kRed);
//gr2->SetMarkerStyle(21);
//gr2->SetMarkerSize(1.5);
//gr2->Draw("p");

f1->SetLineColor(4);
//f2->SetLineColor(2);
gr1->Fit("f1","R+");
//gr2->Fit("f2","R+");
gr1->SetLineColor(14);
//gr2->SetLineColor(2);

TLegend *legend=new TLegend(0.54,0.61,0.91,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
//legend->AddEntry(gr2,serie2,"p");
legend->SetFillColor(0);
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
//legend->SetTextColor(0);
//legend->Draw();	
//legend->AddEntry(titulo,titulo,"p");			// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit

//legend->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
