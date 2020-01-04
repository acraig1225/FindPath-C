/****************************************************************************************************************************************
*	File: Graph.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa4
*****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj
{
	List *adj;
	char *color;
	int *parent;
	int	*distance;
	int order;
	int size;
	int source;
} GraphObj;

//Constructors-Destructors***************************************************************************************************************
//Description: Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n)
{
	int i;
	Graph G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL;

	G->adj = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(char*));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	for(i = 1; i < n + 1; i++)
	{
		G->adj[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	return (G);
}							

//Description: Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG)
{
	if(*pG != NULL && pG != NULL)
	{
		int i;

		free((*pG)->adj[0]);
		for(i = 1; i < getOrder(*pG) + 1; i++)
		{
			freeList(&(*pG)->adj[i]);	
			free((*pG)->adj[i]);
		}
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->distance);
		free((*pG)->parent);
		free(*pG);
		*pG = NULL;
	}
}

//Access Functions***********************************************************************************************************************
//Description: Returns the order field of a given Graph.
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return(G->order);
}	

//Description: Returns the size field of a given Graph.						
int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return(G->size);
}

//Description: Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.							
int getSource(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	return (G->source);
}						

//Description: Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called.
//Precondition: 1 <= u <= getOrder(G)												
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getParent() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	return (G->parent[u]);
}

//Description: Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
//Precondition: 1 <= u <= getOrder(G)												
int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("%d\n", u);
		printf("Graph Error: calling getDist() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	return (G->distance[u]);
}

//Description: Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
//Precondition: getSource(G) != NIL & 1 <= u <= getOrder(G)				
void getPath(List L, Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(L == NULL)
	{
		printf("Graph Error: calling getPath() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL)
	{
		printf("Graph Error: calling getPath() on a NIL source\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getPath() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	if(u == G->source)
	{
		append(L, G->source);
	}
	else if(G->parent[u] == NIL)
	{
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}			

//Manipulation Procedures****************************************************************************************************************
//Description: Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if(getSize(G) > 0)
	{
		int i;
		for(i = 1; i < getOrder(G) + 1; i++)
		{
			clear(G->adj[i]);
			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->distance[i] = INF;
		}
		G->size = 0;
	}
}

//Description: Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)							
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	//insert v into adj[u]
	if(length(G->adj[u]) == 0)
	{
		append(G->adj[u], v);
	}
	else
	{
		moveFront(G->adj[u]);
		while(index(G->adj[u]) != -1 &&  get(G->adj[u]) < v)  //look to see if entry already exists
		{
			moveNext(G->adj[u]);		
		}

		if(index(G->adj[u]) == -1)
		{
			append(G->adj[u], v);
		}
		else if(get(G->adj[u]) != v)
		{
			insertBefore(G->adj[u], v);
		}
	}

	//insert u into adj[v]
	if(length(G->adj[v]) == 0)
	{
		append(G->adj[v], u);
	}
	else
	{
		moveFront(G->adj[v]);
		while(index(G->adj[v]) != -1 &&  get(G->adj[v]) < u)  //look to see if entry already exists
		{
			moveNext(G->adj[v]);		
		}

		if(index(G->adj[v]) == -1)
		{
			append(G->adj[v], u);
		}
		else if(get(G->adj[v]) != u)
		{
			insertBefore(G->adj[v], u);
		}
	}
	G->size++;
}			 

//Description: Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)												
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling addEdge() on a vertex outside the range 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}

	//insert v into adj[u]
	if(length(G->adj[u]) == 0)
	{
		append(G->adj[u], v);
	}
	else
	{
		moveFront(G->adj[u]);
		while(index(G->adj[u]) != -1 &&  get(G->adj[u]) < v)  //look to see if entry already exists
		{
			moveNext(G->adj[u]);		
		}

		if(index(G->adj[u]) == -1)
		{
			append(G->adj[u], v);
		}
		else if(get(G->adj[u]) != v)
		{
			insertBefore(G->adj[u], v);
		}
	}
	G->size++;
}			

//Description: Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.												
void BFS(Graph G, int s)
{
	if(G == NULL)
	{
		printf("Graph Error: calling BFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	int i;
	for(i = 1; i < getOrder(G) + 1; i++)
	{
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	G->source = s;
	G->color[s] = 'g';
	G->distance[s] = 0;
	G->parent[s] = NIL;

	int x;
	int y;
	List queue = newList();
	append(queue, s);
	moveFront(queue);

	while(length(queue) != 0)
	{
		x = front(queue);
		deleteFront(queue);
		moveFront(G->adj[x]);
		while(index(G->adj[x]) != -1)
		{
			y = get(G->adj[x]);
			if(G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(queue, y);
			}
			moveNext(G->adj[x]);
		}
		G->color[x] = 'b';
	}
	freeList(&queue);
}						

//Other Operations***********************************************************************************************************************
//Description: Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		printf("Matrix Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		printf("Matrix Error: calling printGraph() on NULL FILE reference\n");
		exit(EXIT_FAILURE);
	}
	
	int i;
	for(i = 1; i < getOrder(G) + 1; i++)
	{
		fprintf(out, "%d: ", i);
		if(length(G->adj[i]) != 0)
		{
			moveFront(G->adj[i]);
			while(index(G->adj[i]) != -1)
			{
				fprintf(out, "%d ", get(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
		fprintf(out, "\n");
	}
}			