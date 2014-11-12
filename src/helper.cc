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
