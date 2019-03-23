//
//  MovieTree.h
//  CS 201
//
//  Created by Trapper Ross on 3/17/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef MovieTree_h
#define MovieTree_h

#include <stdio.h>

struct mNodeData
{
    //Database ID of the title.
    int ID;
    //Type of title.
    char type [20];
    //The primary title.
    //Assuming titles won't run past 200 characters...
    char titleP[200];
    //Original title.
    char titleO[200];
    //0 for isn't, 1 for is.
    int isAdult;
    //Year the title started.
    int startYear;
    //Year the title ended.
    int endYear;
    //Runtime in minutes.
    int runtime;
    //Genre of the title.
    char genre [40];
};

struct mNode {
    //Attributes for AVL tree.
    struct mNode * left;
    struct mNode * right;
    int weight;
    struct mNodeData *data;
};
#endif /* MovieTree_h */
