#ifndef _DRAW_CPP
#define _DRAW_CPP

#include "utils.cpp"
#include "NameBlock.cpp"
#include "Button.cpp"

void drawloop()
{
   while( ege::is_run() == 1 )
   {
	   	ege::cleardevice();
			// draw blocks
			// draw WhiteBroad
            // draw Buttons
		clickbutton.draw();
		savebutton.draw();
		ege::delay_fps( 60 );
    }
}

#endif
