/* @functions:  int2string, CV_FOURCC, cap.get(CV_CAP_PROP_FRAME_WIDTH, CAP_PROP_FPS), putText
 * @brief:      How to read, edit and save a video from the webcam (show the time and the frame position)
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp" //Include OpenCV header file

using namespace std;
using namespace cv;

string int2string(int number){ //Function to convert an integer number to a string
  std::stringstream ss;
  ss << number;
  return ss.str();
}

int main(int argc, char** argv )
{
  string filename;
  int key = 0;

  filename = "output.avi";

  VideoCapture cap(0); //Create a VideoCapture object. '0' = webcam
  VideoWriter writer; //Create VideoWriter object, not initialized yet

  //Check if videocapture opened successfully
  if(!cap.isOpened())
  {
    cout << "Could not open the video capture" << endl;
    return -1;
  }

  //Getting the video properties
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  Size frame_size(frame_width, frame_height);
  double fps = cap.get(CAP_PROP_FPS); //Frames per second

  int counter = 0; //Counter to compute the time

  cout << "Source info:\n Size:" << frame_size << endl;
  cout << " Frames per seconds:" << fps << endl;

  double fontScale = 2; //Size of the font

  //Define the video codec by FOURCC, recoding method, fourcc integer
  int fcc = CV_FOURCC('X','V','I','D');
  //'X','V','I','D' open source codec
  //'M','J','P','G' Motion JPEG video
  //'X','2','6','4' open source H.264 implementation (compressed)

  //Initialize the VideoWriter object
  writer = VideoWriter(filename,fcc,fps,frame_size,true); //Using the same fps

  if(!writer.isOpened()){
    cout << "Could not open the video writer" << endl;
    return -1;	//Exit
  }

  string window_name = "Video window";
  namedWindow(window_name, WINDOW_AUTOSIZE);


  while(1)
  {
    Mat frame;

    //Capture the actual frame
    cap.read(frame); //cap >> frame;

    //If the frame is empty, break immediately
    if(frame.empty())
    {
      cout << "Error" << endl;
      return -1;
    }

    counter++;

    string pos_frame = int2string(counter);
    putText(frame,"frame = "+pos_frame, Point(10,40),1,fontScale,Scalar(0,0,0),1.5,1);

    double time_seg = (double)(counter/fps); //Compute the time
    cout << "time [s]: " << time_seg << endl;

    int time_s = (int)(time_seg); //Truncate the time
    string t_s = int2string(time_s);
    putText(frame,"time [s] = "+t_s, Point(10,80),1,fontScale,Scalar(0,0,0),1.5,1);

    //Write the actual frame
    writer.write(frame); //writer << frame;

    putText(frame,"REC",Point(10,120),1,fontScale,Scalar(0,0,255),2,1);

    imshow( window_name, frame ); //Display the resulting frame

    //Press ESC on keyboard to exit
    key = waitKey(1);
    if(key == 27) break; //This breaks the while loop

  }

  //Before going, release the video capture and write object
  cap.release();
  writer.release();

  return 0;
}

