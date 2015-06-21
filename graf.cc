//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRint.h>
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
gROOT->SetStyle("Plain");
Float_t datosx[N],datosy[N],errorx[N],errory[N],x[N],y[N],a=0,b=60,d,e,f,g,h; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m2,opc=1,p=1;  
char op[20]="x",titulo[100]="titulo",fich[100],ejex[100]="titulo x",ejey[100]="titulo y",ar[100];
char fitf[100]="([0]-[1]*exp(-x*[2]))";//"-[3]*exp(-x*[4]))";
TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->Divide(1,1);
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << "Modo de empleo: graf [FICHERO](sin extens.) [OPCIONES] [FUNCION DE AJUSTE]" << "\n";
	cout << "[NUMERO DE PARAMETROS] [LIMITES DEL AJUSTE]   			           " << "\n";
	cout << "OPCIONES: 		x: 1 columna (defecto)			           " << "\n";
	cout << "    			y: 2 columnas					   " << "\n";
	cout << "                       e: con errores               	                   " << "\n";
	cout << "                       a: con ajuste               			   " << "\n";
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.txt",argv[1]);
			break;
		case 3: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(op,"%s",argv[2]);
			if ((strstr(op,"x")!=NULL)) opc=1; if ((strstr(op,"xy")!=NULL)) opc=2;
			if ((strstr(op,"xye")!=NULL)) opc=3;if ((strstr(op,"xyea")!=NULL)) opc=4;
			if ((strstr(op,"xyae")!=NULL)) opc=4;if ((strstr(op,"xya")!=NULL)) opc=5;
			break;
		case 4: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(op,"%s",argv[2]);
			if ((strstr(op,"x")!=NULL)) opc=1; if ((strstr(op,"xy")!=NULL)) opc=2;
			if ((strstr(op,"xye")!=NULL)) opc=3;if ((strstr(op,"xyea")!=NULL)) opc=4;
			if ((strstr(op,"xyae")!=NULL)) opc=4;if ((strstr(op,"xya")!=NULL)) opc=5;			
			m=sprintf(fitf,"%s",argv[3]);
			break;
		case 7: m=sprintf(fich,"%s.txt",argv[1]);
			m=sprintf(op,"%s",argv[2]);
			if ((strstr(op,"x")!=NULL)) opc=1; if ((strstr(op,"xy")!=NULL)) opc=2;
			if ((strstr(op,"xye")!=NULL)) opc=3;if ((strstr(op,"xyea")!=NULL)) opc=4;
			if ((strstr(op,"xyae")!=NULL)) opc=4;if ((strstr(op,"xya")!=NULL)) opc=5;
			m=sprintf(fitf,"%s",argv[3]);
			p=atoi(argv[4]);
			a=atof(argv[5]);b=atof(argv[6]);
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
	if (opc==1)
		while (!in->eof())
		{
		*in >>  datosx[i] >> datosy[i] >> errorx[i] >> errory[i];  
		datosy[i]=datosx[i];
		datosx[i]=i+1;
		errorx[i]=0;
		errory[i]=0;
		i++;
		}
	if ((opc==2)||(opc==5))
		while (!in->eof())
		{
		*in >>  datosx[i] >> datosy[i] >> errorx[i] >> errory[i];  
		errorx[i]=0;
		errory[i]=0;
		i++;
		}

	if ((opc==3)||(opc==4))
		while (!in->eof())
		{
		*in >> datosx[i] >> datosy[i] >> errorx[i] >> errory[i];  
		i++;
		}
	}

TGraphErrors *gr1 = new TGraphErrors(i-1,datosx,datosy,errorx,errory);	// Declaración del gráfico con barras de error
gr1->SetLineColor(1);						// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);						// Ancho de la linea 0=blanco 1=negro, 2=rojo
gr1->SetMarkerColor(2);						// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(21);					// Estilo del punto 21 = cuadrado
gr1->GetXaxis()->SetLabelSize(0.04);
gr1->GetYaxis()->SetLabelSize(0.04);

gr1->GetXaxis()->SetTitleOffset(1.0);
gr1->GetYaxis()->SetTitleOffset(1.3);

gr1->SetTitle("Espectro de emision de CsI(Tl)");		// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle("Longitud de onda (nm)");		// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("Intensidad (u.a.)");			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();					// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();					// Para centrar el titulo del eje x
TF1 *f1 = new TF1("f1",fitf,a,b); 				// La variable "fitf" contiene la funcion a ajustar
if ((opc==3)||(opc==4))
	{
				
	switch (p)
		{
		case 1: f1->SetParameter(0,1);
			break;
		case 2: f1->SetParameter(0,1);					
			f1->SetParameter(1,1);
			break;
		case 3: f1->SetParameter(0,6.3);				
			f1->SetParameter(1,0.1);				
			f1->SetParameter(2,0.1);	
			break;
		case 4: f1->SetParameter(0,1);				
			f1->SetParameter(1,1);				
			f1->SetParameter(2,1);	
			f1->SetParameter(3,1);	
			break;
		case 5: f1->SetParameter(0,1);				
			f1->SetParameter(1,1);				
			f1->SetParameter(2,1);	
			f1->SetParameter(3,1);	
			f1->SetParameter(4,1);
			break;

		}
	gr1->Fit("f1","R");					// Hago el Fit en el grafico gr1 de f1 en la region 0 a 14
	
	}

c->cd(1);							// Me cambio al marco 1 en el que se divide el canvas

gr1->Draw("AP");						// Pinta el gráfico A:marco P=puntos L=linea C=curva
if ((opc==1)||(opc==2)||(opc==3))	gr1->FitPanel();	// Muestra el panel de Fit
					
if ((opc==4)||(opc==5))
	{
	TLegend *legend=new TLegend(0.40,0.75,0.90,0.90,"funcion ajustada");	// Declaración de la leyenda
	legend->SetTextFont(72);				// Tipo de fuente de la leyenda
	legend->SetTextFont(1);	
	legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
	d=f1->GetParameter(0);
	e=f1->GetParameter(1);
	f=f1->GetParameter(2);
	m=sprintf(ar,"y(x) = %.1f+%.1f*exp(-x*%.1f)",d,e,f);	// Introduce una leyenda con datos
	legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
	legend->Draw();						// Dibujo la leyenda 
	}	
	
//gStyle->SetOptFit(11);             		        	// Muestro los datos del Fit
theApp->Run(kTRUE);						// Para hacer el ejecutable
delete theApp;
return 0;
}
