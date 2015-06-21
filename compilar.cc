//**** Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.***************

#include <cstdlib>					//LIBRERIAS INCLUIDAS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000 				      
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************


		      
int m,m2;  
char fich[100],ar[100]="ar";

if (argc<2){
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.**********" << "\n";
	cout << "Atencion: falta el nombre del fichero a compilar					   " << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: m=sprintf(fich,"%s.cc",argv[1]);
			break;
		};
	}

m=sprintf(ar,"g++ -I$ROOTSYS/include -L$ROOTSYS/lib -L/usr/local/root/new/lib -lCore -lCint -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lGui -pthread -lm -ldl -rdynamic -o ../%s	%s.cc",fich,fich);
//execl("/bin/sh", "sh", "-c", ar,(char *)0);
m2=system(ar);
return 0;
}
