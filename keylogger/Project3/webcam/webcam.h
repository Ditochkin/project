#include <opencv2/core.hpp>
#include <thread>

const std::string g_photoPath = "../../photos/";

class Webcam
{
private:
	std::thread m_webcamThread;

public:
	Webcam() : m_webcamThread(std::thread(&Webcam::captureFrames, this))
	{
	}

	void captureFrames();

	~Webcam()
	{
		if (m_webcamThread.joinable())
		{
			m_webcamThread.join();
		}
	}
};