#include "general_settings.h"
using namespace cv;
using namespace std;

//Mat img;
bool DO_DRAW = false;
vector<Point> contour;

void
run(){
/*
    int node_amount = 6;
    Graph g;
    for(int i = 0; i < node_amount; i++){
        int tmp = addVertex(g);
    }
    initVertices(g);
    addEdge(g, 0, 1, 10, 10);
    addEdge(g, 1, 2, 15, 15);
    addEdge(g, 2, 5, 3, 3);
    addEdge(g, 0, 3, 12, 12);
    addEdge(g, 3, 4, 6, 6);
    addEdge(g, 4, 5, 17, 17);
    addEdge(g, 3, 1, 5, 5);
    addEdge(g, 2, 4, 8, 8);

    double max_flow = pushRelabel(g, 0, 5);
    cout<<max_flow<<endl;

    vector<Edge> min_cut = getMinCut(g, 0);

    for(int i = 0; i < min_cut.size(); i++){
        cout<<"from "<<min_cut[i]._from<<" to "<<min_cut[i]._to<<endl;
    }
    */
   
    Mat img = imread("baboon.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //img.convertTo(img, CV_64FC1, 1.0/255.0, 0);

    cout<<"Foreground please..."<<endl;
    vector<Point> foreground_pts = getMousePoints(img);
    cout<<"There are totally "<<foreground_pts.size()<<" foreground points."<<endl;

    cout<<"Background please..."<<endl;
    vector<Point> background_pts = getMousePoints(img);
    cout<<"There are totally "<<background_pts.size()<<" background points."<<endl;

}

int 
main(int argc, char** argv){

    long start, end;
    start = clock();

    run();

    end = clock();
    cout<<"Totally used time: "<<((double)(end - start)) / CLOCKS_PER_SEC<<" second"<<endl;
    return 0;
}

