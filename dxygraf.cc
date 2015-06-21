//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TRint.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TH1.h>
#include <TH1I.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TLine.h>
#include <TAttText.h>
#include <TAxis.h>
#include <TPad.h>
#include <TPave.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>
#include <TGaxis.h>
#include <TSpline.h>


#define N 50000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t mean,sigma,newtrigger, dmean,dsigma,datosy[N],datosy2[N],datosx[N],x[N],y[N],y2[N]; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0);
c1->GetFrame()->SetBorderSize(1);    
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TPad *pad2 = new TPad("pad2","",0,0,1,1);
pad2->SetFillStyle(4000); //will be transparent
pad1->Draw();
pad1->cd();



//TH1F *hr = c1->DrawFrame(0,0,10000,500);          // draw a frame to define the range
//hr->SetTitle("Espectro de emision de CsI(Tl) ");	// Escribe como título del grafico lo que hay en titulo
//hr->SetXTitle("Longitud de onda (nm)");		// Escribe como titulo del eje x lo que hay en ejex
//hr->SetYTitle("Produccion de luz (fotones/(MeV.nm)) ");// Escribe como titulo del eje y lo que hay en ejey
//hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
//hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: xygraf [FICHERO](sin extens.) [TITULO] [EJE X] [EJE Y]    " << "\n";
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
		case 3: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			m=sprintf(ejex,"%s",argv[3]);
			break;
		case 6: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(titulo,"%s",argv[2]);
			m=sprintf(ejex,"%s",argv[3]);
			m=sprintf(ejey,"%s",argv[4]);
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
		*in >> datosx[i] >> datosy[i] >> datosy2[i];  
		i++;
		}
	}

TH2F *gr1 = new TH2F("gr1","gr1",100,1,8000000,4096,450,600);
TH2F *gr2 = new TH2F("gr2","gr2",100,1,8000000,4000,0,100); 

for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	gr1->Fill(x[k],y[k]);
	gr2->Fill(x[k],y2[k]);
	}
/*
TGraph *gr1 = new TGraph(k,x,y);			// Declaración del gráfico 1.
TGraph *gr2 = new TGraph(k,x,y2);			// Declaración del gráfico 2.
*/

				


gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(21);
gr1->GetXaxis()->SetLabelSize(0.03);			
gr1->GetYaxis()->SetLabelSize(0.03);	
//gr1->SetTitle("titulo ");				// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle("time");			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("Photopeak channel");			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();
gr1->Draw();					// Pinta el gráfico A:marco P=puntos L=linea C=curva

/*
TSpline *s = new TSpline3("grs",gr1);
s->SetLineColor(kRed);
s->Draw("same");*/

//pad1->Update(); //this will force the generation of the "stats" box


//TPaveStats *ps1 = (TPaveStats*)gr1->GetListOfFunctions()->FindObject("stats");
//ps1->SetX1NDC(0.4); ps1->SetX2NDC(0.6);
//pad1->Modified();
c1->cd();

 //compute the pad range with suitable margins
   Double_t ymin = 10;
   Double_t ymax = 16;
   Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom
   Double_t xmin = 2;
   Double_t xmax = 8000000;
   Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
   pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
   pad2->Draw();
   pad2->cd();

//gStyle->SetOptStat(1);  

gr2->SetMarkerColor(kRed);
gr2->SetMarkerStyle(20);
gr2->Draw("same");


 pad2->Update();
 //TPaveStats *ps2 = (TPaveStats*)gr2->GetListOfFunctions()->FindObject("stats");
 //ps2->SetX1NDC(0.65); ps2->SetX2NDC(0.85);
 //ps2->SetTextColor(kRed);
   
   // draw axis on the right side of the pad
   TGaxis *axis = new TGaxis(xmax,ymin,xmax,ymax,ymin,ymax,50510,"+L");
   //axis->SetLabelColor(kRed);
   axis->Draw();
   axis->SetTitle("Energy resolution (%)");
   axis->CenterTitle();
//pad1->cd();
  c1->cd(); 
//gr1->FitPanel();					// Muestra el panel de Fit
/*TLatex *t = new TLatex();				// Leyenda en cada una de las graficas
   t->SetNDC();
   t->SetTextFont(62);
   t->SetTextColor(36);
   t->SetTextSize(0.08);
   t->SetTextAlign(12);
   t->SetTextSize(0.045);
   t->SetTextColor(kBlue);
   t->DrawLatex(0.20,0.85,"XP1918");
   t->SetTextColor(kGreen);
   t->DrawLatex(0.6,0.85,"XP1901");*/

/*
TLegend *legend=new TLegend(0.64,0.61,0.99,0.66);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
//m=sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
legend->AddEntry(titulo,titulo,"p");			*/// Añado entrada a la leyenda
gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
//legend->Draw();					// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
