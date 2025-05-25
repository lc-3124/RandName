#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

std::string float_to_string( float value, int precision = 2 )
{
    const int buffer_size = 32;
    char      buffer[ buffer_size ];
    snprintf( buffer, buffer_size, "%.*f", precision, value );
    return std::string( buffer );
}

sf::Font   font1( "simhei.ttf" );
std::mutex windowMutex;
bool       isClosed = 0;

class DrawingBox
{
    protected:
    float        x, y, w, h;
    std::wstring label;
    sf::Text *   info_pos, *info_label;
    float        textsize;

    public:
    bool needDraw = 0;
    DrawingBox( float x, float y, float w, float h, std::wstring label )
    {
        this->x    = x;
        this->y    = y;
        this->h    = h;
        this->w    = w;
        info_pos   = new sf::Text( font1 );
        info_label = new sf::Text( font1 );
        info_pos->setFont( font1 );
        info_label->setFont( font1 );
        this->label = label;
    }
    void draw( sf::RenderWindow* win )
    {
        // drawed
        this->needDraw = 0;
        // figure out the text size from window size
        auto winsize = win->getSize();
        if ( winsize.y / 25.0f <= 10.0f )
            this->textsize = 10.0f;
        else
            this->textsize = winsize.y / 25.0f;
        // Set Texts
        info_pos->setString( "X: " + float_to_string( this->x ) + "\n"
                             + "Y: " + float_to_string( this->y ) + "\n"
                             + "W: " + float_to_string( this->w ) + "\n"
                             + "H: " + float_to_string( this->h )

        );
        info_label->setString( this->label );
        info_pos->setPosition( { x, y } );
        info_label->setPosition( { x + w, y + h } );
        info_pos->setFillColor( sf::Color::Red );
        info_label->setFillColor( sf::Color::Red );
        info_pos->setCharacterSize(
            static_cast< unsigned int >( this->textsize ) );
        info_label->setCharacterSize(
            static_cast< unsigned int >( this->textsize ) );
        // Create Lines
        std::array lineO = {
            sf::Vertex{ sf::Vector2f( this->x, this->y ) },
            sf::Vertex{ sf::Vector2f( this->x + w, this->y ) }
        };
        std::array lineD = {
            sf::Vertex{ sf::Vector2f( this->x, this->y + h ) },
            sf::Vertex{ sf::Vector2f( this->x + w, this->y + h ) }
        };
        std::array lineL = {
            sf::Vertex{ sf::Vector2f( this->x, this->y ) },
            sf::Vertex{ sf::Vector2f( this->x, this->y + h ) }
        };
        std::array lineR = {
            sf::Vertex{ sf::Vector2f( this->x + w, this->y ) },
            sf::Vertex{ sf::Vector2f( this->x + w, this->y + h ) }
        };
        lineO[ 0 ].color = sf::Color::Red;
        lineO[ 1 ].color = sf::Color::Red;
        lineD[ 0 ].color = sf::Color::Red;
        lineD[ 1 ].color = sf::Color::Red;
        lineL[ 0 ].color = sf::Color::Red;
        lineL[ 1 ].color = sf::Color::Red;
        lineR[ 0 ].color = sf::Color::Red;
        lineR[ 1 ].color = sf::Color::Red;
        // draw
        win->draw( lineO.data(), lineO.size(), sf::PrimitiveType::Lines );
        win->draw( lineD.data(), lineD.size(), sf::PrimitiveType::Lines );
        win->draw( lineL.data(), lineL.size(), sf::PrimitiveType::Lines );
        win->draw( lineR.data(), lineR.size(), sf::PrimitiveType::Lines );
        win->draw( *info_label );
        win->draw( *info_pos );
    }
};
DrawingBox box( 100, 100, 110, 100, L"控件标记区域Box1" );
DrawingBox box1( 50, 400, 150, 80, L"控件标记区域Box2" );
DrawingBox box2( 400, 200, 110, 130, L"控件标记区域Box3" );
DrawingBox box3( 500, 40, 110, 200, L"控件标记区域Box4" );

void renderingThread( sf::RenderWindow* win )
{
    std::cout << win->setActive( true );
    while ( isClosed == 0 )
        {
            usleep( 100000 );
            win->clear( sf::Color::Black );
            if ( box.needDraw == 0 ) continue;
            box.draw( win );
            box1.draw( win );
            box2.draw( win );
            box3.draw( win );
            win->display();
        }
    std::cout << win->setActive( false );
}

int main( int argc, char** argv )
{
    auto window =
        new sf::RenderWindow( sf::VideoMode( { 800, 600 } ), "My Window" );
    std::cout << window->setActive( false );
    std::thread thrRender( &renderingThread, window );
    while ( window->isOpen() )
        {
            while ( auto event = window->pollEvent() )
                {
                    if ( event->is< sf::Event::Closed >() )
                        {
                            exit( 0 );
                            isClosed = 1;
                            break;
                        }
                    else if ( const auto* wsize =
                                  event->getIf< sf::Event::Resized >() )
                        {
                            sf::FloatRect visibleArea(
                                { 0.f, 0.f }, { ( float )wsize->size.x,
                                                ( float )wsize->size.y } );
                            window->setView( sf::View( visibleArea ) );
                            box.needDraw = 1;
                        }
                    usleep( 10000 );
                    if ( isClosed == 1 ) break;
                }
        }
    thrRender.join();
    window->close();
    return 0;
}
