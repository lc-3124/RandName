#include "fonts.cpp"

int main()
{
    InitWindow( 800, 600, "世界你好" );

    SetTraceLogLevel( LOG_WARNING );
    SetTargetFPS( 120 );
    ExFonts hello;
    hello.loadTtfFile( "ttf1.ttf", "ttf1" );
    while ( !WindowShouldClose() )
        {
            hello.loadTextFormat( "你好世界 , hello world", "ttf1" );
            BeginDrawing();
            hello.drawText( 20, 20, 5, 32, RED );
            EndDrawing();
            hello.releaseFont();
        }
    return 0;
}
