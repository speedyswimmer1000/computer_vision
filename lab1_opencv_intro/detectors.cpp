#include <iostream>
#include <string>
#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <sys/time.h>

using namespace cv;
using namespace std;

/* Keep the webcam from locking up when you interrupt a frame capture */
volatile int quit_signal=0;
#ifdef __unix__
#include <signal.h>
extern "C" void quit_signal_handler(int signum) {
 if (quit_signal!=0) exit(0); // just exit already
 quit_signal=1;
// printf("Will quit at next camera frame (repeat to kill now)\n");
}
#endif

int main(int argc, char* argv[]){

	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened()){ // check if we succeeded
		return -1;
	}
	#ifdef __unix__
	   signal(SIGINT,quit_signal_handler); // listen for ctrl-C
	#endif

	VideoWriter VOut;
   //VideoWriter writer("output.avi", CV_FOURCC('M','J','P','G'),
     //                      50.0, blank.size(), true);
	VOut.open("output.avi", CV_FOURCC('M','J','P','G'), 15, Size(640, 480), 1);

	Mat edges;
	namedWindow("Screen",CV_WINDOW_NORMAL);
	//namedWindow("original", 1);
	char setting = 'z'; // Canny default
	Mat frame;
	Mat gray;
	Mat last_frame;
	Mat out;

	cout << "Help: \n" << "t -- threshold\n" << "c -- canny\n" << "x -- corners\n" << "d -- diff\n" << "Any other key -- lines\n" << endl;

	for(;;){  // Loop through, getting new images from the camera.
		Mat thresh_out;
		Mat canny_out;
		Mat corner_out;
		//cout << "Setting " << setting + 'a' << endl;
		cap >> frame; // get a new frame from camera
		if (last_frame.empty()){
			cvtColor(frame, last_frame, CV_BGR2GRAY);
		}else{
			last_frame = gray.clone();  // Which was the last gray frame, before I update it. 
		}
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (setting == 't'){
	// Threshold
			threshold(gray, out, 100, 255, THRESH_BINARY); // Threshold: 100. White value: 255
		}else if (setting == 'c'){
	// Canny
			GaussianBlur(gray, edges, Size(7,7), 1.5, 1.5);
			Canny(edges, out, 5, 30, 3);
		}else if (setting == 'x'){
	// Corners
	 		vector<Point2f> corners;
	 		double qualityLevel = 0.04;
			double minDistance = 30;
			int blockSize = 5;
			bool useHarrisDetector = false;
			double k = 0.04;
			int maxCorners = 100;

			corner_out = gray.clone();

			goodFeaturesToTrack( gray, corners, maxCorners, qualityLevel,
			               minDistance, Mat(), blockSize, useHarrisDetector, k );

			int r = 4;
			Size winSize = Size( 5, 5 );
			Size zeroZone = Size( -1, -1 );
			TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );

			/// Calculate the refined corner locations
			cornerSubPix( gray, corners, winSize, zeroZone, criteria );

	 	    for( int i = 0; i < corners.size(); i++ )
			   { circle( corner_out, corners[i], r, Scalar(255, 255, 255), -1, 8, 0 ); }
			out = corner_out.clone();
		}else if (setting == 'd'){
	// Diff
			absdiff(gray, last_frame, out);
		}
		else{
	// Lines
			GaussianBlur(gray, edges, Size(7,7), 1.5, 1.5);
			Canny(edges, canny_out, 7, 30, 3);
			vector<Vec4i> lines;
			  HoughLinesP(canny_out, lines, 1, CV_PI/180, 50, 50, 10 );
			  for( size_t i = 0; i < lines.size(); i++ )
			  {
				Vec4i l = lines[i];
				line( edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
			  }
			out = edges.clone();
		}
		imshow("Screen", out);  // Show the image on the screen
		Mat video;
		cvtColor(out, video, CV_GRAY2RGB);
			VOut << video;

		char key = waitKey(30);
		if (key != 0 && key != -1){
			//cout << "setting is " << key + 0<< endl;
			setting = key;
			key = 0;
		}
		if (quit_signal) exit(0); // exit cleanly on interrupt
	
		//imshow("original", gray);
		//if(waitKey(30) >= 0) break;
	}

// the camera will be deinitialized automatically in VideoCapture destructor

return 0;
}

