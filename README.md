# BitcoinCashRecomendation
Bitcoin cash value recommendation based in positive ratings users gave to other users created for CS305 Data Structures UP written in the C language.

DESCRIPTION

All users, called friends, are connected throughout a graph structure, their edges are values (ratings) that they are giving to other users.
The program will accept an integer that represents an ID of a friend as an input in the console.
Based on that ID the program will find it first and then traverse all of his so called "friends of friends", every other user in the graph that is friend with a friend of the ID that was used as an input, looking for the highest positive value.
Once it gets that rating the program will recommend that friend of a friend by writting its ID into the console.

HOW TO PLAY

  1. Download files: main.c, graph.h and ssbca.csv.
  2. Go into your terminal and compile using the command: gcc -o bitcoin main.c 
  **As a pre-requiste you are required to have installed a C or C++ compiler in order to complete the compilation**
  3. Type: ./bitcoin
  4. Input the friend ID from what you want to get your recommendation. 
  5. Every time you want to get a recommendation JUST repeat step number 3 and 4.
