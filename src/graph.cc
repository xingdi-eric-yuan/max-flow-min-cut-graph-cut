#include "graph.h"
using namespace std;

double getMin(double a, double b){
    return a <= b ? a : b;
}

void initVertices(Graph &g){
    for(int i = 0; i < g.vertices.size(); i++){
        g.vertices[i].excess = 0.0;
        g.vertices[i].height = 0;
        g.vertices[i].seen = 0;
        g.vertices[i].marked = false;
    }
}

int addVertex(Graph &g){
    Vertex v;
    g.vertices.push_back(v);
    return g.vertices.size() - 1;
}

void addEdge(Graph &g, int i, int j, double w, double revw){
    if(i >= g.vertices.size() || i < 0) return;
    if(j >= g.vertices.size() || j < 0) return;
    if(i == j) return;
    if(w < 0 || revw < 0) return;

    Edge ij, ji;
    ij._from = i;
    ij._to = j;
    ij.capacities = w;
    ij.flow = 0.0;
    g.edges.push_back(ij);

    ji._from = j;
    ji._to = i;
    ji.capacities = revw;
    ji.flow = 0.0;
    g.edges.push_back(ji);
}

void printEdges(Graph &g){
    cout<<"All Edges..."<<endl;
    for(int i = 0; i < g.edges.size(); i++){
        cout<<"from "<<g.edges[i]._from<<" to "<<g.edges[i]._to<<", capa = "<<g.edges[i].capacities<<", flow = "<<g.edges[i].flow<<endl;
    }
}

void printVertices(Graph &g){
    cout<<"All Vertices..."<<endl;
    for(int i = 0; i < g.vertices.size(); i++){
        cout<<"Vertex "<<i<<", height = "<<g.vertices[i].height<<", excess = "<<g.vertices[i].excess<<", seen = "<<g.vertices[i].seen<<", marked = "<<g.vertices[i].marked<<endl;
    }
}

void setHeight(Graph &g, int vtx_id, int h){
    if(vtx_id >= g.vertices.size()) return;
    g.vertices[vtx_id].height = h;
}

int getHeight(const Graph &g, int vtx_id){
    if(vtx_id >= g.vertices.size()) return INT_MIN;
    return g.vertices[vtx_id].height;
}

void setExcess(Graph &g, int vtx_id, double e){
    if(vtx_id >= g.vertices.size()) return;
    g.vertices[vtx_id].excess = e;
}

double getExcess(const Graph &g, int vtx_id){
    if(vtx_id >= g.vertices.size()) return INT_MIN;
    return g.vertices[vtx_id].excess;
}

int getEdgeId(const Graph &g, int from, int to){
    if(from == to) return -1;
    for(int i = 0; i < g.edges.size(); i++){
        if(g.edges[i]._from == from && g.edges[i]._to == to) return i;
    }
    return -1;
}

void push(Graph &g, int from, int to){
    int which_edge = getEdgeId(g, from, to);
    int which_edge_rev = getEdgeId(g, to, from);
    if(which_edge == -1) return;
    double send = getMin(g.vertices[from].excess, g.edges[which_edge].capacities - g.edges[which_edge].flow);
    g.edges[which_edge].flow += send;
    g.edges[which_edge_rev].flow -= send;
    g.vertices[from].excess -= send;
    g.vertices[to].excess += send;
}

void relabel(Graph &g, int node_id){
    int min_height = INT_MAX;
    for(int i = 0; i < g.vertices.size(); i++){
        int which_edge = getEdgeId(g, node_id, i);
        if(which_edge == -1) continue;
        if(g.edges[which_edge].capacities - g.edges[which_edge].flow > 0){
            min_height = getMin(min_height, g.vertices[i].height);
            g.vertices[node_id].height = min_height + 1;
        }
    }
}

void moveToFront(vector<int> &vec, int which){
    if(which >= vec.size()) return;
    int tmp = vec[which];
    vec.erase(vec.begin() + which);
    vec.insert(vec.begin(), tmp);
}

void discharge(Graph &g, int node_id){
    while(g.vertices[node_id].excess > 0){
        if(g.vertices[node_id].seen < g.vertices.size()){
            int v = g.vertices[node_id].seen;
            int which_edge = getEdgeId(g, node_id, v); 
            if(which_edge >= 0 && 
               g.edges[which_edge].capacities - g.edges[which_edge].flow > 0 && 
               g.vertices[node_id].height > g.vertices[v].height){
                push(g, node_id, v);
            }else ++ g.vertices[node_id].seen;
        }else{
            relabel(g, node_id);
            g.vertices[node_id].seen = 0;
        }
    }
}

double pushRelabel(Graph &g, int source_id, int sink_id){

    setHeight(g, source_id, g.vertices.size());
    setExcess(g, source_id, INT_MAX);

    vector<int> List;
    for(int i = 0; i < g.vertices.size(); i++){
        if(i != source_id && i != sink_id){
            List.push_back(i);
        }
    }

    for(int i = 0; i < g.vertices.size(); i++){
        if(i == source_id) continue;
        push(g, source_id, i);
    }
    int counter = 0;
    while(1){
        if(counter >= g.vertices.size() - 2) break;
        int u = List[counter];
        int old_height = g.vertices[u].height;
        discharge(g, u);
        if(g.vertices[u].height > old_height){
            moveToFront(List, counter);
            counter = 0;
        }else ++ counter;
    }

    double maxFlow = 0.0;
    for(int i = 0; i < g.vertices.size(); i++){
        int which_edge = getEdgeId(g, source_id, i); 
        if(which_edge == -1) continue;
        maxFlow += g.edges[which_edge].flow;
    }
    List.clear();
    return maxFlow;
    
}

vector<Edge> getMinCut(Graph &g, int source_id){
    // reset marks
    for(int i = 0; i < g.vertices.size(); i++){
        g.vertices[i].marked = false;
    }
    // dfs along edges in the residual network, and mark 
    // all vertices that can be reached this way.
    unordered_set<int> visited;
    stack<int> S;
    S.push(source_id);
    while(!S.empty()){
        int p = S.top();
        S.pop();
        for(int i = 0; i < g.vertices.size(); i++){
            if(i == p) continue;
            int which_edge = getEdgeId(g, p, i); 
            int which_edge_rev = getEdgeId(g, i, p); 
            if(which_edge == -1 || which_edge_rev == -1) continue;
            if(g.edges[which_edge].capacities == g.edges[which_edge].flow ||
               g.edges[which_edge_rev].capacities == g.edges[which_edge_rev].flow) continue;
            if(visited.count(i) == 0) S.push(i);
        }
        visited.insert(p);
        g.vertices[p].marked = true;
    }
    // The cut consists of all edges that go from a marked to an unmarked vertex.
    vector<Edge> res;
    for(int i = 0; i < g.edges.size(); i++){
        int from = g.edges[i]._from;
        int to = g.edges[i]._to;
        if(true == g.vertices[from].marked && false == g.vertices[to].marked){
            res.push_back(g.edges[i]);
        }
    }    
    return res;
}

