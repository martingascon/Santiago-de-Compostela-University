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
#include <TH2.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TMath.h>


#define N 2500 					// Número máximo de Datos por Canal
#define I 2000                                  // Número de canales a integrar
#define L 140                                   // Parametro de FIR
#define G 11                                    //parametro de FIR
#define F 2*L+G                                 // Funcion de los dos anteriores

using namespace std;
Double_t Background(Double_t *x, Double_t *par);
Double_t Signal(Double_t *x, Double_t *par);
Double_t fitFunction(Double_t *x, Double_t *par);
 
// linear background function
Double_t Background(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}
// The signal function: a gaussian
Double_t Signal(Double_t *x, Double_t *par)
{  Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}
// Combined background + signal
Double_t fitFunction(Double_t *x, Double_t *par)
{  Double_t tot = Background(x,par) + Signal(x,&par[2]);
   return tot;
}

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char titulo[100]="Titulo del grafico",arch[100],ci[100]="",ar[100]="";
Float_t x[N],datosy[N],datosy2[N],datosy3[N],datosy4[N],suple; 
Float_t y1[N],sum11,sum21,phi1[N],integ1[100000],Emax1,inte; 
Float_t	y2[N],sum12,sum22,phi2[N],integ2[100000],Emax2; 
Float_t y3[N],sum13,sum23,phi3[N],integ3[100000],Emax3; 
Float_t y4[N],sum14,sum24,phi4[N],integ4[100000],Emax4; 

Float_t mean,sigma, dmean,dsigma,deltar,r,dr,factor; 		      
Float_t siga=2,sigb=2;

Int_t i,j,k,m,nini=0, nfin=7999,can,a=6000,b=7200,reb=1,gain=50;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
//TH2F *H2 = new TH2F("H2",arch,32800,0,32799,20,12,15); 
//TH2F *H3 = new TH2F("H3",arch,32800,0,32799,200,12,15); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 
TH1I *H4 = new TH1I("H4",arch,8192,0,8191); 

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
			*in  >> datosy[i] >> datosy2[i] >> datosy3[i] >> datosy4[i];                 // desde -40 a 40 us (otra escala)
        	        if ((strstr(ci,"END")!=NULL)) i=N;               // si llego a END ... salgo
			}   
		for (i=0;i<N;i++)                                        // cargo los datos en y, y2
			{x[i]=i; //*0.04-50;                                 // x está en us 
			y1[i]=datosy[i];
			y2[i]=datosy2[i];		
			y3[i]=datosy3[i];
			y4[i]=datosy4[i];			

			}  
		// comienzan los filtros a los cuatro canales ***************************************************************
		sum11=0;						// comienza XFIR para pulso 1............................
        	sum21=0;						// pongo las sumas del filtro a cero
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
             	   if (Emax1<phi1[k]) 
			{Emax1=phi1[k];           	 		// calculo el máximo de la energía
			can=k;		  	
			}	
		integ1[j]=Emax1;                       			// los pulsos eran negativos.
		Emax1=0;						// termina XFIR PARA PULSO 1 ............................
			
		integ2[j]=inte;	
		sum12=0;						// comienza XFIR para pulso 2.....................
        	sum22=0;						// pongo las sumas del filtro a cero
        	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
        	        {
        	        sum12+=y2[k];					// la primera suma es la que va a restar
        	        sum22+=y2[L+G+k];				// la segunda es la que suma
		         }
		for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
        	        {                                       	// sum2-sum1 me da la energia
        	        phi2[i]=(sum22-sum12);                     	//le sumo un elemento a la derecha
        	        sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
        	        sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar
        	        }
		
		Emax2=phi2[0];
		for (k=0;k<(I-F);k++)
             	   if (Emax2<phi2[k]) Emax2=phi2[k];           	 	// calculo el máximo de la energía
  		integ2[j]=Emax2;                       			// los pulsos eran negativos.
		Emax2=0;						// termina XFIR PARA PULSO 2 ............................

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
		integ3[j]=Emax3;                       			// los pulsos eran negativos.
		Emax3=0;						// termina XFIR PARA PULSO 3 ............................


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
             	   if (Emax4<phi4[k]) Emax4=phi4[k];           	 	// calculo el máximo de la energía
		integ4[j]=Emax4;                       			// los pulsos eran negativos.
		Emax4=0;						// termina XFIR PARA PULSO 4............................


		// terminan los filtros a los cuatro canales ***************************************************************

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
gain=35;

for (j=nini;j<(nfin+1);j++)
	{

	H1->Fill((integ1[j])*gain);             // lleno el histograma h1
	
	

	//if ((integ1[j]+integ2[j]>3.2)&&(integ1[j]<4.1)) 
	//factor=13.33/(3.466e-14*j*j*j-1.665e-9*j*j+1.874e-5*j+13.33);
	//if ((j%100)==0) cout << factor << endl;	
	//H2->Fill(j,(integ1[j]));             // lleno el histograma h2
	//H3->Fill(j,(integ1[j])*factor);             // lleno el histograma h2
	//H4->Fill((integ1[j])*factor*500);             // lleno el histograma h3
	H2->Fill((integ2[j])*gain); 
	H3->Fill((integ3[j])*gain); 

	H4->Fill((integ4[j])*gain);             // lleno el histograma h4
	//if ((integ1[j]>5)&&(integ3[j]>5))               //&&(integ3[j]>2.08)&&(integ4[j]>2.08))
	
//	if ((integ1[j]>12)&&(integ1[j]<14.4))   
//	*out2 <<  j  << "\t" << integ1[j] << endl;
	
	}






/**/
*out1 << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        *out1 << H1->GetBinContent(j) << endl;  // para escribir el histograma 1 en un fichero mca llamado espectro	
*out1 << "<<END>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro

  

*out2 << "<<DATA>>" << endl; 			// para escribir el histograma 2 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 2 en un fichero mca llamado espectro
       // *out2 << (H1->GetBinContent(j))*3.623/(1.86e-14*j*j*j-8.48e-10*j*j+8.92e-6*j+3.623) << endl;  // para escribir el histograma 1 en un fichero mca llamado espectro	
        *out2 << H2->GetBinContent(j) << endl;  
*out2 << "<<END>>" << endl; 			// para escribir el histograma 2 en un fichero mca llamado espectro


*out3 << "<<DATA>>" << endl; 			// para escribir el histograma 3 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 3 en un fichero mca llamado espectro
        *out3 << H3->GetBinContent(j) << endl;  // para escribir el histograma 3 en un fichero mca llamado espectro	
*out3 << "<<END>>" << endl; 			// para escribir el histograma 3 en un fichero mca llamado espectro

*out4 << "<<DATA>>" << endl; 			// para escribir el histograma 4 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 4 en un fichero mca llamado espectro
        *out4 << H4->GetBinContent(j) << endl;  // para escribir el histograma 4 en un fichero mca llamado espectro	
*out4 << "<<END>>" << endl; 			// para escribir el histograma 4 en un fichero mca llamado espectro

c1->Divide(2,2);

H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle(titulo);   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); H1->Rebin(8); 
c1->cd(1); H1->Draw();

TF1 *fitFcn = new TF1("fitFcn",fitFunction,a,b,5);
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);
fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);		// par4 = width, par5 = peak
H1->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
a=Int_t(mean-siga*sigma);                            	// siga y sigb contiene el valor de sigmas por 
b=Int_t(mean+sigb*sigma);
fitFcn->SetRange(a,b);					
H1->Fit(fitFcn,"R+");					// second try: set start values for some parameters
H1->Fit(fitFcn,"R+");	
H1->Fit(fitFcn,"R+");	

H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle(titulo);   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
c1->cd(3); H2->Draw();

H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle(titulo);   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); H3->Rebin(8); 
c1->cd(2); H3->Draw();

H4->SetMarkerColor(7);  H4->SetFillColor(0);  H4->SetLineColor(2);  H4->SetLineWidth(1);  H4->SetMarkerStyle(8); H4->SetMarkerSize(1);  H4->SetTitle(titulo);   
H4->GetXaxis()->SetTitle("Channel");         H4->GetYaxis()->SetTitle(" Counts "); H4->GetXaxis()->CenterTitle(); H4->GetYaxis()->CenterTitle(); H4->Rebin(8); 
c1->cd(4); H4->Draw();



c1->cd(0);



theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

