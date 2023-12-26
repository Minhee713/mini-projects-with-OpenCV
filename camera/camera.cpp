#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in(void);


int main(void)
{
  camera_in();
  destroyAllWindows();
  return 0;
}

void camera_in()
{
  Mat newFrame;
  Mat frame;
  Mat gray;
  Mat img_diff;

  VideoCapture cap(0);

  bool bFlag = false;

  if (!cap.isOpened()) {
    cerr << "Camera open failed!" << endl;
    return;
  }

  while (true) {
    cap >> frame;
    if (frame.empty())
      break;

    int keycode = waitKey(10);

    cvtColor(frame, gray, COLOR_BGR2GRAY);

    imshow("frame", frame);
    imshow("gray", gray);

    if (keycode == 's') {
      cout << "s pressed!!!!! " << endl;
      newFrame = gray.clone();
      bFlag = false;
    }


    if (keycode == 'i') {
      cout << "i pressed!!!!" << endl;
      bFlag = true;
    }

    if (bFlag)
    {
      cout << "diff!" << endl;
      absdiff(newFrame, gray, img_diff);
      imshow("diff", img_diff);
    }

    if (keycode == 27)
      break;
  }

}