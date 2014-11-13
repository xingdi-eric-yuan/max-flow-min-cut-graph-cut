#pragma once
#include "general_settings.h"

using namespace std;
using namespace cv;

void removeContourDuplicate(vector<Point> &);

int point2index(const Mat &, const Point &);

int point2index(const Mat &, int, int);

Point index2point(const Mat &, int);

bool isInsideImage(const Mat &, int, int);

bool isInsideImage(const Mat &, const Point &);

double getEdgeCapacity(const Mat &, int, int, int, int);

void image2Graph(Graph &, const Mat &);

void addSpecificEdges(Graph &, const Mat&, const vector<Point>& , int, double);

vector<Point> getSegment(const Mat&, const vector<Point> &, const vector<Point> &);