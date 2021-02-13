/* @functions:  imshow
 * @brief:      A simple progrma to use the webcam with OpenCV is shown
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace std;
using namespace cv;

int main(){
  int key = 0;
  Mat frame;
  VideoCapture cap(0); //Create a VideoCapture object, '0' to use the webcam
   
  //Check if camera opened successfully
  if(!cap.isOpened())
  {
    cout << "Error opening video stream" << endl;
    return -1;
  }
	
  while(1){

    cap >> frame; //Capture a frame
 
    //If the frame is empty, break immediately
    if(frame.empty())
      break;

    //Display the resulting frame
    imshow("Camera", frame);

    // Press ESC on keyboard to exit
    key = waitKey(10);
    if(key == 27)
      break;
  }
 
  //Before going, release the video capture object
  cap.release();
	
  return 0;
}

