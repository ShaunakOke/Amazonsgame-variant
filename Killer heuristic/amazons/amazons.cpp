// killerheuristicgame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<bitset>
#include<tuple>
#include<vector>
#include<string>
using namespace std;
bitset<64> x;
vector<tuple<int, int,bool>> queens;
bool chance=0;
char a[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
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
bool noqueens(int i, int j)
{
  for (int k = 0; k <4 ; k++)
  {
    if (get<0>(queens[k]) == j && get<1>(queens [ k ]) ==i)
    {
      return 0;
    }
  }
  return 1;
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
      if (blankflag)
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
        if (!get<2>(queens[k]))
        {
            cout << "#  ";
        }
        else if(get<2>(queens[k]))
        {
        cout << "O  ";
        }
        blankflag = 1;
      }
        
      }
      if (x[i * 7 + j - 7] == 1 && noqueens(i, j))
      {
        cout << "X  ";
        blankflag = 1;
      }
    }
    cout << "  |";
    cout << "\n   ------------------------------------------------- ";
  }
  cout << " \n       a      b      c      d      e      f       g";
  cout << "\n Player " << int(chance)+1<<"'s Chance";

  /*for (int i = 7; i > 0; i--)
  {
    for (int j = 1; j < 8; j++)
    {
      cout << i * 7 +j-7<<" ";
    }
    cout << "\n";
  }*/
}
void inputpos()
{
  string b;
  int flag = 0,indexofchar=10;
  cout <<  "\n Player " << int(chance)+1 << "'s move. Select position of your queen to move:";
  cin >> b;
  for (int i = 0; i < 7; i++)           //test alphabet as column         
  {
    if (b[0] == a[i])
    {
      indexofchar = i;

      break;
    }
  }
  if (indexofchar == 10 || !isalpha(b[0]))       //alphabet not between a-g or undefined recall .
  {
    cout << "Enter alphabet please!";
    inputpos();
  }
  if (0 >= (int(b[1]) - 48) || (int(b[1]) - 48) > 7) //test second character is a number from 1 to 7    
  {
    cout << "number 1-7";
    inputpos();
  }
  for (int i = 0; i < 4; i++)  //test if queen of respective player is at that position
  {
    if (get<2>(queens[i])==chance && get<0>(queens[i])== indexofchar+1 && get<1>(queens[i])==(int(b[1])-48) )
    {
      flag = 1;
    }
  }
  if (!flag)
  {
    //system("cls");
    cout << "no queen there!";
    inputpos();
  }
  b = " ";
  cout << "Where to move this queen?";
  cin >> b;
  for (int i = 0; i < 7; i++)           //test alphabet as column         
  {
    if (b[0] == a[i])
    {
      indexofchar = i;

      break;
    }
  }
  if (indexofchar == 10 || !isalpha(b[0]))       //alphabet not between a-g or undefined recall .
  {
    cout << "Enter alphabet please!";
    inputpos();
  }
  if (0 >= (int(b[1]) - 48) || (int(b[1]) - 48) > 7) //test second character is a number from 1 to 7    
  {
    cout << "number 1-7";
    inputpos();
  }

}
int main()
{
  cout << "Hello World!\n";

  initboard();
  system("cls");

  for (int i = 0; i < 4; i++)
  {
   // cout << "queen " << i << " is at " << get<1>(queens[i])<<" pos "<<get<0>(queens[i]);
  }
  printboard();

  inputpos();
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
