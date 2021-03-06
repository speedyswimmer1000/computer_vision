#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

#define WINWIDTH 1920
#define WINHEIGHT 1080

/* Keep the webcam from locking up when you interrupt a frame capture */
volatile int quit_signal=0;
#ifdef __unix__
#include <signal.h>
extern "C" void quit_signal_handler(int signum) {
 if (quit_signal!=0) exit(0); // just exit already
 quit_signal=1;
 printf("Will quit at next camera frame (repeat to kill now)\n");
}
#endif

vector<Point> ROI_Points;
int ROI_done = 0;

Mat drawCroppedImage(Mat& sourceImg, Mat& dstImg, vector<Point> ROI);
Mat translateImg(Mat &img, int offsetx, int offsety);

Mat translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size());
    return trans_mat;
}

Mat drawCroppedImage(Mat& sourceImg, Mat& dstImg, vector<Point> ROI){
	Mat mask = Mat::zeros(sourceImg.rows, sourceImg.cols, CV_8UC1);
	
	vector<Point> ROI_Poly;
	approxPolyDP(ROI, ROI_Poly, 1.0, true);

	fillConvexPoly(mask, &ROI_Poly[0], ROI_Poly.size(), 255, 8, 0);
	
	sourceImg.copyTo(dstImg , mask);
	return mask;
}


void mouseHandlerHSV(int event, int x, int y, int flags, void* param)
{
    /* user press left button */
    // Get the HSV value of the point.
    if (event == CV_EVENT_LBUTTONDOWN )
    {
    	//Mat* img = (Mat*) param;
    	//imshow("Show", *img);
    	
			x = (x > WINWIDTH) ? WINWIDTH : x;  // Makes sure the click is within the image, puts it on the edge of the screen. 
			y = (y > WINHEIGHT) ? WINHEIGHT : y;
			x = (x < 0 ) ? 0 : x;
			y = (y < 0 ) ? 0 : y;
			
			
    	//cout << img->at<Vec3b>(x, y) << endl;
    	Point point(x,y);
		//circle(*img, point, 3, Scalar(255, 255, 255), 3, 5);
		//imshow("Screen", *img);
    	ROI_Points.push_back( point );
    	
    	///Mat tmp = *img;
    }
    if (event == CV_EVENT_RBUTTONDOWN ){
    	ROI_done = 1;
    }
}

string type2str(int type) {
// Useful debugging tool for finding the type of an array. 
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main(int argc, char** argv){

	//Mat img = imread("test.jpg");
	
	VideoCapture cap(0);
	if(!cap.isOpened()){ // check if we succeeded
		return -1;
	}
	#ifdef __unix__
	   signal(SIGINT,quit_signal_handler); // listen for ctrl-C
	#endif
	
	namedWindow("Screen", WINDOW_NORMAL);
	resizeWindow("Screen", WINWIDTH, WINHEIGHT);
	cvSetMouseCallback("Screen", mouseHandlerHSV, NULL);
	Mat lastFrame;
	
//again:
	cap >> lastFrame;

	while(!ROI_done){  // Loop through, getting new images from the camera.
		//cout << "Setting " << setting + 'a' << endl;
		Mat frame;
		cap >> frame; // get a new frame from camera
		
		if (quit_signal) exit(0); // exit cleanly on interrupt

		for (int i = 0; i < ROI_Points.size(); i++){
			circle(frame, ROI_Points[i], 2, Scalar(255, 255, 255), 3, 5);
		}

		imshow("Screen", frame);  // Show the image on the screen

		char key = waitKey(1);
		if (key == ' '){
			//cout << "setting is " << key + 0<< endl;
			cout << "space bar\n";
		}
	}

	int maxCorners = 100;
	double qualityLevel = 0.01f;
	int minDistance = 1;
	int blockSize = 5;
	int useHarrisDetector = 0;
	double k = 0.04f;
	TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,30,0.01);
	Size winSize(10,10);

	Mat last, cropped, last_bw;
	cap >> last;
	Mat mask = drawCroppedImage(last, cropped, ROI_Points);
	vector<Point2f> lastCorners;
	cvtColor(last, last_bw, CV_BGR2GRAY);

	goodFeaturesToTrack(last_bw, lastCorners, maxCorners, qualityLevel, minDistance, 
		Mat(), blockSize, useHarrisDetector, k);
		
	for (int i = lastCorners.size() - 1; i >= 0; i--){
		int x = lastCorners[i].x;
		int y = lastCorners[i].y;
		if (mask.at<uchar>(y,x) == 0){
			// Not within ROI, remove point
			lastCorners.erase(lastCorners.begin() + i);
		}
	}
	goodFeaturesToTrack(last_bw, lastCorners, maxCorners, qualityLevel, minDistance, 
		Mat(), blockSize, useHarrisDetector, k);

	cout << lastCorners.size() << endl; 
	int dilation_size = 12;
	Mat element = getStructuringElement( MORPH_ELLIPSE,
                                   Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                   Point( dilation_size, dilation_size ) );

	while (1) {
		Mat frame, frame_bw;
		cap >> frame;
		vector<Point2f> corners;
		
		cvtColor(frame, frame_bw, CV_BGR2GRAY);
		goodFeaturesToTrack(frame_bw, corners, lastCorners.size(), qualityLevel, minDistance, 
			Mat(), blockSize, useHarrisDetector, k);
			
		/*if (corners.size() < 5) {
			ROI_done = 0;
			ROI_Points.clear();
			goto again;
		}*/

		vector<uchar> status2;
		vector<float> err;
		calcOpticalFlowPyrLK(last_bw, frame_bw, ROI_Points, corners, status2, err, winSize, 2, termcrit);
		vector<uchar> status;
		findFundamentalMat(lastCorners, corners, CV_FM_RANSAC, 3, 0.99, status);
		
		Mat homog = findHomography( lastCorners, corners);
		
		for (int i = corners.size() - 1; i >= 0; i--){
			if (status[i] == 0){ // outlier
				corners.erase(corners.begin() + i);
				lastCorners.erase(lastCorners.begin() + i);
			}
		}
		
		vector<Point2f> ROIout;
		vector<Point2f> pointsROI;
		for (int i = 0; i < ROI_Points.size(); i++){
			pointsROI.push_back(Point2f(ROI_Points[i].x, ROI_Points[i].y) );
		}
		if (ROI_Points.size() > 0){
			perspectiveTransform(pointsROI, ROIout, homog);
		}
		
		for (int i = 0; i < pointsROI.size(); i++){
			ROI_Points[i].x = (int) ROIout[i].x;
			ROI_Points[i].y = (int) ROIout[i].y;
			circle(frame, ROIout[i], 3, Scalar(255,255,255) );
		}

	/*	for (int i = status2.size()-1; i >= 0; i--) {
			if (status2.at(i) == 0) {
				corners.erase(corners.begin()+i);
				lastCorners.erase(lastCorners.begin()+i);
			}
		}
*/
  	/*	vector<Point> intCorners;
  		for (int i = 0; i < corners.size(); i++){
  			int x = (int) corners[i].x;
  			int y = (int) corners[i].y;
  			intCorners.push_back(Point(x,y) );
  		}
  		
  		Mat t1 = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
  		Mat t2 = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
  		Mat inpaintMask = drawCroppedImage(t1, t2, intCorners) ;*/
  		
  		Mat inpaintMask = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
  	//	vector<Point2f> hull;
  	//	convexHull( corners, hull, false, true );
//	approxPolyDP(hull, hull, 1.0, true);
  	//	vector<Point> intHull;
  	/*	for (int i = 0; i < corners.size(); i++){
  			int x = (int) hull[i].x;
  			int y = (int) hull[i].y;
  			intHull.push_back(Point(x,y) );
  		}
  		fillConvexPoly(inpaintMask, &intHull[0], intHull.size(), 255, 8, 0);
  		*/
  		
  		rectangle(inpaintMask, boundingRect(corners), 255, CV_FILLED, 8);
  		
//  		fillConvexPoly(mask, &ROI_Poly[0], ROI_Poly.size(), 255, 8, 0);
		//for (int i = 0; i < corners.size(); i++){
			//circle(inpaintMask, corners[i], 3, 255, 3, 5);
			//circle(frame, corners[i], 2, Scalar(255, 255, 255), 3, 5);
		//}
		
		dilate(inpaintMask, inpaintMask, element);
		//dilate(inpaintMask, inpaintMask, element);
		
		//inpaint(frame, inpaintMask, frame, 1, INPAINT_NS);
		
		if (quit_signal) exit(0); // exit cleanly on interrupt

		//imshow("Screen", inpaintMask);  // Show the image on the screen
		imshow("Screen", frame);

		char key = waitKey(1);
		if (key == ' '){
			//cout << "setting is " << key + 0<< endl;
			cout << "space bar\n";
		}
		last_bw = frame_bw;
		lastCorners = corners;
		vector<Point2f> tmp = corners;
		vector<Point> out;
		out.resize(corners.size() );
		copy(corners.begin(), corners.end(), out.begin() );
		ROI_Points = out;
	}
	
	return 0;
}

