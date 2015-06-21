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
#include <TFile.h>
#include <TSpectrum.h>
#include <strings.h>
#include <TMath.h>
#include <TTree.h>

#define N 2500 					 // Número máximo de Datos por Canal
#define I 2200                                   // Número de canales a integrar
//#define L 33
//#define G 15                   	      	 //parametro de FIR
//#define F 2*L+G                                  // Funcion de los dos anteriores
#define Gain 159				//10500/(2*L) 		                 // Parametro de FIR

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
Float_t y5[N],sum15,sum25,phi5[N],integ5[100000],Emax5;
Float_t Emin1,Ezer1,Emin2,Ezer2,Emin3,Ezer3,Emin4,Ezer4,Amp4; 
Float_t mean,sigma, dmean,dsigma,deltar,r,dr,factor; 		      
Float_t siga=2,sigb=2;
Int_t Tmin1,Tzer1,Tmin2,Tzer2,Tmin3,Tzer3,Tmin4,Tzer4,pulsos=0;

Int_t i,j,k,k1=0,k2=0,k3=0,k4=0,k5=0,k6=0,k7=0,k8=0,m,nini=0, nfin=7999,can,a=6000,b=7200,reb=8;;           //ficheros inicial y finalTH1I *H1 = new TH1I("H1",arch,8192,0,8191); 
TH1I *H2 = new TH1I("H2",arch,8192,0,8191); 
//TH2F *H2 = new TH2F("H2",arch,32800,0,32799,20,12,15); 
//TH2F *H3 = new TH2F("H3",arch,32800,0,32799,200,12,15); 
TH1I *H3 = new TH1I("H3",arch,8192,0,8191); 
TH1I *H4 = new TH1I("H4",arch,8192,0,8191); 
TH1I *H5 = new TH1I("H5",arch,8192,0,8191); 

/*
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1400,800);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
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
ofstream *out1 = new ofstream("espectro1.mca");                   //genero el fich del espect para guardar datos
ofstream *out2 = new ofstream("espectro2.mca");                 //genero el fich del espect para guardar datos
ofstream *out3 = new ofstream("espectro3.mca");  
ofstream *out4 = new ofstream("espectro4.mca");  
ofstream *out5 = new ofstream("espectro5.mca");  
ofstream *out6 = new ofstream("extras.txt");  
ofstream *out = new ofstream("datos.txt");    			// archivo para sacar datos


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
			for (i=0;i<N;i++)                                               // cargo los datos en datosy, y2
			{
			*in  >> datosy4[i] >> datosy2[i] >> datosy3[i] >> datosy[i];    // desde -40 a 40 us (otra escala)
        	        if ((strstr(ci,"END")!=NULL)) i=N;               		// si llego a END ... salgo
			}   
		for (i=0;i<N;i++)                                        		// cargo los datos en y, y2
			{x[i]=i; //*0.04-50;                                 		// x está en us cuando hago *0.04-50; 
		//	y1[i]=datosy[i];
		//	y2[i]=datosy2[i];		
		//	y3[i]=datosy3[i];
			y4[i]=datosy4[i];//-datosy4[0];			
			//y5[i]=datosy[i]+datosy2[i]*1.397+datosy3[i]*1.3333+datosy4[i]*1.55468;
			}  

		// comienzan los filtros a los cuatro canales ***************************************************************
		Int_t L=10;
		Int_t G=30;                   	      	 //parametro de FIR
		Int_t F=2*L+G;
		sum11=0;sum12=0;sum21=0;sum22=0;sum13=0;		// pongo las sumas del filtro a cero
		sum23=0;sum14=0;sum24=0;sum15=0;sum25=0;	
   		for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
        	        {
     /*   	        sum11+=y1[k];
        	        sum21+=y1[L+G+k];
        	        sum12+=y2[k];					// la primera suma es la que va a restar
        	        sum22+=y2[L+G+k];				// la segunda es la que suma		         
        	        sum13+=y3[k];
        	        sum23+=y3[L+G+k];	*/		
        	        sum14+=y4[k];
        	        sum24+=y4[L+G+k];
        	 //       sum15+=y5[k];
        	 //       sum25+=y5[L+G+k];

			}
		for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
        	        {                                       	// sum2-sum1 me da la energia
    /*    	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
        	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
        	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
    	  	        phi2[i]=(sum22-sum12);                     	//le sumo un elemento a la derecha
        	        sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
        	        sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar
        	        phi3[i]=(sum23-sum13);                     	//le sumo un elemento a la derecha
        	        sum13=sum13+y3[i+L+1]-y3[i];        		//le resto un elemento a la izquierda
        	        sum23=sum23+y3[F+1+i]-y3[L+G+i];    		//a sum1 y suma dos, antes que sumar*/
        	        phi4[i]=(sum24-sum14);                     	//le sumo un elemento a la derecha
        	        sum14=sum14+y4[i+L+1]-y4[i];        		//le resto un elemento a la izquierda
        	        sum24=sum24+y4[F+1+i]-y4[L+G+i];    		//a sum1 y suma dos, antes que sumar
         	        //phi5[i]=(sum25-sum15);                     	//le sumo un elemento a la derecha
        	      //  sum15=sum15+y5[i+L+1]-y5[i];        		//le resto un elemento a la izquierda
        	       // sum25=sum25+y5[F+1+i]-y5[L+G+i];    		//a sum1 y suma dos, antes que sumar
	       	        } 
		Emax1=phi1[0];Emax2=phi2[0];Emax3=phi3[0];Emax4=phi4[0];
		Float_t Div=0,Fa=0,Sl=0,lb=0;
		Int_t pul=0,cond=0,cond2=0,t;
		for (k=0;k<(I-F);k++)
			{
             	  	//if (Emax1<phi1[k]) 	 {Emax1=phi1[k];k1=k;}          // calculo el máximo de la energía
	             	//if (Emax2<phi2[k])  	 {Emax2=phi2[k];k2=k;}          				  	
             	   	//if (Emax3<phi3[k])	 {Emax3=phi3[k];k3=k;}           	 		
			if (Emax4<phi4[k]) 	 {Emax4=phi4[k];k4=k;}  			
			//if (Emax5<phi5[k]) 	 Emax5=phi5[k]; 			
						
			Int_t lim=k4-120;
			lb=0;
			if (lim>0)			
				{
				for (t=lim;t<lim+20;t++) 		// calculo la linea base
					lb = lb+y4[t];		// sumo sobre 50 canales
				}
			else 
				lb=0;
			lb = lb/140.0;
			if (phi4[k]>1)                     /// PARA CONTAR PULSOS FIR >1
				{
				if (cond==0) 
					{pul++;cond=1;}
				}	
			else	
			  	cond=0;                    //// para contar pulsos fir
			

			
			
			if ((k<200)&&(y4[k]>0.1)) {cond2++;} // para eliminar los que vengan >0.1
			



			}
		k4=k4+75;	
		if ((pul>1)||(cond2>1))  {Emax4=0;} 	// 	 {Emax4=0;} 
		else
		
		////////////////////////////////////////////// FILTRO NACHO START	
  		{
		pulsos++;
		
		for (i=0;i<N;i++)                   // resto la linea base
			y4[i]=y4[i]-lb;	


		for (k=k4-30;k<k4+100;k++)  // calculo el de la derecha
        	 	{	
			Fa=Fa+y4[k];		//-Emax4*0.0175;; 	 
			}
		
		//cout << Fa << endl;
		for (k=k4+150;k<k4+720;k++)  // calculo el de la derecha
        	 	{	
			Sl=Sl+y4[k];//-Emax4*0.0175; 	 
			}

		Div=Fa/Sl;
					///////////////////////// Filtro Nacho End
		
		}

		///////////////////////////////////////////   DOBLE FIR START
/*		L=400;
		G=50;
		F=2*L+G;                   	      	 //parametro de FIR
		Float_t phi4b[N],Emax4b;

		sum14=0;sum24=0;	
   		for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
        	        {
               	        sum14+=y4[k];
        	        sum24+=y4[L+G+k];

			}
		for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
        	        {                                       	// sum2-sum1 me da la energia

        	        phi4b[i]=(sum24-sum14);                     	//le sumo un elemento a la derecha
        	        sum14=sum14+y4[i+L+1]-y4[i];        		//le resto un elemento a la izquierda
        	        sum24=sum24+y4[F+1+i]-y4[L+G+i];    		//a sum1 y suma dos, antes que sumar
   
	       	        } 
		Emax4b=phi4b[0];
		for (k=0;k<(I-F);k++)
			{
      	 		
 			if (Emax4b<phi4b[k]) 	 {Emax4b=phi4b[k];k4=k;}  

			}*/
	///////////////////////////////////////////   doble FIR end

/*		/////////////////////////////////////////////////  TIME FWIDTH START
		Float_t Amax4=0;
		for (k=0;k<1500;k++)  // calculo el maximo del pulso preamp
				{	
				if (Amax4<(y4[k]-y4[0])) 	 {Amax4=(y4[k]-y4[0]);k4=k;}
				}
		
		Float_t A34=Amax4/4.0*3;
		Float_t A12=Amax4/2;
		Int_t l1=0,r1=0,l2=0,r2=0,t34=0,t12=0;		
		for (k=k4;k<1500;k++)  				// calculo el de la derecha para t34
				if ((y4[k]-y4[0])<A34) 	 {r1=k;k=1500;}
		for (k=k4;k>0;k--)  				// calculo el de la izquierda para t34
				if ((y4[k]-y4[0])<A34) 	 {l1=k;k=0;}
			
		for (k=k4;k<1500;k++)  				// calculo el de la derecha para t12
				if ((y4[k]-y4[0])<A12) 	 {r2=k;k=1500;}
		for (k=k4;k>0;k--)  				// calculo el de la izquierda para t12
				if ((y4[k]-y4[0])<A12) 	 {l2=k;k=0;}

		t34=r1-l1;
		t12=r2-l2;*/		
		


		////////////////////////////////////////////////  time width start
/*		////////////////////////////////////////////// CALCULO MAXIMO DEL PULSO
		
		Float_t Amax4=0;
		for (k=0;k<(I-F);k++)
				{	
				if (Amax4<y4[k]) 	 {Amax4=y4[k];}  

				}
		*/
	
	
  				
/*	 ////////////////////////////////////////////////////// maximo del pulso.	
	
/*		////////////////////////////////////////////// CALCULO INTEGRAL START

		Ezer4=0;
		for (k=k4+81;k<k4+681;k++)  // integral
	        	 	
				{	
				Ezer4+=y4[k];
  				}
		
		Ezer4=Ezer4-y4[k4+681]*600;*/
	
  				
/*	 ////////////////////////////////////////////////////// CALCULO ZERO START			
		for (k=k3;k<1500;k++)
			if (phi3[k]<0)          	 	// calculo el cero 
				{	
				k7=k;				
				Ezer1=phi1[k];
  				Tzer1=k7;
				k=1500;
				}*/
	/*	Ezer4=0;
		for (k=k4;k<1500;k++)
			if (phi4[k]<0)            	// calculo el cero 
				{
				k8=k;		   
				Ezer4=phi4[k]; 	
				//Tzer4=k8;
				k=1500; 
				}

		Amp4=0;
		for (k=0;k<k8;k++) 
			{Amp4+=phi4[k];}*/


	////////////////////////////////////////////////////////////// SALIDAS POR ARCHIVO
		
		
		// out  << la x  << espacio   << la y 
		//*out << t34 << " " << Emax4 << endl;
		if (Emax4==0)	Emax4=1000000000000;	
		*out << Fa/Emax4 << " " << Sl/Emax4 << endl;
		//*out << Amp4 << " " << Emax4 << endl;
		//*out << Emax1 << " " << Tzer1 << " " << Emax2 << " " << Tzer2 << " " << Emax3 << " " << Tzer3 << " " << Emax4 << " " << Tzer4 << endl;

	////////////////////////////////////////////////////////////// salidas por archivo

		
		integ1[j]=Emax1;integ2[j]=Emax2;integ3[j]=Emax3;
		integ4[j]=Emax4;integ5[j]=Emax5;    				// meto las las amplitudes en la integral.	
		Emax1=0; Emax2=0;Emax3=0;Emax4=0;Emax5=0;			// pongo las sumas del filtro a cero


  // terminan los filtros a los cuatro canales ***************************************************************
		delete in;						
		if ((j%100)==0) cout << "ficheros: " << j << "/" << nfin << endl; // contador de archivos
	}
}

cout << pulsos << endl;
/*
for (j=nini;j<(nfin+1);j++)
	{
	//H1->Fill((integ1[j])*Gain);             // lleno el histograma h1
	//H2->Fill((integ2[j])*Gain); 
	//H3->Fill((integ3[j])*Gain); 
	H4->Fill((integ4[j])*Gain);		// lleno el histograma h4
	//H5->Fill(((integ1[j])*0.09542-2.169)+((integ2[j])*0.07684-1.064)+((integ4[j])*0.08415-5.782)+((integ4[j])*0.08415-5.782));     

	//if ((integ1[j]>3.3)&&(integ1[j]<3.4)) 
	//if ((integ1[j]<40)&&(integ1[j]>10)&&(integ4[j]>10)&&(integ4[j]<40)) 
	//*out5 <<  j  << "\t" << integ1[j] << " " << integ2[j] << " " << integ3[j] << " " << integ4[j] << endl;		
	//factor=13.33/(3.466e-14*j*j*j-1.665e-9*j*j+1.874e-5*j+13.33);
	//if ((j%100)==0) cout << factor << endl;	
	//H2->Fill(j,(integ1[j]));             // lleno el histograma h2
	//H3->Fill(j,(integ1[j])*factor);           	  // lleno el histograma h2
	//H4->Fill((integ1[j])*factor*500);             // lleno el histograma h3

	//if ((integ1[j]>5)&&(integ3[j]>5))               //&&(integ3[j]>2.08)&&(integ4[j]>2.08))
	
//	if ((integ1[j]>12)&&(integ1[j]<14.4))   
//	*out2 <<  j  << "\t" << integ1[j] << endl;
	
	}






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

*out5 << "<<DATA>>" << endl; 			// para escribir el histograma 4 en un fichero mca llamado espectro
for (j=0;j<8192;j++)				// para escribir el histograma 4 en un fichero mca llamado espectro
        *out5 << H5->GetBinContent(j) << endl;  // para escribir el histograma 4 en un fichero mca llamado espectro	
*out5 << "<<END>>" << endl; 	

c1->Divide(2,3);

H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle(titulo);   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle();// H1->Rebin(8); 
c1->cd(1); H1->Draw();
/*
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

mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;
TLegend *legend=new TLegend(0.37,0.92,0.70,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar); 
legend->AddEntry(ar,ar,"p");
legend->Draw();


H2->SetMarkerColor(7);  H2->SetFillColor(0);  H2->SetLineColor(2);  H2->SetLineWidth(1);  H2->SetMarkerStyle(8); H2->SetMarkerSize(1);  H2->SetTitle(titulo);   
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); //H2->Rebin(8); 
c1->cd(3); H2->Draw();

H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle(titulo);   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); //H3->Rebin(8); 
c1->cd(2); H3->Draw();

H4->SetMarkerColor(7);  H4->SetFillColor(0);  H4->SetLineColor(2);  H4->SetLineWidth(1);  H4->SetMarkerStyle(8); H4->SetMarkerSize(1);  H4->SetTitle(titulo);   
H4->GetXaxis()->SetTitle("Channel");         H4->GetYaxis()->SetTitle(" Counts "); H4->GetXaxis()->CenterTitle(); H4->GetYaxis()->CenterTitle();// H4->Rebin(8); 
c1->cd(4); H4->Draw();

H5->SetMarkerColor(7);  H5->SetFillColor(0);  H5->SetLineColor(2);  H5->SetLineWidth(1);  H5->SetMarkerStyle(8); H5->SetMarkerSize(1);  H5->SetTitle(titulo);   
H5->GetXaxis()->SetTitle("Channel");         H5->GetYaxis()->SetTitle(" Counts "); H5->GetXaxis()->CenterTitle(); H5->GetYaxis()->CenterTitle();// H5->Rebin(8); 
c1->cd(5); H5->Draw();

c1->cd(0);

*/

theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

