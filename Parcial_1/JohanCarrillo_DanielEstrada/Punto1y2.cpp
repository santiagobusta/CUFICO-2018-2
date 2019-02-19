/*
Este codigo ejecuta el juego de la vida y se sdetiene cuando el sistema se estabiliza.
Esto corresponde al punto 1 y 2
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

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

int main()
{
  int n, k=0; 
  int vivos[6]; // arreglo en el que se almacena el numero de vivos de los tres ultimos ciclos 
  cout << "Ingrese el tamaño de la matriz: \n ";
  cin >> n ;
  srand(time(NULL));
  Mapa mapa(n, n);

  while(1)
    {
      mapa.dibujar();
      usleep(500000);
      //system("clear");
      
      vivos[k] = mapa.N_Vivos;
      cout << vivos[k] << "\n";
      mapa.ciclo();
      
      if(k == 5){
        // luego de hacer 6 ciclos se evalua si el numero de vivos es estable o no(tres ciclos seguidos tengan el mismo numero de vivos)
        if(vivos[0]==vivos[1] && vivos[1]==vivos[2] && vivos[1] == vivos[3] && vivos[1]==vivos[4] && vivos[1] == vivos[5])
          break; // si se estabiliza se rompe el proceso
        else if((vivos[0]==vivos[2] && vivos[0]==vivos[4]) && (vivos[1]==vivos[3] && vivos[1]==vivos[5]))
          break;
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

    return 0;
}
