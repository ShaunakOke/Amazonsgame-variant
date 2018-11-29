// killerheuristicgame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
uint64_t x,temp;
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

struct node
{
  uint64_t board;
  int a;
  node **child;
};
void init()
{

}

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
    //j=0top j=1bottom j=2left 3right diagonally 4topleft 5topright 6bottomleft 7bottomright
    for (int j = 0; j < 8; j++)
    {
      if (j == 0)
      {
        for (int k = 1; k < 4; k++)
        {
          if (row + k > 4)
          {
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row) * 5 + column + k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row) * 5 + column +k));
        }
      }
      if (j == 4)
      {
        for (int k = 1; k < 4; k++){

          if (row+k>4 || column-k<0)
          {
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
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
      if (j == 7)
      {

        for (int k = 1; k < 4; k++)
        {

          if (row-k<0 || column+k>4)
          {
            n->masks[i]->y[j][k - 1] = 0xFFFFFFFFF;
            continue;
          }
          if (k == 1)
          {
            n->masks[i]->y[j][k - 1] |= (1ULL << ((row - k) * 5 + column+k));
            continue;
          }

          n->masks[i]->y[j][k - 1] = n->masks[i]->y[j][k - 2] | (1ULL << ((row - k) * 5 + column+k));
        }
      }
    }
  }
  
  queens.emplace_back(3, 0,0);
  x |=1ULL<<3;

  queens.emplace_back(4, 1, 0);
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
  cout << "\n        ---------------------------------------------- ";
  for (int i = 4; i >= 0; i--)
  {
    cout << "\n        ";
    cout << i << left<<"    |";
    for (int j = 0; j <= 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (((x >> (i * 5 + j)) & 1) == 1 && get<0>(queens[k]) == (j) && get<1>(queens[k]) == (i))
        {
          if (!get<2>(queens[k]))
          {
            cout << "#      |";
          }
          else
          {
            cout << "O      |";
          }
          blankflag = 1;
        }
      }
      if (((x >> (i * 5 + j)) & 1) == 1 && noqueens(i, j))
      {
        cout << "X      |";
        blankflag = 1;
      }
      if (!blankflag)
      {
        cout << "       |";
      }
      blankflag = 0;
    }
    cout << "\n        ---------------------------------------------- ";
  }
  cout << " \n                A        B        C        D        E";
  
 // cout << "\n Player " << int(chance)+1<<"'s Chance";
  /*
  for (int i = 5; i > 0; i--)
  {
    for (int j = 1; j < 8; j++)
    {
      cout << i * 5 +j-5<<" ";
    }
    cout << "\n";
  }*/
}
void printboardbits()
{
  //system("cls");
  int blankflag = 0;
  cout << "\n        ---------------------------------------------- ";
  for (int i = 4; i >= 0; i--)
  {
    cout << "\n        ";
    cout << i << left << "    |";
    for (int j = 0; j <= 4; j++)
    {
     
        if (((x >> (i * 5 + j)) & 1) == 1)
        {
          cout << "1      |";
     
          blankflag = 1;
        }
      
    
      if (!blankflag)
      {
        cout << "       |";
      }
      blankflag = 0;
    }
    cout << "\n        ---------------------------------------------- ";
  }
  cout << " \n                A        B        C        D        E";

  // cout << "\n Player " << int(chance)+1<<"'s Chance";
   /*
   for (int i = 5; i > 0; i--)
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
   
  x &= ~(1ULL << (no1 * 5 + char1));//reset the old queen to be blank to ensure 
  //arrow can be shot at initial position of queen
  //if it cant we will set this bit again.


   

    if (abs(no3 - no2) > 3 || abs(char3-char2) > 3)
    {
      cout << "greater than 3 distance!";
      x |= 1ULL << (no1 * 5 + char1);
      return 0;
    }
    if (no3 != no2 && char3!=char2)       //test for diagonal if both  x,y changed.
    {
      cout << abs(no3 - no2) << "  " << abs(char3-char2);
      if (abs(no3 - no2) != abs(char3-char2))
      {
        cout << "not diagonal!";
        x |= 1ULL << (no1 * 5 + char1);
        return 0;
      }
      if (no2 < no3)                //moving diagonal up.
      {
        if (char2 < char3) //moving diagonal is going  up and right
        {
          if ((n->masks[no2*5+char2]->y[5][abs(no3 - no2)-1] & x )!= 0)
          {
            cout << "obstacle found tr";
            x |= 1ULL << (no1 * 5 + char1);
            return 0;
          }
        }

        else   //moving diagonal is going to the left
        {
          if ((n->masks[no2*5+char2]->y[4][abs(no3 - no2)-1] & x )!= 0)
          {
            cout << "obstacle found tl";
            x |= 1ULL << (no1 * 5 + char1);
            return 0;
          }
        }
      }
      else 
      {                         // diagonal is going down
        if (char2 < char3) //moving diagonal is going down and right
        {
          if( (n->masks[no2 * 5 + char2]->y[7][abs(no3 - no2) - 1] & x) != 0)
          {
            cout << "obstacle found dr";
            x |= 1ULL << (no1 * 5 + char1);
            return 0;
          }
        }
        else   //moving diagonal is going down and left
        {
          if ((n->masks[no2 * 5 + char2]->y[6][abs(no3 - no2) - 1] & x) != 0)
          {
            cout << "obstacle found dl";
            x |= 1ULL << (no1 * 5 + char1);
            return 0;
          }
        }
      }
    }
    else if (no2 == no3) //player is moving only horizontally
    {
      if (char2 < char3)//player is moving only right
      {
        if ((n->masks[no2 * 5 + char2]->y[3][abs(char3-char2) - 1] & x )!= 0)
        {
          cout << "obstacle found r";
          x |= 1ULL << (no1 * 5 + char1);
          return 0;
        }
      }
      else//player is moving only left
      {
        if ((n->masks[no2 * 5 + char2]->y[2][abs(char3-char2) - 1] & x) != 0)
        {
          cout << "obstacle found l";
          x |= 1ULL << (no1 * 5 + char1);
          return 0;
        }
      }
    }
    else  //player is moving up or down
    {
      if (no2 > no3)
      {
        if ((n->masks[no2 * 5 + char2]->y[1][abs(no3 - no2) - 1] & x) != 0)
        {
          cout << "obstacle found d";
          x |= 1ULL << (no1 * 5 + char1);
          return 0;
        }
      }
      else
      {
        if ((n->masks[no2 * 5 + char2]->y[0][abs(no3 - no2) - 1] & x) != 0)
        {
          cout << "obstacle found t";
          x |= 1ULL << (no1 * 5 + char1);
          return 0;
        }
      }
    }
    get<0>(queens[queenindex]) = char2;
    get<1>(queens[queenindex]) = no2; //move the queen since correct position!!!
    cout << (no1*5+char1);
    //x &= ~(1ULL << (no1*5+char1));//reset the old queen to be blank 
    // make new position filled
    x |= 1ULL << (no2*5+char2);
  
    x |= 1ULL <<( no3* 5 + char3);//shoot an arrow at given position.
    printboard();
    cout << queenindex;
    return 1;                                                                               

}
bool simpletest(string b)
{
  int flag = 0, indexofchar = 0, queenindex = 10,j=0;
  if (b[2] == b[4] && b[3] == b[5])
  {
    cout << "cant shoot arrow on the ground!!!";
    return 0;
  }
  for (j = 0; j <= 4; j+=2) {
    for (int i = 0; i < 5; i++)           //test alphabet as column         
    {
      if (b[j] == a[i])
      {
        flag = 1;
        if (j == 0)
        {
          indexofchar = i;
        }
        break;
      }
    }
    if (flag==0 || !isalpha(b[j]))       //alphabet not between a-e or undefined recall .
    {
      cout << "Enter alphabet please!";
      return 0;
    }

    if (0 > (int(b[j+1]) - 48) || (int(b[j+1]) - 48) > 4) //test second character is a no from 0-4    
    {
      cout << "no2 0-4";
      return 0;
    }
  

  }
  flag = 0;
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
  return 1;
}
int endgame() //returns 0 if game ongoing 1 if player 1 lost 2 if player 2 lost.
{
  int flagp1 = 0,flagp2=0,pos;
  for (int i = 0; i < 4; i++)
  {
    pos = get<1>(queens[i])*5+get<0>(queens[i]);
    for (int j = 0; j < 8; j++)
    {
      if ((n->masks[pos]->y[j][0] & x) == 0)
      {
        if (i < 2)
        {
          flagp1 = 1;
        }
        else
        {
          flagp2 = 1;
        }
        if (flagp1 + flagp2 == 2)
        {
          return 0;
        }
      }

    }
    
  }

  //now test if both players have possible moves
  if (flagp1 + flagp2 == 2)
  {
    return 0;
  }
  else if(flagp1==1)
  {
    return 1;
  }
  else if(flagp2 == 1)
  {
    return 2;
  }

}

int main()
{
  initboard();
  string b;
  /*
  x |= 1ULL<<2;
  x |= 1ULL << 7;
  x |= 1ULL << 8;
  x |= 1ULL << 13;
  x |= 1ULL << 14;
  x |= 1ULL << 4;*/
  for (int i = 0; i < 25; i++)
  {
    cout << ((x >> i)&1U);
  }

  printboard();
  int flag = 0, char1, char2, char3, no1, no2, no3;
  chance = 0;
  while (endgame()==0)
  {
    if (chance == 0)
    {
      while (true)
      {
        do
        {
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
       
        if (inputpos(char1, char2, char3, no1, no2, no3))
        {
          printboardbits();
          cout << "successful";
          cout << chance;
          chance = !chance;
          cout << "new p" << chance;
          break;
        }
      }
    }
  
    else
    {
      while (true)
      {
        do {
          b = "";
          char1 = rand() % 5;
          char2 = rand() % 5;
          char3 = rand() % 5;
          no1 = rand() % 5;
          no2 = rand() % 5;
          no3 = rand() % 5;
          b += a[char1];
          b += '0' + no1;
          b += a[char2];
          b += '0' + no2;
          b += a[char3];
          b += '0' + no3;
          cout << "b is" << b;
        } while (!simpletest(b));
        
        if (inputpos(char1, char2, char3, no1, no2, no3))
        {
          //printboardbits(); print board state for testing only
          cout << "successful";
          cout << chance;
          chance = !chance;
          break;
        }
      }
    }
    
    
  }
  if (endgame()==1)
  {
    cout << "\n the human has somehow won";
  }
  else
  {
    cout << "\n the program has won 01010100 01001111 01001111 00100000 01000101 01000001 01010011 01011001 00001010 ";
  }
  return 0;
}
/*
20 21 22 23 24
15 16 17 18 19
10 11 12 13 14
5  6  7  8  9
0  1  2  3  4
 ypos = get<1>(queens[i]),xpos=get<0>(queens[i]);
    for (int j = 0; j <= 1; j++)
    {
      for (int k= 0; k <= 1; k++)
      {//test all possible one moves top and right first as boundaries max are 4
        cout << "\n topleft stuff" << (min((get<1>(queens[i]) + j), 4) * 5 + min((get<0>(queens[i]) + k), 4));
        if ((xpos*5+ypos)<20 && (xpos*5+ypos+1)%4 !=0) //checks for positions that have both top and right free
        {
          if (x >> ((ypos + j) * 5 + xpos + k) & 1U == 0)
          {//found free position
            if (i < 2)
            {
              flagp1 = 1;
            }
            else
            {
              flagp2 = 1;
            }
          }
        }
        else if (xpos * 5 + ypos < 20)//queen at right boundary
        {//only check top
          if (x >> ((ypos + 1) * 5 + xpos) & 1U == 0)
          {//found free position
            if (i < 2)
            {
              flagp1 = 1;
            }
            else
            {
              flagp2 = 1;
            }
            continue;
          }
      }
        else if ((xpos * 5 + ypos) % 5 != 0)// queen at top boundary
        {

        }
    }
    for (int l = -1; l <= 0; l++)
    {
      for (int m = -1; m <= 0; m++)
      {//test bottom and left now boundaries min is 0
        if (x>>(max((get<1>(queens[i]) + l), 0) * 5 + max((get<0>(queens[i]) + m), 0))& 1U == 0)
        {
          if (i < 2)
          {
            flagp1 = 1;
          }
          else
          {
            flagp2 = 1;
          }
        }
      }
    }
*/
