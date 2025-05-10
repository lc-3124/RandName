#include <map>
#include <raylib.h>
#include <string>
#include <vector>

class ExFonts
{
    struct textformat_struct
    {
        std::string Text;
        Font        font;
    } textfs;
    struct ttfformat_struct
    {
        int            fileSize;
        unsigned char* fontFileData = nullptr;
    };
    std::map< std::string, ttfformat_struct > TTF_files;

public:
    bool loadTtfFile( std::string path, std::string Key );
    bool loadTextFormat( std::string Text, std::string ChooseTTF );
    bool drawText( float x, float y, int spacing, int size, Color color );
    bool releaseFont();
    ~ExFonts();
};

ExFonts::~ExFonts()
{
    for ( const auto& tmp : this->TTF_files )
        {
            UnloadFileData( tmp.second.fontFileData );
        }
}

bool ExFonts::loadTtfFile( std::string path, std::string Key )
{
    ttfformat_struct tmp_tfmt;
    tmp_tfmt.fontFileData =
        LoadFileData( path.c_str(), &tmp_tfmt.fileSize );
    this->TTF_files.insert(
        std::pair< std::string, ttfformat_struct >( Key, tmp_tfmt ) );
    return 1;
}
bool ExFonts::loadTextFormat( std::string Text, std::string ChooseTTF )
{
    const char* text = Text.c_str();
    int         codepointsCount;
    int*        codepoints = LoadCodepoints( text, &codepointsCount );
    Font        font       = LoadFontFromMemory(
        ".ttf", this->TTF_files[ ChooseTTF ].fontFileData,
        this->TTF_files[ ChooseTTF ].fileSize, 32, codepoints,
        codepointsCount );
    this->textfs.font = font;
    this->textfs.Text = Text;
    UnloadCodepoints( codepoints );
    return 1;
}
bool ExFonts::drawText( float x, float y, int spacing, int size,
                        Color color )
{
    if ( this->textfs.font.baseSize == -1 )
        return 0;
    DrawTextEx( this->textfs.font, this->textfs.Text.c_str(), { x, y },
                size, spacing, color );
    return 1;
}
bool ExFonts::releaseFont()
{
    UnloadFont( this->textfs.font );
    textfs.font.baseSize = -1;
    return 1;
}
