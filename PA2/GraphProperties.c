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

    for(int i = 0; i < 160; i++)
    {
        tokenlist[i] = 'a';
    }

    fgets(line, MAX_LEN, in);
    token = strtok(line, " \n");
    tokenlist[0] = '\0';

    while (token != NULL)
    {
        strcat(tokenlist, "");
        strcat(tokenlist, token);
        strcat(tokenlist, " ");
        token = strtok(NULL, " \n");
    }

    Graph G = newGraph(tokenlist[0] - '0');
    int counter = 0;
    int j = 0;

    for(int i = 1; i < 160; i++)
        if(isdigit(tokenlist[i]))
            counter++;

    int array[counter];

    for(int i = 1; i < 160; i++)
    {
        if(isdigit(tokenlist[i]))
        {
            array[j] = tokenlist[i];
            j++;
        }
    }

    for(int i = 0; i < counter; i+=2)
        addEdge(G, array[i] - '0', array[i+1] - '0');

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
            else
            {
                int theFoundValue;
                unvisitAll(G);
                fprintf(out,"PathExists %d %d\n",atoi(ret+11), atoi(ret+13));
                theFoundValue = pathExistsRecursive(G,atoi(ret+11), atoi(ret+13));
                if(theFoundValue == FOUND)
                    fprintf(out,"YES\n");
                else
                    fprintf(out,"NO\n");
            }
        }
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}