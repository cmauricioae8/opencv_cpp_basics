/* @functions:  int2string, CV_FOURCC, cap.get(CV_CAP_PROP_FRAME_WIDTH, CAP_PROP_FPS, CV_CAP_PROP_FRAME_COUNT,
 * CV_CAP_PROP_POS_FRAMES), putText
 * @brief:      How to read, edit and save a video from another video (show the time and the frame position)
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp" //Include OpenCV header file
//#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

string int2string(int number){ //Function to convert an integer number to a string
  std::stringstream ss;
  ss << number;
  return ss.str();
}

int main(int argc, char** argv ) //char *argv[]
{
  string source, filename;
  bool finish = false;
  int key = 0;

  if (argc >= 3)
  {
    source = argv[1]; //Source video
    filename = argv[2]; //Output video name
  }else {
    cout << "Not enough parameters. Default values" << endl;
    source = "short_vid.avi";
    filename = "output.avi";
  }


  VideoCapture cap(source); //Create a VideoCapture object
  VideoWriter writer; //Create a VideoWriter object, not initialized yet

  //Check if videocapture opened successfully
  if(!cap.isOpened())
  {
    cout << "Could not open the video capture: " << source << endl;
    return -1;
  }

  //Getting the video properties
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  Size frame_size(frame_width, frame_height);
  double fps = cap.get(CAP_PROP_FPS); //after open the capture obj
  int total_frames = cap.get(CV_CAP_PROP_FRAME_COUNT);

  cout << "Source info:\n Size:" << frame_size << endl;
  cout << " Frames per seconds:" << fps << endl;
  cout << " Total frames: " << total_frames << endl;

  //Define the output video fps
  int FPS = 30; //Frames per second
  double fontScale = 2; //Size of the font

  //Define the video codec by FOURCC, recoding method, fourcc integer
  int fcc = CV_FOURCC('X','V','I','D');
  //'X','V','I','D' open source codec
  //'M','J','P','G' Motion JPEG video
  //'X','2','6','4' open source H.264 implementation (compressed)

  //Initialize the VideoWriter object
  writer = VideoWriter(filename,fcc,FPS,frame_size,true);

  if(!writer.isOpened()){
    cout << "Could not open the video writer" << endl;
    return -1;	//Exit
  }

  //Creating the video window
  string window_name = "Video window: "+source;
  namedWindow(window_name, WINDOW_NORMAL);


  while(!finish) //while finish == false
  {
    cout << "Starting video" << endl;
    cap.set(CV_CAP_PROP_POS_FRAMES, 0); //Set the initial videocapture position on 0
    while(cap.get(CV_CAP_PROP_POS_FRAMES) <= total_frames-1)//Compare if the video has not finished
    {
      Mat frame;

      //Capture frame-by-frame
      cap.read(frame); //cap >> frame;

      //If the frame is empty, break immediately
      if(frame.empty())
      {
        cout << "Error: frame empty" << endl;
        return -1;
      }

      //Getting the frame position
      int frame_pos = cap.get(CV_CAP_PROP_POS_FRAMES);
      string pos_frame = int2string(frame_pos);
      putText(frame,"frame pos = "+pos_frame, Point(10,50),2,fontScale,Scalar(0,0,0),1.5,1);

      //double time_seg = cap.get(CV_CAP_PROP_POS_AVI_RATIO)*total_frames/fps;
      double time_seg = (double)(frame_pos/fps);
      //cout << "time [s]: " << time_seg << endl;

      //Getting the time
      int time_s = (int)(time_seg); //Truncate the time
      string t_s = int2string(time_s);
      putText(frame,"time [s] = "+t_s, Point(10,150),2,fontScale,Scalar(0,0,0),1.5,1);

      //Write the frame into the filename
      writer.write(frame); //writer << frame;

      putText(frame,"REC",Point(10,400),2,4*fontScale,Scalar(0,0,255),4,1);

      imshow( window_name, frame ); //Display the resulting frame

      // Press ESC on keyboard to exit
      key = waitKey(1);
      if(key == 27)
      {
          finish = true; //This will break the first while
          break; //Break this loop (comparison of the frames)
      }

    }
  }

  //Before going, release the video capture and write object
  cap.release();
  writer.release();

  return 0;
}
