//************** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**************************
//Programa para sumar archivos

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TObject.h>
#include <TGraph.h>
#include <TRint.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TH1.h>
#include <TH1I.h>
#include <TLegend.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <strings.h>

#define N 2500 				        // Número máximo de Datos 

using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char titulo[100]="Pulso Protones", fich[100], ejex[100]="Canal", ejey[100]="Amplitud (V)";
Float_t x[N],y[N],datosCH1[N],datosCH2[N],datosCH3[N],datosy[N], area; 	     		// Datos en canal x e y 
Int_t i,j,k,m,nfin,nini,p=0,l=0,a=0,ts,r=0;
char arch[100],arch1[100], ci[100]="";                         
//*********************************** Cuerpo del programa   *************************************
if (argc<2){
	cout << " 									   " << "\n";
	cout << "Modo de empleo: sumar [FICHERO](sin extens.) [inicial] [final]            " << "\n";
	cout << "		          				  	           " << "\n";
	cout << "Este programa suma los datos (1 columna) de n ficheros ASCII y los escribe" << "\n";
	cout << "en un fichero llamado Suma " 		   				     <<	"\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "									   " << "\n";
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
		case 6: cout << "ESCRIBA EL NOMBRE DEL PROGRAMA SIN ARGUMENTOS PARA OBTENER AYUDA"  << endl;
			break;
		};
	}
cout << nini << " " << nfin << endl;
for (i=0;i<(N-1);i++)                                                       // inicializacion de x[i]
	{
	x[i]=0;
	}
for (j=nini;j<(nfin+1);j++) 						//sumo desde nini a nfin
	{
	m=sprintf(arch,"%d.txt",j);  					//cargo en arch el nombre del fichero
	ifstream *in = new ifstream(arch);				// in es puntero asignado a fichero
	if(!*in) 							// Si no se puede abrir in 
		{cout << " ERROR OPENING FILE " <<  fich << endl; 	// Imprime que hay un error
		return 1;						// Salida 1 => error
		}
	else    {							// sino (abierto)
		i=0;
		*in >> ci;
		if ((strstr(ci,"START")!=NULL))	
			{
			i=0;
			}			// i es contador de linea
		
		while (i!=0);                    // mientras que no encuentre el START que siga	
		for (i=0;i<(N-1);i++)
			{*in  >> datosCH1[i] >> datosCH2[i] >> datosCH3[i] >> datosy[i];                 
              		  if ((strstr(ci,"END")!=NULL))     // si encuentro el END
				{
				i=N;			     // le pongo a i, N para que salga del for	
				}

			}

					// i final me da el numero de datos
		}
	//cout << datosy[1700] << endl;
	//if ((datosy[2690]>(-0.02))&&(datosy[2690]<(-0.01)))
	while ((a==0)&&(l<400))					// Mientras no llegue al final
		{							// elimino los que antes del 2500
		if (datosy[l]<(0.07))  				// superen -0.002
		l++;						        // Lea el fichero e incremente i
		else
		   a=1;							//a=1 significa que no vale
		}
	l=2000;	
	while ((a==0)&&(l<N))					// Mientras no llegue al final
		{							// elimino los que despues del 6000
		if (datosy[l]<(0.2))  				// superen -0.006
		l++;						        // Lea el fichero e incremente i
		else
		   a=1;							//a=1 significa que no vale
		}
	if (a==0)							// si son buenos, es decir a=0
		{							// corrijo por el jitter de rise time
		/*for (k=0;k<i;k++)					// recorro desde 0 hasta i final	
			{						// tomo el canal para el cual la  
			if ((datosy[k] < (-0.02))&&(r!=1))		// amplitud es -0.02 (si r=1 -> hecho)
				{ts=k-2500;r=1;}			// ts es dicho canal - 2500 (varia de 0 a 300)
			}						// 
		for (k=1000;k<i;k++)					// muevo los pulsos 1000 canales para atras
			{						// ya que tengo espacio al principio
			if (datosy[k+ts]>0) datosy[k+ts]=0;		// si el dato es positivo lo pongo a 0		
			x[k-1000]=x[k-1000]-datosy[k+ts];		// guardo 1000 canales antes del dato		
			}						// invertido ya que eran negativos
		*/p++;							// incremento p (nro. de pulsos buenos)
		
		for (k=250;k<(N-1);k++)					// muevo los pulsos 1000 canales para atras
			{						// ya que tengo espacio al principio
			//if (datosy[k+ts]>0) datosy[k+ts]=0;		// si el dato es positivo lo pongo a 0		
			x[k-250]=x[k-250]+datosy[k]-datosy[0];		// 		
			}	


		}
	r=0;								// pongo r=0 (para volver a calcular ts
	a=0;								// pongo a=0 (el pulso puede ser bueno)
	l=0;								// pongo l=0 (nro de canal desde principio)
	delete in; 							// borro fichero
	}

ofstream *out = new ofstream("PulsoSuma.txt");				// out puntero a fichero de salida 
//*out << " <<START>> " << endl;	
for (k=0;k<(N-1);k++)
	{
	*out << x[k] << endl;						//escribe el archivo suma
	}
//*out << " <<END>> " << endl;	
delete out;
cout << p << endl;							// imprime numero de archivos sumados
theApp->Run(kTRUE);							// Para hacer el ejecutable
delete theApp;
return 0;
}

