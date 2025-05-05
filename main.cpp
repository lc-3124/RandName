#include "Broad.cpp"  
#include "NameBlock.cpp"
#include "draw.cpp" 
#include "mouseclick.cpp"
int main()  
{
    ege::initgraph( WIN_W, WIN_H );
	ege::setrendermode(ege::RENDER_MANUAL); // close auto swap
   
	std::thread mouse_th(drawloop);
	std::thread draw_th(mouseloop);
	draw_th.join();
	mouse_th.join();            
	
    return 0;
}
