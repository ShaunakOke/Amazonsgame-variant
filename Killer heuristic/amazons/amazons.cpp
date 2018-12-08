// killerheuristicgame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//ShaunakOke 18204307

#include "pch.h"
#include <iostream>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
using namespace std;
uint64_t x,temp;
vector<tuple<int, int,bool>> queens;
int actual;
bool chance=0;
int counter = 0;
bool killerflag = 1;//set for killer heuristic.

char a[] = { 'A', 'B', 'C', 'D', 'E' };
//masks
struct avail
{
public:
   int value;
    uint64_t y[8][3];
    avail **masks;
};
//nodes of gametree
struct node
{
public:
  uint64_t board;
  int eval,arrowpos;
  vector<node*>child;
  vector<tuple<int, int, bool>> queensnodes;
};

vector<tuple<node*, int>> cutoffarr;
avail *n = new avail;
//initialize starting masks and queen positions
void initboard()
{
  n->masks = new avail*[25];
  int row, column;
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
    column = i % 5;
    row = i / 5;
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
//check if queen at i,j
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
//print square ascii board representation
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
//debugging board bits ascii
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

/*this format used everywhere.n->masks[position]->y[j][magnitude] is format.

20 21 22 23 24
15 16 17 18 19
10 11 12 13 14
5  6  7  8  9
0  1  2  3  4
pos is the corresponding no. on board
j=0top j=1bottom j=2left 3right 4topleft 5topright 6bottomleft 7bottomright*/
//check user input according to board AND move the board positions
bool inputpos(int char1, int char2,int char3,int no1,int no2,int no3)
{
  cout << a[char1] << no1 << a[char2] << no2 << a[char3] << no3 << "\n";
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
//check user input 
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
//check who won and if game has ended
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
//find eval of any node,m means which player
int evalfn(node* e,bool m)
{
  int it, till;
  if (m)
  {
    it = 2;
    till = 3;
  }
  else
  {
    it = 0;
    till = 1;
  }
  
  int char1, char2, char3, no1, no2, no3, factor = 50, sum = 0, pos;
  for (int i = 0; i < 4; i++)
  {
    char1 = get<0>(e->queensnodes[i]);
    no1 = get<1>(e->queensnodes[i]);
    pos = no1 * 5 + char1;
    if (pos < 5)//lower row
    {
      factor -= 50;
    }
    if (pos > 19)//higher row
    {
      factor -= 50;
    }
    if (pos % 5 == 0)//left side
    {
      factor -= 50;
    }
    if ((pos - 1) % 5 == 0)//right side
    {
      factor -= 50;
    }
    int free = 0;
    for (int j = 0; j < 8; j++)
    {
      if ((n->masks[pos]->y[j][0] & e->board) == 0)
      {
        free++;//degrees of freedom
      }
    }
    if (free == 0)
    {
      factor -= 600;
    }
    factor += 40 * free;
    if (i != it & i != till)
    {//opponents queen;
      factor *= -1;
    }
    sum += factor;
    factor = 0;
  }
  sum = sum + 100+(rand() % 50);
  //cout << "\n eval is:" << sum;
  return sum;
}
//generate gametree for each programs's chance


tuple<node*, int> gentree(node *z, int limit, bool maxing, int achievable, int hope)
{
  int char1 = 5, char2 = 5, char3 = 5, no1 = 5, no2 = 5, no3 = 5, countb = 0, flag = 0, quind = 10;

  if (limit == 0)
  {
    return make_tuple(z, evalfn(z, maxing));
  }
  int  i, till, temp, score = 0;
  if (maxing)
  {
    score = -30000;
    i = 2;
    till = 3;
  }
  else
  {
    score = +30000;
    i = 0;
    till = 1;
  }

  while (i <= till)
  {

    for (int j = 0; j < 8; j++)
    {

      if ((n->masks[get<1>(z->queensnodes[i]) * 5 + get<0>(z->queensnodes[i])]->y[j][0] & z->board) == 0)
      {
        flag = 1;
        break;
      }
    }
    i++;
  }

  if (flag == 0)// no moves possible  for any queen shouldn't be called normally.
  {
    return make_tuple(z, evalfn(z, maxing));

  }
  if (maxing)
  {
    score = -30000;
    i = 2;
    till = 3;
  }
  else
  {
    score = +30000;
    i = 0;
    till = 1;
  }
  node* selected = new node;
  while (i <= till)
  { //pick right queen at each height.
    char1 = get<0>(z->queensnodes[i]);
    no1 = get<1>(z->queensnodes[i]);
    quind = i;
    for (int j = 0; j < 8; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        if (((n->masks[no1 * 5 + char1]->y[j][k]) & z->board) == 0)
        {
          flag = 1;
          if (j == 0)
          {
            no2 = no1 + k + 1;
            char2 = char1;
          }
          else if (j == 1)
          {
            no2 = no1 - k - 1;
            char2 = char1;
          }
          else if (j == 2)
          {
            no2 = no1;
            char2 = char1 - k - 1;
          }
          else if (j == 3)
          {
            no2 = no1;
            char2 = char1 + k + 1;
          }
          else if (j == 4)
          {
            no2 = no1 + k + 1;
            char2 = char1 - k - 1;
          }
          else if (j == 5)
          {
            no2 = no1 + k + 1;
            char2 = char1 + k + 1;
          }
          else if (j == 6)
          {
            no2 = no1 - k - 1;
            char2 = char1 - k - 1;
          }
          else if (j == 7)
          {
            no2 = no1 - k - 1;
            char2 = char1 + k + 1;
          }
          if (no2 > 4 || char2 > 4 || no2 < 0 || char2 < 0)
          {

            continue;
          }
          z->board &= ~(1ULL << (no1 * 5 + char1));
          for (int l = 0; l < 8; l++)
          {
            for (int m = 0; m < 3; m++)
            {
              if ((n->masks[no2 * 5 + char2]->y[l][m] & z->board) == 0)
              {

                if (l == 0)
                {
                  no3 = no2 + m + 1;
                  char3 = char2;
                }
                else if (l == 1)
                {
                  no3 = no2 - m - 1;
                  char3 = char2;
                }
                else if (l == 2)
                {
                  no3 = no2;
                  char3 = char2 - m - 1;
                }
                else if (l == 3)
                {
                  no3 = no2;
                  char3 = char2 + m + 1;
                }
                else if (l == 4)
                {
                  no3 = no2 + m + 1;
                  char3 = char2 - m - 1;
                }
                else if (l == 5)
                {
                  no3 = no2 + m + 1;
                  char3 = char2 + m + 1;
                }
                else if (l == 6)
                {
                  no3 = no2 - m - 1;
                  char3 = char2 - m - 1;
                }
                else if (l == 7)
                {
                  no3 = no2 - m - 1;
                  char3 = char2 + m + 1;
                }

                if (no3 > 4 || char3 > 4 || no3 < 0 || char3 < 0 || (char3 == char2 && no3 == no2))
                {
                  continue;
                }
                node *c = new node;
                for (int p = 0; p < 4; p++)
                {
                  if (p != quind)
                  {
                    c->queensnodes.emplace_back(get<0>(z->queensnodes[p]), get<1>(z->queensnodes[p]), get<2>(z->queensnodes[p]));
                    //copy all queens except the ones moved
                  }
                  else
                  {
                    c->queensnodes.emplace_back(char2, no2, get<2>(z->queensnodes[p]));
                  }

                }
                counter++;
                c->board = z->board;
                c->board &= ~(1ULL << (no1 * 5 + char1));
                c->board |= 1ULL << (no2 * 5 + char2);
                c->board |= 1ULL << (no3 * 5 + char3);
                c->arrowpos = no3 * 5 + char3;
                c->eval = evalfn(c, maxing);
                //cout <<"\n"<<c->arrowpos<< "arrowpos"<<char1<<no1<<char2<<no2<<char3<<no3;
                z->child.emplace_back(c);

                countb++;
                auto ag = (gentree(z->child.back(), limit - 1, !maxing, achievable, hope));
                temp = get<1>(ag);
                selected = get<0>(ag);
                if (maxing)
                {
                  score = max(score, temp);
                  achievable = max(achievable, score);
                  selected = z->child.back();
                }
                else
                {
                  score = min(score, temp);
                  hope = min(hope, score);
                  selected = z->child.back();
                }
                if (achievable >= hope)
                {
                  z->board |= (1ULL << (no1 * 5 + char1));
                  return make_tuple(c, score);
                  if (killerflag == 1 && maxing)
                  {
                    int cf = 0;
                    for (int g = 0; g < cutoffarr.size(); g++)
                    {
                      if (get<0>(cutoffarr[g])->board == c->board)
                      {
                        cf = 1;
                        get<1>(cutoffarr[g]) += 1;
                      }
                    }
                    if (cf == 0)
                    {
                      cutoffarr.emplace_back(c, 0);
                    }
                  }
                  //break;
                }
              }

            }
          }


          z->board |= (1ULL << (no1 * 5 + char1));//add removed queen used for testing purposes.


        }

      }
    }
    i++;
  }

  if (killerflag == 0 || cutoffarr.size() == 0)
  {
    return make_tuple(selected, score);
  }
  else
  {
    
    node *max = new node;
    max = get<0>(cutoffarr[0]);
    for (i = 0; i < cutoffarr.size()-2; i++)
    {
      if (get<1>(cutoffarr[i]) < get<1>(cutoffarr[i + 1]))
      {
        max = get<0>(cutoffarr[i + 1]);
     }
    }
    counter++;
    return make_tuple(max, evalfn(max, maxing));
  
  }
}
node* traverse(node* root, node* target)
{//messy code but works for depth 3
  int flag = 0;
  
  for (int i = 0; i < root->child.size(); i++)
  {
    if (root->child[i] == target)
    {
      return root->child[i];
    }
    else
    {
      for (int j = 0; j < root->child[i]->child.size(); j++)
      {
        if (root->child[i]->child[j]==target)
        {
          return root->child[i];
        }
        else
        {
          for (int k = 0; k < root->child[i]->child[j]->child.size(); k++)
          {
            if (root->child[i]->child[j]->child[k] == target)
            {
              return root->child[i];
              flag = 1;
            }
            
          }
        }
      }
    }
    if (flag)//unexpected for safekeeping.
    {
      return root->child[0];
   }
  }
}

//call everything
//note indexes 0,1 are always players queens(hardcoded)
//2,3 are programs.
int main()
{
  initboard();
  string b;
 
  for (int i = 0; i < 25; i++)
  {
    cout << ((x >> i)&1U);
  }

  printboard();
  int flag = 0, char1, char2, char3, no1, no2, no3;
  chance = 0;
  while (endgame() == 0)
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
          //printboardbits();
          cout << "successful";
          cout << chance;
          chance = !chance;
          cout << "new p" << chance;
          b = "";
          break;
        }
      }
    }
    else
    {
      printboardbits();
      node *start = new node;
      start->board = x;
      for (int i = 0; i < 4; i++)
      {
        start->queensnodes.emplace_back(get<0>(queens[i]), get<1>(queens[i]), get<2>(queens[i]));
        cout << "\n"<<get<0>(start->queensnodes[i]);
      }
      node *ab = new node;
      actual = 3;
      killerflag = 1;
      ab = get<0>(gentree(start, actual,true,-34000,34000));
      cout << "ok";
      int quind,as=0;
      if (killerflag == 1)
      {
      ab=traverse(start,ab);//works for depth 3
      }
      cout << "counter" << counter++;
      for (int i = 2; i < 4; i++)
      {
        if (get<0>(queens[i]) != get<0>(ab->queensnodes[i])
          || get<1>(queens[i]) != get<1>(ab->queensnodes[i]))
        {
          //find which queen was moved
          quind = i;
          char1 = get<0>(start->queensnodes[i]);
          char2 = get<0>(ab->queensnodes[i]);
          char3 = ab->arrowpos % 5;
          no1 = get<1>(start->queensnodes[i]);
          no2 = get<1>(ab->queensnodes[i]);
          no3 = ab->arrowpos / 5;
          
          as = 1;
        }


      }
      if (as == 0)
      {
        //no queen moved error testing condition.
        return 0;
      }
      b.clear();
      b += a[char1];
      b += '0' + no1;
      b += a[char2];
      b += '0' + no2;
      b += a[char3];
      b += '0' + no3;
      cout << "b is" << b;
      if (inputpos(char1, char2, char3, no1, no2, no3))
       {
       
        printboardbits();// print board state for testing only
        get<0>(queens[quind]) = get<0>(ab->queensnodes[quind]);
        get<1>(queens[quind]) = get<1>(ab->queensnodes[quind]);
        cout << "successful";
        
        chance = !chance;
        cout << chance;
        counter = 0;
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
*/
