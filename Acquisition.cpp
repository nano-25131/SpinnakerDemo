#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>



using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Use the following enum to select the stream mode
enum StreamMode
{
	STREAM_MODE_TELEDYNE_GIGE_VISION, // Teledyne Gige Vision is the default stream mode for spinview which is supported on Windows
	STREAM_MODE_PGRLWF, // Light Weight Filter driver is our legacy driver which is supported on Windows
	STREAM_MODE_SOCKET, // Socket is supported for MacOS and Linux, and uses native OS network sockets instead of a
	// filter driver
};

#if defined(WIN32) || defined(WIN64)
const StreamMode chosenStreamMode = STREAM_MODE_TELEDYNE_GIGE_VISION;
#else
const StreamMode chosenStreamMode = STREAM_MODE_SOCKET;
#endif


// This function demonstrates how we can change stream modes.
int SetStreamMode(CameraPtr pCam)
{
	int result = 0;

	// Retrieve Stream nodemap
	const INodeMap& sNodeMap = pCam->GetTLStreamNodeMap();

	// The node "StreamMode" is only available for GEV cameras.
	// Skip setting stream mode if the node is inaccessible.
	const CEnumerationPtr ptrStreamMode = sNodeMap.GetNode("StreamMode");
	if (!IsReadable(ptrStreamMode) || !IsWritable(ptrStreamMode))
	{
		return 0;
	}

	gcstring streamMode;
	switch (chosenStreamMode)
	{
	case STREAM_MODE_PGRLWF:
		streamMode = "LWF";
		break;
	case STREAM_MODE_SOCKET:
		streamMode = "Socket";
		break;
	case STREAM_MODE_TELEDYNE_GIGE_VISION:
	default:
		streamMode = "TeledyneGigeVision";
	}

	// Retrieve the desired entry node from the enumeration node
	const CEnumEntryPtr ptrStreamModeCustom = ptrStreamMode->GetEntryByName(streamMode);
	if (!IsReadable(ptrStreamModeCustom))
	{
		// Failed to get custom node
		cout << "Stream mode " + streamMode + " not available.  Aborting..." << endl;
		return -1;
	}
	// Retrieve the integer value from the entry node
	const int64_t streamModeCustom = ptrStreamModeCustom->GetValue();

	// Set integer as new value for enumeration node
	ptrStreamMode->SetIntValue(streamModeCustom);

	// Print out the current stream mode
	cout << endl << "Stream Mode set to " + ptrStreamMode->GetCurrentEntry()->GetSymbolic() << "..." << endl;

	return 0;
}

// This function acquires and saves 10 images from a device.
int AcquireImages(CameraPtr pCam, INodeMap& nodeMap, INodeMap& nodeMapTLDevice)
{
	int result = 0;


	try
	{
		int group_id;
		std::cout << "请输入当前组的图片命名ID：\n";
		std::cin >> group_id;
		int image_id = 1;

		std::string save_folder;   //指定保存的文件夹
		std::cout << "请输入图片要保存的文件夹名称：\n";
		std::cin >> save_folder;




		// 设置采集模式为连续
		CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
		CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
		const int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();
		ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
		cout << "Acquisition mode set to continuous..." << endl;

		// 启动采集
		pCam->BeginAcquisition();
		cout << "Start acquiring images (press ESC to exit)..." << endl;

		// 初始化图像处理器
		ImageProcessor processor;
		processor.SetColorProcessing(SPINNAKER_COLOR_PROCESSING_ALGORITHM_HQ_LINEAR);

		cv::namedWindow("Live View", cv::WINDOW_AUTOSIZE);  // 确保窗口创建
		// 实时图像采集循环
		while (true)
		{
			try
			{

				// 抓图（50ms 超时）
				ImagePtr pResultImage = pCam->GetNextImage(50);

				if (pResultImage->IsIncomplete())
				{
					cout << "Image incomplete: " << Image::GetImageStatusDescription(pResultImage->GetImageStatus()) << endl;
				}
				else
				{
					// 转换为 8 位灰度图像
					ImagePtr convertedImage = processor.Convert(pResultImage, PixelFormat_Mono8);

					// 转换为 OpenCV Mat
					cv::Mat cvImage(
						static_cast<int>(convertedImage->GetHeight()), // 将 size_t 转为 int，确保不会丢失数据
						static_cast<int>(convertedImage->GetWidth()),
						CV_8UC1,
						convertedImage->GetData()
					);

					// 缩小显示图像
					cv::Mat resizedImage;
					cv::resize(cvImage, resizedImage, cv::Size(), 0.5, 0.5);  // 缩放比例根据需要设置

					// 显示缩小后的图像

					try {
						// 显示图像
						if (!cvImage.empty())
						{
							cv::imshow("Live View", resizedImage);
						}
						else
						{
							std::cerr << "cvImage is empty!" << std::endl;
						}

						// 检查是否按下 ESC 键
						int key = cv::waitKey(1);
						if (key == 27)  // ESC 键
						{
							cout << "ESC pressed, exiting..." << endl;
							break;
						}
						else if (key == 'q' || key == 'Q')  // Q 键保存图像
						{
							std::ostringstream filename;
							filename << save_folder << "/" << group_id << "-" << image_id << ".png";
							cv::imwrite(filename.str(), cvImage);
							cout << "Saved: " << filename.str() << endl;

							image_id++;
							if (image_id > 3)
							{
								image_id = 1;
								group_id++;
							}
						}

					}
					catch(cv::Exception& e){
						std::cerr << "OpenCV error: " << e.what() << std::endl;
						break;  // 或者 return -1;
					}


				}

				// 释放图像缓冲
				pResultImage->Release();
			}
			catch (Spinnaker::Exception& e)
			{
				cout << "Image error: " << e.what() << endl;
			}
		}

		// 停止采集
		pCam->EndAcquisition();
		cv::destroyAllWindows();
	}
	catch (Spinnaker::Exception& e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

int PrintDeviceInfo(INodeMap& nodeMap)
{
	int result = 0;
	cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

	try
	{
		FeatureList_t features;
		const CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
		if (IsReadable(category))
		{
			category->GetFeatures(features);

			for (auto it = features.begin(); it != features.end(); ++it)
			{
				const CNodePtr pfeatureNode = *it;
				cout << pfeatureNode->GetName() << " : ";
				CValuePtr pValue = static_cast<CValuePtr>(pfeatureNode);
				cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
				cout << endl;
			}
		}
		else
		{
			cout << "Device control information not available." << endl;
		}
	}
	catch (Spinnaker::Exception& e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

int RunSingleCamera(CameraPtr pCam)
{
	int result;

	try
	{
		// Retrieve TL device nodemap and print device information
		INodeMap& nodeMapTLDevice = pCam->GetTLDeviceNodeMap();
		result = PrintDeviceInfo(nodeMapTLDevice);

		// Initialize camera
		pCam->Init();

		// Retrieve GenICam nodemap
		INodeMap& nodeMap = pCam->GetNodeMap();
		//===========================================================================
		// 设置分辨率为 2048x2048
		CIntegerPtr ptrWidth = nodeMap.GetNode("Width");
		CIntegerPtr ptrHeight = nodeMap.GetNode("Height");
		CIntegerPtr ptrOffsetX = nodeMap.GetNode("OffsetX");
		CIntegerPtr ptrOffsetY = nodeMap.GetNode("OffsetY");

		if (IsWritable(ptrWidth) && IsWritable(ptrHeight))
		{
			// 设置宽度和高度为 2048
			ptrWidth->SetValue(2048);
			ptrHeight->SetValue(2048);
			cout << "Resolution set to 2048x2048..." << endl;

			// 调整偏移量以居中 ROI（假设传感器支持此分辨率）
			if (IsWritable(ptrOffsetX) && IsWritable(ptrOffsetY))
			{
				// 计算居中偏移：(2448 - 2048) / 2 = 200, (2048 - 2048) / 2 = 0
				ptrOffsetX->SetValue(200); // 水平居中
				ptrOffsetY->SetValue(0);   // 垂直居中（高度无需偏移）
				cout << "Offset set to X: " << ptrOffsetX->GetValue() << ", Y: " << ptrOffsetY->GetValue() << "..." << endl;
			}
			else
			{
				cout << "Warning: OffsetX or OffsetY not writable, ROI may not be centered." << endl;
			}
		}
		else
		{
			cout << "Error: Width or Height not writable, cannot set resolution to 2048x2048." << endl;
			result = -1;
		}
		//===========================================================================
		// Set stream mode
		result = result | SetStreamMode(pCam);

		// Acquire images
		result = result | AcquireImages(pCam, nodeMap, nodeMapTLDevice);

		// Deinitialize camera
		pCam->DeInit();
	}
	catch (Spinnaker::Exception& e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

int main(int /*argc*/, char** /*argv*/)
{
	//=========================测试权限============================================
	FILE* tempFile = fopen("test.txt", "w+");
	if (tempFile == nullptr)
	{

		cout << "Failed to create file in current folder.  Please check "
			"permissions."
			<< endl;
		cout << "Press Enter to exit..." << endl;
		getchar();
		return -1;
	}
	fclose(tempFile);
	remove("test.txt");
	//============================================================================
		// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();

	// Print out current library version
	const LibraryVersion spinnakerLibraryVersion = system->GetLibraryVersion();
	cout << "Spinnaker library version: " << spinnakerLibraryVersion.major << "." << spinnakerLibraryVersion.minor
		<< "." << spinnakerLibraryVersion.type << "." << spinnakerLibraryVersion.build << endl
		<< endl;

	// Retrieve list of cameras from the system
	CameraList camList = system->GetCameras();

	const unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Finish if there are no cameras
	if (numCameras == 0)
	{
		// Clear camera list before releasing system
		camList.Clear();

		// Release system
		system->ReleaseInstance();

		cout << "Not enough cameras!" << endl;
		cout << "Done! Press Enter to exit..." << endl;
		getchar();

		return -1;
	}

	CameraPtr pCam = nullptr;

	int result = 0;

	// Run example on each camera
	for (unsigned int i = 0; i < numCameras; i++)
	{
		// Select camera
		pCam = camList.GetByIndex(i);

		cout << endl << "Running example for camera " << i << "..." << endl;

		// Run example
		result = result | RunSingleCamera(pCam);

		cout << "Camera " << i << " example complete..." << endl << endl;
	}
	pCam = nullptr;

	// Clear camera list before releasing system
	camList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
