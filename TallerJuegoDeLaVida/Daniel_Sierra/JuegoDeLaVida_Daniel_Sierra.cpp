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
  int vecinos_1;
  int vecinos_2;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos_1(int posf, int posc);
  int analizarVecinos_2(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
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
	  mapa[f][c] = rand()%3;
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
	  else if(mapa[f][c] == 2)
	    cout << "+ ";
	  else
	    cout << ". ";
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos_1(int posf, int posc)
{
  vecinos_1 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos_1++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos_1++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos_1++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos_1++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos_1++;
  return vecinos_1;
}

int Mapa::analizarVecinos_2(int posf, int posc)
{
  vecinos_2 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 2)
      vecinos_2++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 2)
      vecinos_2++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 2)
      vecinos_2++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 2)
      vecinos_2++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 2)
      vecinos_2++;
  return vecinos_2;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos_1 = analizarVecinos_1(f, c);
          int n_vecinos_2 = analizarVecinos_2(f, c);
	  if(mapa[f][c] == 0)
            {
	      if(vecinos_1 >= vecinos_2 and vecinos_1 == 3)
		nueva_conf[f][c] = 1;
	      else if(vecinos_1 < vecinos_2 and vecinos_2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1)
            {
	      if(vecinos_1 >= vecinos_2 and (vecinos_1 == 2 || vecinos_1 == 3))
		nueva_conf[f][c] = 1;
              else if(vecinos_1 < vecinos_2 and vecinos_2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 2)
            {
	      if(vecinos_1 >= vecinos_2 and vecinos_1 == 3)
		nueva_conf[f][c] = 1;
              else if(vecinos_1 < vecinos_2 and (vecinos_2 == 2 || vecinos_2 == 3))
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
        }
    }
  
  mapa = nueva_conf;
}

int main()
{
  srand(time(NULL));
  Mapa mapa(50, 50);
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}
