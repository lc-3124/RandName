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
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("�¼κ�");
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("�Ƴ���");
NameList.push_back("���Ժ�");
NameList.push_back("��̩��");
NameList.push_back("����");
NameList.push_back("���");
NameList.push_back("������");
NameList.push_back("���ڽ�");
NameList.push_back("������");
NameList.push_back("��ͮ");
NameList.push_back("����");
NameList.push_back("���");
NameList.push_back("���ÿ�");
NameList.push_back("������");
NameList.push_back("��˧��");
NameList.push_back("������");
NameList.push_back("��Ц");
NameList.push_back("��չ��");
NameList.push_back("������");
NameList.push_back("�޿���");
NameList.push_back("Ī����");
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("����");
NameList.push_back("�����");
NameList.push_back("�����");
NameList.push_back("���ҽ�");
NameList.push_back("������");
NameList.push_back("�����");
NameList.push_back("����ݼ");
NameList.push_back("Ф��ɽ");
NameList.push_back("Ф�");
NameList.push_back("л��֥");
NameList.push_back("л��ϣ");
NameList.push_back("л_����_��Τ");
NameList.push_back("л����");
NameList.push_back("������");
NameList.push_back("�պ���");
NameList.push_back("�̲�ӱ");
NameList.push_back("�");
NameList.push_back("���");
NameList.push_back("��ɽ�");
NameList.push_back("������");
NameList.push_back("������");
NameList.push_back("������");
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
 	gettextstyle(&f);						// ��ȡ��ǰ��������
 	_tcscpy(f.lfFaceName, "����");	
	 f.lfHeight = 30;
	 f.lfWidth = 14;						// ��������߶�Ϊ 48
 	settextstyle(&f);						// ����������ʽ
    setbkmode(TRANSPARENT);
    setcolor(RGB(0,0,0));
	bar(button.x,button.y,button.x+button.w,button.y+button.l);
	outtextxy(button.x+1,button.y+1,"��һ��");
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
 	gettextstyle(&f);						// ��ȡ��ǰ��������
 	_tcscpy(f.lfFaceName, "����");	
	 f.lfHeight = 70;	
	 f.lfWidth = 40;					// ��������߶�Ϊ 48
 	settextstyle(&f);						// ����������ʽ
    setbkmode(TRANSPARENT);
    setcolor(RGB(250,0,0));
    outtextxy(maxX-400,maxY-230,"ȫ��������");
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
	
