#ifndef _RISK_H
#define _RISK_H

int roll_die(const int sides);
void sort_int_dsc(int a[], const int size);
void roll_player(int rolls[], const int ndice);
int handle_battle(const int nattack, const int ndefend);
double win_chances(const int nattack, const int ndefend, const int nbattles);

#endif
