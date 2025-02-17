#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void convert_to_ascii(const string& folderName, vector<Mat> &frames){
    string signs = " -+*^%#$@";
    Mat varFrame;
    string filePath;
    fstream file;

    for (int num = 0; num < frames.size(); num++){
        filePath = folderName + to_string(static_cast<long long>(num))+ ".txt";
        file.open(filePath, ios_base::out);
        varFrame = frames[num];
        uchar value;

        for (int row = 0; row < varFrame.rows; row++){
            for (int col = 0; col < varFrame.cols; col++){
                value = varFrame.at<uchar>(row, col);
                file << signs[value/29];
            }
        }
        file.close();
    }

    //cout << frame << endl;
}

void extract_frames(const string& filename, vector<Mat>& frames){
    VideoCapture cap(filename);

    if(!cap.isOpened())  // check if we succeeded
        printf("cannot open");

    long long framesNum = cap.get(CAP_PROP_FRAME_COUNT); // contains the number of frames in the video;

    for(int frameNum = 0; frameNum < framesNum;frameNum++)
    {
        Mat frame;
        cap >> frame; // get the next frame from video
        Mat done;
        Mat done2;
        cvtColor(frame, done, COLOR_BGR2GRAY);
        resize(done, done2, Size(640, 360));
        frames.push_back(done2);
    }

    cap.release();
}

void save_frames(const string& foldername, vector<Mat>& frames){
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);
    string filePath;
    Mat matVar;

    for(int frameNumber=0; frameNumber != frames.size(); frameNumber++){
        matVar = frames[frameNumber];
        filePath = foldername + to_string(static_cast<long long>(frameNumber))+ ".jpg";
        imwrite(filePath, matVar,compression_params);
    }
}

void display(const string & folderName){

}

int main() {
    vector<Mat> frames;

    extract_frames("videoTest.mp4", frames);

    convert_to_ascii("ascii/", frames);

    display("ascii/");

    save_frames("frames/", frames);

    return 0;
}
