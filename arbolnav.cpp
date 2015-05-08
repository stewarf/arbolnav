/* ------------------------------------------------------------ *
 * Nombre del Programa.............: ARBOLNAV                   *
 * Version.........................: 1.1.6.2                    *
 * Programador.....................: Stewarf                    *
 * F/C.............................: 02/Dic/2004                *
 * F/M (v1.1)......................: 04/Dic/2004                *
 * F/M (v1.1.2)....................: 06/Dic/2004                *
 * F/M (v1.1.3)....................: 07/Dic/2004                *
 * F/M (v1.1.4)....................: 10/Dic/2004                *
 * F/M (v1.1.5)....................: 13/Dic/2004                *
 * F/M (v1.1.6)....................: 14/Dic/2004                *
 * F/M (v1.1.6.1)..................: 17/Dic/2004                *
 * F/M (v1.1.6.2)..................: 18/Dic/2004                *
 * ------------------------------------------------------------ */

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#define	SPACE	'\000'
#define	HOJAS	'*'
#define	TRONCO	'|'

short oclr=0;
static int clrnav[4] = { LIGHTGREEN,LIGHTRED,YELLOW,WHITE };
void drwchx(short ,char ,int ,int );
void initArbol(short ,int ,int );

// [Manual de uso del programa con argumentos]
// Aparece cuando solamente se escribio el nombre del
// programa sin argumentos.

void howto(){
 printf("\nArbolNav para DOS [v1.1.6.2]\n");
 printf("Sharak 2001-2004\n\n");
 printf("Sintaxis: ARBOLNAV <size> <tcr> <tbc> \n");
 printf(" <size>\t: Tama§o del Arbol de Navidad.\n");
 printf(" <tcr> \t: Color de las luces.\t[Opcional] \n");
 printf(" <tbc> \t: Color de las hojas.\t[Opcional] \n");
 printf("\nEjemplos:\n\t ARBOLNAV 18 998 3\n");
 printf("\t ARBOLNAV 22 997\n");
 printf("\t ARBOLNAV 7 14\n\n");
}

/* Metodo Principal */
int main(int argc, char **argv){
 short flg_w=0; char argqw;

 // Si solamente se escribe el nombre del programa
 // o se ejecuta al dar doble click entrar† en este
 // modulo del programa donde se deplegara la forma
 // de usar dicho programa y la opcion de agregar
 // datos para dibujar un arbol.

 if(argc < 2){
  howto();
  short flg_y=0;
  do{
   do{

    if(flg_w==0) printf("Desea ejecutar el programa proporcionando sus valores? (y/n):> ");
		else printf("Desea dibujar otro arbol? (y/n):> ");
		argqw=getchar();
		if(argqw=='y'){ printf("\n"); flg_w=1; flg_y=1; }
		else if(argqw=='n'){ system("cls"); exit(1); }
    else {
		 printf("\nOpcion incorrecta: \"%c\"\n",argqw);
     printf("Escriba una opcion valida. \n\n");
     flg_y=0;
    }
   } while(flg_y==0);

   int varg[3];
   printf("\nCuanto medira el arbol?:> "); scanf("%i",&varg[0]);
   printf("\nDe que color quiere sus luces (0 al 15 o 997 al 999):> "); scanf("%i",&varg[1]);
   printf("\nDe que color quiere las hojas (0 al 15 o 999):> "); scanf("%i",&varg[2]);
   randomize();
   if(varg[1]==999||varg[1]==998)
    while(!kbhit()){
     initArbol(varg[0],varg[1],varg[2]); delay(1700);
    }
   else { initArbol(varg[0],varg[1],varg[2]); getch(); }
   system("cls");
  } while(flg_y!=0);
 }

 // Si agrego parametros al programa desde la consola o en las
 // propiedades del dicho programa, entrara a este metodo para
 // procesar los datos previamente agregados.

 int anim;
 anim=atoi(argv[2]);
 randomize();
 if(anim==999||anim==998)
  while(!kbhit()){
   initArbol(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])); delay(1700);
  }
 else { initArbol(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])); getch(); }

 system("cls");
 return 0;
}




/* Metodo del dibujado del arbol con sus hojas y luces
 * donde se representa los caracteres como luces y las
 * hojas como el fondo de las luces, el tronco toma su
 * forma a partir del tamaœo del arbol. */

void initArbol(short ysz,int tcrg,int tbcg){
 clrscr();

 /* Valores por defecto de las luces y las hojas. */
 if(tcrg==NULL) tcrg=997;
 if(tbcg==NULL) tbcg=2;

 /* Dibuja la parte de las hojas y luces. */
 short asize=ysz,bsize=1,tsize,csize;
 for(csize=0;csize<ysz;csize++){
	drwchx(asize,SPACE,0,0);
	if(csize==0) drwchx(bsize,HOJAS,WHITE,YELLOW);
	else drwchx(bsize,HOJAS,tcrg,tbcg);
	drwchx(asize,SPACE,0,0);
	asize--;
	bsize+=2;
	printf("\n");
 }

 /* Determina el tamaœo del tronco */
 if(ysz<=5){ asize=ysz; bsize=1; tsize=1; }
 else if(ysz>5&&ysz<=15){ asize=ysz-1; bsize=3; tsize=1; }
 else if(ysz>15&&ysz<=30){ asize=ysz-1; bsize=3; tsize=2; }
 else{ asize=ysz-2; bsize=5; tsize=3; }

 /* Dibuja el tronco */
 for(csize=0;csize<tsize;csize++){
	drwchx(asize,SPACE,0,0);
	drwchx(bsize,TRONCO,6,4);
	drwchx(asize,SPACE,0,0);
	printf("\n");
 }

}




// [Graficador de Caracteres en Linea]
// Uso: drwchx(arg1,arg2,arg3,arg4);
// arg1..: Tama§o de la franja de caracteres.
// arg2..: Caracter a representar.
// arg3..: Color del caracter.
// arg4..: Color de fondo del caracter.

void drwchx(short xsz,char obj,int tcr,int tbc){
 for(short cxa=0;cxa<xsz;cxa++){

	// arg3=999 : Color aleatorio de las luces
	// arg3=998 : Colores navide§os aleatorios.
	// arg3=997 : Colores navide§os de las luces.

	switch(tcr){
	 case 999: textcolor(random(16)); break;
	 case 998: textcolor(clrnav[random(4)]); break;
	 case 997: textcolor(clrnav[oclr]); break;
	 default: textcolor(tcr);
	}

	if (tcr==997) { oclr++; if(oclr==4) oclr=0; }

	// arg4=999 : Color aleatorio para las hojas.

	switch(tbc){
	case 999: textbackground(random(16)); break;
	default: textbackground(tbc);
	}

	/* Impresion del caracter con o sin colores. */
	cprintf("%c",obj);
 }
}