#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <camera/camera_wrapper.h>

using namespace std;

int main() {
    CameraWrapper camera(0);
    if(!camera.init()){
        cout << "Init fail!" << endl;
        exit(-1);
    }
    cv::Mat mat;
    std::string name;
    cout << "The video path to save: ";
    cin >> name;
    cv::VideoWriter *video;
    bool save = false;
    while(camera.read(mat)){
        cv::imshow("frame", mat);
        int k;
        if((k=cv::waitKey(33)) == 'q'){
            if(save){
                delete video;
            }
            break;
        }else if(k == 's'){
            if(!save) {
                video = new cv::VideoWriter(name, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 33, cv::Size(480, 640));
                save = true;
                cout << "Start save" << endl;
            }
        }else if(k == 'e'){
            if(save){
                delete video;
                save = false;
                cout << "Stop save" << endl;
            }
        }
        if(save) {
            video->write(mat);
        }
    }
    return 0;
}