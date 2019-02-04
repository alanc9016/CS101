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

void pathExists(FILE* out, Graph G, int u, int v);

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

    fgets(line, MAX_LEN, in);
    token = strtok(line, " \n");
    tokenlist[0] = '\0';

    Graph G = newGraph(atoi(token));

    token = strtok(NULL, " \n");

    int a;
    int b;
    int i = 1;

    while( token != NULL )
    {
        strcat(tokenlist, "");
        strcat(tokenlist, token);
        strcat(tokenlist, "");
        if(i == 1)
            a = atoi(token);
        else if(i == 2)
        {
            b = atoi(token);
            addEdge(G, a ,b);
            i = 0;
        }
        token = strtok(NULL, " \n");
        i++;
    }



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
        else if(strcmp(tokenlist, "GetOrder ") == 0)
        {
            fprintf(out, "GetOrder\n");
            fprintf(out, "%d\n", getOrder(G));
        }
        else if(strstr(tokenlist, "GetNeighborCount ") != NULL)
        {
            char *ret = strstr(tokenlist, "GetNeighborCount ");

            fprintf(out,"GetNeighbor Count %d\n", atoi(ret+17));

            if(getNeighborCount(G,atoi(ret+17)) == -1)
                fprintf(out,"ERROR\n");
            else
            fprintf(out,"%d\n", getNeighborCount(G,atoi(ret+17)));
        }
        else if(strstr(tokenlist, "PathExists ") != NULL)
        {
            char *ret = strstr(tokenlist, "PathExists ");

            if(atoi(ret+11) == 0 || atoi(ret+13) == 0)
            {
                if(atoi(ret+11) == 0)
                    fprintf(out,"PathExists %d\n",atoi(ret+13));
                else
                    fprintf(out,"PathExists %d\n",atoi(ret+11));
                fprintf(out,"ERROR\n");
            }
            else if(atoi(ret+11) > G->numVertices || atoi(ret+13) > G->numVertices ||
            atoi(ret+11) < 0 || atoi(ret+13) < 0)
            {
                fprintf(out,"PathExists %d %d\n",atoi(ret+11), atoi(ret+13));
                fprintf(out,"ERROR\n");
            }
            else
            {
                fprintf(out,"PathExists %d %d\n",atoi(ret+11), atoi(ret+13));
                pathExists(out, G, atoi(ret+11), atoi(ret+13));
            }
        }
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}

void pathExists(FILE* out, Graph G, int u, int v)
{
    int theFoundValue;
    unvisitAll(G);
    theFoundValue = pathExistsRecursive(G,u,v);
    if(theFoundValue == FOUND)
        fprintf(out,"YES\n");
    else
        fprintf(out,"NO\n");
}