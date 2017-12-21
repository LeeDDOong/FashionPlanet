//
//  MpFont.h
//  Party
//
//
//

#ifndef Party_MpFont_h
#define Party_MpFont_h


#define FONT_S          0
#define FONT_L          1
#define FONT_XL         2


extern int fontSize;

typedef struct
{
    bool isUse;
    Label* lable;
    
    char src[1024];
    int fontSize;
    bool isBold;
} XFONTRESLOT;


#define FONTRESLOTMAX       150
typedef struct
{
    int totalNum;
    bool isBold;
    XFONTRESLOT xSlot[FONTRESLOTMAX];
    
} XFONTRE;
extern XFONTRE xFontRe;





typedef struct
{
    int totalNum;
    char strText[10][128];
    int colorType[10];
    
} XCOLORSTRING;
extern XCOLORSTRING xColorString;

















extern int iLabelWidth;
extern int iLabelHeight;


int getFontRe(const char* src, int fontSize,bool isBold);
int addFontRe(const char* src, int fontSize,bool isBold);


void gDrawString(int x, int y,const char* src, int ankNum);
void gDrawStringColor(int x, int y,const char* src, int ankNum);
void gDrawStringBold(float x, float y,const char* src, int ankNum, int r, int g, int b, int rr, int gg, int bb);
int getLabelWidth(const char *src,int fontSize, bool isBold);
int getLabelHeight(const char *src,int fontSize, bool isBold);
void setLabelWidth(int width);
void setLabelHeight(int height);
void setFontSize(int fontSize);
void setFontSizeORI(int fontSize22);

#endif
