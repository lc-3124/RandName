#include "Button.cpp"

using namespace ege;

ChosseButton chbutton;

void drawloop()
{
	while(is_run() == 1)
	{	
		static PIMAGE page = NULL;//绘图层2，用于刷新画面
		if (page == NULL) {
			page = newimage(1200,800);
			setbkcolor(WHITE);
		}
		cleardevice(page);
		settarget(page);
		setbkcolor(BLACK);

		cleardevice();
		chbutton.draw();
		delay_ms(0);
		settarget(NULL);
		putimage(0, 0, page);  //输出一个图
		
	}
}

void mouseloop()
{      
	while(true)
	{
		delay_fps(120);
		
		if (keystate(key_mouse_l)) { // 鼠标左键按下了
			int mouse_x,mouse_y;
			mousepos(&mouse_x,&mouse_y);
			chbutton.handle(mouse_x , mouse_y ,1);
			
		}
		
	}
}

int main()
{
	initgraph(1200,800,INIT_RENDERMANUAL);
	setrendermode(RENDER_MANUAL); // 关闭自动刷新（手动控制刷新）
	std::thread drawlp(drawloop);
	mouseloop();
}
