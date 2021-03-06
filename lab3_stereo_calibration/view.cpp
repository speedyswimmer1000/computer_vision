#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <boost/algorithm/string.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include <pthread.h>
#include <ctime>

#define NUM_THREADS 2
volatile int running_threads = 0;

using namespace cv;
using namespace std;

Mat readIntrinsicFile(string fileName){
	ifstream File;
	File.open(fileName.c_str());
	string line;
	getline (File,line);
	istringstream iss(line);
	vector<string> fields;
	split(fields, line, boost::is_any_of(" ") );

	Mat intrinsics = Mat(3,3, CV_64F);

	for(int i = 0; i < 9; i++){
		intrinsics.at<double>(i / 3, i %3) = (double)atof(fields[i].c_str());
	}
	return intrinsics;
}

Mat readDistortionFile(string fileName){
	ifstream File;
	File.open(fileName.c_str());
	string line;
	getline (File,line);
	istringstream iss(line);
	vector<string> fields;
	split(fields, line, boost::is_any_of(" ") );

	Mat distort = Mat::ones(5,1, CV_64F);

	for(int i = 0; i < 5; i++){
		distort.at<double>(i) = (double)atof(fields[i].c_str());
	}
	return distort;
}

int main(){
	
	VideoCapture cap("http://192.168.1.90/mjpg/video.mjpg"); // open the default camera
	if(!cap.isOpened()){ // check if we succeeded
		return -1;
	}

	namedWindow("screen", WINDOW_NORMAL);

	Mat intrinsic = readIntrinsicFile("intrinsic_webcam.txt");
	Mat distortion = readIntrinsicFile("distortion_webcam.txt");

	for ( ;;){
		Mat img;
		cap >> img;
	undistort(img, img, intrinsic, distortion);

		imshow("screen", img);
		waitKey(2);

		

	}
}
