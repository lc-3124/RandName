#ifndef USED_HPP
#define USED_HPP

#include <ege.h>
#include <thread>
#include <vector>
#include <atomic> 
#include <string>
#include <unistd.h>
using namespace ege;

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

#endif


