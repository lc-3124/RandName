#include "Button.cpp"

using namespace ege;

ChosseButton chbutton;

void drawloop()
{
	
	while(is_run() == 1)
	{	
		cleardevice();
		chbutton.draw();
		delay_fps(60);
	}

}

void mouseloop()
{      
	while(true)
	{
		api_sleep(10); // api_sleep , avoid form triggering ege's manual-buffer-swap 
		
		if (keystate(key_mouse_l)) { // if leftkey down
			int mouse_x,mouse_y;
			mousepos(&mouse_x,&mouse_y);
			chbutton.handle(mouse_x , mouse_y ,1);
			
		}
		
	}
}

int main()
{
	initgraph(1200,800,INIT_RENDERMANUAL);
	setrendermode(RENDER_MANUAL); // close auto swap
	std::thread drawlp(drawloop);
	mouseloop();
}
