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

vector<Point> getMousePoints(const Mat &img){
    Mat imgshow;
    cvtColor(img, imgshow, CV_GRAY2RGB);
    contour.clear();
    cout<<"Use mouse please, press left button down and move mouse to select points..."<<endl;
    cout<<"-- Press D to draw selected points on image."<<endl;
    cout<<"-- Press P to print selected points."<<endl;
    cout<<"-- Press ESC to next step."<<endl;
    const string winName = "image";
    namedWindow( winName, CV_WINDOW_AUTOSIZE );
    imshow(winName, imgshow);
    setMouseCallback( winName, onMouse, 0);
    int key;
    do{
        key = waitKey(0);
        switch((char)key){
            case 'p':
                for(int i = 0; i < contour.size(); i++){
                    cout<<"x = "<<contour[i].x<<", y = "<<contour[i].y<<endl;
                }
                break;
            case 'd':
                for(int i = 0; i < contour.size(); i++){
                    circle(imgshow, contour[i], 2, Scalar(0, 0, 255), 1); 
                }
                imshow(winName, imgshow);
                break;
        }
    }while (key > 0 && key != 27);
    destroyWindow(winName);
    //cout<<"contour.size = "<<contour.size()<<endl;
    removeContourDuplicate(contour);
    //cout<<"contour.size = "<<contour.size()<<endl;
    vector<Point> res = contour;
    contour.clear();
    imgshow.release();
    return res;
}

