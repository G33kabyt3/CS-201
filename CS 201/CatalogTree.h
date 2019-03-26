//
//  CatalogTree.h
//  CS 201
//
//  Created by Trapper Ross on 3/22/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef CatalogTree_h
#define CatalogTree_h
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

struct cNodeData
{
    //Database ID of the title.
    int ID;
    //Type of title.
    char type [20];
    //The primary title.
    //Assuming titles won't run past 200 characters...
    char titleP[500];
    //Original title.
    char titleO[500];
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

struct cNode
{
    struct cNodeData key;
    struct cNode *left;
    struct cNode *right;
    int height;
};

struct cNode* newCNode(struct cNodeData key);
struct cNode* insertC(struct cNode* cNode, struct cNodeData key);
#endif /* MovieTree_h */

#include <stdio.h>
#endif /* CatalogTree_h */
