#include "opencv2/opencv.hpp"
#include <signal.h>
#include <cstdio>
#include <string>
#include <unistd.h>

using namespace std;
using namespace cv;

bool isContinue = true;
const int FRAME_RATE = 24;
const bool ISCOLOR = true;
const int CODEC = cv::VideoWriter::fourcc('F', 'M', 'P', '4'); //for .avi file
const std::string SRC_DIR = std::string(__FILE__).erase(std::string(__FILE__).rfind('/'));

void sigint_handler(int s)
{
    printf("--- SIGINT ---\n");
    isContinue = false;
}

string getCurrentTime()
{	
	time_t curr_time = time(NULL);
	char time_char[128];
	strftime(time_char, 128, "%Y-%m-%d-%H%M%S", localtime(&curr_time));
	string time_str(time_char);
	return time_str;
}

int main(int argc, char** argv)
{
    signal(SIGINT, sigint_handler);
    VideoCapture capture(0);
    Size size = Size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH), (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT));
    VideoWriter writer;

	string name = SRC_DIR + "/../recordings/record_" + getCurrentTime() + ".avi";
	writer.open(name, CAP_FFMPEG, CODEC, FRAME_RATE, size, ISCOLOR);

	if (!writer.isOpened())
	{
		cout << "Could not open file: " + name << endl;
		exit(-1);
	}

    while (isContinue)
    {

        if (!capture.isOpened())
        {
            capture.open(0);
            sleep(1);
            continue;
        }
        else
        {
            Mat frame;
            capture >> frame; // get a new frame from camera
            imshow("frame", frame);
            writer.write(frame);
            waitKey(1);
        }
    }
}
