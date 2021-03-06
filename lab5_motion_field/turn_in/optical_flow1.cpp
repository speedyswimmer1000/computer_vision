#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <string>
#include <sstream>
#include <vector>

/*
*	Optical Flow Program, Ben Lewis, 3/18/15, Robot Vision Class
*	Uses the LK algorithm to determine where features in one image end up in a subsequent image. 
*
*/
//#define FRAME_DIFFERENCE 1 // One frame difference = sequential frames. 2 frame diff = skip one frame, etc. 

using namespace cv;
using namespace std;

int main(int argc, char** argv){

	int numImages = 17;
	namedWindow("Screen",WINDOW_NORMAL);
	resizeWindow("Screen", 1800, 1000);
	
	// Max 500 points to track, quality of 0.01, min. distance 15 pixels, etc. 
	const int MAX_COUNT = 500;
	const float QUALITY = 0.01;
	const int MIN_DIST = 10;
	Size winSize(10,10);
	vector<Point2f> points[2];  // Index 0 = last image, index 1 = this image. 
	TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
	Mat image, prevImage;
	
	VideoWriter Vout;
	//optical_flow.avi
	Vout.open("junk.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(640,480), 1);
	
	for (int j = 1; j < 4; j++){
	// Do for subsequent frames, 2 frame difference, and 3 frame difference. 
		for (int i = 0; i < numImages - j; i++){
		
		// Open a previous and a next image to compute the optical flow between them. 
			ostringstream prev;
			prev << "optical_flow/O" << i + 1 << ".jpg";
			ostringstream next;
			next << "optical_flow/O" << i + 1 + j << ".jpg";
			
			
			/*ostringstream prev;
			prev << "parallel_cube/ParallelCube" << i + 1 << ".jpg";
			ostringstream next;
			next << "parallel_cube/ParallelCube" << i + 1 + j << ".jpg";*/
		
			Mat lastImage, nextImage;
		
			string lastFilename = prev.str();
			lastImage = imread(lastFilename, CV_LOAD_IMAGE_GRAYSCALE);
			string nextFilename = next.str();
			nextImage = imread(nextFilename, CV_LOAD_IMAGE_GRAYSCALE);
			
			// Get good features to track, which will be fed into the optical flow algorithm.
			goodFeaturesToTrack(lastImage, points[0], MAX_COUNT, 0.01, MIN_DIST, Mat(), 3, 0, 0.04);
			cornerSubPix(lastImage, points[0], winSize, Size(-1,-1), termcrit);
			
			// Set up some output vectors, then compute optical flow. 
			vector<uchar> status;
			vector<float> err;
			calcOpticalFlowPyrLK(lastImage, nextImage, points[0], points[1], status, err, winSize, 3, termcrit);

			cvtColor(nextImage, nextImage, CV_GRAY2BGR);
			
			// Graph previous point (circle) and then a line between the two points, showing where the point has moved. 
			for (int k = 0; k < points[0].size(); k++){
				circle(nextImage,points[0][k],3,cv::Scalar(0,255,0),1);
				line(nextImage, points[0][k], points[1][k], Scalar(0,0,255), 1);
			}
			
			// Write out the image. 
			imshow("Screen", nextImage);
			for (int vid = 0; vid < 9; vid++){
				Vout << nextImage;  // SUPER HACK!!! YAY! Video writer is super fast at 30fps, so write more frames. 
			}
			waitKey(0);
			
		}
	
	}

}
