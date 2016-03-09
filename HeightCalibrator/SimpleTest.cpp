#include "stdafx.h"
#include "SimpleTest.h"


void SimpleTest::Run(std::string pImagePath, std::vector<Post> &pPosts, PostImage pTestPost)
{
	// Initialization

	HeightCalibrator calibr;
	LineF skyline;
	calibr.Initialize(pPosts, &skyline);

	// Processing

	float height;
	calibr.GetHeight(pTestPost, height);
	std::cout << "Height: " << height << "\n";

	// Output results

	cv::namedWindow("output");
	cv::Mat img = cv::imread(pImagePath);
	if (img.empty()) return;
	for (unsigned int i = 0; i < pPosts.size(); ++i)
		cv::line(img, cv::Point(pPosts[i].BaseX, pPosts[i].BaseY), cv::Point(pPosts[i].BaseX, pPosts[i].TopY), cv::Scalar(0, 0, 255), 2);
	cv::line(img, cv::Point(pTestPost.BaseX, pTestPost.BaseY), cv::Point(pTestPost.BaseX, pTestPost.TopY), cv::Scalar(0, 255, 0), 2);
	cv::line(img, cv::Point((int)skyline.Pt1.X, (int)skyline.Pt1.Y), cv::Point((int)skyline.Pt2.X, (int)skyline.Pt2.Y), cv::Scalar(255, 0, 0), 2);

	cv::imshow("output", img);

	cv::waitKey(0);
}
