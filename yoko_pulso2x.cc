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

Float_t datosy[N],datosy2[N],x[N],y[N],y2[N]; 		// para poner los   datos      
Int_t i,j,m,pulso,ini=0,fin=0,tot=0;  				// variables sueltas
char tituloa[100]="Preamp. Out",titulob[100]="Preamp / T.F. Out ", ejex[100]="time (#mus)",ejey[100]="voltage (V)";
char ar[100],arch[100], ci[100]="";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,400);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);


gROOT->SetStyle("Pub");


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
	c1->Divide(2,tot+1);
	}
else
	{
	if (tot<10)
		c1->Divide(4,tot/2+1);
	else
		c1->Divide(8,tot/4+1);
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
		{*in  >> datosy[i] >> datosy2[i];                  
                if ((strstr(ci,"END")!=NULL))          // si encuentro el END
			{
			i=N;			        // le pongo a i, N para que salga del for	
			}

		}   
	}
	delete in;   

for (i=0;i<(N-1);i++)                                      // cargo los datos en x e y, y2
		{
		x[i]=i*0.02-25;
		y[i]=datosy[i];
		y2[i]=datosy2[i];		
		}   


TGraph *gr1 = new TGraph(N-1,x,y);			// Declaración del gráfico.
gr1->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);					// Ancho de la linea
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x

TGraph *gr2 = new TGraph(N-1,x,y2);			// Declaración del gráfico.
gr2->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr2->SetLineWidth(1);					// Ancho de la linea
gr2->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x




c1->cd(1+(j-ini)*2);						// Me cambio al marco 1 en el que se divide el canvas
gr1->Draw("AL");					// Pinta el gráfico A:marco P=puntos L=linea C=curva

/*
TLegend *legend=new TLegend(0.30,0.92,0.70,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"Preamp. Out"); 
legend->AddEntry(ar,ar,"p");
legend->Draw();

*/

c1->cd(2+(j-ini)*2);						// Me cambio al marco 1 en el que se divide el canvas
gr2->Draw("AL");
/*
TLegend *legend2=new TLegend(0.30,0.92,0.70,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Preamp / T.F. Out" );  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();*/
}




//gr1->FitPanel();					// Muestra el panel de Fit
c1->cd(0);
/*
TLegend *legend=new TLegend(0.54,0.05,0.74,0.10);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
m=sprintf(ar," Pulso Nro: %d ",pulso);  		// Introduce una leyenda con datos
legend->AddEntry(ar,ar,"p");			        // Añado entrada a la leyenda
//gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
legend->Draw();			        		// Dibujo la leyenda
*/
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;


}
