#include <iostream> /* cout, endl, etc. */
#include <cstdlib>  /* srand(), rand() */
#include <ctime>    /* time() */
#include "risk.h"


int roll_die(const int sides)
{
    if (sides >= 1)
    {
        //std::srand(time(0));
        int die = (std::rand() % sides)+ 1;
        return die;
    }
    else
    {
        return -1;
    }
}

void sort_int_dsc(int a[], const int size)
{
    bool switched = true;
    int i;
    int hold;
    while (switched)
    {
        switched = false;
        for (i=0; i < size-1; i++)
        {
            if (a[i] < a[i+1])
            {
                hold = a[i];
                a[i] = a[i+1];
                a[i+1] = hold;
                switched = true;
            }
        }
    }
}

void roll_player(int rolls[], const int ndice)
{
    int i;
    int die;
    for (i = 0; i < ndice; i++)
    {
        die = roll_die(6);
        rolls[i]=die;
    }
    sort_int_dsc(rolls, ndice);
}

int handle_battle(const int nattack, const int ndefend)
{
    if (nattack > 3 || ndefend > 2)
    {
        return -1;
    }
    int adice[3];
    int ddice[2];
    roll_player(adice, nattack);
    roll_player(ddice, ndefend);
    int i;
    int n;
    if (nattack < ndefend){
        n = nattack;
    }
    else
    {
        n = ndefend;
    }
    int loss = 0;
    for (i=0; i<n; i++)
    {
        if (adice[i] > ddice[i])
        {
            loss++;
        }
    }
    return loss;
}

double win_chances(const int nattack, const int ndefend, const int nbattles)
{
    int i;
    double dloss = 0;
    double aloss = 0;
    int loss;
    double min;
    if (nattack < ndefend)
    {
        min = nattack;
    }
    else
    {
        min = ndefend;
    }
    for (i=0; i < nbattles; i++)
    {
        loss = handle_battle(nattack, ndefend);
        if (loss == -1)
        {
            return -1;
        }
        else
        {
            dloss += loss;
            aloss += (min - loss);
        }
    }
    double total;
    double dtotal;
    total = dloss+aloss;
    dtotal = dloss/total;
    return dtotal;
}

int main(int argc, char *argv[])
{
  int nbattles;
  int nattack;
  int ndefend;
    if (argc < 4)
    {
            std::cout<<"usage error: please enter" << argv[0] << " #of attack die, #of defend die, #of simulations"<<std::endl;
      return 0;
    }
  nattack=std::atoi(argv[1]);
  ndefend=std::atoi(argv[2]);
  nbattles=std::atoi(argv[3]);
  std::srand(time(0));
  double test;
  test = win_chances(nattack, ndefend, nbattles);
  std::cout << test << std::endl;
}
