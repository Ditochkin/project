#include "webcam.h"
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <vector>
#include <chrono>
#include <time.h>
#include <Windows.h>

void Webcam::captureFrames()
{
	LPCTSTR dirPath = L"../../photos";
	CreateDirectory(dirPath, nullptr);

	cv::VideoCapture cap;
	
	while (true)
	{
		cap.open(0);
		if (!cap.isOpened()) {
			std::cerr << "Failed to open video device !" << std::endl;
			return;
		}
		std::cout << "Device was opened\n";

		cv::Mat frame;

		for (int i = 0; i < 10; ++i)
		{
			if (!cap.read(frame))
			{
				std::cerr << "Failed to read image!" << std::endl;
				return;
			}
			std::cout << "Frame was captered\n";
		}

		std::vector<int> params(2);
		params[0] = cv::IMWRITE_JPEG_QUALITY;
		params[1] = 50;


		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		ltm.tm_year += 1900;
		ltm.tm_mon += 1;
		std::string date;
		date.reserve(32);
		date = std::to_string(ltm.tm_hour) + "_" + std::to_string(ltm.tm_min) + "_" + std::to_string(ltm.tm_sec) + "_" + std::to_string(ltm.tm_mday) + std::to_string(ltm.tm_mon) + std::to_string(ltm.tm_year);

		if (!cv::imwrite(g_photoPath + date + ".jpg", frame, params))
		{
			std::cerr << "Failed to save image!" << std::endl;
			return;
		}

		cap.release();
		frame.release();

		std::this_thread::sleep_for(std::chrono::seconds(60));
	}
	
}