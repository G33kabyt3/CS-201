//
//  UserTree.h
//  CS 201
//
//  Created by Trapper Ross on 3/22/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#ifndef UserTree_h
#define UserTree_h

#include <stdio.h>
struct UNode
{
    char key [100];
    struct UNode *left;
    struct UNode *right;
    int height;
};
#endif /* UserTree_h */
