
#include "pobr.h"




void konwersja(obr *obrazek) 
{
  int i,j;
    obrazek->obraz_pgm=(int**)malloc(obrazek->wymy*sizeof(int*));
   for (i=0;i<obrazek->wymy;i++)
  obrazek->obraz_pgm[i]=(int*)malloc(obrazek->wymx*sizeof(int));
  
   obrazek->znak='2';
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_pgm[i][j]=(obrazek->obraz_ppm_R[i][j]+obrazek->obraz_ppm_G[i][j]+obrazek->obraz_ppm_B[i][j])/3;
  }
  }
  
  
   for (i=0;i<obrazek->wymy;i++)
   {
     	free(obrazek->obraz_ppm_R[i]);
     	free(obrazek->obraz_ppm_G[i]);
     	free(obrazek->obraz_ppm_B[i]);
   }
     	free(obrazek->obraz_ppm_R);
     	free(obrazek->obraz_ppm_G);
     	free(obrazek->obraz_ppm_B);
}







void negatyw(obr *obrazek,char kolor) 
{
  int i,j;
  if(obrazek->znak=='2')
  {
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_pgm[i][j]=obrazek->szarosci-obrazek->obraz_pgm[i][j];
  }
  }
  }
  else  if(obrazek->znak=='3')
  {
  switch(kolor)
  {
   case 'r':
   {
     for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_ppm_R[i][j]=obrazek->szarosci-obrazek->obraz_ppm_R[i][j];
  }
  }
   }
   break;
      case 'g':
   {
     for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_ppm_G[i][j]=obrazek->szarosci-obrazek->obraz_ppm_G[i][j];
  }
  }
   }
   break;
      case 'b':
   {
     for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_ppm_B[i][j]=obrazek->szarosci-obrazek->obraz_ppm_B[i][j];
  }
  }
   }
   break;
  }
  
  }
}



void konturowanie(obr *obrazek) 
{
  int i,j;
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
        if(i<obrazek->wymy-1 && j<obrazek->wymx-1)
  	obrazek->obraz_pgm[i][j]=abs(obrazek->obraz_pgm[i+1][j]-obrazek->obraz_pgm[i][j])+abs(obrazek->obraz_pgm[i][j+1]-obrazek->obraz_pgm[i][j]);
  	else if(i==obrazek->wymy-1 && j==obrazek->wymx-1)
  	obrazek->obraz_pgm[i][j]=abs(obrazek->obraz_pgm[0][j]-obrazek->obraz_pgm[i][j])+abs(obrazek->obraz_pgm[i][0]-obrazek->obraz_pgm[i][j]);
  	else if(i==obrazek->wymy-1)
  	obrazek->obraz_pgm[i][j]=abs(obrazek->obraz_pgm[0][j]-obrazek->obraz_pgm[i][j])+abs(obrazek->obraz_pgm[i][j+1]-obrazek->obraz_pgm[i][j]);
  	else
  	obrazek->obraz_pgm[i][j]=abs(obrazek->obraz_pgm[i+1][j]-obrazek->obraz_pgm[i][j])+abs(obrazek->obraz_pgm[i][0]-obrazek->obraz_pgm[i][j]);
  }
  }
}

void rozmycie(obr *obrazek,char kolor) 
{
  int i,j;
   if(obrazek->znak=='2')
  {
  for(i=3; i<obrazek->wymy-3; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  
  	obrazek->obraz_pgm[i][j]=1.0/3*(obrazek->obraz_pgm[i-1][j]+obrazek->obraz_pgm[i][j]+obrazek->obraz_pgm[i+1][j]);
  }
  }
  }
   else  if(obrazek->znak=='3')
  {
  switch(kolor)
  {
   case 'r':
   {
  for(i=3; i<obrazek->wymy-1; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  
  	obrazek->obraz_ppm_R[i][j]=1.0/3*(obrazek->obraz_ppm_R[i-1][j]+obrazek->obraz_ppm_R[i][j]+obrazek->obraz_ppm_R[i+1][j]);
  }
  }
   }
   break;
      case 'g':
   {
     for(i=0; i<obrazek->wymy-1; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
 obrazek->obraz_ppm_G[i][j]=1.0/3*(obrazek->obraz_ppm_G[i-1][j]+obrazek->obraz_ppm_G[i][j]+obrazek->obraz_ppm_G[i+1][j]);
  }
  }
   }
   break;
      case 'b':
   {
     for(i=0; i<obrazek->wymy-1; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  obrazek->obraz_ppm_B[i][j]=1.0/3*(obrazek->obraz_ppm_B[i-1][j]+obrazek->obraz_ppm_B[i][j]+obrazek->obraz_ppm_B[i+1][j]);
  }
  }
   }
   break;
  }
  
  }
}

void histogram(obr *obrazek) 
{
  int i,j;
  int min, max;
  min=max=obrazek->obraz_pgm[0][0];
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	if(min>obrazek->obraz_pgm[i][j])
  	{
  	min=obrazek->obraz_pgm[i][j];
  	}
  	if(max<obrazek->obraz_pgm[i][j])
  	{
  	max=obrazek->obraz_pgm[i][j];
  	}
  }
  }
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  	obrazek->obraz_pgm[i][j]=(obrazek->obraz_pgm[i][j]-min)*(float)obrazek->szarosci/(max-min);
  }
  }
}

void progowanie(obr *obrazek,float procent) 
{
  int i,j;
  if(procent<0 || procent>100)
  {
  	fprintf(stderr,"Blad: wartosc powina byc w zakresie 0-100\n");
  	return;
  
  }
  int prog = (obrazek->szarosci*procent)/100;
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {
  if(obrazek->obraz_pgm[i][j]<=prog)
  	obrazek->obraz_pgm[i][j]=0;
  	else
  	obrazek->obraz_pgm[i][j]=obrazek->szarosci;
  }
  }
}
void gamma_f(obr *obrazek,float gamma) 
{
  int i,j;
if(gamma<0 )
  {
  	fprintf(stderr,"Blad: gamma musi byc wieksza od 0\n");
  	return;
  
  }
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {

  	obrazek->obraz_pgm[i][j]=pow( (float)obrazek->obraz_pgm[i][j]/obrazek->szarosci,1/gamma )*obrazek->szarosci;
  	
  }
  }
}


int poziomy(obr *obrazek,float p_biel, float p_czern) 
{
  int i,j;
  if(p_biel<p_czern)
  {
  fprintf(stderr,"Blad: niedozwolone zakresy\n");
  return 1;
  }
  int biel =(obrazek->szarosci*p_biel)/100;
  int czern =(obrazek->szarosci*p_czern)/100;
  
  for(i=0; i<obrazek->wymy; i++)
  {
    for(j=0; j<obrazek->wymx; j++)
  {

  	if(obrazek->obraz_pgm[i][j]<=czern)
  	{
  	obrazek->obraz_pgm[i][j] =0;
  	}
  	else if(czern<obrazek->obraz_pgm[i][j] && biel>obrazek->obraz_pgm[i][j] )
  	{
  	obrazek->obraz_pgm[i][j] =(obrazek->obraz_pgm[i][j]-czern)*obrazek->szarosci/(biel-czern);
  	}
  	else
  	{
  	obrazek->obraz_pgm[i][j] =obrazek->szarosci;
  	}
  	
  }
  }
}


