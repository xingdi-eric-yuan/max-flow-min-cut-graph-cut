#include "general_settings.h"
using namespace cv;
using namespace std;

//Mat img;
bool DO_DRAW = false;
vector<Point> contour;

void
run(){

    /*
    int node_amount = 4;
    Graph g;
    for(int i = 0; i < node_amount; i++){
        int tmp = addVertex(g);
    }
    initVertices(g);
    addEdge(g, 0, 1, 1);
    addEdge(g, 0, 2, 2);
    addSingleEdge(g, 1, 2, 3);
    addSingleEdge(g, 2, 1, 4);
    addEdge(g, 1, 3, 5);
    addEdge(g, 2, 3, 6);

    double max_flow = pushRelabel(g, 0, 3);
    cout<<max_flow<<endl;

    vector<Edge> min_cut = getMinCut(g, 0);
    for(int i = 0; i < min_cut.size(); i++){
        cout<<"from "<<min_cut[i]._from<<" to "<<min_cut[i]._to<<endl;
    }
*/


/*
    int node_amount = 6;
    Graph g;
    for(int i = 0; i < node_amount; i++){
        int tmp = addVertex(g);
    }
    initVertices(g);
    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 2, 12);
    addEdge(g, 1, 2, 5);
    addEdge(g, 1, 3, 15);
    addEdge(g, 2, 4, 6);
    addEdge(g, 3, 4, 8);
    addEdge(g, 4, 5, 17);
    addEdge(g, 3, 5, 3);
    double max_flow = pushRelabel(g, 0, 5);
    cout<<max_flow<<endl;

    vector<Edge> min_cut = getMinCut(g, 0);
    for(int i = 0; i < min_cut.size(); i++){
        cout<<"from "<<min_cut[i]._from<<" to "<<min_cut[i]._to<<endl;
    }
    */
/*

    int node_amount = 6;
    Graph g;
    for(int i = 0; i < node_amount; i++){
        int tmp = addVertex(g);
    }
    initVertices(g);
    addEdge(g, 0, 1, 1, 1);
    addEdge(g, 1, 2, 1.5, 1.5);
    addEdge(g, 2, 5, 0.3, 0.3);
    addEdge(g, 0, 3, 1.2, 1.2);
    addEdge(g, 3, 4, 0.6, 0.6);
    addEdge(g, 4, 5, 1.7, 1.7);
    addEdge(g, 3, 1, 0.5, 0.5);
    addEdge(g, 2, 4, 0.8, 0.8);
    double max_flow = pushRelabel(g, 0, 5);
    cout<<max_flow<<endl;

    vector<Edge> min_cut = getMinCut(g, 0);
    for(int i = 0; i < min_cut.size(); i++){
        cout<<"from "<<min_cut[i]._from<<" to "<<min_cut[i]._to<<endl;
    }
*/
    
   /*
    //Mat img = imread("ball.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img = imread("baboon_tiny.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //Mat img = imread("baboon.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat resimg;
    cvtColor(img, resimg, CV_GRAY2RGB);

    cout<<"Foreground please..."<<endl;
    vector<Point> foreground_pts = getMousePoints(img);
    cout<<"There are totally "<<foreground_pts.size()<<" foreground points."<<endl;

    cout<<"Background please..."<<endl;
    vector<Point> background_pts = getMousePoints(img);
    cout<<"There are totally "<<background_pts.size()<<" background points."<<endl;

    img.convertTo(img, CV_64FC1, 1.0, 0);
//    img.convertTo(img, CV_64FC1, 1.0/255.0, 0);
    vector<Point> seg = getSegment(img, foreground_pts, background_pts);
    cout<<seg.size()<<endl;

    for(int i = 0; i < seg.size(); i++){
        circle(resimg, seg[i], 2, Scalar(0, 0, 255), 1); 
    }
    imshow("Result", resimg);
    waitKey(0);
    */
   
//    Mat img = Mat::ones(5, 5, CV_64FC1);
//    randn(img, 10, 5);
    Mat img = Mat::zeros(5, 5, CV_64FC1);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(i > 2) img.ATD(i, j) += 1000;
        }
    }

    vector<Point> foreground_pts;
    foreground_pts.push_back(Point(0, 0));
    foreground_pts.push_back(Point(0, 1));
    vector<Point> background_pts;
    background_pts.push_back(Point(4, 4));
    background_pts.push_back(Point(4, 3));

    vector<Point> seg = getSegment(img, foreground_pts, background_pts);

    for(int i = 0; i < seg.size(); i++){
        cout<<seg[i].x<<", "<<seg[i].y<<endl;
    }

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

