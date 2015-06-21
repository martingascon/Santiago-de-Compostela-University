//*************************************************************************************************
//    AUTHOR : Martin Gascon                  Date: 04/2006                Last Update: 24/04/06
//    Copyright: GENP (Universidad de Santiago de Compostela)
//*************************************************************************************************
//    tel                                                                  Telefonic list of Genp
//*************************************************************************************************
// How to run this program: tel <name or alias>
//*************************************************************************************************

#include <stdio.h>
#include <string.h>

int i,k,j,l=0,m;
char apodo[100],nombre[100],nombre2[100],arch[100];
char *c,*ci;
FILE *fp;
/*char filtro(char c)			/* este filtro convierte todas las letras acentuadas en*/
/*{   						/*minúsculas sin acento */
/*    if(c>='A' && c<='Z')
        return (c+'a'-'A');
    if(c=='á')
	return 'a';
    if(c=='é')
	return 'e';
    if(c=='í')
	return 'i';
    if(c=='ó')
	return 'o';
    if(c=='ú')
	return 'u';
    if(c=='Á')
	return 'a';
    if(c=='É')
	return 'e';
    if(c=='Í')
	return 'i';
    if(c=='Ó')
	return 'o';
    if(c=='Ú')
	return 'u';
    return c;
}*/
int main(int argc,char *argv[])
{
if ((argc)!=2)  
	{
     	printf("\ntel: Falta introducir el nombre a buscar \n");
     	exit(1); 
    	}
if (argc==2) 
	{
     	if ((fp = fopen( "/usr/bin/agenda.txt", "r" )) == NULL )
		printf("ERROR: no puedo abrir la Agenda: \nConsulte con Martín Gascón ext:14000\n");
	else
		{  
      		do
    			{
        		ci = fgets(nombre, 100, fp);    /* Obtiene una linea del archivo */
       			strcpy(apodo,argv[1]);
			for (i=0;i<100;i++) apodo[i]=tolower(apodo[i]);
			for (i=0;i<100;i++) nombre2[i]=tolower(nombre[i]);
			if ((strstr(nombre,apodo)!=NULL)||(strstr(nombre2,apodo)!=NULL))
				{
				for (i=0;i<80;i++) printf("*");
				printf("\n");
				for (i=7;i<strlen(nombre);i++) printf("%c",nombre[i]);
				for (i=0;i<80;i++) printf("*");
				printf("\n");
				l=1;
				}
  		 	}
    		while (ci!= NULL);      /* Se repite hasta encontrar NULL */
    		if (l==0) 
			{
			for (i=0;i<80;i++) printf("*");	printf("\n");
			printf("No se encontró ninguna referencia a ese nombre\n");	
			}
		}
     	}
      
fclose(fp);     
printf("Copyright: GENP\n\n");
exit(0);
}
