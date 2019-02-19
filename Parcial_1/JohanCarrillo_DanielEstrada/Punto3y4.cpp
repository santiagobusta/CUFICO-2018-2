/*

*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <ctime>

using namespace std;

float T_computo(int);

class Mapa
{
public:
  int fil;
  int col;
  int vecinos;
  int N_Vivos; // atributo que tiene la informacion de cuantos vivos hay 
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
  N_Vivos = 0;
  fil = f;
  col = c;
  mapa.resize(fil);
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col);
    }
  
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	         mapa[f][c] = rand()%2;
           if (mapa[f][c] == 1)
            N_Vivos++; // esta linea cuenta el numero de vivos al establecer el arreglo inical
        }
    }
}

void Mapa::dibujar()
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1)
	    cout << "* ";
	  else
	    cout << ". ";
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos(int posf, int posc)
{
  vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos++;
  return vecinos;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  N_Vivos = 0; // se reinicia el contador de vivos para recalcularse 
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos = analizarVecinos(f, c);
	  if(mapa[f][c] == 0)
            {
	      if(vecinos == 3){
		nueva_conf[f][c] = 1;
    N_Vivos++; // aumenta el numero de vivos 
    }
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1)
            {
	      if(vecinos == 2 || vecinos == 3){
		nueva_conf[f][c] = 1;
    N_Vivos++; // aumenta el numero de vivios 
    }
	      else
		nueva_conf[f][c] = 0;
            }
        }
    }
  
  mapa = nueva_conf;
}

float T_computo(int n)
// Esta funcion calcula el tiempo que le toma a juego de la vida estabilizarse dado un tamaño n
{
  clock_t t;
  t = clock();
  int k=0; 
  int vivos[6]; // arreglo en el que se almacena el numero de vivos de los tres ultimos ciclos 
  
  srand(time(NULL));
  Mapa mapa(n, n);

  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      //system("clear");
      printf("%d\n",mapa.N_Vivos);
      vivos[k] = mapa.N_Vivos;
      mapa.ciclo();
      if(k == 5){
        // luego de hacer 6 ciclos se evalua si el numero de vivos es estable o no(tres ciclos seguidos tengan el mismo numero de vivos)
        if(vivos[0]==vivos[1] && vivos[1]==vivos[2] && vivos[1] == vivos[3] && vivos[1]==vivos[4] && vivos[1] == vivos[5]){
          t = clock() - t;
          break; // si se estabiliza se rompe el proceso
        }
        else if((vivos[0]==vivos[2] && vivos[0]==vivos[4]) && (vivos[1]==vivos[3] && vivos[1]==vivos[5])){
          t = clock() - t;
          break;
        }
        else{
          // sino se cumple la estabilidad se reordenan los elementos del arreglo vivos para incluir una iteración más del while
          vivos[0] = vivos[1];
          vivos[1] = vivos[2];
          vivos[2] = vivos[3];
          vivos[3] = vivos[4];
          vivos[4] = vivos[5];
          k = 4;

        }  
      }

      k++;
     } 

  for (int i = 0; i < 6; i++)
  {
    printf("%d ", vivos[i]);
  }   

  return ((float)t) / CLOCKS_PER_SEC; 
}

int main()
{
  float tiempo;

  for (int n = 5; n < 60; n = n + 2)
  {
    int k = 0;
    char nombre_archivo[30];
    sprintf(nombre_archivo, "Tiempo_Computo_%d.txt", n);
    FILE *archivo = fopen(nombre_archivo, "w");
    for (int i = 0; i < 12; i++)
    {
      tiempo = T_computo(n);
      fprintf(archivo, "%f \n",tiempo);
      k++;
    }
    fclose(archivo);
    printf("%d\n", k);
  }
  return 0;
}
