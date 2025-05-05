#ifndef _BUTTON_CPP
#define _BUTTON_CPP

#include "utils.cpp"

class Button {
protected:
	std::atomic<float> x, y, w, h;
	std::string label;
	bool isAble2Click = true;
	bool isShow = true;
	
public:
	// build
	Button(float x, float y, float w, float h, const std::string& label)
	: x(x), y(y), w(w), h(h), label(label) {}
	
	virtual void clickprocess() = 0 ;
	void passiveMouseCheck ( int x , int y );
	void draw();
	
	void setPosition(float newX, float newY) {x.store(newX);y.store(newY);}
	void setSize(float newW, float newH) {w.store(newW);h.store(newH);}
	void setLabel(const std::string& newLabel) {label = newLabel;}
	void setVisible(bool visible) {isShow = visible;}
	void setClickable(bool clickable) {isAble2Click = clickable;}
};

class ClickButton : public Button 
{
public:
	// inherit building function
	using Button::Button;
	void clickprocess() override
 	{
		// TODO
		this->x.store(0);
	};
}clickbutton(CLICK_BUTTON_X,CLICK_BUTTON_Y,CLICK_BUTTON_W,CLICK_BUTTON_H,CLICK_BUTTON_LABEL);


class SaveButton : public Button 
{
public:
	// inherit building function
	using Button::Button;
	void clickprocess() override
	{
		// TODO
	};
}savebutton( SAVE_BUTTON_X, SAVE_BUTTON_Y, SAVE_BUTTON_W, SAVE_BUTTON_H, SAVE_BUTTON_LABEL);


void Button::draw(){
	if(this-> isShow !=1)return;
	// draw background
	int colors[3]={CLICK_BUTTON_COLOR};
	ege::setfillcolor(RGB(colors[0],colors[1],colors[2]));
	ege::bar(x, y, x + w, y + h);
	
	// figure out the size of fonts
	const float font_height = std::min(w.load(), h.load()) / 6.0f*5.0f;
	
	// set fonts
	ege::setfont(font_height, 0, "Noto Sans CJK SC");
	ege::setbkmode(TRANSPARENT);
	ege::setcolor(ege::WHITE); 
	
	// figure out the pos of fonts
	std::string text = UTF8ToGBK(this->label);
	//std::string text = this->label;
	const int text_width = ege::textwidth(text.c_str());
	const int text_height = ege::textheight(text.c_str());
	
	// text pos
	const float text_x = x + (w - text_width) / 2;
	const float text_y = y + (h - text_height) / 2;
	
	// draw
	ege::xyprintf(text_x, text_y, "%s", text.c_str());
}

inline void Button::passiveMouseCheck(int x , int y)
{
	if(    x >= this->x.load() && x <= this->x.load() + this->w.load() 
		&& y >= this->y.load() && y <= this->y.load() + this->h.load() )
	{
		this->clickprocess();
	}
}


#endif
