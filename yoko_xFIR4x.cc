//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Programa para leer 8000 pulsos del Osciloscopio YOKOGAWA 9140 DL 
//************************************* LIBRERIAS INCLUIDAS  **************************************

#include <cstdlib>				
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TRint.h> 
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>
#include <TFrame.h>
#include <TLatex.h>

#define N 2500 					// Número máximo de Datos por Canal
#define I 2000                                  // Número de canales a integrar
#define L 33                                 // Parametro de FIR
#define G 15                                //parametro de FIR
#define F 2*L+G                                 // Funcion de los dos anteriores

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);


char arch[100],ci[100]="", ejex[100]="tiempo (puntos)",ejey[100]="voltaje (V)";
char tituloa[100]="Yokogawa 9140DL (ch1)",titulob[100]="Yokogawa 9140DL (ch2) ",tituloe[100]="XFIR de ch1",titulof[100]="XFIR de ch2 ";
char tituloc[100]="Yokogawa 9140DL (ch3)",titulod[100]="Yokogawa 9140DL (ch4) ",titulog[100]="XFIR de ch3",tituloh[100]="XFIR de ch4 ";
Float_t x[N],datosy[N],datosy2[N],datosy3[N],datosy4[N]; 
Float_t y1[N],sum11,sum21,phi1[N],Emax1; 
Float_t	y2[N],sum12,sum22,phi2[N],Emax2; 
Float_t	y3[N],sum13,sum23,phi3[N],Emax3; 
Float_t	y4[N],sum14,sum24,phi4[N],Emax4; 

Int_t i,k,m;       

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1100,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->Divide(4,2);

gROOT->SetStyle("Default");



     
//*********************************** Cuerpo del programa   *************************************

if (argc<2){
	cout << "Falta el nombre del archivo a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "pulsoyoko [nombre-fichero][sin extensión] 				 " << "\n";
	cout << "									 " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.********" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(arch,"%s.txt",argv[1]);
			break;
		};
	}


for (i=0;i<N;i++)     x[i]=0;                                   // inicializacion de x[i]
ifstream *in = new ifstream(arch);				// in es puntero asignado a fichero
if(!*in) 							// Si no se puede abrir in 
	{	cout << " ERROR OPENING FILE " <<  arch << endl;// Imprime que hay un error
		return 1;					// Salida 1 => error
	}
else    
	{
        i=1;
        do	
	{	*in >> ci;
		if ((strstr(ci,"START")!=NULL))	i=0;
	}
	while (i!=0);	
	for (i=0;i<N;i++)                                        // cargo los datos en datosy, y2
		{
		*in  >> datosy[i] >> datosy2[i] >> datosy3[i] >> datosy4[i];                 // desde -40 a 40 us (otra escala)
       	        if ((strstr(ci,"END")!=NULL)) i=N;               // si llego a END ... salgo
		}   
	for (i=0;i<N;i++)                                        // cargo los datos en y, y2
		{x[i]=i; //*0.04-50;                             // x está en us 
		y1[i]=datosy[i];
		y2[i]=datosy2[i];		
		y3[i]=datosy3[i];
		y4[i]=datosy4[i];	
		}  
	
	// comienzan todos los filtros ***********************************************************************
	sum11=0;						// comienza XFIR para pulso 1.....................
       	sum21=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum11+=y1[k];
       	        sum21+=y1[L+G+k];
	         }
	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
       	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
       	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        }
	Emax1=phi1[0];
	for (k=0;k<(I-F);k++)
      	   if (Emax1<phi1[k]) Emax1=phi1[k];           	 	// calculo el máximo de la energía
	cout << "Emax1: " << Emax1 << endl;
								// termina XFIR PARA PULSO 1 ............................
	sum12=0;						// comienza XFIR para pulso 2.....................
       	sum22=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum12+=y2[k];
       	        sum22+=y2[L+G+k];
	         }
	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi2[i]=(sum22-sum12);                     	//le sumo un elemento a la derecha
       	        sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
       	        sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        }
	Emax2=phi2[0];
	for (k=0;k<(I-F);k++)
            	   if (Emax2<phi2[k]) Emax2=phi2[k];     	// calculo el máximo de la energía
	cout << "Emax2: " << Emax2 << endl;
								// termina XFIR PARA PULSO 2 ............................

	sum13=0;						// comienza XFIR para pulso 3.....................
       	sum23=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum13+=y3[k];
       	        sum23+=y3[L+G+k];
	         }
	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi3[i]=(sum23-sum13);                     	//le sumo un elemento a la derecha
       	        sum13=sum13+y3[i+L+1]-y3[i];        		//le resto un elemento a la izquierda
       	        sum23=sum23+y3[F+1+i]-y3[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        }
	Emax3=phi3[0];
	for (k=0;k<(I-F);k++)
      	   if (Emax3<phi3[k]) Emax3=phi3[k];           	 	// calculo el máximo de la energía
	cout << "Emax3: " << Emax3 << endl;
								// termina XFIR PARA PULSO 3 ............................
	sum14=0;						// comienza XFIR para pulso 4.....................
       	sum24=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum14+=y4[k];
       	        sum24+=y4[L+G+k];
	         }
	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi4[i]=(sum24-sum14);                     	//le sumo un elemento a la derecha
       	        sum14=sum14+y4[i+L+1]-y4[i];        		//le resto un elemento a la izquierda
       	        sum24=sum24+y4[F+1+i]-y4[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        }
	Emax4=phi4[0];
	for (k=0;k<(I-F);k++)
            	   if (Emax4<phi4[k]) Emax4=phi4[k];     	// calculo el máximo de la energía
	cout << "Emax4: " << Emax4 << endl;
								// termina XFIR PARA PULSO 4 ............................
	}
	// terminan todos los filtros ***********************************************************************

TGraph *gr1 = new TGraph(N,x,y1);			// Declaración del gráfico.
gr1->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);					// Ancho de la linea
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr1->SetTitle(tituloa);					// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr2 = new TGraph(N,x,y2);			// Declaración del gráfico.
gr2->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr2->SetLineWidth(1);					// Ancho de la linea
gr2->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr2->SetTitle(titulob);					// Escribe como título del grafico lo que hay en titulo
gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr3 = new TGraph(N,x,y3);			// Declaración del gráfico.
gr3->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr3->SetLineWidth(1);					// Ancho de la linea
gr3->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr3->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr3->SetTitle(tituloc);					// Escribe como título del grafico lo que hay en titulo
gr3->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr3->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr3->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr3->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr4 = new TGraph(N,x,y4);			// Declaración del gráfico.
gr4->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr4->SetLineWidth(1);					// Ancho de la linea
gr4->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr4->SetTitle(titulod);					// Escribe como título del grafico lo que hay en titulo
gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr4->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr4->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr5 = new TGraph(I-F,x,phi1);			// Declaración del gráfico.
gr5->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr5->SetLineWidth(1);					// Ancho de la linea
gr5->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr5->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr5->SetTitle(tituloe);					// Escribe como título del grafico lo que hay en titulo
gr5->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr5->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr5->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr5->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr6 = new TGraph(I-F,x,phi2);			// Declaración del gráfico.
gr6->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr6->SetLineWidth(1);					// Ancho de la linea
gr6->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr6->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr6->SetTitle(titulof);					// Escribe como título del grafico lo que hay en titulo
gr6->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr6->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr6->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr6->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x


TGraph *gr7 = new TGraph(I-F,x,phi3);			// Declaración del gráfico.
gr7->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr7->SetLineWidth(1);					// Ancho de la linea
gr7->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr7->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr7->SetTitle(titulog);					// Escribe como título del grafico lo que hay en titulo
gr7->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr7->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr7->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr7->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr8 = new TGraph(I-F,x,phi4);			// Declaración del gráfico.
gr8->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr8->SetLineWidth(1);					// Ancho de la linea
gr8->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr8->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr8->SetTitle(tituloh);					// Escribe como título del grafico lo que hay en titulo
gr8->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr8->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr8->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr8->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x




c1->cd(1);						// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(2);						// Me cambio al marco 1 en el que se divide el canvas
gr2->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(3);						// Me cambio al marco 1 en el que se divide el canvas
gr3->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(4);						// Me cambio al marco 1 en el que se divide el canvas
gr4->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(5);						// Me cambio al marco 1 en el que se divide el canvas
gr5->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(6);						// Me cambio al marco 1 en el que se divide el canvas
gr6->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(7);						// Me cambio al marco 1 en el que se divide el canvas
gr7->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
c1->cd(8);						// Me cambio al marco 1 en el que se divide el canvas
gr8->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva


c1->cd(0);


theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

