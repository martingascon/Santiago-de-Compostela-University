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
#include <TPad.h>
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
#include <TSystem.h>

#define N 2500 					// Número máximo de Datos por Canal
#define L 90					// parámetro del FIR
#define G 24                            	// parametro de FIR
#define F 2*L+G                                 // Funcion de los dos anteriores
#define I N-F-10                                // Número de canales a integrar
#define Gain 30500/(2*L)	                // Ganancia

using namespace std;

int main(int argc, char **argv)
{

//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char ch, titulo[100]="Spectrum",arch[100],ci[100]="",ejex[100]="time (channels)",ejey[100]="voltage (V)",tituloc[100]="FIR Algorithm (ch1)",titulod[100]="FIR Algorithm (ch2)";
Float_t x[N],datosy[N],datosy2[N],suple; 
Float_t y1[N],sum11,sum21,phi1[N],integ1[100000],Emax1,inte; 
Float_t	y2[N],sum12,sum22,phi2[N],integ2[100000],Emax2; 
Float_t y3[N],sum13,sum23,phi3[N],integ3[100000],Emax3; 

Int_t i,j,k,m=0,nini=0, nfin=7999,can;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

c1->Divide(2,3);



for (i=0;i<N;i++)    {phi1[i]=0,phi2[i]=0,y1[i]=0,y2[i]=0;}       

TGraph *gr1 = new TGraph(N,x,y1);			// Declaración del gráfico.
gr1->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr1->SetLineWidth(1);					// Ancho de la linea
gr1->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr1->SetTitle("Preamplifier pulse (ch1)");					// Escribe como título del grafico lo que hay en titulo
gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
c1->cd(1);

TGraph *gr2 = new TGraph(N,x,y2);			// Declaración del gráfico.
gr2->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr2->SetLineWidth(1);					// Ancho de la linea
gr2->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr2->SetTitle("Preamplifier pulse (ch2)");					// Escribe como título del grafico lo que hay en titulo
gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
c1->cd(2);


TGraph *gr3 = new TGraph(I-F,x,phi1);			// Declaración del gráfico.
gr3->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr3->SetLineWidth(1);					// Ancho de la linea
gr3->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr3->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr3->SetTitle(tituloc);					// Escribe como título del grafico lo que hay en titulo
gr3->GetXaxis()->SetTitle(ejex);	// Escribe como titulo del eje x lo que hay en ejex
gr3->GetYaxis()->SetTitle("FIR Amplitude (a.u.)");			// Escribe como titulo del eje y lo que hay en ejey
gr3->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr3->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
c1->cd(3);



TGraph *gr4 = new TGraph(I-F,x,phi2);			// Declaración del gráfico.
gr4->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
gr4->SetLineWidth(1);					// Ancho de la linea
gr4->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
gr4->SetTitle(titulod);					// Escribe como título del grafico lo que hay en titulo
gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
gr4->GetYaxis()->SetTitle("FIR Amplitude (a.u.)");	// Escribe como titulo del eje y lo que hay en ejey
gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
gr4->GetYaxis()->CenterTitle();	
c1->cd(4);



c1->cd(5);
H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle(titulo);   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); H1->Rebin(8); 
H1->Draw();

c1->cd(6);
H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle(titulo);   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
H2->Draw();

c1->cd(0);


/*



H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle(titulo);   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
c1->cd(3); H2->Draw();
H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle(titulo);   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); H3->Rebin(8); 
c1->cd(2); H3->Draw();
*/





     
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
//ofstream *out3 = new ofstream("espectro3.mca");  

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
			{x[i]=i; //*0.04-50;;                                 // x está en us 
			y1[i]=datosy[i];
			y2[i]=datosy2[i];		
			//y3[i]=y1[i]*1.0323+y2[i];
			}  
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
        	        phi2[i]=(sum22-sum12);                     	//le sumo un elemento a la derecha
        	        sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
        	        sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar
         	        }

		c1->cd(1);
		TGraph *gr1 = new TGraph(N,x,y1);
		gr1->SetLineColor(1);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr1->SetLineWidth(1);					// Ancho de la linea
		gr1->SetMarkerColor(1);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr1->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr1->SetTitle("Preamplifier pulse");			// Escribe como título del grafico lo que hay en titulo
		gr1->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr1->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
		gr1->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr1->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr1->Draw("AL");	
		c1->cd(2);
		TGraph *gr2 = new TGraph(N,x,y2);
		gr2->SetLineColor(1);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr2->SetLineWidth(1);					// Ancho de la linea
		gr2->SetMarkerColor(1);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr2->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr2->SetTitle("Preamplifier pulse");			// Escribe como título del grafico lo que hay en titulo
		gr2->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr2->GetYaxis()->SetTitle(ejey);			// Escribe como titulo del eje y lo que hay en ejey
		gr2->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr2->GetYaxis()->SetTitleOffset(1.1);			// Para separar el título
		gr2->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr2->Draw("AL");

		c1->cd(3);
		TGraph *gr3 = new TGraph(I-F,x,phi1); 
		gr3->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr3->SetLineWidth(1);					// Ancho de la linea
		gr3->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr3->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr3->SetTitle(tituloc);					// Escribe como título del grafico lo que hay en titulo
		gr3->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr3->GetYaxis()->SetTitle("FIR Amplitude (a.u.)");	// Escribe como titulo del eje y lo que hay en ejey
		gr3->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr3->GetYaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr3->Draw("AL");
		//c1->Update();

		c1->cd(4);
		TGraph *gr4 = new TGraph(I-F,x,phi2); 
		gr4->SetLineColor(4);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr4->SetLineWidth(1);					// Ancho de la linea
		gr4->SetMarkerColor(4);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr4->SetTitle(titulod);					// Escribe como título del grafico lo que hay en titulo
		gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr4->GetYaxis()->SetTitle("FIR Amplitude (a.u.)");	// Escribe como titulo del eje y lo que hay en ejey
		gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr4->GetYaxis()->CenterTitle();	
		gr4->Draw("AL");
		c1->Update();

	
		
		Emax1=phi1[0];
		for (k=0;k<(I-F);k++)
             	   if (Emax1<phi1[k]) 
			{Emax1=phi1[k];           		 	// calculo el máximo de la energía
			can=k;		  	
			}


	
		integ1[j]=Emax1;                       			// los pulsos eran negativos.
		Emax1=0;	
			   						// termina XFIR PARA PULSO 1 ............................
		Emax2=phi2[0];
		for (k=0;k<(I-F);k++)
             	   if (Emax2<phi2[k]) Emax2=phi2[k];           	 	// calculo el máximo de la energía
  		integ2[j]=Emax2;                       			// los pulsos eran negativos.
		Emax2=0;	


		c1->cd(5);		
		H1->Fill((integ1[j])*Gain);            		 // lleno el histograma
		H1->Draw();
		//c1->Update();

		c1->cd(6);		
		H2->Fill((integ2[j])*Gain);            		 // lleno el histograma
		H2->Draw();
		c1->Update();

      		//if ((integ1[j]*Gain) > 1650) gROOT->ProcessLine(".!sleep 2");		

		if (j%20==0)
			{Char_t ch[100];
			m=sprintf(ch,"fig_%04d.png",j);
			c1->Print(ch);
			}			
 									// termina XFIR PARA PULSO 2 ............................

		
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
		//if  (phi2[1275]>0.04)	*/
		//integ3[j]=integ1[j]+integ2[j];                       			// los pulsos eran negativos.
				
		//Emax3=0;						// termina XFIR PARA PULSO 3 ............................

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
/*
for (j=nini;j<(nfin+1);j++)
	{

	H1->Fill((integ1[j])*Gain);             // lleno el histograma
	H2->Fill((integ2[j])*Gain);             // lleno el histograma
	H3->Fill(integ3[j]*Gain/2);             // lleno el histograma

	}
*/
  /*
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

**/






theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

