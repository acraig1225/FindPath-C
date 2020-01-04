/****************************************************************************************************************************************
*	File: Graph.h
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa4
*****************************************************************************************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

typedef struct GraphObj* Graph;

#define INF -1
#define NIL 0

//Constructors-Destructors***************************************************************************************************************
Graph newGraph(int n);							//Returns a Graph pointing to a newly created GraphObj representing a graph having
												//n vertices and no edges.
void freeGraph(Graph* pG);						//Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG 
												//to NULL. 

//Access Functions***********************************************************************************************************************
int getOrder(Graph G);							//Returns the order field of a given Graph.
int getSize(Graph G);							//Returns the size field of a given Graph.
int getSource(Graph G);							//Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not 
												//yet been called.
int getParent(Graph G, int u);					//Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if 
												//BFS() has not yet been called.
												//Precondition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);					//Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has 
												//not yet been called.
												//Precondition: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);			//Appends to the List L the vertices of a shortest path in G from source to u, or appends 
												//to L the value NIL if no such path exists.
												//Precondition: getSource(G) != NIL & 1 <= u <= getOrder(G)

//Manipulation Procedures****************************************************************************************************************
void makeNull(Graph G);							//Deletes all edges of G, restoring it to its original (no edge) state.
void addEdge(Graph G, int u, int v);			//Inserts a new edge joining u to v. 
												//i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
												//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v);				//Inserts a new directed edge from u to v.
												//i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
												//Precondition: 1 <= u <= getOrder(G) & 1 <= v <= getOrder(G)
void BFS(Graph G, int s);						//Runs the BFS algorithm on the Graph G with source s, setting the color, distance, 
												//parent, and source fields of G accordingly.

//Other Operations***********************************************************************************************************************
void printGraph(FILE* out, Graph G);			//Prints the adjacency list representation of G to the file pointed to by out.

#endif