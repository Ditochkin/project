#include <opencv2/core.hpp>
#include <thread>

const std::string g_photoPath = "../../photos/";

class Webcam
{
private:
	std::thread webcamThread;

public:
	Webcam() : webcamThread(std::move(std::thread(&Webcam::captureFrames, this)))
	{
	}

	void captureFrames();

	~Webcam()
	{
		if (webcamThread.joinable())
		{
			webcamThread.join();
		}
	}
};