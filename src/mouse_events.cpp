/* @functions:  setMouseCallback
 * @brief:      A simple program to show how to use mouse events
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace cv;
using namespace std;

//This function will be called every time that mouse events occur in the specified window
void mouseHandler(int event, int x, int y, int flags, void* userdata)
{
   cout << "\n-- event: " << event << endl;
   cout << "mouse position: (" << x << ", " << y << ")" << endl;
   cout << "flags: " << flags << endl;

  //Simple events comparison
  if( event == EVENT_LBUTTONDOWN ) { cout << "Left button of the mouse is clicked" << endl; }
  else if( event == EVENT_RBUTTONDOWN ) { cout << "Right button of the mouse is clicked" << endl; }
  else if( event == EVENT_MBUTTONDOWN ) { cout << "Middle button of the mouse is clicked" << endl; }
  else if( event == EVENT_MOUSEMOVE ) { cout << "Mouse move over the window" << endl; }

  //Comparisons using the 'flags' argument. Note: flags = event_flag + another event_flag
  if( flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON) )
  {
    cout << "Left mouse button is clicked while pressing CTRL key" << endl;
  }
  else if( flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_RBUTTON) )
  {
    cout << "Right mouse button is clicked while pressing SHIFT key" << endl;
  }
  else if( flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_CTRLKEY + EVENT_FLAG_ALTKEY) )
  {
    cout << "SHIFT, CTRL and ALT keys are pressed" << endl; //To execute, move your mouse
  }
  else if ( event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_ALTKEY) //ALT is a particular case
  {//For the ALT KEY, AND operation is nedeed with the event
    cout << "Mouse is moved over the window while pressing ALT key" << endl;
  }
}

int main(int argc, char** argv )
{
  Mat img;
  img = imread("lena.jpg", IMREAD_COLOR);

  if( !img.data )
  {
    printf("No image data\n");
    return -1; //Exit
  }

  //Creating the window
  string img_window = "Color Image";
  namedWindow(img_window, WINDOW_AUTOSIZE);

  setMouseCallback(img_window, mouseHandler, NULL); //set the callback function for any mouse event ('NULL' or '0')

  imshow(img_window, img); //Display the color image

  cout << "Press ESC key to exit" << endl;

  while(1){ //This loop is needed since key events are used
    int key = waitKey(10);
    if(key == 27)
      break;
  }

  return 0;
}
