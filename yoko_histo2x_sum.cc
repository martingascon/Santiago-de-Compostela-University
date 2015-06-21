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
#include <TFile.h>
#include <TTree.h>
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
#define L 50
#define G 50                  	  	    	 //parametro de FIR
#define F 2*L+G                                  // Funcion de los dos anteriores
#define Gain 30500/(2*L)	                 // Parametro de FIR

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t k5=0,k6=0,k7=0;
char titulo[100]="Titulo del grafico",arch[100],ci[100]="";
Float_t x[N],datosy[N],datosy2[N],suple,Emin1=0,Ezer1,Emin2=0,Ezer2,Amin1; 
Float_t y1[N],sum11,sum21,phi1[N],integ1[100000],Emax1,inte; 
Float_t	y2[N],sum12,sum22,phi2[N],integ2[100000],Emax2; 
Float_t y3[N],sum13,sum23,phi3[N],phi4[N],integ3[100000],Emax3;
Int_t Tmin1,Tzer1,Tmin2,Tzer2;
Int_t i,j,k,k1=0,k2=0,k3=0,k4=0,m,nini=0, nfin=7999;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 
TH1I *H4 = new TH1I("H4",arch,8192,0,8191); 

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
//c1->Divide(3,1);
     
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


ofstream *out4 = new ofstream("datos.txt");                   	//genero el fich del espect para guardar datos
ofstream *out = new ofstream("espectro.mca");                 	//genero el fich del espect para guardar datos
ofstream *out2 = new ofstream("espectro2.mca");               	//genero el fich del espect para guardar datos
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
			{x[i]=i;					 //*0.04-50;      // x está en us 
			y1[i]=datosy[i];
			y2[i]=datosy2[i];		
			//y3[i]=y1[i]*1.122+y2[i];
			}  
		sum11=0;						//comienza XFIR para pulso 1.....................
        	sum21=0;
		sum12=0;						//comienza XFIR para pulso 2.....................
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
       	        	phi2[i]=(sum22-sum12);                     	//le sumo un elemento a la derecha
       	        	sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
       	        	sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar
			}
		Emax1=phi1[0];
 		Emax2=phi2[0];
		
		
		//Emin1=0;	Emin2=0;	Ezer1=0;	Ezer2=0;
		for (k=0;k<(I-F);k++)
			{
             	  	if (Emax1<phi1[k]) 	 {Emax1=phi1[k];k1=k;}          // calculo el máximo de la energía
	             	if (Emax2<phi2[k])  	 {Emax2=phi2[k];k2=k;}         
			}

		//cout << Emax1 << " " << Emax2 << endl;
		/*for (k=k1-30;k<k1+30;k++)
				{	
				k3=k;				
				Ezer1=phi1[k];
  				Tzer1=k3;
				k=800;
				}
		for (k=k2;k<800;k++)
			if (phi2[k]<0)            			// calculo el cero 
				{
				k4=k;		   
				Ezer2=phi2[k]; 	
				Tzer2=k4;
				k=800; 
				}
		
		for (k=k3;k<1000;k++)
             		if (Emin1>phi1[k])
				{
				k5=k;
				Emin1=phi1[k];        	 	// calculo el máximo para 1	
				Tmin1=k5;        	 	// calculo el máximo para 1
				}
		for (k=k4;k<1000;k++)
			if (Emin2>phi2[k])
				{
				k6=k;		
				Emin2=phi2[k];			// calculo el máximo para 2
				Tmin2=k6;			// calculo el máximo para 2
				}
		*/
		integ1[j]=Emax1;                       			// los pulsos eran negativos.
  		integ2[j]=Emax2;       		
		//if ((Emax1>1.99) && (Emax1<2.02)) cout << j  << endl;
	       	//*out <<  << " " << Tzer2 << " " << Tmin2 << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
		
 		//*out4 << k3 << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	

		Emax1=0;						// termina XFIR PARA PULSO 1 ............................
		Emax2=0;						// termina XFIR PARA PULSO 2 ............................
		
		/*
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
		//if  (phi2[1275]>0.04)	
		//integ3[j]=(integ1[j]+integ2[j])/2;                       			// los pulsos eran negativos.
		integ3[j]=Emax3;		
		Emax3=0;*/						// termina XFIR PARA PULSO 3 ............................
		//integ3[j]=suple;
		delete in;						
		//*out4 << integ3[j] << endl; 		
		if ((j%100)==0) cout << "ficheros: " << j << "/" << nfin << endl;


	}




}



for (j=nini;j<(nfin+1);j++)
	{
	H1->Fill((integ1[j])*Gain);           // lleno el histograma
	H2->Fill((integ2[j])*Gain);           // lleno el histograma
	H3->Fill(integ3[j]*Gain/2);           // lleno el histograma
	}

 
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

H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle("H1");   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); H1->Rebin(8); 
c1->cd(1); H1->Draw();

H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle("H2");   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
c1->cd(2); H2->Draw();

H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle("H1+H2");   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); H3->Rebin(8); 
c1->cd(3); H3->Draw();

c1->cd(0);




theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

