//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************

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
#include <TTree.h>
#include <TFile.h>

#define N 10000 				       // Número máximo de Datos 
#define Z 1000 		       			       // Número Pulsos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t mean,sigma,newtrigger, dmean,dsigma,datosy[N],datosx[N],x[N],y[N]; 		      
Float_t XINCR=4.0E-10, PT_OFF= 0, XZERO= -1.9E-6,YMULT= 2.0E-3 , YZERO= 1.0E-2 ,YOFF= 72;
Int_t i,j=0,k,l,xini,aux=0,oldtim,m,m2,fin=1,ffi=1;  
char arch[100],fich[100],nom[100],dummy[7];
TH1F *signal =new TH1F();
TGraph *graf1 =new TGraph();
TFile *fichroot=new TFile("tree.root","RECREATE");
TTree *tree = new TTree("tree","signals");
tree->Branch("Signal","TH1F",&signal,32000,0);
tree->Branch("graph","TGraph",&graf1,32000,0);

//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: bin2asc [FICHERO](sin extens.) 		           " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa transforma de un fichero binario a N ficheros ascii.        " << "\n";
	cout << "y los crea en la carpeta datos con el nombre backup(i).txt 		   " << "\n";
	cout << "									   " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.bin",argv[1]);
			break;
		};
	

	ifstream *in = new ifstream(fich,ios::in | ios::binary);
	if(!*in) 
		{cout << " ERROR OPENING FILE " <<  fich << endl; 
		return 1;
		}
	else    {
 		while (!in->eof()) 
			{	
			j++;
			sprintf(nom,"signal_%d",j);
			signal->SetNameTitle(nom,nom);
			signal->SetBins(N,0,N);
	      		signal->SetXTitle("tiempo (s)");
	      		signal->SetYTitle("Amplitud (V)");
			graf1->SetMarkerColor(2);
			graf1->SetFillColor(19);
			graf1->SetLineColor(2);
			graf1->SetLineWidth(1);
			graf1->SetMarkerStyle(8);
			graf1->SetMarkerSize(0.1);
			graf1->SetTitle(nom);
			graf1->GetXaxis()->SetTitle("tiempo (s)");
			graf1->GetYaxis()->SetTitle("Amplitud (V)");
			graf1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
			graf1->GetYaxis()->CenterTitle();
			graf1->GetYaxis()->SetTitleOffset(1.3);
			graf1->GetYaxis()->SetLabelSize(0.035);
			graf1->GetXaxis()->SetLabelSize(0.035);	
			
			in->read(dummy,7);  
			Char_t *buf = new Char_t[N];
			in->read(buf,N);
			for(i=0;i<N;i++)
    				{
     		 		datosx[i]=XZERO+XINCR*(N-PT_OFF);
     				aux = *(buf+i);
     			 	datosy[i]=YZERO+YMULT*(aux-YOFF);
		 		signal->SetBinContent(i,datosy[i]);
				graf1->SetPoint(i,datosx[i],datosy[i]);
				}
			in->read(dummy,1);
			signal->Write();  
			graf1->Write(); 
			tree->Fill();
			
			signal->Reset();
			}
		tree->Write();
		fichroot->Close();
		delete fichroot;
  		}
	
	}

}

