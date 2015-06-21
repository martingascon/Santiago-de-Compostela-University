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

#define GAIN 968 				// GANANCIA
#define N 2500 					// Número máximo de Datos por Canal
#define I 2100                                  // Número de canales a integrar
#define L 40                                   // Parametro de FIR
#define G 7                                     //parametro de FIR
#define F 2*L+G                                 // Funcion de los dos anteriores

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char titulo[100]="Titulo del grafico",arch[100],ci[100]="";
Float_t x[N],datosy[N],datosy2[N],suple; 
Float_t y1[N],sum11,sum21,phi1[N],integ1[100000],Emax1; 
Float_t	y2[N],sum12,sum22,phi2[N],integ2[100000],Emax2; 
Float_t y3[N],sum13,sum23,phi3[N],integ3[100000],Emax3; 

Int_t i,j,k,m,nini=0, nfin=7999,dif,ts1,ts2,cont=0;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 


//TH1F *signal =new TH1F("signal","signal",810,0,809);
//TGraph *graf1 =new TGraph();
//TFile *fichroot=new TFile("tree.root","RECREATE");
//TTree *tree = new TTree("tree","signals");
//tree->Branch("Signal","TH1F",&signal,32000,0);

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
ofstream *out = new ofstream("espectro.mca");                 //genero el fich del espect para guardar datos
ofstream *out2 = new ofstream("espectro2.mca");                 //genero el fich del espect para guardar datos
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
			*in  >> datosy[i] >> datosy2[i];                 // desde -40 a 40 us (otra escala)
        	        if ((strstr(ci,"END")!=NULL)) i=N;               // si llego a END ... salgo
			}   
		for (i=0;i<N;i++)                                        // cargo los datos en y, y2
			{x[i]=i; //*0.04-50;                                 // x está en us 
			y1[i]=datosy[i];
			y2[i]=datosy2[i];		
			y3[i]=y1[i]+y2[i];
			}  
		sum11=0;						// comienza XFIR para pulso 1.....................
        	sum21=0;
        	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
        	        {
        	        sum11+=y1[k];
        	        sum21+=y1[L+G+k];
		         }
        	//cout << "sum11: " << sum11 << endl;  
       		//cout << "sum21: " <<sum21 << endl;
		for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
        	        {                                       	// sum2-sum1 me da la energia
        	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
        	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
        	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
        	        //*out << phi1[i] << endl;                		//todo otra vez
        	        }

		Emax1=phi1[0];
		for (k=0;k<(I-F);k++)
             	   if (Emax1<phi1[k]) 
			{
			Emax1=phi1[k];           	 	// calculo el máximo de la energía
			ts1=k;		  	
			}	
		//integ1[j]=Emax1;                       			// los pulsos eran negativos.
		integ1[j]=Emax1;						// termina XFIR PARA PULSO 1 ............................
			
		//integ2[j]=inte;	
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
             	   if (Emax2<phi2[k])
			{ 
			Emax2=phi2[k];           	 	// calculo el máximo de la energía
			ts2=k;	
			}
		//integ2[j]=Emax2;                       			// los pulsos eran negativos.
								// termina XFIR PARA PULSO 2 ............................

		dif=ts2-ts1;					//time stamp 2 - time stamp 1
		//if (dif<0) dif=dif*(-1);			// aplico modulo
		
		if ((dif<3)&&(dif>-3))				// las que la diferencia esté entre -2 y 2 incluidas
			{
			integ2[j]=Emax1+Emax2;			// pongo la suma de las coincidencias		
			cont=cont+1;
			//system("mv %.3d.txt coincidentes",j);			
			}
		else
			integ3[j]=Emax1;			// pongo las de h1 quitandole el compton, es decir coincidencias
	
		Emax1=0;
		Emax2=0;
/*		sum13=0;						// comienza XFIR para pulso 3.....................
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
		//if  (phi2[1275]>0.04)	
		integ3[j]=Emax3;                       			// los pulsos eran negativos.
				
		Emax3=0;						// termina XFIR PARA PULSO 3 ............................
*/
		//integ3[j]=suple;
		delete in;						


if ((j%100)==0) cout << "ficheros: " << j << "/" << nfin << endl;
	}
//signal->Write();
//tree->Fill();
//signal->Reset();
//tree->Write();
}


//fichroot->Close();
//delete fichroot;

for (j=nini;j<(nfin+1);j++)
	{

	H1->Fill((integ1[j])*GAIN);             // lleno el histograma
	H2->Fill((integ2[j])*GAIN);             // lleno el histograma
	H3->Fill((integ3[j])*GAIN);             // lleno el histograma

	}
cout << "contador: " << cont << endl;
  
*out << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        *out << H1->GetBinContent(j) << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
*out << "<<END>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro



*out2 << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        *out2 << H2->GetBinContent(j) << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
*out2 << "<<END>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro

*out3 << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        *out3 << H3->GetBinContent(j) << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
*out3 << "<<END>>" << endl; 


c1->Divide(2,2);

H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle(titulo);   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); H1->Rebin(8); 
c1->cd(1); H1->Draw();

H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle(titulo);   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
c1->cd(3); H2->Draw();

H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle(titulo);   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); H3->Rebin(8); 
c1->cd(2); H3->Draw();

c1->cd(0);



theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

