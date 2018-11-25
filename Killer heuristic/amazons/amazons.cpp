// killerheuristicgame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<bitset>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
uint64_t x;
//uint64_t y (0);
vector<tuple<int, int,bool>> queens;
bool chance=0;
char a[] = { 'A', 'B', 'C', 'D', 'E' };
struct avail
{
public:
   int value;
    uint64_t y[8][3];
    avail **masks;
};

avail *n = new avail;
void initboard()
{
  n->masks = new avail*[25];
  int row, column,temp,templimit,temp2,temp2limit;
  for (int i = 0; i < 25; i++)
  {
    n->masks[i] = new avail;
    for (int j = 0; j < 8; j++)
    {
      for (int l = 0; l < 3; l++)
      {
        n->masks[i]->y[j][l] = 0x0000000000000000;
        //cout <<( n->masks[i]->y[j][l]>>i);
      }
    }
  }
 
  
  
  
  
  
  for (int i = 0; i < 25; i++)
  {
   // n->masks[i] = n;
    column = i % 5;
    row = i / 5;
    //directions = enum(top, bottom, left, right)
    for (int j = 0; j < 8; j++)//j=0 top j=1bottom j=2left right diagonally topleft topright bottomleft bottomright
    {
      if (j == 0)
      {
        for (int k = 1; k < 4; k++)
        {
          if (row + k > 4)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row + k) * 5 + column));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row + k) * 5 + column));
        }
      }
      if (j == 1)
      {
        for (int k = 1; k < 4; k++)
        {
          if (row - k < 0)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row - k) * 5 + column));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row - k) * 5 + column));
        }
      }
      if (j == 2)
      {
        for (int k = 1; k < 4; k++) 
        {
          if (column - k < 0)
          {
            //cout << "HEY------------------------";
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row * 5 + column-k)));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row ) * 5 + column - k));

        }
      }
      if (j == 3)
      {
      for (int k = 1; k < 4; k++)
        {
          if (column + k > 4)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row) * 5 + column + k));
            continue;
          }

          //n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row) * 5 + column +k));
        }
      }
      if (j == 4)
      {
        for (int k = 1; k < 4; k++){

          if (row+k>4 || column-k<0)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row + k) * 5 + column-k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row + k) * 5 + column-k));
        }
      }
      if (j == 5)
      {

        for (int k = 1; k < 4; k++) {

          if (column + k > 4 || row + k > 4)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row + k) * 5 + column+k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row + k) * 5 + column+k));

        }
      }
      if (j == 6)
      {

        for (int k = 1; k < 4; k++)
        {

          if (column - k < 0 || row - k < 0)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row - k) * 5 + column-k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row - k) * 5 + column-k));

        }
      }
      if (j == 5)
      {

        for (int k = 1; k < 4; k++)
        {

          if (column - k < 0 || row + k > 6)
          {
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row + k) * 5 + column-k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row + k) * 5 + column-k));
        }
      }
    }
  }
  
  queens.emplace_back(3, 0,0);
  x |=1ULL<<3;
  x |= 1ULL << 2;
  queens.emplace_back( 4,1,0);
  x |= 1ULL << 9;
  queens.emplace_back( 0,3,1);
  x |= 1ULL << 15;
  queens.emplace_back (1,4,1);
  x |= 1ULL << 21;
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
  //system("cls");
  int blankflag = 0;
  cout << "\n   ------------------------------------------------- ";
  for (int i = 4; i >= 0; i--)
  {
    cout << "\n";
    cout << i;

    if (i == 0) {
      cout << "  ";
    }
    for (int j = 0; j <= 4; j++)
    {
    if (blankflag)
      {
        cout << "   |";
        blankflag = 0;
      }
      else
      {
        cout << "     |";
      }
      for (int k = 0; k < 4; k++)
      {
        if (((x >> (i * 5 + j)) & 1 )== 1 && get<0>(queens[k]) == (j) && get<1>(queens[k]) == (i))
        {
          if (!get<2>(queens[k]))
          {
            cout << "# ";
          }
          else if (get<2>(queens[k]))
          {
            cout << "O ";
          }
          blankflag = 1;
        }

      }
      if (((x >> (i * 5 + j)) & 1) == 1 && noqueens(i, j))
      {
        cout << "X";
        blankflag = 1;
      }
    }
    if (blankflag)
    {
      cout << "   |";
    }
    else
    {
      cout << "     |";
    }
    cout << "\n   ------------------------------------------------- ";
  }
  cout << " \n         a     b    c     d     e";
 // cout << "\n Player " << int(chance)+1<<"'s Chance";

  /*for (int i = 5; i > 0; i--)
  {
    for (int j = 1; j < 8; j++)
    {
      cout << i * 5 +j-5<<" ";
    }
    cout << "\n";
  }*/
}

void printbits(int pos, int dir, int dist)
{
  for (int i = 24; i >= 0; i--)
  {
    cout << ((n->masks[pos]->y[dir][dist] >> i) & 1ULL);
  }
}

//j=0top j=1bottom j=2left 3right 4topleft 5topright 6bottomleft 7bottomright

bool inputpos(int char1, int char2,int char3,int no1,int no2,int no3)
{
  int indexofchar = 10,queenindex=10;
for (int i = 0; i < 4; i++)  //test which queen to move
{
  if (get<2>(queens[i]) == chance && get<0>(queens[i]) == char1 && get<1>(queens[i]) == no1)
  {
    queenindex = i;
     break;
  }
}
if (queenindex == 10)
{
  cout << "unknown error???";
  return 0;
}
  
//test if queen can be moved at that position
      

    if (abs(no2-no1) > 3 || abs(char2-char1) > 3)
    {
      cout << "greater than 3 distance!";
      return 0;
    }
    if (no2 != no1 && char2 != char1)       //test for diagonal if both  x,y changed.
    {
      cout << abs(no2 - no1) << "  " << abs(char2-char1);
      if (abs(no2 - no1) != abs(char2-char1))
      {
        cout << "not diagonal!";
        return 0;
      }

      if (no1 < no2)                //moving diagonal up.
      {
        if (char1<char2) //moving diagonal is going  up and right
        {
          if ((n->masks[no1*5+char1]->y[5][abs(no2 - no1)-1] & x) != 0)
          {
            cout << "obstacle found tr";
            return 0; 
          }
        }
        else   //moving diagonal is going to the left
        {
          if ((n->masks[no1*5+char1]->y[4][abs(no2 - no1)-1] & x) != 0)
          {
            cout << "obstacle found tl";
            return 0;
          }
        }
      }
      else                         // diagonal is going down
      {
        if (char1 < char2) //moving diagonal is going down and right
        {
          if ((n->masks[no1*5+char1]->y[7][abs(no2 - no1)-1] & x) != 0)
          {
            cout << "obstacle found dr";
            return 0;
          }
        }
        else   //moving diagonal is going down and left
        {
          if ((n->masks[no1*5+char1]->y[6][abs(no2 - no1)-1] & x) != 0)
          {
            cout << "obstacle found dl";
            return 0;
          }
        }
      }


    }
    else if (no1 == no2) //player is moving only horizontally
    {
      if (char1 < char2)//player is moving only right
      {
        if ((n->masks[no1*5+char1]->y[3][abs(char2-char1)-1] & x) != 0)
        {
          cout << "obstacle found r";
          return 0;
        }
      }
      else//player is moving only left
      {
        if ((n->masks[no1*5+char1]->y[2][abs(char2-char1)-1] & x) != 0)
        {
          cout << "obstacle found l";
          return 0;
        }
      }
    }
    else  //player is moving up or down
    {
      if (no2 > no1)//up
      {
        if ((n->masks[no1*5+char1]->y[0][abs(no2 - no1)-1] & x) != 0)
        {
          cout << "obstacle found t";
          return 0;
        }
      }
      else
      {
        if ((n->masks[no1*5+char1]->y[1][abs(no2 - no1)-1] & x )!= 0)
        {
          cout << "obstacle found d";
          return 0;
        }
      }
    }

  
  

  cout << "old character place" <<char1 << "old n place" << no1<< "new" << char2 << "new n place" << no2;

//Done and done Now check if user can shoot an arrow at valid pos
  //=======================================================================================================\\

  indexofchar = 10;
   
     
   

    if (abs(no3 - no2) > 3 || abs(char3-char2) > 3)
    {
      cout << "greater than 3 distance!";
      return 0;
    }
    if (no3 != no2 && char3!=char2)       //test for diagonal if both  x,y changed.
    {
      cout << abs(no3 - no2) << "  " << abs(char3-char2);
      if (abs(no3 - no2) != abs(char2-char1))
      {
        cout << "not diagonal!";
        return 0;
      }
      if (no2 < no3)                //moving diagonal up.
      {
        if (char2 < char3) //moving diagonal is going  up and right
        {
          if ((n->masks[no2*5+char2]->y[5][abs(no3 - no2)-1] & x )!= 0)
          {
            cout << "obstacle found";
            return 0;
          }
        }

        else   //moving diagonal is going to the left
        {
          if ((n->masks[no2*5+char2]->y[4][abs(no3 - no2)-1] & x )!= 0)
          {
            cout << "obstacle found";
            return 0;
          }
        }
      }
      else 
      {                         // diagonal is going down
        if (char1 < char2) //moving diagonal is going down and right
        {
          if( (n->masks[no2 * 5 + char2]->y[7][abs(no3 - no2) - 1] & x) != 0)
          {
            cout << "obstacle found";
            return 0;
          }
        }
        else   //moving diagonal is going down and left
        {
          if ((n->masks[no2 * 5 + char2]->y[6][abs(no3 - no2) - 1] & x) != 0)
          {
            cout << "obstacle found";
            return 0;
          }
        }
      }
    }
    else if (no1 == no2) //player is moving only horizontally
    {

      if (char1 < char2)//player is moving only right
      {
        if ((n->masks[no2 * 5 + char2]->y[3][abs(char3-char2) - 1] & x )!= 0)
        {
          cout << "obstacle found";
          return 0;
        }
      }
      else//player is moving only left
      {
        if ((n->masks[no2 * 5 + char2]->y[2][abs(char3-char2) - 1] & x) != 0)
        {
          cout << "obstacle found";
          return 0;
        }
      }
    }
    else  //player is moving up or down
    {
      if (no2 > no1)
      {
        if ((n->masks[no2 * 5 + char2]->y[1][abs(no3 - no2) - 1] & x) != 0)
        {
          cout << "obstacle found";
          return 0;
        }
      }
      else
      {
        if ((n->masks[no2 * 5 + char2]->y[5][abs(no3 - no2) - 1] & x) != 0)
        {
          cout << "obstacle found";
          return 0;
        }
      }
    }
    get<0>(queens[queenindex]) = char2;
    get<1>(queens[queenindex]) = no2; //move the queen since correct position!!!
    cout << (no1*5+char1);
    x &= ~(1ULL << (no1*5+char1));//reset the old queen to be blank 
    //and make new position filled
    x |= 1ULL << (no2*5+char2);
  
    x |= 1ULL <<( no3* 5 + char3);//shoot an arrow at given position.
    chance = !chance;
    printboard();
    cout << queenindex;
    return 1;

}
bool simpletest(string b)
{
  int flag = 0, indexofchar = 10, queenindex = 10,j=0;
  for (j = 0; j <= 4; j+=2) {
    for (int i = 0; i < 5; i++)           //test alphabet as column         
    {
      if (b[j] == a[i])
      {
        indexofchar = i;
        break;
      }
    }
    if (indexofchar == 10 || !isalpha(b[j]))       //alphabet not between a-g or undefined recall .
    {
      cout << "Enter alphabet please!";
      return 0;
    }

    if (0 > (int(b[j+1]) - 48) || (int(b[j+1]) - 48) > 4) //test second character is a no2 from 1 to 5    
    {
      cout << "no2 0-4";
      return 0;
    }
  
   
    for (int i = 0; i < 4; i++)  //test if queen of respective player is at that position
    {
      if (get<2>(queens[i]) == chance && get<0>(queens[i]) == indexofchar && get<1>(queens[i]) == (int(b[1]) - 48))
      {
        queenindex = i;
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      //system("cls");
      cout << "no queen there!";
      return 0;
    }
  }
}


int main()
{
  initboard();
  string b;
  for (int i = 0; i < 4; i++)
  {
   cout << "queen " << i << " is at " << get<1>(queens[i])<<" pos "<<get<0>(queens[i]);
  }

  printboard();
  int flag = 0, char1, char2, char3, no1, no2, no3;
  chance = 0;
  while (true)
  {
    do {
      cout << "\n Player " << int(chance) + 1 << "'s move. Select position of your queen to move:where to move and arrow position like:D0C0C3\n";
      cin >> b;
    } while (!simpletest(b));
    for (int i = 0; i < 5; i++)                  
    {
      if (b[0] == a[i])
      {
        char1 = i;
        break;
      }
    }
    for (int i = 0; i < 5; i++)
    {
      if (b[2] == a[i])
      {
        char2 = i;
        break;
      }
    }
    for (int i = 0; i < 5; i++)
    {
      if (b[4] == a[i])
      {
        char3 = i;
        break;
      }
    }
    no1 = int(b[1]) - 48;
    no2 = int(b[3]) - 48;
    no3 = int(b[5]) - 48;
    if (inputpos(char1,char2,char3,no1,no2,no3))
    {
      cout << "successful";
      chance = !chance;
    }
    
  }
  return 0;
}
/*
20 21 22 23 24
15 16 17 18 19
10 11 12 13 14
5  6  7  8  9
0  1  2  3  4

*/
