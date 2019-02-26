/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 3
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
    B = newList();

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
        freeList(&B);
        free(buffer);
        exit(1);
    }

    g=newDigraph(vcount);
    parseEdges(restOfTheBuffer+1,g);


    // Read next set of lines and perform actions
    while(fgets(buffer,n,in) != NULL)
    {
        if(strstr(buffer, "PrintDigraph") != NULL)
        {
            fprintf(out,"PrintDigraph\n");
            printDigraph(out,g);
            fprintf(out,"\n");
        }
        else if(strstr(buffer, "GetSize") != NULL)
        {
            fprintf(out,"GetSize\n");
            fprintf(out,"%d\n", getSize(g));
        }
        else if(strstr(buffer, "GetOrder") != NULL)
        {
            fprintf(out, "GetOrder\n");
            fprintf(out, "%d\n", getOrder(g));
        }
        else if(strstr(buffer, "GetOutDegree ") != NULL)
        {
            char *ret = strstr(buffer, "GetOutDegree ");

            fprintf(out,"GetOutDegree %d\n", atoi(ret+13));

            fprintf(out,"%d\n", getOutDegree(g,atoi(ret+13)));
        }
        else if(strstr(buffer, "Distance") != NULL)
        {
            fprintf(out,"%s", buffer);

            char *ret  = strtok(buffer, " \r\t\n");
            int a = 0;
            int b = 0;
            int count = 0;

            while(ret != NULL)
            {
                if(isdigit(*ret))
                    count++;
                if(count == 1)
                    a = atoi(ret);
                if (count == 2)
                    b = atoi(ret);
                ret = strtok(NULL, " ");
            }

            if(count != 2)
                fprintf(out,"ERROR\n");
            else
            {
                distance(out,g, a, b);
                fprintf(out, "\n");
            }

        }
        else if(strstr(buffer, "Acyclic") != NULL)
        {
            char *ret = strstr(buffer, "Acyclic");

            if(strncmp((ret+8),"",1))
            {
                fprintf(out, "%s", buffer);
                fprintf(out, "ERROR\n");
            }
            else
            {
                fprintf(out,"Acyclic\n");
                acyclic(out, g);
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "TopoSort") != NULL)
        {
            fprintf(out, "TopoSort\n");
            topoSort(out, g);
            freeList(&B);
            B = newList();
        }
        else if(strstr(buffer, "DeleteEdge") != NULL)
        {
            fprintf(out,"%s", buffer);

            char *ret  = strtok(buffer, " \r\t\n");
            int a = 0;
            int b = 0;
            int count = 0;

            while(ret != NULL)
            {
                if(isdigit(*ret))
                    count++;
                if(count == 1)
                    a = atoi(ret);
                if (count == 2)
                    b = atoi(ret);
                ret = strtok(NULL, " ");
            }

            if(count != 2)
                fprintf(out,"ERROR\n");
            else
            {
                fprintf(out,"%d", deleteEdge(g, a, b));
                fprintf(out, "\n");
            }
        }
        else if(strstr(buffer, "AddEdge") != NULL)
        {
            fprintf(out,"%s", buffer);

            char *ret  = strtok(buffer, " \r\t\n");
            int a = 0;
            int b = 0;
            int count = 0;

            while(ret != NULL)
            {
                if(isdigit(*ret))
                    count++;
                if(count == 1)
                    a = atoi(ret);
                if (count == 2)
                    b = atoi(ret);
                ret = strtok(NULL, " ");
            }

            if(count != 2)
                fprintf(out,"ERROR\n");
            else
            {
                fprintf(out,"%d", addEdge(g, a, b));
                fprintf(out, "\n");
            }
        }
        else
        {
            fprintf(out, "%s", buffer);
            fprintf(out, "ERROR\n");
        }
    }

    // Free all allocated data.
    fclose(in);
    fclose(out);
    freeDigraph(&g);
    freeList(&B);
    free(buffer);
    return 0;
}

FILE *openFileOrExitOnFailure(char *filename, char *mode) {
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
            freeList(&B);
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
            freeList(&B);
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