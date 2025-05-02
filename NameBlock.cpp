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

public:
    // interface of status
    std::atomic< float >* GetStatusVal( NameBlockStatus index );
    std::string           GetName();
    // draw method
    void draw();
    // clicked process
    void click( int mx, int my );
    // move method
    void move();

    // build
    NameBlock( float x, float y, float w, float h, float sp, float dr_max360, std::string name );
    // release
    ~NameBlock ()
    {
        /* No Chance of it to release */
    }
};

inline std::atomic< float >* NameBlock::GetStatusVal( NameBlockStatus index )
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

inline void NameBlock::move()
{
    if ( this->isCh == true )
        return;
}

#endif
