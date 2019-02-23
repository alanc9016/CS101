/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 3
 **********************************************/

#include <string.h>
#include <ctype.h>
#include "List.h"
#include "Digraph.h"
#define MAX_LEN 5000

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


    if(atoi(token) <= 0)
    {
        while( token != NULL )
        {
            strcat(tokenlist, "");
            strcat(tokenlist, token);
            strcat(tokenlist, " ");
            token = strtok(NULL, " \n");
        }

        fprintf(out, "%s", tokenlist);
        fprintf(out, "\nERROR");
        fclose(in);
        fclose(out);
        exit(1);
    }

    Digraph G = newDigraph(atoi(token));
    B = newList();

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
            if(a > G->numVertices|| b > G->numVertices)
            {
                fprintf(out, "ERROR");
                fclose(in);
                fclose(out);
                exit(1);
            }
            else if(a <= 0 || b <= 0)
            {
                fprintf(out, "ERROR");
                fclose(in);
                fclose(out);
                exit(1);
            }
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

        if(strcmp(tokenlist,"PrintDigraph ") == 0)
        {
            fprintf(out,"PrintGraph\n");
            printDigraph(out,G);
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
        else if(strstr(tokenlist, "GetOutDegree ") != NULL)
        {
            char *ret = strstr(tokenlist, "GetOutDegree ");

            fprintf(out,"GetOutDegree %d\n", atoi(ret+13));

            if(getOutDegree(G,atoi(ret+13)) == -1)
                fprintf(out,"ERROR\n");
            else
                fprintf(out,"%d\n", getOutDegree(G,atoi(ret+13)));
        }
        else if(strstr(tokenlist, "Distance ") != NULL)
        {
            char *ret = strstr(tokenlist, "Distance ");

            fprintf(out,"Distance %d %d\n",atoi(ret+8), atoi(ret+10));
            distance(out, G, atoi(ret+8), atoi(ret+10));
            fprintf(out, "\n");

        }
        else if(strstr(tokenlist, "Acyclic") != NULL)
        {
            fprintf(out,"Acyclic\n");
            acyclic(out, G);
            fprintf(out, "\n");
        }
        else if(strstr(tokenlist, "TopoSort") != NULL)
        {
            fprintf(out, "TopoSort\n");
            topoSort(out, G);
        }
        else if(strstr(tokenlist, "DeleteEdge") != NULL)
        {
            char *ret = strstr(tokenlist, "DeleteEdge ");

            fprintf(out,"DeleteEdge %d %d\n",atoi(ret+11), atoi(ret+13));
            fprintf(out,"%d", deleteEdge(G, atoi(ret+11), atoi(ret+13)));
            fprintf(out, "\n");
        }
        else if(strstr(tokenlist, "AddEdge") != NULL)
        {
            char *ret = strstr(tokenlist, "AddEdge ");

            fprintf(out, "AddEdge %d %d\n", atoi(ret+8), atoi(ret+10));
            fprintf(out, "%d", addEdge(G, atoi(ret+8), atoi(ret+10)));
            fprintf(out, "\n");
        }
        else
        {
            fprintf(out, "%s\n", tokenlist);
            fprintf(out, "ERROR\n");
        }
    }


    freeList(&B);
    freeDigraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}