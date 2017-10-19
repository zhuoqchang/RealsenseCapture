#include <windows.h>
#include <iostream>
#include <fstream>

#include <pxcsensemanager.h>


class MyHandler :public PXCSenseManager::Handler {
public:
	virtual pxcStatus PXCAPI OnNewSample(pxcUID, PXCCapture::Sample * sample) {
		return PXC_STATUS_NO_ERROR;
	}
};

class Realsense {

public:
	Realsense() {
	};
	~Realsense() {
	};

	void init() {
		// need to add input to specify save location
		int width = 640;
		int height = 480;
		float frameRate = 30.0f;


		pxcSenseManager = PXCSenseManager::CreateInstance();

		// std::string outputFile_s = outputFolder + "gaze_recording.rssdk";
		std::string outputFile_s = "./gaze_recording.rssdk";
		std::wstring outputFile_ws = std::wstring(outputFile_s.begin(), outputFile_s.end());
		const wchar_t* outputFile = outputFile_ws.c_str();
		pxcSenseManager->QueryCaptureManager()->SetFileName(outputFile, true);


		pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_IR, width, height, frameRate);
		pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_COLOR, width, height, frameRate);
		pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, width, height, frameRate);

		pxcSenseManager->Init(&handler);
		pxcSenseManager->StreamFrames(false);

	}

	void stop() {
		pxcSenseManager->Release();
	}

private:
	PXCSenseManager* pxcSenseManager;
	MyHandler handler;
};

int main(int argc, char* argv[]) {
	Realsense rs;
	// start the recording
	rs.init();
	// wait a long time
	for (int i = 0; i < 10000000; i++) {
	}
	// stop the recording
	rs.stop();
}