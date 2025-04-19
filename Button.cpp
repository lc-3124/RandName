#include "gofor.cpp"
#include "used.hpp"

class Button {
protected:
	std::atomic<float> x=0, y=0, w=80, h=30;
	std::string label;
	bool isAble2Click = true;
	
public:
	virtual void handle(int x , int y , int event) = 0;
	virtual void draw() = 0;
};

class ChosseButton : protected Button {
public:
	ChosseButton() {
		this->x.store(0);
		this->y.store(0);
		this->label = "抽取";
	}
	
	void draw() override {
		// 绘制按钮背景
		setfillcolor(RGB(150, 150, 150));
		bar(x, y, x + w, y + h);
		
		// 计算自适应字体大小（取宽高的最小值的5/6）
		const float font_height = std::min(w.load(), h.load()) / 6.0f*5.0f;
		
		// 设置透明黑体字体
		setfont(font_height, 0, "Noto Sans CJK SC Thin");
		setbkmode(TRANSPARENT);
		setcolor(WHITE);  // 文字颜色设为白色
		
		// 计算文字居中位置
		//std::string text = UTF8ToGBK(this->label);
		std::string text = this->label;
		const int text_width = textwidth(text.c_str());
		const int text_height = textheight(text.c_str());
		
		// 文字绘制位置（水平垂直居中）
		const float text_x = x + (w - text_width) / 2;
		const float text_y = y + (h - text_height) / 2;
		
		// 绘制文字
		xyprintf(text_x, text_y, "%s", text.c_str());
	}
	
	// clicked , process data and play cg
	void handle(int x , int y , int event )override{
		if(x >= this->x.load() && x <= this->x.load()+this->w.load()
			&& y >= this->y.load() && y <= this->y.load()+this->h.load())
		{
		
		}
	}
};
