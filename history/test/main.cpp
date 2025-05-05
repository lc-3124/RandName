#include <graphics.h>
#include <conio.h>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>

std::atomic<int> timecnt(0);

void timego() {
    while (true) {
        usleep(1000);  // 休眠1毫秒（1000微秒）
        timecnt++;
    }
}

int timepoint() {
    return timecnt.load();
}

int timepast(int started) {
    return timecnt.load() - started;
}

void thgofor(float sta, float sto, int duration, std::atomic<float>& val) {
    int start = timepoint();
    float a = 2.0f * (sto - sta) / float((duration * duration));

    while (true) {
        int elapsed = timepast(start);
        float t = static_cast<float>(elapsed);
        
        if (t >= duration) {
            val.store(sto);
            break;
        }
        
        float current = sta + a * t * t / 2.0f;
        val.store(current);
        //usleep(1);  // 更新频率控制
    }
}

class block {
private:
    std::atomic<float> targetX, targetY;
    std::mutex mtx;
	int st_r = 20;
public:
	std::atomic<float> r ;
	std::atomic<float> x, y;
    block() : x(10), y(10), st_r(20) {
	r.store(st_r);}

    void draw() {
        float currentX = x.load();
        float currentY = y.load();
        circle(currentX,currentY,r);
    }

    void goforto(int X, int Y) {
        targetX = X;
        targetY = Y;
        
        std::thread([this]() {
            thgofor(x.load(), targetX.load(), 20, x);
        }).detach();
        
        std::thread([this]() {
            thgofor(y.load(), targetY.load(), 20, y);
        }).detach();
    }
    
	void breakout()
	{
		std::thread([this](){
			thgofor(this->r , 1500 , 20 , r);
		}).join();
		
		std::thread([this](){
			thgofor(0 , 20 , 10 , r);
		}).join();
		
		std::thread([this](){
			thgofor(this->r , 1500 , 10 , r);
		}).join();
		
		std::thread([this](){
			thgofor(0 , 170 , 20 , r);
		}).join();
		Sleep(200);
		
		std::thread([this](){
			thgofor( 170 , 0 , 150 , r);
		}).join();
		
		std::thread([this](){
			thgofor( 0 , 20 , 40 , r);
		}).join();

		r.store( st_r );
	 } 
};

block b;

void draw() {
    while (true) {
        cleardevice();
        b.draw();
        FlushBatchDraw();
        usleep(1600);  // 约60FPS
    }
}

int main() {
    initgraph(1400, 800);
    BeginBatchDraw();

    std::thread tm(timego);
    tm.detach();

    std::thread dra(draw);
    dra.detach();

	ExMessage m;		// 定义消息变量

    while (true) {
   		m = getmessage(EX_MOUSE | EX_KEY);
   		if(m.message == WM_LBUTTONDOWN)
   		{
   			b.goforto(m.x,m.y);
   			usleep(1500000);
   			if(m.x >= b.x-b.r && m.x <= b.x+b.r && m.y >= b.y-b.r &&m.y <= b.y+b.r)
			   {
			   	b.breakout();
			   	Sleep(1500);
				} 
		   }
    }

    closegraph();
    return 0;
}
