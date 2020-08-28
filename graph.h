//
//  graph.h
//  HWG-Graphs
//
//  Created by Lute Lillo on 8/4/20.
//  Copyright © 2020 Lute Lillo. All rights reserved.
//

#ifndef graph_h
#define graph_h


typedef struct Vertice Vertice;                         //Struct of nodes of the graph. Vertices and nodes are the same.
typedef struct Edge Edge;                               //Struct of edges between nodes of the graph
typedef struct Friend Friend;

struct Vertice{
    int vertNum;                                        //ID of the vertice
    Vertice *next;                                      //Pointing to next vertice
    Edge *top;                                          //adjacency list
};

struct Edge{
    int src;                                            //Source
    int dest;                                           //Destiny
    int weight;                                         //Value of the bitcoin transaction.
    Edge *next;
};

struct Friend{
  int friendID;                                         //ID of the friend.
  int numberRatings;                                    //Total number of times that some node is getting to the friend.
  int sumRatings;                                       //Total sum of the weights that get to a friend. 
  Friend *next;
};


#endif /* graph_h */
