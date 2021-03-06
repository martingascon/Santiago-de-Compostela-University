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
#include <TCutG.h>
#define N 2500 					// Número máximo de Datos por Canal

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char tituloa[100]="Yokogawa 9140DL (ch1)",titulob[100]="Yokogawa 9140DL (ch2) ",tituloc[100]="XFIR de ch1",titulod[100]="XFIR de ch2 ",arch[100],ci[100]="", ejex[100]="time (channels)",ejey[100]="voltage (V)";
Float_t x[N],datosy[N],datosy2[N]; 
Float_t y1[N],sum11,sum21,phi1[N],Emax1; 
Float_t	y2[N],sum12,sum22,phi2[N],Emax2; 

Int_t I=2000, L=50, G=50, F=2*L+G;
Int_t i,k,m;       

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1000,400);     //Definición de canvas 400 era 800
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
//c1->Divide(2,2);
c1->Divide(2,1);
gROOT->SetStyle("Default");

for (i=0;i<N;i++)    phi1[i]=0;       
for (i=0;i<N;i++)    phi2[i]=0;  
     
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

		case 4: m=sprintf(arch,"%s.txt",argv[1]);
			L=atoi(argv[2]);G=atoi(argv[3]);
			F=2*L+G;
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
		*in  >> datosy[i] >> datosy2[i];                 // desde -40 a 40 us (otra escala)
       	        if ((strstr(ci,"END")!=NULL)) i=N;               // si llego a END ... salgo
		}   
	for (i=0;i<N;i++)                                        // cargo los datos en y, y2
		{x[i]=i; //  *0.02-50;                           // x está en us 
		y1[i]=datosy[i];
		y2[i]=datosy2[i];		
		}  

TGraph *gr1 = new TGraph(N,x,y1);			// Declaración del gráfico.
gr1->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);					// Ancho de la linea
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr1->SetTitle("Preamplifier pulse");			// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("time ((#mus)");		// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr2 = new TGraph(N,x,y2);			// Declaración del gráfico.
gr2->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr2->SetLineWidth(1);					// Ancho de la linea
gr2->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr2->SetTitle("Preamplifier pulse");			// Escribe como título del grafico lo que hay en titulo
gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr2->GetYaxis()->SetTitleOffset(1.1);			// Para separar el título
gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr3 = new TGraph(I-F,x,phi1);			// Declaración del gráfico.
gr3->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr3->SetLineWidth(1);					// Ancho de la linea
gr3->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr3->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr3->SetTitle(tituloa);					// Escribe como título del grafico lo que hay en titulo
gr3->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr3->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr3->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr3->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr4 = new TGraph(I-F,x,phi2);			// Declaración del gráfico.
gr4->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr4->SetLineWidth(1);					// Ancho de la linea
gr4->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr4->SetTitle(titulob);					// Escribe como título del grafico lo que hay en titulo
gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr4->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr4->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x



c1->cd(1);						// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AL");
c1->cd(2);							// Me cambio al marco 2 en el que se divide el canvas
gr2->Draw("AL");

c1->cd(3);						// Me cambio al marco 3 en el que se divide el canvas
gr3->Draw("AL");	
c1->cd(4);						// Me cambio al marco 4 en el que se divide el canvas
gr4->Draw("AL");

	sum11=0;						// comienza XFIR para pulso 1.....................
       	sum21=0;
	sum12=0;						// comienza XFIR para pulso 2.....................
       	sum22=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum11+=y1[k];
       	        sum21+=y1[L+G+k];	
       	        sum12+=y2[k];
       	        sum22+=y2[L+G+k];
	         }

	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
       	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
       	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        phi2[i+F]=(sum22-sum12);                     	//le sumo un elemento a la derecha
       	        sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
       	        sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar



		c1->cd(1);					// Me cambio al marco 1 en el que se divide el canvas
		TGraph *gr4 = new TGraph(I,x,phi2);		// Declaración del gráfico.
		gr4->SetLineColor(2);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr4->SetLineWidth(1);					// Ancho de la linea
		gr4->SetMarkerColor(2);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr4->SetTitle("FIR pulse");					// Escribe como título del grafico lo que hay en titulo
		gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr4->GetYaxis()->SetTitle("FIR amplitude (a.u.)");			// Escribe como titulo del eje y lo que hay en ejey
		gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr4->GetYaxis()->CenterTitle();	
	
		if (i%19==0) c1->Update();
		Float_t	xb1[4]={L+G+i,F+i,F+i,L+G+i},yb1[4]={-0.02,-0.02,0.25,0.25}; 	
		Float_t	xb2[4]={i,L+i,L+i,i},yb2[4]={-0.02,-0.02,0.25,0.25}; 
		TCutG *g1= new TCutG("corte1",4,xb1,yb1);
		TCutG *g2= new TCutG("corte2",4,xb2,yb2);
		g1->SetFillColor(3); g1->SetFillStyle(3001); //g1->SetLineWidth(1);  		
		g2->SetFillColor(2); g2->SetFillStyle(3001); //g1->SetLineWidth(1);    
		if (i%19==0) g1->Draw("F"); 
		if (i%19==0) g2->Draw("F");
		c1->cd(2);				// Me cambio al marco 1 en el que se divide el canvas
		/*TGraph *gr2 = new TGraph(I-F,x,phi2);
		if (i%20==0) c1->Update();	
		Float_t	xb3[4]={L+G+i,F+i,F+i,L+G+i},yb3[4]={-0.02,-0.02,0.25,0.25}; 	
		Float_t	xb4[4]={i,L+i,L+i,i},yb4[4]={-0.02,-0.02,0.25,0.25}; 
		TCutG *g3= new TCutG("corte3",4,xb3,yb3);
		TCutG *g4= new TCutG("corte4",4,xb4,yb4);
		g3->SetFillColor(2); g3->SetFillStyle(3001); //g1->SetLineWidth(1);    
		g4->SetFillColor(3); g4->SetFillStyle(3001); //g1->SetLineWidth(1);  
		if (i%20==0)  if (i%20==0) g4->Draw("F");//g3->Draw("F");
		if (i%20==0) c1->Update();*/	
		//c1->cd(3);						// Me cambio al marco 1 en el que se divide el canvas
		//if (i%20==0) gr1->Draw("AL");		
		//c1->cd(4);						// Me cambio al marco 1 en el que se divide el canvas
		if (i%19==0) gr4->Draw("AL");c1->Update();
		//gROOT->ProcessLine(".!sleep 0.00005");		
		/*if (i%19==0)
			{Char_t ch[100];
			m=sprintf(ch,"fig_%04d.png",i);
			c1->Print(ch);
			}	*/			
		}
	Emax1=phi1[0];
	for (k=0;k<(I-F);k++)
      	   if (Emax1<phi1[k]) Emax1=phi1[k];           	 	// calculo el máximo de la energía
	cout << "Emax1: " << Emax1 << endl;			// termina XFIR PARA PULSO 1 ............................
	Emax2=phi2[0];
	for (k=0;k<(I-F);k++)
            	   if (Emax2<phi2[k]) Emax2=phi2[k];     	// calculo el máximo de la energía
	cout << "Emax2: " << Emax2 << endl;
								// termina XFIR PARA PULSO 2 ............................
	}

c1->cd(0);








theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

