// killerheuristicgame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<bitset>
#include<tuple>
#include<vector>
using namespace std;
bitset<64> x;
vector<tuple<int, int,int>> queens;
char a[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
void initboard()
{
  for (int i = 1; i < 50; i++)
  {
    x[i] = 0;
  }
  x[3] = 1;
  x[5] = 1;
  x[45] = 1;
  x[47] = 1;
  queens.emplace_back(3, 1,0);
  queens.emplace_back(5, 1,0);
  queens.emplace_back(3, 7,1);
  queens.emplace_back(5, 7,1);
}
void printboard()
{
  int blankflag = 0;
  cout << "\n   ------------------------------------------------- ";
  for (int i = 7; i > 0; i--)
  {
    cout << "\n";
    cout << i;
    for (int j = 1; j < 8; j++)
    {
      if (blankflag == 1)
      {
        cout << "|   ";
        blankflag = 0;
      }
      else
      {
        cout << "   |   ";
      }

      for (int k = 0; k < 4; k++)
      {
        
        if (x[i * 7 + j - 7] == 1 && get<0>(queens[k]) == (j) && get<1>(queens[k]) == (i))
        {
          if (get<2>(queens[k]) == 0)
          {
            cout << "#  ";
          }
          else
          {
            cout << "O  ";
          }
          blankflag = 1;
        }
      }
    }
    cout << "  |";
    cout << "\n   ------------------------------------------------- ";
  }
  cout << " \n       a      b      c      d      e      f       g";
  /*for (int i = 7; i > 0; i--)
  {
    for (int j = 1; j < 8; j++)
    {
      cout << i * 7 +j-7<<" ";
    }
    cout << "\n";
  }*/
}
int main()
{
  cout << "Hello World!\n";

  initboard();
  cout << get<0>(queens[3]) << get<1>(queens[3]);
  cout << get<0>(queens[0]) << get<1>(queens[0]);
  get<1>(queens[2]) = 3;
  get<0>(queens[2]) = 2;
  
  system("cls");
  cout << get<1>(queens[2]);
  printboard();
  return 0;
}
/*
1234567
891011121314
15161718192021
2122232425262728
29303132333435
36373839404142
43444546474849*/
