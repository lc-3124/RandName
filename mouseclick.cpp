#ifndef _MOUSECLIICK_CPP
#define _MOUSECLIICK_CPP

#include "utils.cpp"
#include "Button.cpp"

void mouseloop()
{
	using namespace ege;
	while( true )
	{
	if (keystate( key_mouse_l )) { 
		int mouse_x , mouse_y;
		mousepos( &mouse_x , &mouse_y );
		clickbutton.passiveMouseCheck( mouse_x , mouse_y );
		savebutton.passiveMouseCheck ( mouse_x , mouse_y );
		
		api_sleep(10);
	}
	}		
}

#endif
