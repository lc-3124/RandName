#include "gofor.cpp"
#include "used.hpp"
#include "chbroad.cpp"

class Button {
protected:
	std::atomic<float> x=0, y=0, w=160, h=30;
	std::string label;
	bool isAble2Click = true;
	bool isShow= 1 ;
	
public:
	virtual void handle(int x , int y , int event) = 0;
	virtual void draw() = 0;
};

class ChosseButton : protected Button {
public:
	ChosseButton() {
		this->x.store(1000);
		this->y.store(750);
		this->label = "狂按抽取";
	}
	
	void draw() override {
		if(this-> isShow !=1)return;
		// draw background
		setfillcolor(RGB(180, 150, 130));
		bar(x, y, x + w, y + h);
		
		// figure out the size of fonts
		const float font_height = std::min(w.load(), h.load()) / 6.0f*5.0f;
		
		// set fonts
		setfont(font_height, 0, "Noto Sans CJK SC");
		setbkmode(TRANSPARENT);
		setcolor(WHITE); 
		
		// figure out the pos of fonts
		std::string text = UTF8ToGBK(this->label);
		//std::string text = this->label;
		const int text_width = textwidth(text.c_str());
		const int text_height = textheight(text.c_str());
		
		// text pos
		const float text_x = x + (w - text_width) / 2;
		const float text_y = y + (h - text_height) / 2;
		
		// draw
		xyprintf(text_x, text_y, "%s", text.c_str());
	}
	
	// clicked , process data and play cg
	void handle(int x , int y , int event )override{
		if(x >= this->x.load() && x <= this->x.load()+this->w.load()
			&& y >= this->y.load() && y <= this->y.load()+this->h.load()
			&& this->isAble2Click == true)
		{
			this->isShow =0;
			 this->isAble2Click = false;
			  srand((unsigned)time(NULL)); 
			circatcher.playcg(rand()%50);
			this->isShow =1;
			this->isAble2Click = true;
		}
	}
};
