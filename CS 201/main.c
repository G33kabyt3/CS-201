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
#include "MovieTree.h"
#include <string.h>
#include "MovieStack.h"
#

int main(int argc, const char * argv[]) {
    // insert code here...
   // char string [] = "0000014 \t short \t The Sprinkler Sprinkled \t L'arroseur arrosé \t 0 \t 1895 \t 0 \t 1 \t Comedy,Short";
   // char string [] = "0000010\tshort\tExiting the Factory\tLa sortie de l'usine Lumière à Lyon\t0\t1895\t\N\t1\tDocumentary,Short\t1\t11112011";
    //extractData(string);
   
   // addUserUL("a", "a");
   // addUserUL("b", "b");
    //addUserUL("1", "1");
    //extractCData("0000010\tshort\tExiting the Factory\tLa sortie de l'usine Lumière à Lyon\t0\t1895\t\N\t1\tDocumentary,Short\t1\t11112011");
    //extractCData(string);
    if ( bootDatabase() == 1)
    {
        bootInterface();
        closeDatabase();
    }
        
    
    //printSample();
    
    
    
   
    return 0;
}
