//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Este programa representa un pulso del osciloscopio YOKOGAWA DL 9140 DL

#include <cstdlib>					//LIBRERIAS INCLUIDAS
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

#define N 2500				       // Número máximo de Datos por Canal
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t datosy[N],datosy2[N],datosy3[N],datosy4[N],x[N],y[N],y2[N],y3[N],y4[N]; 		// para poner los   datos      
Int_t i,j,m,pulso,ini=0,fin=0,tot=0;  							// variables sueltas
char tituloa[100]="channel 1",titulob[100]="channel 2 ",tituloc[100]="channel 3 ",titulod[100]="channel 4 ",ejex[100]="tiempo (#mus)",ejey[100]="voltaje (V)";
char ar[100],arch[100], ci[100]="";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);


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
			ini=atoi(argv[1]);fin=ini;
			break;
		case 3: m=sprintf(arch,"%s.txt",argv[1]);
			ini=atoi(argv[1]);fin=atoi(argv[2]);
			break;		
        	case 4: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
        	case 5: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
		case 6: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
			
		};
	}

tot=fin-ini;
if (tot<5)
	{
	c1->Divide(4,tot+1);
	}
else
	{
	if (tot<20)
		c1->Divide(8,tot/2+1);
	else
		c1->Divide(16,tot/4+1);
	}
pulso=atoi(argv[1]);



for (j=ini;j<(fin+1);j++) 	
{
m=sprintf(arch,"%d.txt",j); 
ifstream *in = new ifstream(arch);

if(!*in) 
	{cout << " ERROR OPENING FILE " <<  arch << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in >> ci;
		if ((strstr(ci,"START")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);                                   // mientras que no encuentre el START que siga	
	for (i=0;i<(N-1);i++)
		{*in  >> datosy[i] >> datosy2[i] >> datosy3[i] >> datosy4[i];                  
                if ((strstr(ci,"END")!=NULL))          // si encuentro el END
			{
			i=N;			        // le pongo a i, N para que salga del for	
			}

		}   
	}
	delete in;   

for (i=0;i<(N-1);i++)                                      // cargo los datos en x e y, y2
		{
		x[i]=i*0.4-500;
		y[i]=datosy[i];
		y2[i]=datosy2[i];		
		y3[i]=datosy3[i];
		y4[i]=datosy4[i];
		}   
TGraph *gr1 = new TGraph(N-1,x,y);			// Declaración del gráfico.
gr1->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);					// Ancho de la linea
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr1->SetTitle(tituloa);					// Escribe como título del grafico lo que hay en titulo
//gr1->GetTitle()->CenterTitle();
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr2 = new TGraph(N-1,x,y2);			// Declaración del gráfico.
gr2->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr2->SetLineWidth(1);					// Ancho de la linea
gr2->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr2->SetTitle(titulob);					// Escribe como título del grafico lo que hay en titulo
gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr3 = new TGraph(N-1,x,y3);			// Declaración del gráfico.
gr3->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr3->SetLineWidth(1);					// Ancho de la linea
gr3->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr3->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr3->SetTitle(tituloc);					// Escribe como título del grafico lo que hay en titulo
gr3->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr3->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr3->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr3->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr4 = new TGraph(N-1,x,y4);			// Declaración del gráfico.
gr4->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr4->SetLineWidth(1);					// Ancho de la linea
gr4->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr4->SetTitle(titulod);					// Escribe como título del grafico lo que hay en titulo
gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr4->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr4->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x		


c1->cd(1+(j-ini)*4);						// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva

c1->cd(2+(j-ini)*4);						// Me cambio al marco 1 en el que se divide el canvas
gr2->Draw("AL");

c1->cd(3+(j-ini)*4);						// Me cambio al marco 1 en el que se divide el canvas
gr3->Draw("AL");

c1->cd(4+(j-ini)*4);						// Me cambio al marco 1 en el que se divide el canvas
gr4->Draw("AL");

}

//gr1->FitPanel();					// Muestra el panel de Fit
c1->cd(0);
/*TLegend *legend=new TLegend(0.74,0.95,0.94,0.99);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.03);				// Tamaño de la fuente de la leyenda
m=sprintf(ar," Pulsos del Yokogawa DL9140: %d-%d ",ini,fin);  		// Introduce una leyenda con datos
legend->AddEntry(ar,ar,"p");			        // Añado entrada a la leyenda
gStyle->SetOptFit(1);             		        // Muestro los datos del Fit
legend->Draw();	*/		        		// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;


}
