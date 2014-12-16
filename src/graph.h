#pragma once
#include "general_settings.h"

using namespace std;

double getMin(double, double);
void initVertices(Graph&);
int addVertex(Graph&);
void addEdge(Graph&, int, int, double);
void addSingleEdge(Graph&, int, int, double, double);
void addSingleEdge(Graph&, int, int, double);
void setFlow(Graph&, int, int, double);
void printEdges(Graph&);
void printVertices(Graph&);
void setHeight(Graph&, int, int);
int getHeight(const Graph&, int);
void setExcess(Graph&, int, double);
double getExcess(const Graph&, int);
string getEdgeId(int, int);
void push(Graph&, int, int);
void relabel(Graph&, int);
void moveToFront(vector<int>&, int);
void discharge(Graph&, int);
double pushRelabel(Graph&, int, int);
vector<Edge> getMinCut(Graph&, int);