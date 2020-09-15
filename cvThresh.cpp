// Have a look to: https://docs.opencv.org/3.4/d4/d7d/tutorial_harris_detector.html

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/// Global variables
int threshold_value = 80;
int const max_value = 255;

Mat camFrame, grayFrame, binFrame, dst;

const char* threshed_window = "Binary";

/// Function headers
void Threshold_Demo( int, void* );

int main() {
    VideoCapture stream1(0);   // 0 is the id of video device.0 if you have only one camera.
    if (!stream1.isOpened()) { // check if video device has been initialised
        cout << "cannot open camera";
    }

    while (true) {
        stream1.read(camFrame);
        imshow("Webcam", camFrame);

        //Canny( camFrame, grayFrame, 0.25, 0.5, 3, true );
        cvtColor( camFrame, grayFrame, COLOR_BGR2GRAY );
        //imshow("Grayscale", grayFrame);

        createTrackbar( "Threshold: ", threshed_window, &threshold_value, max_value, Threshold_Demo);
        Threshold_Demo( 0, 0 );

        if (waitKey(30) >= 0 )
            break;
    }

    return 0;
}

void Threshold_Demo( int, void* )
{
    threshold( grayFrame, binFrame, threshold_value, max_value, THRESH_BINARY );
    imshow( threshed_window, binFrame );
}
