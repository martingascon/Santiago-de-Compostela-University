//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Program to analyze x pulses comming from the YOKOGAWA DL9140 Osciloscope  

//*************************************  included libraries  **************************************
#include <cstdio>                               
#include <cstdlib>				
#include <fstream>
#include <iostream>
#include <Riostream.h>
#include <strings.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TFrame.h>
#include <TGraph.h>
#include <TH1.h>
#include <TH1I.h>
#include <TH2.h>
#include <TH2F.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TObject.h>
#include <TRint.h>
#include <TROOT.h>
#include <TSpectrum.h> 
#include <TStyle.h>
#include <TTree.h>

#define N 2500 					// maximum number of data per channel
#define FN 100000				// maximum number of files
#define I 2000                                  // numbers of channels to integrate
#define L 140                                   // xfir Parameter 1 
#define G 11                                    // xfir Parameter 2 
#define F 2*L+G                                 // function of the fir parameters

using namespace std;

int main(int argc, char **argv)
{//**********************************  variables declarations ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char title[100]="Graph Title",arch[100],ci[100]="",ar[100]="";
Int_t i,j,k,m,nini=0, nfin=7999,can;		//ficheros inicial y final
Float_t sum11,sum21,phi1[N],Emax1,inte; 
Float_t	sum12,sum22,phi2[N],Emax2; 
Float_t sum13,sum23,phi3[N],Emax3; 
Float_t sum14,sum24,phi4[N],Emax4; 
Int_t nlines = 0;


struct event_t {
	Float_t y1[N],y2[N],y3[N],y4[N];	// pulses
	Float_t z1[N],z2[N],z3[N],z4[N];	// filters
	Float_t integral;			// integral	
	Float_t ts;				// time stamp	
	Int_t mult;				// multiplicity
};

event_t event;

    
//*********************************** program body  *************************************
switch (argc)
{
case 3: nini=atoi(argv[1]);  nfin=atoi(argv[2]); break;
};


TFile *f = new TFile("events.root","RECREATE");
TTree *tree = new TTree("tree","signals");
tree->Branch("pulse",&event.y1,"y1[N]/F",&event.y2,"y2[N]/F",event.y3,"y3[N]/F",event.y4,"y4[N]/F");
tree->Branch("filter",&event.z1,"y1[N]/F",&event.z2,"y2[N]/F",event.z3,"y3[N]/F",event.z4,"y4[N]/F");
tree->Branch("integral",&event.integral,"integral/F");
tree->Branch("timestamp",&event.ts,"integral/F");
tree->Branch("mult",&event.mult,"mult/F");

TH2F *signal1 = new TH2F("signal1","signal1",2500,0,2500,1000,-0.2,0.2);
signal1->SetMarkerColor(kBlue);
signal1->SetLineColor(kBlue);
signal1->SetTitle("channel 1");
signal1->GetXaxis()->SetTitle("Channel");
signal1->GetYaxis()->SetTitle("Voltage (V) ");
signal1->GetXaxis()->CenterTitle();
TH2F *signal2 = new TH2F("signal2","signal2",2500,0,2500,1000,-0.2,0.2);
signal2->SetMarkerColor(kBlue);
signal2->SetLineColor(kBlue);
signal2->SetTitle("channel 2");
signal2->GetXaxis()->SetTitle("Channel");
signal2->GetYaxis()->SetTitle("Voltage (V) ");
signal2->GetXaxis()->CenterTitle();
TH2F *signal3 = new TH2F("signal3","signal3",2500,0,2500,1000,-0.2,0.2);
signal3->SetMarkerColor(kBlue);
signal3->SetLineColor(kBlue);
signal3->SetTitle("channel 3");
signal3->GetXaxis()->SetTitle("Channel");
signal3->GetYaxis()->SetTitle("Voltage (V) ");
signal3->GetXaxis()->CenterTitle();
TH2F *signal4 = new TH2F("signal4","signal4",2500,0,2500,1000,-0.2,0.2);
signal4->SetMarkerColor(kBlue);
signal4->SetLineColor(kBlue);
signal4->SetTitle("channel 4");
signal4->GetXaxis()->SetTitle("Channel");
signal4->GetYaxis()->SetTitle("Voltage (V) ");
signal4->GetXaxis()->CenterTitle();



for (j=nini;j<(nfin+1);j++) 					// Processing of the files
{	m=sprintf(arch,"%d.txt",j);  				// arch: Filename to open
	ifstream *in = new ifstream(arch);			// in: file asigned pointer
	if(!*in) 						// if "file"=0 (is not open)
	{	cout << " ERROR OPENING FILE " <<  arch << endl;// error msg
		return 1;					// 1 => error
	}
	else    						// if "file"=1 (is open)
	{
	        i=1;
	        do	
		{	*in >> ci;
			if ((strstr(ci,"START")!=NULL))	i=0;
		}
		while (i!=0);	
			for (i=0;i<N;i++)                            
			{
			*in >> y1[i] >> y2[i] >> y3[i] >> y4[i];            
        	        if ((strstr(ci,"END")!=NULL)) i=N;              
			//signal1->Fill(i,y1);signal2->Fill(i,y2);signal3->Fill(i,y3);signal4->Fill(i,y4);
      			tree->Fill();
			//ntuple->Fill(y1,y2,y3,y4);
      			nlines++;
			} 
		//printf(" found %d points\n",nlines);
	}
   	delete in;
	tree->Print();   	
	f->Write();
	//signal1->Reset();signal2->Reset();signal3->Reset();signal4->Reset();
	if ((j%50)==0) cout << "file: " << j << "/" << nfin << endl;
}


/*

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
		cout << integ1[j] << endl;		
		integ1[j]=Emax1;                       			// los pulsos eran negativos.
		tree->Fill();		
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
*/
//tree->Write("tree");
//fichroot->Close();//
//delete fichroot;
//}



/*
for (j=nini;j<(nfin+1);j++)
	{
	H1->Fill((integ1[j])*500);             // lleno el histograma h1
	//if ((integ1[j]>3.3)&&(integ1[j]<3.4)) 
	//if ((integ1[j]<40)&&(integ1[j]>10)&&(integ4[j]>10)&&(integ4[j]<40)) 
	//*out5 <<  j  << "\t" << integ1[j] << " " << integ2[j] << " " << integ3[j] << " " << integ4[j] << endl;		
	//factor=13.33/(3.466e-14*j*j*j-1.665e-9*j*j+1.874e-5*j+13.33);
	//if ((j%100)==0) cout << factor << endl;	
	//H2->Fill(j,(integ1[j]));             // lleno el histograma h2
	//H3->Fill(j,(integ1[j])*factor);             // lleno el histograma h2
	//H4->Fill((integ1[j])*factor*500);             // lleno el histograma h3
	H2->Fill((integ2[j])*500); 
	H3->Fill((integ3[j])*500); 
	H4->Fill((integ4[j])*500);             // lleno el histograma h4
	//if ((integ1[j]>5)&&(integ3[j]>5))               //&&(integ3[j]>2.08)&&(integ4[j]>2.08))
	
//	if ((integ1[j]>12)&&(integ1[j]<14.4))   
//	*out2 <<  j  << "\t" << integ1[j] << endl;
	
	}





/*
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
/*
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
H2->GetXaxis()->SetTitle("Channel");         H2->GetYaxis()->SetTitle(" Counts "); H2->GetXaxis()->CenterTitle(); H2->GetYaxis()->CenterTitle(); H2->Rebin(8); 
c1->cd(3); H2->Draw();

H3->SetMarkerColor(7);  H3->SetFillColor(0);  H3->SetLineColor(2);  H3->SetLineWidth(1);  H3->SetMarkerStyle(8); H3->SetMarkerSize(1);  H3->SetTitle(titulo);   
H3->GetXaxis()->SetTitle("Channel");         H3->GetYaxis()->SetTitle(" Counts "); H3->GetXaxis()->CenterTitle(); H3->GetYaxis()->CenterTitle(); H3->Rebin(8); 
c1->cd(2); H3->Draw();

H4->SetMarkerColor(7);  H4->SetFillColor(0);  H4->SetLineColor(2);  H4->SetLineWidth(1);  H4->SetMarkerStyle(8); H4->SetMarkerSize(1);  H4->SetTitle(titulo);   
H4->GetXaxis()->SetTitle("Channel");         H4->GetYaxis()->SetTitle(" Counts "); H4->GetXaxis()->CenterTitle(); H4->GetYaxis()->CenterTitle(); H4->Rebin(8); 
c1->cd(4); H4->Draw();



c1->cd(0);

*/

theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

