/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 4
 **********************************************/

#include "Digraph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

char *parseVertex(char *buffer, int *numOfVertices);

void parseEdges(char *buf, Digraph g);

void getIntsBetween(char *buf, char *tmp, int *u, int *v);

char *getNumber(const char *buffer, int *numOfVertices, char **found);

FILE *openFileOrExitOnFailure(char *filename, char *mode);

FILE *in;
FILE *out;
char *buffer;

int main(int argc, char **argv)
{
    Digraph g;
    path = newList();

    if (argc != 3)
        exit(EXIT_FAILURE);

    char *infileName = argv[1];
    char *outfileName = argv[2];
    in = openFileOrExitOnFailure(infileName, "r");
    out = openFileOrExitOnFailure(outfileName, "w");

    int n = 10000; // large graph. You may even allocate 1000000 bytes to read a line. But for PA3, line length will be restricted to 1000 bytes.
    buffer = calloc(n, 1);
    fgets(buffer,n,in); // Alternatively, instead of fgets() you can use getline() on Linux machines only as: char *buffer; int n; getline(&buffer, &n, in);

    // Setup graph data.
    int vcount=0;
    char* restOfTheBuffer = parseVertex(buffer, &vcount);

    if(vcount <= 0)
    {
        fprintf(out,"%s", buffer);
        fprintf(out, "ERROR");
        fclose(in);
        fclose(out);
        freeList(&path);
        free(buffer);
        exit(1);
    }

    g = newDigraph(vcount);
    parseEdges(restOfTheBuffer+1,g);

    getSCC(g);
    modifiedSCC = 0;

    // Read next set of lines and perform actions
    while(fgets(buffer,n,in) != NULL)
    {
        fprintf(out,"%s", buffer);

        char *ret  = strtok(buffer, " \r\t\n");
        int a = 0;
        int b = 0;
        int numCount = 0;
        int argCount = 0;

        while(ret != NULL)
        {
            argCount++;

            if(isdigit(*ret))
                numCount++;
            if(numCount == 1)
                a = atoi(ret);
            if (numCount == 2)
                b = atoi(ret);
            ret = strtok(NULL, " ");
        }

        if(strstr(buffer, "PrintDigraph") != NULL)
        {
            if(argCount != 1)
                fprintf(out, "ERROR\n");
            else
            {
                printDigraph(out,g);
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "GetSize") != NULL)
        {
            if(argCount != 1)
                fprintf(out, "ERROR\n");
            else
                fprintf(out,"%d\n", getSize(g));
        }
        else if(strstr(buffer, "GetOrder") != NULL)
        {
            if(argCount != 1)
                fprintf(out, "ERROR\n");
            else
                fprintf(out, "%d\n", getOrder(g));
        }
        else if(strstr(buffer, "GetOutDegree") != NULL)
        {
            if(numCount != 1 || argCount != 2)
                fprintf(out, "ERROR\n");
            else
            {
                if(getOutDegree(g, a) == -1)
                    fprintf(out, "ERROR\n");
                else
                    fprintf(out,"%d\n", getOutDegree(g,a));
            }

        }
        else if(strstr(buffer, "DeleteEdge") != NULL)
        {
            if(numCount != 2 || argCount != 3)
                fprintf(out,"ERROR\n");
            else
            {
                int returnValue = deleteEdge(g, a, b);

                if(returnValue == -1)
                    fprintf(out, "ERROR");
                else if(returnValue == 0)
                {
                    modifiedSCC = 1;
                    fprintf(out,"%d", returnValue);
                }
                else
                    fprintf(out,"%d", returnValue);
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "AddEdge") != NULL)
        {
            if(numCount != 2 || argCount != 3)
                fprintf(out,"ERROR\n");
            else
            {
                int returnValue = addEdge(g, a, b);

                if(returnValue == -1)
                    fprintf(out, "ERROR");
                else if(returnValue == 0)
                {
                    modifiedSCC = 1;
                    fprintf(out,"%d", returnValue);
                }
                else
                    fprintf(out,"%d", returnValue);
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "GetCountSCC") != NULL)
        {
            if(argCount != 1)
                fprintf(out,"ERROR\n");
            else
            {
                if(modifiedSCC == 1)
                {
                    for(int i = 0; i <= g->SCCCount; i++)
                        clear(g->SCC[i]);
                    getSCC(g);
                    modifiedSCC = 0;
                }

                fprintf(out,"%d", getCountSCC(g));
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "GetNumSCCVertices") != NULL)
        {
            if(numCount != 1 || argCount != 2)
                fprintf(out,"ERROR\n");
            else
            {
                if(modifiedSCC == 1)
                {
                    for(int i = 0; i <= g->SCCCount; i++)
                        clear(g->SCC[i]);
                    getSCC(g);
                    modifiedSCC = 0;
                }

                int returnValue = getNumSCCVertices(g, a);

                if(returnValue == -1)
                    fprintf(out, "ERROR");
                else
                    fprintf(out, "%d", returnValue);

                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "InSameSCC") != NULL)
        {
            if(numCount != 2 || argCount != 3)
                fprintf(out,"ERROR\n");
            else
            {
                if(modifiedSCC == 1)
                {
                    for(int i = 0; i <= g->SCCCount; i++)
                        clear(g->SCC[i]);
                    getSCC(g);
                    modifiedSCC = 0;
                }

                int returnValue = inSameSCC(g, a, b);

                if(returnValue == -1)
                    fprintf(out, "ERROR");
                else if(returnValue == 1)
                    fprintf(out,"YES");
                else
                    fprintf(out, "NO");

                fprintf(out, "\n");
            }
        }
        else
            fprintf(out, "ERROR\n");
    }

    //Free all allocated data.
    fclose(in);
    fclose(out);
    freeDigraph(&g);
    freeList(&path);
    free(buffer);

    return 0;
}

FILE *openFileOrExitOnFailure(char *filename, char *mode)
{
    FILE *in = fopen(filename, mode);
    if (in == NULL) {
        fprintf(stderr, "unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return in;
}

void parseEdges(char *buf, Digraph g)
{
    char* tmp=buf;
    char* start=buf;
    int u,v;

    while (tmp!=NULL) {
        tmp = strchr(start, ',');
        getIntsBetween(start,tmp,&u,&v);

        if(u > g->numVertices || v > g->numVertices)
        {
            fprintf(out, "%d,%s", g->numVertices, buf);
            fprintf(out, "ERROR");
            freeDigraph(&g);
            freeList(&path);
            fclose(in);
            fclose(out);
            free(buffer);
            exit(1);
        }
        else if (u <= 0 || v <= 0)
        {
            fprintf(out, "%d,%s", g->numVertices, buf);
            fprintf(out, "ERROR");
            freeDigraph(&g);
            freeList(&path);
            fclose(in);
            fclose(out);
            free(buffer);
            exit(1);
        }
        else if(u == v)
        {
            fprintf(out, "%d,%s", g->numVertices, buf);
            fprintf(out, "ERROR");
            freeDigraph(&g);
            freeList(&path);
            fclose(in);
            fclose(out);
            free(buffer);
            exit(1);
        }

        addEdge(g,u,v);
        start=tmp+1;
    }

}

void getIntsBetween(char *buf, char *tmp, int *u, int *v)
{
    while (*buf == ' ')
        buf++;

    char* found = strchr(buf,' ');
    getNumber(buf,u,&found);
    getNumber(found,v,&tmp);
}

char *parseVertex(char *buffer, int *numOfVertices)
{
    char* found = strchr(buffer,',');
    return getNumber(buffer, numOfVertices, &found);
}

char *getNumber(const char *buffer, int *numOfVertices, char **found)
{
    errno =0;
    *numOfVertices = (int) strtol(buffer, found, 10);

    if (errno == ERANGE)
    {
        *numOfVertices=-1;
        (*found) =NULL;
        fprintf(stderr,"Error occurred while parsing vertex.");
        exit(EXIT_FAILURE);
    }
    return (*found);
}