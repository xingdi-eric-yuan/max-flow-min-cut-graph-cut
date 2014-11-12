#pragma once
#include <iostream>
#include <stack>
#include <unordered_set>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "data_structure.h"
#include "graph.h"
#include "helper.h"
#include "mouse_draw.h"

#define ATD at<double>
#define AT3D at<cv::Vec3d>
#define elif else if
//#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

using namespace std;
using namespace cv;

//extern Mat img;
extern bool DO_DRAW;
extern vector<Point> contour;
