//
//  main.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include <stdio.h>
#include "Interface201.h"
#include "Database.h"
#include "UserList.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    //bootDatabase();
   // char string [] = "0000014 \t short \t The Sprinkler Sprinkled \t L'arroseur arrosé \t 0 \t 1895 \t 0 \t 1 \t Comedy,Short";
    //extractData(string);
    //bootInterface();
    addUserUL("a", "a");
    addUserUL("b", "b");
    addUserUL("1", "1");
    printUsers();
   
    return 0;
}
