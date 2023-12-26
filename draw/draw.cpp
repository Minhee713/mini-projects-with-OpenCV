#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img(Size(1024, 1024), CV_8UC3, Scalar(255, 255, 255));
Point ptOld;
vector<Point> ptNew;
int click_cnt = 0;

void on_mouse(int event, int x, int y, int flags, void*);
void check_key(void);

int main(void)
{

	namedWindow("img");
	imshow("img", img);
	setMouseCallback("img", on_mouse);
	check_key();
	destroyAllWindows();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		click_cnt++;
		cout << "click_cnt: " << click_cnt << endl;

		ptOld = Point(x, y);
		ptNew.push_back(ptOld);
		cout << "x: " << x << "y: " << y << endl;

		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_SHIFTKEY) {
			line(img, ptOld, Point(x, y), Scalar(255, 255, 255), 20);
			imshow("img", img);
		}
		break;
	default:
		break;
	}
}

void check_key(void)
{

	while (true) {
		int keycode = waitKey();

		if (keycode == 'c' && click_cnt >= 2) {
			double circle_x = ptNew[click_cnt - 2].x - ptNew[click_cnt - 1].x;
			double circle_y = ptNew[click_cnt - 2].y - ptNew[click_cnt - 1].y;
			double radius = sqrt(pow(circle_x, 2) + pow(circle_y, 2));
			circle(img, ptNew[click_cnt - 2], (int)radius, Scalar(0, 255, 255), 2, LINE_AA);
			imshow("img", img);
			click_cnt = 0;
			ptNew.clear();
		}
		else if (keycode == 'r' && click_cnt >= 4) {
			rectangle(img, ptNew[click_cnt - 4], ptNew[click_cnt - 2], Scalar(255, 0, 0), 2);
			imshow("img", img);
			click_cnt = 0;
			ptNew.clear();
		}
		else if (keycode == 'p' && click_cnt >= 3) {
			polylines(img, ptNew, true, Scalar(255, 0, 255), 2);
			imshow("img", img);
			click_cnt = 0;
			ptNew.clear();
		}
		else if (keycode == 'a') {
			Mat eraseImage(Size(1024, 1024), CV_8UC3, Scalar(255, 255, 255));
			img = eraseImage;
			imshow("img", img);
		}

		if (keycode == 27) {
			break;
		}

	}

}