//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Programa para transformar los ficheros CSV del Osciloscopio YOKOGAWA 9140 DL 

//************************************* LIBRERIAS INCLUIDAS  **************************************

#include <cstdlib>				
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
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

#define N 2500 					// Número máximo de Datos por Canal
#define I 1700                                  // Número de canales a integrar
#define L 500                                   // Parametro de FIR
#define G 5                                    //parametro de FIR
#define F 2*L+G                                 // Funcion de los dos anteriores

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char arch[100],arch2[100],ci[100]="",*dat0, *dat1="", *dat2="";
Float_t x[N],y[N]; 
Int_t h,i,j,k,m,nini=0, nfin=7999;         			  //ficheros inicial y final 
     
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									" << "\n";
	cout << "Modo de uso: yoko_csv2root [FICHERO](sin extens.) [N_ini] [N_fin]       " << "\n";
	cout << "		          				  	        " << "\n";
	cout << "Este programa lee los datos del yokogawa y los pasa a ficheros txt    " << "\n";
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
system("clear");
cout << "Programa para pasar archivos CSV a 800 pulsos en TXT"  << endl;
cout << "****************************************************"  << endl;
system("mkdir pulsos"); cout << "Creada la carpeta PULSOS"  << endl;
cout << "Trasformando archivos, espere por favor .... " <<  endl << endl ;
for (j=nini;j<(nfin+1);j++) 						//sumo desde nini a nfin los 8000 ficheros
{	
	m=sprintf(arch,"00%d.csv",j);  					//cargo en arch el nombre del fichero
	ifstream *in = new ifstream(arch);				// in es puntero asignado a fichero
	if(!*in) 							// Si no se puede abrir in 
	{	cout << " ERROR OPENING FILE " <<  arch << endl;	// Imprime que hay un error
		return 1;						// Salida 1 => error
	}
	else    
	{
	for (h=0;h<800;h++)
		{      
		m=sprintf(arch2,"./pulsos/%d.txt",h+j*800);		
		ofstream *out = new ofstream(arch2); 		
		*out << " <<START>> " << endl;		
		i=1;
	        	do	
			{	*in >> ci;
				if ((strstr(ci,"block")!=NULL))	i=0;
			}
			while (i!=0);	
			*in >> ci;
			for (i=0;i<(N-1);i++)                                        // cargo los datos en datosy, y2
			{
				*in >> ci; 
				dat0= strtok( ci," ,");
				k=0;
		        	while (dat0 != NULL)
					{
					if (k==0) dat1=dat0;                		
					if (k==1) dat2=dat0;   
					dat0 = strtok(NULL," ,");
					k++;
					}
				x[i]=atof(dat1); y[i]=atof(dat2);
				*out << x[i] << " " << y[i] << endl;
 
		
			}   
		*out << " <<END>> " << endl;	               
		delete out;
	        if ((h%50)==0) cout << "completados: " << h+j*800 <<"/"<< (nfin+1)*800 << endl;
		}		
	}
}
cout << "Terminado. Gracias por participar.		     "  << endl;
cout << "****************************************************"  << endl << endl;

delete theApp;
return 0;
}

