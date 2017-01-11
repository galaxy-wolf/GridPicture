#include <opencv2/opencv.hpp>  
#include <vector>
#include <string>


using namespace cv;

const int row = 2;// 2;
const int col = 2;
const int picSize = 512;
const int interPicSize = 25;
const std::string picBase = ".\\sss\\";
const std::string picOut = "out.jpg";


int main()
{
	char temp[128];

	int outWidth = (picSize + interPicSize)* col - interPicSize;
	int outHeight = (picSize + interPicSize)* row - interPicSize;

	cv::Mat out(outHeight, outWidth, CV_8UC3, Scalar{ 255, 255, 255, 255 });

	int baseX = 0;
	int baseY = 0;
	for (int r = 0; r < row; r++)
	{
		baseX = 0;
		for (int c = 0; c < col; c++)
		{
			sprintf(temp, "%s%d.bmp", picBase.c_str(), r*col + c + 1);
			Mat in = imread(temp);
			printf("%s\n", temp);
			for (int i = 0; i < picSize; i++)
				for (int j = 0; j < picSize; j++)
					out.at<cv::Vec3b>(i + baseY, j + baseX) = in.at<cv::Vec3b>(i, j);

			baseX += picSize + interPicSize;
		}

		baseY += picSize + interPicSize;
	}

	std::vector<int> params;
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(100);   // that's percent, so 100 == no compression, 1 == full 

	sprintf(temp, "%s%s", picBase.c_str(), picOut.c_str());
	cv::imwrite(temp, out, params);
	imshow("out", out);
	waitKey();


	return 0;

}