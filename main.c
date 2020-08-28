//  Bitcoin Graph Recomendation
//  main.c
//  HWG-Graphs
//
//  Created by Lute Lillo on 8/4/20.
//  Copyright © 2020 Lute Lillo. All rights reserved.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define MaxLine 128
int isValidFriend(Vertice* recommended, int idFriend){              //Checks if that friend is not the original friend or in the list.
    Edge* checkingForId = recommended->top;
    if(recommended->vertNum == idFriend){                          //Sees what are the edges of that node and if they are invalids. If they are going back to the given
        return 0;                                                  //node or not. Checks the first one.
    }
    while(checkingForId!=NULL){                                    //Checks for all of them.
        if(checkingForId->dest == idFriend){
            return 0;
        }
        checkingForId = checkingForId->next;
    }
    return 1;                                                      //When returns 1 is Valid.
}

Vertice* findNode(Vertice *node, int v){
    Vertice* temp = node;
    while(temp!= NULL){                                             //You check for all new nodes.
           if(temp->vertNum == v){                                  //If that id was previously created return that node that already exists.
               
               return temp;
           }
           temp = temp->next;                                       //Else, keep traversing.
       }
    
    return NULL;
}

Vertice* addNode(int v)
{
    Vertice* newNode = (Vertice*)malloc(sizeof(Vertice));           //Allocate memory
    newNode->vertNum = v;                                           //Assign id from line into that node, and assign next
    newNode->next = NULL;                                           //to NULL
    newNode->top = NULL;                                            //Assign also the top of the adjency list to NULL.
    return newNode;                                                 //return the new node.
}

Edge* addEdge(int src, int dest, int weight){                       //Creates a new edge between nodes.
    Edge *newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->src = src;                                             //Sets destiny, weigth and source.
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;                                                 //Returns Edge.
}

Vertice* load_graph(){
 
    FILE* get = fopen("ssbca.csv", "r");                            //Open file
    
    char line[MaxLine];
    
    int firstN;                                                     //Temporary variables to store the data read from the file.
    int secondN;
    int tempW;
    Vertice *head = NULL;                                           //head of the linkedlist of vertices.
    
   
    
    while(fgets(line, sizeof(line), get) != NULL){                  //Read lines until file is empty.
        Vertice *reading = (Vertice*)malloc(sizeof(Vertice));
        
        firstN = atoi(strtok(line, ","));                           //Reads first, second and third integer from a line.
        secondN = atoi(strtok(NULL, ","));
        tempW = atoi(strtok(NULL, ","));
        
        
        Vertice *readingSource;                                     //Checks for the First node if it has been created (Uses it) or creates a new one.
        readingSource = findNode(head, firstN);
        if(readingSource == NULL){
            reading = addNode(firstN);
            reading->next = head;                                   //Adds node to Linked list of Nodes.
            head = reading;
                  
        }else{
            reading = readingSource;
        }
        
        Vertice *readingDestiny;
        
        readingDestiny = findNode(head, secondN);                   //Checks for the second node if it has been created (Uses it) or creates a new one.
        if(readingDestiny == NULL){
            
            readingDestiny = addNode(secondN);
            readingDestiny->next = head;                            //Adds node to Linked list of Nodes.
            head = readingDestiny;
        }
        
        Edge* tempEdge;
        
        tempEdge = addEdge(firstN, secondN, tempW);                 //Creates an edge between the nodes of the line and assigns it to the linked list of the edges.
        
        tempEdge->next = reading->top;
        reading->top = tempEdge;
    

    }
    /*
    Vertice* temph = head;
    
    while(temph!=NULL){
        Edge* tempE = temph->top;
        printf("Node source %d -> ", temph->vertNum);
        while(tempE!= NULL){
            printf("%d with weight %d,", tempE->dest, tempE->weight);
            tempE = tempE->next;
        }
        printf("\n");
        temph = temph->next;
    }*/ //Debug: to check that every Node was been assigned correctly.
   
    return head;                                                    //Returns the Node Struct.
}

Friend* createFOF(Friend **group, int value){
    Friend* temp = *group;                                          //Create temporary value to check if Friend of Friend already exists.
    while(temp != NULL){
        if(temp->friendID == value){
            return temp;                                            //If exists return that FOF.
        }
        temp = temp->next;
    }
    
    Friend* newFriend = (Friend*)malloc(sizeof(Friend));           //If not, create newFriend and initialize its variables.
    newFriend->friendID = value;
    newFriend->numberRatings = 0;
    newFriend->sumRatings = 0;
    
    
    newFriend->next = *group;                                      //Then, update the big group of friends (and that's why is a **) and set the new Friend to the group.
    *group = newFriend;
    return newFriend;
}

Friend* findBest(Friend* group){                                    //Finds the best recommendationn based in the inital node that was input.
    Friend* sendBest = group;                                       //Friend struct that has the best recommendation.
    Friend* forThisGroup = group;
    int best = 0;
    
    while(forThisGroup!=NULL){                                       //Is checking if for that group of friends there is a better option.
        int getAVG = (forThisGroup->sumRatings / forThisGroup->numberRatings);
        if(getAVG > best){                                           //If there is, just updates the best.
            best = getAVG;
            sendBest = forThisGroup;
        }
        forThisGroup = forThisGroup->next;                           //If not, keeps looking for it.
    }
    return sendBest;                                                 //Returns the best.
}

void makeRecommendation(int in, Vertice* head){                      //Based on the given node, checks what's the best recommendation a friend of a friend can give.
    
    Vertice* recommend = (Vertice*)malloc(sizeof(Vertice));
    recommend = findNode(head, in);                                 //Finds if that given node exists.
        
    if(recommend == NULL){                                          //If not, is invalid.
        printf("Invalid ID\n");
        return;
    }
    Edge* friendsEdge = (Edge*)malloc(sizeof(Edge));                //Now checks the edges of that friend.
    friendsEdge = recommend->top;
    if(friendsEdge == NULL){                                        //If has no primary friends, it returns.
        printf("I'm sorry but this ID has no friends.\n");
        return;
    }
    
    Friend* groupOfFriends = NULL;                                  //Creates the big group of friends based on that given node.
    
    while (friendsEdge != NULL){                                    //For all of the edges of that given friend...
        if(friendsEdge->weight > 0){                                //If the weight is positive:
            Vertice* getFriend = (Vertice*)malloc(sizeof(Vertice));
            getFriend = findNode(head, friendsEdge->dest);          //Gets a friend of the given node and...
            Edge* forThatFriend = (Edge*)malloc(sizeof(Edge));
            forThatFriend = getFriend->top;                         //Gets the adjency list for that friend.
            
            if(forThatFriend == NULL){                              //If has no Friends return.
                printf("That user has no friends of friends\n");
                return;
            }
            
            while(forThatFriend!=NULL){                             //If it has, looks through all of them.
                if(forThatFriend->weight > 0 && (isValidFriend(recommend, forThatFriend->dest)==1)){            //When it is valid (Explained in the valid function)
                    Friend* getFriendValues = createFOF(&groupOfFriends, forThatFriend->dest);                  //Creates a friend of a friend and gets the data.
                    getFriendValues->sumRatings += forThatFriend->weight;                                       //Updates it to check later the average of weights
                    getFriendValues->numberRatings++;                                                           //that points to that specific friend of a friend.
               
                }
                
                forThatFriend = forThatFriend->next;                                    //Keeps looking in the loop.
              
            }
        }
        friendsEdge = friendsEdge->next;
        
                
    }
        
    
    Friend* bestRecommendation = findBest(groupOfFriends);                                      //What's the best recommendation?
    printf("The best recommendation for this Friend is: %d\n", bestRecommendation->friendID);     //Prints it to the console.
}


int main(int argc, const char * argv[]) {
    Vertice* start;
    start = load_graph();
    printf("Let's try a recommendation. What user should we ask?\n");       //Lets get the given node to start the recommendation
    int input;                                                                  //Ask the user for a starting given node.
    scanf("%d", &input);
    makeRecommendation(input, start);
    return 0;
}
