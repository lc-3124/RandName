#ifndef _UTILS_CPP
#define _UTILS_CPP

#include "used.hpp"

std::string UTF8ToGBK(const std::string& str) {
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);
	
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* gbk_str = new char[len];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, gbk_str, len, NULL, NULL);
	
	std::string result(gbk_str);
	delete[] wstr;
	delete[] gbk_str;
	return result;
}


// this function code by AI ,but it works well
bool PlayAsync(const char* filePath) {
	if (!filePath || !PathFileExistsA(filePath)) {
		return false;
	}
	
	static std::atomic<uint64_t> counter{0};
	std::string alias = "audio_" + std::to_string(++counter) + 
	"_" + std::to_string(GetCurrentThreadId());
	
	std::thread([=]() {
		std::string openCmd = "open \"" + std::string(filePath) + 
		"\" type mpegvideo alias " + alias;
		if (mciSendStringA(openCmd.c_str(), nullptr, 0, nullptr) != 0) {
			return;
		}
		
		HWND hWnd = CreateWindowExA(0, "STATIC", nullptr, 0, 
			0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
		
		std::string playCmd = "play " + alias + " notify";
		if (mciSendStringA(playCmd.c_str(), nullptr, 0, hWnd) != 0) {
			mciSendStringA(("close " + alias).c_str(), nullptr, 0, nullptr);
			DestroyWindow(hWnd);
			return;
		}
		
		MSG msg;
		bool isPlaying = true;
		while (isPlaying && GetMessage(&msg, hWnd, 0, 0)) {
			if (msg.message == MM_MCINOTIFY) {
				switch (msg.wParam) {  
				case MCI_NOTIFY_SUCCESSFUL:
					isPlaying = false;
					break;
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		mciSendStringA(("close " + alias).c_str(), nullptr, 0, nullptr);
		DestroyWindow(hWnd);
	}).detach();
	
	return true;
}

#endif 

