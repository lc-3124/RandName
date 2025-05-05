#ifndef _NAMEBLOACK_CPP
#define _NAMEBLOACK_CPP

#include "utils.cpp"

enum class NameBlockStatus
{
    x,
    y,
    w,
    h,
    sp,
    dr
};
class NameBlock
{
protected:
    std::atomic< float > x, y, w, h, sp, dr;
    std::string          label;
    bool                 isCh = false, isShow = true;
	int 				 cur_stamp = 0 ;	
public:
    // interface of status
    std::atomic< float >* StatusVal( NameBlockStatus index );
    std::string           GetName();
    // draw method
    void draw();
    // clicked process
    void click( int mx, int my );
    // move method
    void move( int stamp );
	// choose it
	void setCh   ( bool is ){this->isCh   = is;};
	void setShow ( bool is ){this->isShow = is;};

    // build
    NameBlock( float x, float y, float w, float h, float sp, float dr_max360, int stamp , std::string name );
    // release
    ~NameBlock ()
    {
        /* No Chance of it to release */
    }
};

// build
NameBlock::NameBlock(float x, float y, float w, float h, float sp, float dr_max360, int stamp, std::string name)
	: x(x), y(y), w(w), h(h), sp(sp), dr(dr_max360),  // 原子变量的初始化
	label		(std::move(name)),                    // 使用move避免字符串拷贝
	isCh		(false),                              // 默认值
	isShow	 	(true),                               // 默认值
	cur_stamp	(stamp)                               // 时间戳初始化
	{}

inline std::atomic< float >* NameBlock::StatusVal( NameBlockStatus index )
{
    switch ( index )
        {
        case NameBlockStatus::x:
            return &this->x;
            break;
        case NameBlockStatus::y:
            return &this->y;
            break;
        case NameBlockStatus::h:
            return &this->h;
            break;
        case NameBlockStatus::w:
            return &this->w;
            break;
        case NameBlockStatus::sp:
            return &this->sp;
            break;
        case NameBlockStatus::dr:
            return &this->dr;
            break;
        }
}

inline void NameBlock::draw()
{
    if ( this->isShow != 1 )
        return;
    // draw background
    ege::setfillcolor( RGB( 180, 150, 130 ) );
    ege::bar( x, y, x + w, y + h );

    // figure out the size of fonts
    const float font_height = std::min( w.load(), h.load() ) / 6.0f * 5.0f;

    // set fonts
    ege::setfont( font_height, 0, "Noto Sans CJK SC" );
    ege::setbkmode( TRANSPARENT );
    ege::setcolor( ege::WHITE );

    // figure out the pos of fonts
    std::string text = UTF8ToGBK( this->label );
    // std::string text = this->label;
    const int text_width  = ege::textwidth( text.c_str() );
    const int text_height = ege::textheight( text.c_str() );

    // text pos
    const float text_x = x + ( w - text_width ) / 2;
    const float text_y = y + ( h - text_height ) / 2;

    // draw
    ege::xyprintf( text_x, text_y, "%s", text.c_str() );
}

inline void NameBlock::move(int stamp)
{
	// sp : px/1000ms
    if ( this->isCh == true ){ return;}
	
	if(stamp - this->cur_stamp >= 10)
	{
		int past_time = stamp = cur_stamp;
		this->cur_stamp = stamp;
		// a pile of shit 
		this->x.store(x.load() + static_cast<float>(cos(this->dr) * (sp * past_time) / 1000));
		this->y.store(y.load() + static_cast<float>(sin(this->dr) * (sp * past_time) / 1000));
		if( x.load() >= WIN_W - w.load() || x.load() <= 0 )dr.store( ege::PI - dr.load());
		if( x.load() >= WIN_H - h.load() || y.load() <= 0 )dr.store( 0 - dr.load());
	}
}

#endif
