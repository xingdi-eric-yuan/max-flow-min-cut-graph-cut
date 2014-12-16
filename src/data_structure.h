#pragma once
#include "general_settings.h"

using namespace std;
using namespace cv;

struct Edge{
    int _from;
    int _to;
    double capacities;
    double flow;
};

struct Vertex{
    int height;
    double excess;
    int seen;
    bool marked;
    vector<Edge*> adj_edges;
};

struct Graph{

    vector<Vertex> vertices;
    unordered_map<string, Edge> edges;
    double flow;
};
