/****************************************************************************************************************************************
*	File: FindPath.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa4
*****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
	//Check for appropriate number of arguments. 
	if(argc != 3)
	{
		fprintf(stderr, "FindPath Error: incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	//Open up input and output files.
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	//Check to see if the files were successfully opened.
	if(in == NULL)
	{
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int n;
	int a;
	int b;
	int s;
	int d;
	List source = newList();
	List destination = newList();
	List path = newList();
	Graph G = NULL;

	fscanf(in, "%d", &n);
	G = newGraph(n);

	//Generate edges from the in file until the line "0 0" is found
	while(!feof(in))
	{
		fscanf(in, "%d", &a);
		fscanf(in, "%d", &b);
		if(a == 0 && b == 0)
		{
			break;
		}
		addEdge(G, a, b);
	}

	//Store source and destination vertices until the line "0 0" is found
	while(!feof(in))
	{
		fscanf(in, "%d", &s);
		fscanf(in, "%d", &d);
		if(s == 0 && d == 0)
		{
			break;
		}
		append(source, s);
		append(destination, d);
	}

	//Print out the resulting graph
	printGraph(out, G);

	//For each pair of source and destination vertices print the distance between them
	//and the shortest x-y path between them.
	moveFront(source);
	moveFront(destination);
	while(index(source) != -1 || index(destination) != -1)
	{
		s = get(source);
		d = get(destination);
		BFS(G, s);
		if(getDist(G, d) == INF)
		{
			fprintf(out, "\nThe distance from %d to %d is infinity\n", s, d);
			fprintf(out, "No %d-%d path exists\n", s, d);
		}
		else
		{
			fprintf(out, "\nThe distance from %d to %d is %d\n", s, d, getDist(G, d));
			getPath(path, G, d);
			fprintf(out, "A shortest %d-%d path is: ", s, d);
			printList(out, path);
			fprintf(out, "\n");
			clear(path);
		}
		moveNext(source);
		moveNext(destination);
	}


	freeGraph(&G);
	freeList(&source);
	freeList(&destination);
	freeList(&path);

	//Close input and output files.
	fclose(in);
	fclose(out);

	return (0);
}