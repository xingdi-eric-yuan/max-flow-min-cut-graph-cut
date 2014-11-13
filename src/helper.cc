#include "helper.h"
using namespace std;
using namespace cv;

void removeContourDuplicate(vector<Point> &vec){
    if(vec.empty()) return;
    unordered_set<string> set;
    vector<Point> newvec;
    for(int i = 0; i < vec.size(); i++){
        string tmp = to_string(vec[i].x) + "," + to_string(vec[i].y);
        if(set.count(tmp) == 0){
            newvec.push_back(vec[i]);
            set.insert(tmp);
        }
    }

    swap(vec, newvec);
    newvec.clear();
    set.clear();
}

int point2index(const Mat &img, const Point &pt){
    return img.cols * pt.y + pt.x;
}

int point2index(const Mat &img, int x, int y){
    return img.cols * y + x;
}

Point index2point(const Mat &img, int ind){
    int y = ind / img.cols;
    int x = ind % img.cols;
    return Point(x, y);
}

bool isInsideImage(const Mat &img, int x, int y){
    return x >= 0 && y >= 0 && x < img.cols && y < img.rows;
}

bool isInsideImage(const Mat &img, const Point &pt){
    return pt.x >= 0 && pt.y >= 0 && pt.x < img.cols && pt.y < img.rows;
}

double getEdgeCapacity(const Mat &img, int x1, int y1, int x2, int y2){
    return - log(fabs(img.ATD(y1, x1) - img.ATD(y2, x2))) + 1;
}

void image2Graph(Graph &g, const Mat &img){

    for(int i = 0; i < img.rows; i++){
        for(int j = 0; j < img.cols; j++){
            int index = point2index(img, j, i);
            // 8 neighbors
            /*
            for(int m = -1; m <= 1; m++){
                for(int n = -1; n <= 1; n++){
                    if(m != 0 || n != 0){
                        if(isInsideImage(img, j + m, i + n)){
                            double capa = getEdgeCapacity(img, j, i, j + m, i + n);
                            addEdge(g, index, point2index(img, j + m, i + n), capa, capa);
                        }
                    } 
                }
            }
            */
            // 4 neighbors
            if(isInsideImage(img, j - 1, i)){
                double capa = getEdgeCapacity(img, j, i, j - 1, i);
                addEdge(g, index, point2index(img, j - 1, i), capa, capa);
            }
            if(isInsideImage(img, j + 1, i)){
                double capa = getEdgeCapacity(img, j, i, j + 1, i);
                addEdge(g, index, point2index(img, j + 1, i), capa, capa);
            }
            if(isInsideImage(img, j, i - 1)){
                double capa = getEdgeCapacity(img, j, i, j, i - 1);
                addEdge(g, index, point2index(img, j, i - 1), capa, capa);
            }
            if(isInsideImage(img, j, i + 1)){
                double capa = getEdgeCapacity(img, j, i, j, i + 1);
                addEdge(g, index, point2index(img, j, i + 1), capa, capa);
            }
        }
    }
}

void addSpecificEdges(Graph &g, const Mat& img, const vector<Point>& vec, int vertex, double capacity){
    for(int i = 0; i < vec.size(); i++){
        if(!isInsideImage(img, vec[i])) continue;
        int index = point2index(img, vec[i]);
        addEdge(g, index, vertex, capacity, capacity);
    }
    for(int i = 0; i < img.rows * img.cols; i++){
        string which_edge = getEdgeId(vertex, i);
        if(g.edges.find(which_edge) == g.edges.end()){
            addEdge(g, i, vertex, 1.0, 1.0);
        }
    }
}

vector<Point> getSegment(const Mat& img, const vector<Point> &fore, const vector<Point> &back){
    int height = img.rows;
    int width = img.cols;
    double source_capacity = 100.0;
    double sink_capacity = 100.0;
    vector<Point> res;

    Graph g;
    int node_amount = height * width + 2;
    for(int i = 0; i < node_amount; i++){
        int tmp = addVertex(g);
    }
    int source_id = node_amount - 2;
    int sink_id = node_amount - 1;
    initVertices(g);
    image2Graph(g, img);
    addSpecificEdges(g, img, fore, source_id, source_capacity);
    addSpecificEdges(g, img, back, sink_id, sink_capacity);

    cout<<"Successfully create graph. There're totally "<<g.vertices.size()<<" vertices and "<<g.edges.size()<<" edges"<<endl;
    double max_flow = pushRelabel(g, source_id, sink_id);
    cout<<"Max flow = "<<max_flow<<endl;
    vector<Edge> min_cut = getMinCut(g, source_id);
    cout<<"One of the min-cut contains "<<min_cut.size()<<" of edges"<<endl;
    for(int i = 0; i < min_cut.size(); i++){
        Point from = index2point(img, min_cut[i]._from);
        Point to = index2point(img, min_cut[i]._to);
        if(isInsideImage(img, from) && isInsideImage(img, to)){
            res.push_back(from);
            res.push_back(to);
        }
    }
    return res;
}
