#include <graphics.h>		
#include <conio.h>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <random>

std::vector<std::string> NameList;

std::vector<std::string> CurrentNameList;
void initNamelist()
{
NameList.push_back("熬齐文");
NameList.push_back("曾京奥");
NameList.push_back("陈嘉豪");
NameList.push_back("陈梁宇");
NameList.push_back("陈奕欣");
NameList.push_back("贺天佑");
NameList.push_back("胡西侯");
NameList.push_back("黄楚雄");
NameList.push_back("黄以涵");
NameList.push_back("金泰宇");
NameList.push_back("李金颗");
NameList.push_back("李静凯");
NameList.push_back("李若晞");
NameList.push_back("李在锦");
NameList.push_back("梁杰文");
NameList.push_back("梁彤");
NameList.push_back("刘畅");
NameList.push_back("刘馥");
NameList.push_back("刘好俊");
NameList.push_back("刘力豪");
NameList.push_back("刘帅祥");
NameList.push_back("刘天佑");
NameList.push_back("刘笑");
NameList.push_back("刘展江");
NameList.push_back("刘紫晴");
NameList.push_back("罗俊哲");
NameList.push_back("莫宇轩");
NameList.push_back("彭泽宇");
NameList.push_back("漆瑞霖");
NameList.push_back("阮鑫");
NameList.push_back("孙沐均");
NameList.push_back("王佳睿");
NameList.push_back("王家杰");
NameList.push_back("王雅婷");
NameList.push_back("文天道");
NameList.push_back("向子菁");
NameList.push_back("肖东山");
NameList.push_back("肖睿");
NameList.push_back("谢媚芝");
NameList.push_back("谢雨希");
NameList.push_back("谢_吉吉_火韦");
NameList.push_back("谢政宇");
NameList.push_back("熊铭灿");
NameList.push_back("颜浩宇");
NameList.push_back("晏伯颖");
NameList.push_back("杨晨");
NameList.push_back("杨洁");
NameList.push_back("余飞健");
NameList.push_back("喻祺开");
NameList.push_back("张艺菡");
NameList.push_back("周子霖");
}
int maxX = 900, maxY = 600;

class Button
{
	public:
		int x = maxX * 2 / 4 - 80;
		int y = maxY * 7 / 8;
		int w = 90;
		int l = 30;
}button;

void draw ()
{
 	LOGFONT f;
 	gettextstyle(&f);						// 获取当前字体设置
 	_tcscpy(f.lfFaceName, "楷体");	
	 f.lfHeight = 30;
	 f.lfWidth = 14;						// 设置字体高度为 48
 	settextstyle(&f);						// 设置字体样式
    setbkmode(TRANSPARENT);
    setcolor(RGB(0,0,0));
	bar(button.x,button.y,button.x+button.w,button.y+button.l);
	outtextxy(button.x+1,button.y+1,"抽一个");
	setcolor(RGB(250,100,250));
	std::string str;
	
	int row = 0;
	if(CurrentNameList.empty() == 0){
	int tmp = 0;
	for(int i=0 ; i<CurrentNameList.size();i++)
	{
		str+= "  "+CurrentNameList.at(i);
		tmp++;
		if(tmp == 7)
		{
			tmp =0;
			row++;
			outtextxy(0,row*40,str.c_str());
			str="";
		}
	}
	outtextxy(0,(row+1)*40,str.c_str());
	}
}

int main()
{
    initNamelist();
	initgraph(maxX,maxY);
	BeginBatchDraw();
	ExMessage m;
	draw();
    FlushBatchDraw();	
    int t=0;
	while(1)
	{
		srand(time(0));
		t=rand();
		draw();
		FlushBatchDraw();
		m = getmessage(EX_MOUSE | EX_KEY);

		switch(m.message)
		{
			case WM_LBUTTONDOWN:
				if(NameList.empty()==1)
				{
					while(1){
						draw();
						 	LOGFONT f;
 	gettextstyle(&f);						// 获取当前字体设置
 	_tcscpy(f.lfFaceName, "楷体");	
	 f.lfHeight = 70;	
	 f.lfWidth = 40;					// 设置字体高度为 48
 	settextstyle(&f);						// 设置字体样式
    setbkmode(TRANSPARENT);
    setcolor(RGB(250,0,0));
    outtextxy(maxX-400,maxY-230,"全部抽完了");
						FlushBatchDraw();
					}
				}
				else{			
					CurrentNameList.push_back(NameList.at(t%NameList.size()));
					for(int i = t%NameList.size() ; i< NameList.size()-1 ; i++)
					{
						NameList[i]=NameList[i+1];
					}
					NameList.pop_back();
				} 
				break;
		}
	}
	return 0;	
}
	
