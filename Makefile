all:
	x86_64-w64-mingw32-g++ main.cpp -o RandName.exe -leasyx -static -std=c++11 -lmsvcrt -D__USE_MINGW_ANSI_STDIO=0
