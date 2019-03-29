//
//  Database.c
//  CS 201
//
//  Created by Trapper Ross on 2/27/19.
//  Copyright © 2019 Trapper Ross. All rights reserved.
//

#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "MovieTree.h"
#include <dirent.h>
#include <unistd.h>
#include "MovieStack.h"
//#include <literally_every_C_library.h>
/*
 * MAKE SURE YOU BOOT THE DATABASE BEFORE USING ANY OF THESE FUNCTIONS. Some of these are dependent on others.
 * I can neither confirm nor deny its resemblence to a certain type of pasta. But that's what you get in a non-OOP langugue. (Not really, but shhhh.)
 *
 */
FILE* userFile;
FILE* movieFile;
//Movie tree
Tree mTree;
//Catalog tree
Tree cTree;

/*
 *
 * Required functions and structs for Movie Tree
 *
 */
//Data required for movie database.
typedef struct mNodeData
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
} *mNodeData;

//Data required for catalog.
typedef struct cNodeData
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
    //Media Type. 0 for digital, 1 for DVD, 2 for blueray.
    int mediaType;
    //Data aquired in format MM/DD/YYYY. The digits are stored in the array.
    char date[9];
    
}*cNodeData;

//Comparison for movie data by key. Read throught the function before use.
int compM (void *a1, void *a2)
{
     //This "casts" the void pointers to be type mNodeData from my understanding.
     //This means that if this function is used for a tree that doesn't use this data, IT WILL NOT WORK!
    //So if anybody else is using these, be careful.
    mNodeData nd1 = (mNodeData) a1;
    mNodeData nd2 = (mNodeData) a2;
    //Now we compare. I know I'm using strcmp, but I know I null terminated these string because (my program) null terminated them.
    //And the program doesn't work if I use strncmp and a string length. I may try and fix it later, but for now y'all just going
    //to have to give me quiet looks of disapproval and finger waggles. Or fail me. But please don't do that.
    
    if (strcmp(nd1->titleP, nd2->titleP) <0) {
        return -1;
    } else if (strcmp(nd1->titleP, nd2->titleP) >0) {
        return +1;
    } else {
        if (nd1->ID< nd2->ID)
        {
            return -1;
        } else if (nd1->ID> nd2->ID){
            return 1;
        } else{
            return 0;
        }
    }
}

//Comparison for catalog data by key. Read throught the function before use.
int compC (void *a1, void *a2)
{
    //This "casts" the void pointers to be type cNodeData from my understanding.
    //This means that if this function is used for a tree that doesn't use this data, IT WILL NOT WORK!
    //So if anybody else is using these, be careful.
    cNodeData nd1 = (cNodeData) a1;
    cNodeData nd2 = (cNodeData) a2;
    //Now we compare.
    if (strcmp(nd1->titleP, nd2->titleP) <0) {
        return -1;
    } else if (strcmp(nd1->titleP, nd2->titleP) >0) {
        return +1;
    } else {
        //If we get the same title, compare by ID.
        if (nd1->ID< nd2->ID)
        {
            return -1;
        } else if (nd1->ID> nd2->ID){
            return 1;
        } else{
            return 0;
        }
    }
}
int compQC(void *a1, char * string)
{
    if( a1 == NULL)
    {
        return 0;
    }
     cNodeData nd1 = (cNodeData) a1;
    if (strncmp(nd1->titleP, string, strlen(string)) <0) {
        return -1;
    } else if (strncmp(nd1->titleP, string, strlen(string)) >0) {
        return +1;
    } else {
        return 0;
    }
}

int compQM(void *a1, char * string)
{
    if( a1 == NULL)
    {
        return -2;
    }
    mNodeData nd1 = (mNodeData) a1;
    if (strncmp(nd1->titleP, string, strlen(/*nd1->titleP*/ string)) <0) {
        return -1;
    } else if (strncmp(nd1->titleP, string, strlen(/*nd1->titleP*/ string)) >0) {
        return +1;
    } else {
        return 0;
    }
}


void printM (void *a) {
    mNodeData nd = (mNodeData) a;
    printf("%i \t" , nd->ID);
    printf("%s \t" , nd->type);
    printf("%s \t" , nd->titleP);
    printf("%s \t" , nd->titleO);
    printf("%i \t" , nd->isAdult);
    printf("%i \t" , nd->startYear);
    printf("%i \t" , nd->endYear);
    printf("%i \t" , nd->runtime);
    printf("%s \t" , nd->genre);
}
void printC (void *a) {
    cNodeData nd = (cNodeData) a;
    printf("%i \t" , nd->ID);
    printf("%s \t" , nd->type);
    printf("%s \t" , nd->titleP);
    printf("%s \t" , nd->titleO);
    printf("%i \t" , nd->isAdult);
    printf("%i \t" , nd->startYear);
    printf("%i \t" , nd->endYear);
    printf("%i \t" , nd->runtime);
    printf("%s \t" , nd->genre);
    //Print out media type
    switch (nd->mediaType)
    {
        case 0:
            printf("Digital\t");
            break;
        case 1:
            printf("DVD\t");
            break;
        case 2:
            printf("BluRay\t");
    }
    printf("%c" , nd->date[0]);
    printf("%c" , nd->date[1]);
    printf("/");
    printf("%c" , nd->date[2]);
    printf("%c" , nd->date[3]);
    printf("/");
    printf("%c", nd->date[4]);
    printf("%c", nd->date[5]);
    printf("%c", nd->date[6]);
    printf("%c\n", nd->date[7]);
}


/*
 * Creation, selections, printing, logout, and deletion of users.
 *
 */

// Takes a username, creates a file for it.
int createUser(char username[50])
{
    //Path shouldn't be more than 75 due to the fact the functions take an array of size 50.
    char path [75] = "UserData/";
    strcat(path, username);
    strcat(path, ".log");
    userFile = fopen(path, "r");
    if(access(path, F_OK ) != -1) {
        printf("User already exists!\n");
        return 0;
    }
    userFile = fopen(path, "w+");
    if (userFile == NULL)
    {
        printf("User file not found!\n");
        return 0;
    }
    return 1;
}

// Takes a username, sets the current user file to that user.
int chooseUser(char username[50])
{
    char path [75] = "UserData/";
    strncat(path, username, 75);
    strncat(path, ".log", 75);
    userFile = fopen(path, "r+");
    if (userFile == NULL)
    {
        printf("User file not found!\n");
        return 0;
    }
    return 1;
}

int printUsers ()
{
    struct dirent *subdir;
    DIR *dir;
    dir = opendir("./UserData");
    if (dir)
    {
        subdir = readdir(dir);
        subdir = readdir(dir);
        while ((subdir = readdir(dir)) != NULL)
        {
            printf("%s\n", subdir->d_name);
        }
        closedir(dir);
    }
    return(0);
}

void logOutUser()
{
    fclose(userFile);
    userFile = NULL;
}

int deleteUser(char username[50])
{
    char path [75] = "UserData/";
    strncat(path, username, 75);
    strncat(path, ".log", 75);
    int success = remove(path);
    return success;
}







/*
 *
 * Extractions functions. They take a string, turn it into the appropriate data struct. They take advantage of how the data is formated to know what data
 * will end up where and how far it needs to read. THEY RETURNS MEMORY BLOCKS THAT NEEDS TO BE FREED!
 *
 */


mNodeData extractMData(char movieString [] ){
    
    mNodeData temp = malloc(sizeof(struct mNodeData));
    char delim = '\t';
    int j=0;
    long entryLength = strlen(movieString);
    //Using a for loop to keep track of what part of the entry we are on.
    for (int i = 0; i < 9; i++ )
    {
        char token [entryLength];
        int sep =0;
        while (j < entryLength && movieString[j] != delim)
        {
            token[sep] = movieString[j];
            j++;
            sep++;
        }
        token [sep] = '\0';
        j++;
        switch (i){
            case 0:
                memmove(&token[0], &token[1], strlen(token));
                memmove(&token[0], &token[1], strlen(token));
                // printf("%s ", token);
                temp->ID = atoi (token);
                break;
            case 1: strcpy(temp->type, token);
                // printf("%s ", token);
                break;
            case 2: strcpy(temp->titleP, token);
                // printf("%s \n", token);
                break;
            case 3: strcpy(temp->titleO, token);
                // printf("%s ", token);
                break;
            case 4: temp->isAdult = atoi (token);
                // printf("%s ", token);
                break;
            case 5: temp->startYear = atoi(token);
                //  printf("%s ", token);
                break;
            case 6: temp->endYear = atoi (token);
                // printf("%s ", token);
                break;
            case 7: temp->runtime = atoi (token);
                //printf("%s ", token);
                break;
            case 8: strcpy(temp->genre, token);
                //printf("%s\n", token);
                break;
        }
    }
    return temp;
}

cNodeData extractCData(char movieString [])
{
    cNodeData temp = malloc(sizeof(struct cNodeData));
    char delim = '\t';
    int j=0;
    long entryLength = strlen(movieString);
    //Using a for loop to keep track of what part of the entry we are on.
    for (int i = 0; i < 11; i++ )
    {
        char token [entryLength];
        int sep =0;
        while (j < entryLength && movieString[j] != delim)
        {
            token[sep] = movieString[j];
            j++;
            sep++;
        }
        token [sep] = '\0';
        j++;
        switch (i){
            case 0:
                temp->ID = atoi (token);
                break;
            case 1: strcpy(temp->type, token);
                
                break;
            case 2: strcpy(temp->titleP, token);
                
                break;
            case 3: strcpy(temp->titleO, token);
                
                break;
            case 4: temp->isAdult = atoi (token);
                
                break;
            case 5: temp->startYear = atoi(token);
                
                break;
            case 6: temp->endYear = atoi (token);
                
                break;
            case 7: temp->runtime = atoi (token);
                
                break;
            case 8: strcpy(temp->genre, token);
                break;
            case 9:
                temp->mediaType = atoi(token);
                break;
            case 10:
                strcpy(temp->date, token);
                break;
        }
    }
    
    return temp;
}

/*
 *
 * Functions for loading the user file into memory (The AVL tree), and loading the memory back into the file
 *
 */

//Converting a node's data into a line of data in the user file.
int addMovieToFile(struct cNodeData data)
{
    if (userFile == NULL)
    {
        return 0;
    }
    
    //add to user file.
    fprintf(userFile, "%i\t", data.ID);
    fprintf(userFile, "%s\t" , data.type);
    fprintf(userFile, "%s\t" , data.titleP);
    fprintf(userFile,"%s\t" , data.titleO);
    fprintf(userFile,"%i\t" , data.isAdult);
    fprintf(userFile,"%i\t" , data.startYear);
    fprintf(userFile,"%i\t" , data.endYear);
    fprintf(userFile,"%i\t" , data.runtime);
    fprintf(userFile,"%s\t" , data.genre);
    fprintf(userFile,"%i\t" , data.mediaType);
    fprintf(userFile,"%s\n" , data.date);
    
    return 1;
}


void loadMovies()
{
    // Max length of file line to read.
    int maxLength = 500;
    // Temporary string variable.
    char curLine [maxLength];
    while (fgets(curLine, maxLength, movieFile) != NULL)
    {
        Tree_Insert(mTree, extractMData(curLine));
    }
}

/*
 *
 * Functions working on a single node.
 *
 */
Stack mTree_Query (Tree T, char* string)
{
    //Stack for node data
    Stack S = Stack_New();
    Node node = T-> root;
    //Runs down the tree searching for first match.
    while (node != NULL)
    {
        if (compQM(node->data, string) <0)
        {
            node = node->right;
        } else if (compQM(node->data, string)>0)
        {
            node = node->left;
        } else
        {
            Push(S, node);
            (mTree->print)(node->data);
            Node temp =Tree_NextNode(T, node);
            while (compQM(temp->data, string) ==0)
            {
                Push(S, temp);
                (mTree->print)(temp->data);
                temp = Tree_NextNode(T, temp);
                
            }
            temp = Tree_PrevNode(T, node);
            while (compQM(temp->data, string) ==0)
            {
                Push(S, temp);
                (mTree->print)(temp->data);
                temp = Tree_PrevNode(T, temp);
            }
            //Call recursive function on both children to scan for matches.
            return S;
        }
    }
    return NULL;
}

Stack cTree_Query (Tree T, char* data)
{
    //Stack for node data
    Stack S = Stack_New();
    Node node = T-> root;
    //Runs down the tree searching for first match.
    while (node != NULL)
    {
        if (compQC(node->data, data) <0)
        {
            node = node->left;
        } else if (compQC(node->data, data)>0)
        {
            node = node->right;
        } else
        {
            Push(S, node->data);
            Node temp =Tree_NextNode(T, node);
            while (compQC(temp->data, data) ==0)
            {
                Push(S, temp);
                temp = Tree_NextNode(T, temp);
            }
            temp = Tree_PrevNode(T, node);
            while (compQC(temp->data, data) ==0)
            {
                Push(S, temp);
                temp = Tree_PrevNode(T, temp);
            }
            //Call recursive function on both children to scan for matches.
            return S;
        }
    }
    return NULL;
}

Stack searchMovies(char* title)
{
    Stack S = Stack_New();
    //Longest title is 196 characters, + 1 null space = 197, so the maximum length the arrays should need to be is...
    char title_A [197+2];
    char title_THE [197+4];
    char title_AN [197+3];
    //If the user SPECIFICALLY CHOOSES to begin their search with an article, they clearly wanted it there. So we keep the title.
    if (strncmp(title,"The ", strlen("The ")) || strncmp(title,"A ", strlen("A ")) || strncmp(title,"An ", strlen("An ")) == 1)
    {
        Stack temp =mTree_Query(mTree, title);
        return temp;
    } else {
        strcat(title_A, "A ");
        strcat(title_AN, "An ");
        strcat(title_THE,"The " );
        //This, on the otherhand... best to be safe.
        strncat(title_A, title, strlen(title_A));
        strncat(title_THE, title, strlen(title_A));
        strncat(title_AN, title, strlen(title_A));
        // Get the stacks of the result of each...
        Stack temp =mTree_Query(mTree, title);
        Stack temp_A = Stack_New();
        Stack temp_THE = Stack_New();
        Stack temp_AN = Stack_New();
        temp_A = mTree_Query(mTree, title_A);
        temp_THE = mTree_Query(mTree, title_THE);
        temp_AN = mTree_Query(mTree, title_AN);
        
        while(Peek(temp_A)!= NULL)
        {
            Push(temp, Pop(temp_A));
        }
        while(Peek(temp_THE)!= NULL)
        {
            Push(temp, Pop(temp_THE));
        }
        while(Peek(temp_AN)!= NULL)
        {
            Push(temp, Pop(temp_AN));
        }
    }
    return S;
}
Stack searchCatalog(char* title)
{
    Stack S = Stack_New();
    //Longest title is 196 characters, + 1 null space = 197, so the maximum length the arrays should need to be is...
    char title_A [197+2];
    char title_THE [197+4];
    char title_AN [197+3];
    //If the user SPECIFICALLY CHOOSES to begin their search with an article, they clearly wanted it there. So we keep the title.
    if (strncmp(title,"The ", strlen("The ")) || strncmp(title,"A ", strlen("A ")) || strncmp(title,"An ", strlen("An ")) == 0)
    {
        Stack temp =cTree_Query(cTree, title);
        return temp;
        //If not, we check all the articles that could be at the start.
    } else {
        //Pointless to use strncat... we know it won't overflow.
        strcat(title_A, "A ");
        strcat(title_AN, "An ");
        strcat(title_THE,"The " );
        //This, on the otherhand... best to be safe.
        strncat(title_A, title, strlen(title_A));
        strncat(title_THE, title, strlen(title_A));
        strncat(title_AN, title, strlen(title_A));
        // Get the stacks of the result of each...
        Stack temp =cTree_Query(cTree, title);
        Stack temp_A = Stack_New();
        Stack temp_THE = Stack_New();
        Stack temp_AN = Stack_New();
        temp_A = cTree_Query(cTree, title_A);
        temp_THE = cTree_Query(cTree, title_THE);
        temp_AN = cTree_Query(cTree, title_AN);
        
        while(Peek(temp_A)!= NULL)
        {
            Push(temp, Pop(temp_A));
        }
        while(Peek(temp_THE)!= NULL)
        {
            Push(temp, Pop(temp_THE));
        }
        while(Peek(temp_AN)!= NULL)
        {
            Push(temp, Pop(temp_AN));
        }
    }
    return S;
}

//Little wrapper for deleting from the cTree. We won't be deleting from the mTree.
void deleteC(Node n)
{
    Tree_DeleteNode(cTree, n);
}
void addMovieToCatalog(struct mNodeData data, int media, char dateArray[9])
{
    struct cNodeData temp;
    temp.ID = data.ID;
    strncpy (temp.type, data.type, strlen(temp.type));
    strncpy(temp.titleP, data.titleP, strlen(temp.titleP));
    strncpy(temp.titleO, data.titleO, strlen(temp.titleP));
    temp.isAdult = data.isAdult;
    temp.startYear = data.startYear;
    temp.endYear = data.endYear;
    temp.runtime = data.runtime;
    strncpy(temp.genre, data.genre, strlen(temp.genre));
    temp.mediaType =media;
    strncpy(temp.date, dateArray, strlen(temp.date));
    Tree_Insert(cTree, &temp);
}


/*
 *
 *Functions for when the app closes, like saving the catalog currently in memory, and freeing the tree.
 *
 */
// Recursive Function for save catalog.
int saveCatalogR(Node node)
{
    if (node == NULL)
    {
        return 1;
    }
    return  addMovieToFile(*(cNodeData)node->data) || saveCatalogR(node->left)|| saveCatalogR(node->right);
    
}

// Saves the tree to the user file.
int saveCatalog()
{
    Node root = Tree_FirstNode(cTree);
    if(root== NULL)
    {
        return 1;
    }
    struct cNodeData temp = *(cNodeData)root->data;
    return addMovieToFile(temp) || saveCatalogR(root->left)|| saveCatalogR(root->right);;
    
    
}

//Recursive function for freeing tree.
void freeTreeR(Node node)
{
    if(node!= NULL)
    {
        freeTreeR(node->left);
        freeTreeR(node->right);
        free(node->data);
        free(node);
    }
}

//Frees the tree from memory.
void freeTree(Tree tree)
{
    Node root = tree->root;
    if(root!= NULL)
    {
        freeTreeR(root->left);
        freeTreeR(root->right);
        free(root->data);
        free(root);
        free(tree);
    }
}


/*Stack searchTreeM(char * name)
{
    Stack S = Stack_New();
    Tree T = mTree;
    Tree_SearchNode(T,);
    return S;
}

Stack searchTreeC(char *name)
{
    Stack S = Stack_New();
    Tree T = cTree;
    return S;
}
 */


//Tree_Query --
//
//      This one is mine, not part of the site's implementation. Queries for all nodes starting with the keyName.
//       Returns NULL if none are found.
//


// Search functions. I gave it a think and I came to the conclution that conducting four seperate searches for the title,
//,one if it already begins with an article, is the best way to go. Altering tree nodes in any way will lose me time and space, as I'll have to perform the opperations to store an article-less name.
// Searching for A title by keyword just wouldn't work with the tree alone. This seemed like the best solution.


//Proceedure for closing the database on exiting.
void closeDatabase()
{
    freeTree(mTree);
    saveCatalog();
    freeTree(cTree);
    fclose(userFile);
    fclose(movieFile);
   
}

/*
 *
 * Functions for booting up the database.
 *
 */
void loadCatalog()
{
    // Max length of file line to read.
    int maxLength = 550;
    // Temporary string variable.
    char curLine [maxLength];
    while (fgets(curLine, maxLength, userFile))
    {
        Tree_Insert(cTree, extractCData(curLine));
    }
}

void bootDatabase()
{
    //TODO: Make better file pathnames.
    mkdir("MovieData", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("UserData", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mTree = Tree_New(compM, printM);
    cTree = Tree_New(compC, printC);
    
    movieFile = fopen("/Users/Theepicone1/Documents/MovieInfo.txt", "r");
    if (movieFile == NULL)
    {
        printf("Movie file not found!\n");
    }
    loadMovies();
}


/*
 *
 * Utility Functions
 *
 */

int StartsWith(const char *a, const char *b)
{
    if(strncmp(a, b, strlen(a)) == 0) return 1;
    return 0;
}

char * Trimmer(char * original)
{
    //Basically if the string starts with any of these, trim it off and return a new string without them.
    if (strncmp(original,"The ", strlen("The "))==0)
    {
        original = original +4;
    } else if (strncmp(original,"A ", strlen("A "))==0)
    {
        original = original +2;
    } else if ( strncmp(original,"An ", strlen("An ")) == 0)
    {
        original = original +3;
    }
    return original;
    
}

void printSample()
{
    (mTree->print)(mTree->root->data);
    (mTree->print)(mTree->root->left->data);
    (mTree->print)(mTree->root->right->data);
}

// ONLY WORKS IF POINTER IS TO AN mNode!
mNodeData getMNodeData(Node mNode)
{
    mNodeData temp = (mNodeData)(mNode->data);
    return temp;
}

cNodeData getCNodeData(Node cNode)
{
    cNodeData temp = (cNodeData)(cNode->data);
    return temp;
}

