/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 2
 **********************************************/

#include <string.h>
#include <ctype.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[])
{
    char line[MAX_LEN];
    char tokenlist[MAX_LEN];
    char* token;
    FILE *in, *out;

    if(argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    if(out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }


    Graph G = newGraph(4);
    int theFoundValue;
    addEdge(G,3,1);
    addEdge(G,3,2);
    addEdge(G,1,3);
    addEdge(G,4,3);
    addEdge(G,4,2);
    addEdge(G,4,3);

    while( fgets(line, MAX_LEN, in) != NULL)
    {
        token = strtok(line, " \n");
        tokenlist[0] = '\0';

        while( token != NULL )
        {
            strcat(tokenlist, "");
            strcat(tokenlist, token);
            strcat(tokenlist, " ");
            token = strtok(NULL, " \n");
        }

        if(strcmp(tokenlist,"PrintGraph ") == 0)
        {
            fprintf(out,"PrintGraph\n");
            printGraph(out,G);
            fprintf(out,"\n");
        }
        else if(strcmp(tokenlist,"GetSize ") == 0)
        {
            fprintf(out,"GetSize\n");
            fprintf(out,"%d\n", getSize(G));
        }
        else if(strstr(tokenlist, "GetNeighborCount ") != NULL)
        {
            char *ret = strstr(tokenlist, "GetNeighborCount ");
            fprintf(out,"GetNeighbor Count %d\n", atoi(ret+17));
            fprintf(out,"%d\n", getNeighborCount(G,atoi(ret+17)));
        }
        else if(strstr(tokenlist, "PathExists ") != NULL)
        {
            char *ret = strstr(tokenlist, "PathExists ");
            unvisitAll(G);
            fprintf(out,"PathExists %d %d\n",atoi(ret+11), atoi(ret+13));
            theFoundValue = pathExistsRecursive(G,atoi(ret+11), atoi(ret+13));
            if(theFoundValue == FOUND)
                fprintf(out,"YES\n");
            else
                fprintf(out,"NO\n");
        }
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}