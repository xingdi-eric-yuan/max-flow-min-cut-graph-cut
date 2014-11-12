#include "mouse_draw.h"
using namespace std;
using namespace cv;


void onMouse(int event, int x, int y, int flags, void*){
    
    switch(event){
    case CV_EVENT_MOUSEMOVE:
        //cout<<"mouse move, x = "<<x<<", y = "<<y<<endl;
        if(DO_DRAW){
            contour.push_back(Point(x, y));
        }
        break;
    case CV_EVENT_LBUTTONDOWN:
        DO_DRAW = true;   
        //cout<<"begin drawing ***********************"<<endl;
        contour.push_back(Point(x, y)); 
        break;
    case CV_EVENT_LBUTTONUP:
        //cout<<"end drawing ^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        DO_DRAW = false;
        break;
    }
}
