/* @functions:   mouse_callback, setMouseCallback, createButton
 * @Description: A simple program to extract a ROI from an image using mouse events and displaying checkbox and push button
 * @author:      C. Mauricio Arteaga-Escamilla
 */
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file
//Source: https://docs.opencv.org/master/dc/d46/group__highgui__qt.html#gad15c7adb377e778dc907c0e318be193e

using namespace cv;
using namespace std;

string my_window = "Image";

//Global variables. Note: those variables can be part of my custom struct
Mat img;
Point corner1, corner2;
Rect box;
bool ldown = false, lup = false; //Initial values

struct userdata{ //My custom struct called 'userdata'. Default values
  Scalar color = Scalar(0,0,255);
  int thickness = 4;
  string cropped_img_win = "Result: Cropped Image";
};


void mouse_callback(int event, int x, int y, int, void* data_ptr) //The flags argument is not used
{
  userdata *data = ((userdata *) data_ptr); //Pass the pointer to the local variable
  if(event == EVENT_LBUTTONDOWN) //If the left button is clicked
  {
    ldown = true;
    corner1.x = x;
    corner1.y = y;
  }

  if(event == EVENT_LBUTTONUP) //If the left button is released
  {
    lup = true;
    corner2.x = x;
    corner2.y = y;
  }

  if(ldown == true && lup == false) //Create the effect of selecting
  {
    Mat temp_img = img.clone(); //A temporal image is used
    rectangle(temp_img, corner1, Point(x, y), data->color, data->thickness);
    imshow(my_window, temp_img);
  }

  if(ldown == true && lup == true) //Define the box
  {
    box.width = abs(corner1.x -corner2.x);
    box.height = abs(corner1.y - corner2.y);
    box.x = min(corner1.x, corner2.x);
    box.y = min(corner1.y, corner2.y);

    if(box.width == 0 || box.height == 0) //Probably, a double click event occurred
    {
      cout << "Try again...\n";
    }else{
      Mat cropped_img = img(box);
      imshow(data->cropped_img_win, cropped_img);
    }
    ldown = false;
    lup = false;
  }
}

void callback_checkbox_button(int state, void*)
{ //It could be 0 or 1 for a check box button
  cout << "check box state: " << state << endl;
}

void callback_push_button(int state, void *data_ptr)
{
  cout << "You clicked the push button, state value: " << state << endl;

  userdata *data = ((userdata *) data_ptr);
  destroyWindow(data->cropped_img_win); //Close the specified window
}


int main(int argc, char** argv )
{
  img = imread("picture.jpeg", IMREAD_COLOR); //Read the image

  if( !img.data )
  {
    printf("No image data\n");
    return -1; //Exit
  }


  //ASSIGNING SOME VALUES
  userdata local_data;
  local_data.color = Scalar(255,255,255);
  local_data.thickness = 4;

  namedWindow(my_window, WINDOW_NORMAL); //Create the window to show the image
  //resizeWindow(my_window,Size(src_img.cols/2,src_img.rows/2)); //With WINDOW_NORMAL


  imshow(my_window, img); //Display the image

  //set the callback function for any mouse event. Only events in that particular window will trigger
  setMouseCallback(my_window, mouse_callback, &local_data); //this specific callback


  //Creating check-box and push buttons in the "main settings" window (Control panel)
  //createButton("Check-box",callback_checkbox_button, NULL, QT_CHECKBOX, 0); //Initial state = off
  //createButton("Close window",callback_push_button, &local_data, QT_PUSH_BUTTON);


  cout << "Select the region of interest.\nPress any key to exit" << endl;
  waitKey(0);
  return 0;
}
