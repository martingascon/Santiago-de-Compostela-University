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
#include <TMath.h>


#define N 2500 					 // Número máximo de Datos por Canal
#define I 2200                                   // Número de canales a integrar
#define L 25
#define G 25                 	  	    	 //parametro de FIR
#define F 2*L+G                                  // Funcion de los dos anteriores
#define Gain 151579/(2*L)	                 // Parametro de FIR

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char titulo[100]="Titulo del grafico",arch[100],ci[100]="";
Float_t x[N],datosy[N],suple; 
Float_t y1[N],sum11,sum21,phi1[N],integ1[100000],Emax1,inte; 


Int_t i,j,k,k1=0,k2=0,m,nini=0, nfin=7999;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

     
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									" << "\n";
	cout << "Modo de uso: read800_yoko [FICHERO](sin extens.) [N_ini] [N_fin]       " << "\n";
	cout << "		          				  	        " << "\n";
	cout << "Este programa lee los datos de 8000 ficheros ASCII, los integra y      " << "\n";
	cout << "los representa en un histograma  					" << "\n";
	cout << "		          		  			        " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.*******" << "\n";
	cout << "									" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA" << endl;
			break;
		case 3: nini=atoi(argv[1]);
			nfin=atoi(argv[2]);	
			break;
		case 4: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA"  << endl;
			break;
		case 5: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA"  << endl;
			break;
		};
	}
for (i=0;i<N;i++)     x[i]=0;                                   // inicializacion de x[i]


ofstream *out4 = new ofstream("datos.txt");                      //genero el fich del espect para guardar datos
ofstream *out = new ofstream("espectro.mca");                 //genero el fich del espect para guardar datos
ofstream *out2 = new ofstream("espectro2.mca");               //genero el fich del espect para guardar datos
ofstream *out3 = new ofstream("espectro3.mca");  
for (j=nini;j<(nfin+1);j++) 					//sumo desde nini a nfin los 8000 ficheros
{	m=sprintf(arch,"%d.txt",j);  				//cargo en arch el nombre del fichero
	ifstream *in = new ifstream(arch);			// in es puntero asignado a fichero
	if(!*in) 						// Si no se puede abrir in 
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
			*in  >> datosy[i];                 // desde -40 a 40 us (otra escala)
        	        if ((strstr(ci,"END")!=NULL)) i=N;               // si llego a END ... salgo
			}   
		for (i=0;i<N;i++)                                        // cargo los datos en y, y2
			{x[i]=i;					 //*0.04-50;      // x está en us 
			y1[i]=datosy[i];
			}  
		sum11=0;						//comienza XFIR para pulso 1.....................
        	sum21=0;
        	for (k=0;k<=L;k++)                              	//Caculo las dos primeras sumas
        	        {
        	        sum11+=y1[k];
        	        sum21+=y1[L+G+k];
		         }
		for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
        	        {                                       	//sum2-sum1 me da la energia
        	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
        	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
        	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
        	        }
		Emax1=phi1[0];

		for (k=0;k<1000;k++)
             	  {
		   if (Emax1<phi1[k])  
			{
			Emax1=phi1[k];          	 		// calculo el máximo para 1
			k1=k; 						//cout << k1 << endl;
			}

		   }

		integ1[j]=Emax1;                       			// los pulsos eran negativos.
		Emax1=0;						// termina XFIR PARA PULSO 1 ............................
		delete in;						
	

if ((j%100)==0) cout << "ficheros: " << j << "/" << nfin << endl;
	}

}


//fichroot->Close();
//delete fichroot;

for (j=nini;j<(nfin+1);j++)
	{

	H1->Fill((integ1[j])*Gain);           // lleno el histograma

	}

 
*out << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        *out << H1->GetBinContent(j) << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
*out << "<<END>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro




H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle("H1");   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); H1->Rebin(8); 
c1->cd(1); H1->Draw();
c1->cd(0);



theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

