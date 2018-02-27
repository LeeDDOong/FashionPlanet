//
//  MpFont.cpp
//  Party
//
//
//
#include "Global.h"

int iLabelWidth;
int iLabelHeight;
XFONTRE xFontRe;
XCOLORSTRING xColorString;



int fontSize;



int getFontRe(const char* src, int fontSize,bool isBold)
{
    for(int i=0;i<xFontRe.totalNum;i++)
    {
        if(xFontRe.xSlot[i].isUse == false
           && xFontRe.xSlot[i].fontSize == fontSize
           && xFontRe.xSlot[i].isBold == isBold
           && strcmp(src, xFontRe.xSlot[i].src) == 0)
        {
            return i;
        }
    }
    return DONT;
}


int addFontRe(const char* src, int fontSize,bool isBold)
{
    int index = xFontRe.totalNum++;
    
    xFontRe.xSlot[index].isUse = false;
    xFontRe.xSlot[index].fontSize = fontSize;
    xFontRe.xSlot[index].isBold = isBold;
    
    sprintf(xFontRe.xSlot[index].src, "%s",src);
    return index;
}






void gDrawStringColor(int x, int y,const char* src, int ankNum)
{
    
    
    memset(&xColorString, 0, sizeof(xColorString));

    
    int index = 0;
    
    for(int i=0; i<strlen(src); i++)
    {
        if((unsigned char)src[i] >= 0xA4)
        {
            //한글
            xColorString.strText[xColorString.totalNum][index++] = src[i++];
            xColorString.strText[xColorString.totalNum][index++] = src[i++];
            xColorString.strText[xColorString.totalNum][index++] = src[i];
        }
        else if(src[i] == 'c' && src[i+1] == '0')
        {
            xColorString.colorType[xColorString.totalNum] = 0;
            i++;
        }
        else if(src[i] == 'c' && src[i+1] == '1')
        {
            xColorString.colorType[xColorString.totalNum] = 1;
            i++;
        }
        else if(src[i] == 'c' && src[i+1] == 'e')
        {
            xColorString.totalNum++;
            i++;
            index = 0;
        }
        else
        {
            xColorString.strText[xColorString.totalNum][index++] = src[i];
        }
    }
    
    int www = 0;
    for(int k=0;k<xColorString.totalNum;k++)
        www += getLabelWidth(xColorString.strText[k],fontSize, false);
    
    int w = 0;
    for(int k=0;k<xColorString.totalNum;k++)
    {
        switch(xColorString.colorType[k])
        {
        case 0:gSetColor(255, 255, 225);break;
        case 1:gSetColor(255, 0, 0);break;
        }
        
        gDrawString(x+w, y, xColorString.strText[k], VL);
        w += getLabelWidth(xColorString.strText[k],fontSize, false);
    }
}


void gDrawString(int x, int y,const char* src, int ankNum)
{
    char strFileName[32];
    float fCharWidth = 0;
    
    sprintf(strFileName, "nanumgothic.ttf");
    
    float fscale;
    float fscaleX;
    float fscaleY;
    
    if(xGame.isReSizeDraw == true)
    {
        if(xGame.fgameScale != 1.0f)
            fscale = xGame.fgameScale * ((float)(xGame.reSize)/100.f);
        else
        {
            fscale = xGame.fgameScale + ((float)(xGame.reSize-100)/100.f);
        }
        
        fscaleX = fscale;
        fscaleY = fscale;
    }
    else if(xGame.isReSizeDrawXY == true)
    {
        if(xGame.fgameScale != 1.0f)
        {
            fscaleX = xGame.fgameScale * ((float)(xGame.reSizeX)/100.f);
            fscaleY = xGame.fgameScale * ((float)(xGame.reSizeY)/100.f);
        }
        else
        {
            fscaleX = xGame.fgameScale + ((float)(xGame.reSizeX-100)/100.f);
            fscaleY = xGame.fgameScale + ((float)(xGame.reSizeY-100)/100.f);
        }
    }
    else
    {
        fscale = xGame.fgameScale;
        fscaleX = fscale;
        fscaleY = fscale;
    }
    
    
    
    
    x += ((x-xGame.fgameScaleCx) * (xGame.fgameScale-1.f));
    y += ((y-xGame.fgameScaleCy) * (xGame.fgameScale-1.f));
    
    
    if(xGame.isClip == true)
    {
        x -= clip->getPosition().x;
        y += clip->getPosition().y;
    }
    bool isNew = false;
    Label* label;
    
    if(xGame.isClip == true)
    {
        /*
         int index = getFontReClip(src, fontSize);
         
         if(index == DONT)
         {
         isNew = true;
         index = addFontReClip(src, fontSize);
         xFontReClip.xSlot[index].lable = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
         }
         
         xFontReClip.xSlot[index].isUse = true;
         */
        label = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
    }
    else
    {
        int index = getFontRe(src, fontSize,false);
        
        if(index == DONT)
        {
            isNew = true;
            index = addFontRe(src, fontSize,false);
            xFontRe.xSlot[index].lable = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
        }
        
        xFontRe.xSlot[index].isUse = true;
        label = xFontRe.xSlot[index].lable;
    }
    
    label->setOpacity(xGame.alpha);
    label->setPosition(x,lcdH-y);
    label->setColor(Color3B(xGame.r, xGame.g, xGame.b));
    label->setAdditionalKerning(fCharWidth);
    label->setScale(fscale);
    
    
    
    if(iLabelWidth != 0)	label->setWidth(iLabelWidth);
    if(iLabelHeight != 0)	label->setHeight(iLabelHeight);
    
    switch(ankNum)
    {
    case TL:label->setAnchorPoint(Vec2(0, 1.0f));label->setAlignment(TextHAlignment::LEFT);break;
    case VH:label->setAnchorPoint(Vec2(0.5f, 0.5f));label->setAlignment(TextHAlignment::CENTER);break;
    case TH:label->setAnchorPoint(Vec2(0.5f, 1.0f));label->setAlignment(TextHAlignment::CENTER);break;
    case BH:label->setAnchorPoint(Vec2(0.5f, 0));label->setAlignment(TextHAlignment::CENTER);break;
    case VL:label->setAnchorPoint(Vec2(0, 0.5f));label->setAlignment(TextHAlignment::LEFT);break;
    case VR:label->setAnchorPoint(Vec2(1.0f, 0.5f));label->setAlignment(TextHAlignment::RIGHT);break;
    }
    
    if(xGame.isClip == true)
    {
        clip->addChild(label,0,100);
    }
    else
    {
        if(isNew == true)
            xGame.layer->addChild(label,0,200);
        else
            xGame.layer->reorderChild(label, 0);
    }
}


void gDrawStringBold(float x, float y,const char* src, int ankNum, int r, int g, int b, int rr, int gg, int bb)
{

    char strFileName[32];
    //간격
    float fCharWidth = -3;
    
    sprintf(strFileName, "nanumgothic.ttf");
    
    float fscale;
    float fscaleX;
    float fscaleY;
    
    if(xGame.isReSizeDraw == true)
    {
        if(xGame.fgameScale != 1.0f)
            fscale = xGame.fgameScale * ((float)(xGame.reSize)/100.f);
        else
        {
            fscale = xGame.fgameScale + ((float)(xGame.reSize-100)/100.f);
        }
        
        fscaleX = fscale;
        fscaleY = fscale;
    }
    else if(xGame.isReSizeDrawXY == true)
    {
        if(xGame.fgameScale != 1.0f)
        {
            fscaleX = xGame.fgameScale * ((float)(xGame.reSizeX)/100.f);
            fscaleY = xGame.fgameScale * ((float)(xGame.reSizeY)/100.f);
        }
        else
        {
            fscaleX = xGame.fgameScale + ((float)(xGame.reSizeX-100)/100.f);
            fscaleY = xGame.fgameScale + ((float)(xGame.reSizeY-100)/100.f);
        }
    }
    else
    {
        fscale = xGame.fgameScale;
        fscaleX = fscale;
        fscaleY = fscale;
    }
    
    x += ((x-xGame.fgameScaleCx) * (xGame.fgameScale-1.f));
    y += ((y-xGame.fgameScaleCy) * (xGame.fgameScale-1.f));
    
    
    
    if(xGame.isClip == true)
    {
        x -= clip->getPosition().x;
        y += clip->getPosition().y;
    }
    
    //auto label = cocos2d::Label::createWithSystemFont(src, strFileName, fontSize);
    bool isNew = false;
    Label* label;
    if(xGame.isClip == true)
    {
        label = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
    }
    else
    {
        int index = getFontRe(src, fontSize,true);
        
        if(index == DONT)
        {
            isNew = true;
            index = addFontRe(src, fontSize,true);
            xFontRe.xSlot[index].lable = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
        }
        
        xFontRe.xSlot[index].isUse = true;
        label = xFontRe.xSlot[index].lable;
    }
    label->setScale(fscale);
    label->setPosition(x,lcdH-y);
//    label->setColor(Color3B(r, g, b));
    label->setTextColor(Color4B(Color3B(r, g, b)));
    label->enableOutline(Color4B(rr, gg, bb, 255),2);
    label->setAdditionalKerning(fCharWidth);
    label->setOpacity(xGame.alpha);
    
    if(iLabelWidth != 0)	label->setWidth(iLabelWidth);
    if(iLabelHeight != 0)	label->setHeight(iLabelHeight);
    
    switch(ankNum)
    {
        case TL:label->setAnchorPoint(Vec2(0, 1.0f));label->setAlignment(TextHAlignment::LEFT);break;
        case VH:label->setAnchorPoint(Vec2(0.5f, 0.5f));label->setAlignment(TextHAlignment::CENTER);break;
        case TH:label->setAnchorPoint(Vec2(0.5f, 1.0f));label->setAlignment(TextHAlignment::CENTER);break;
        case BH:label->setAnchorPoint(Vec2(0.5f, 0));label->setAlignment(TextHAlignment::CENTER);break;
        case VL:label->setAnchorPoint(Vec2(0, 0.5f));label->setAlignment(TextHAlignment::LEFT);break;
        case VR:label->setAnchorPoint(Vec2(1.0f, 0.5f));label->setAlignment(TextHAlignment::RIGHT);break;
    }
    
    if(xGame.isClip == true)
        clip->addChild(label,0,100);
    else
    {
        if(isNew == true)
            xGame.layer->addChild(label,0,200);
        else
            xGame.layer->reorderChild(label, 0);
    }
}


int getLabelWidth(const char *src,int fontSize, bool isBold)
{
    char strFileName[32];
	float fCharWidth = -2;
	int width = 0;
	
    
    
    sprintf(strFileName, "nanumgothic.ttf");
    

	//auto label = cocos2d::Label::createWithSystemFont(src, strFileName, fontSize);
	auto label = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
	label->setColor(Color3B(255, 255,255));
	if(isBold == true)		label->enableOutline(Color4B(255,255,255,255),2);
	label->setAdditionalKerning(fCharWidth);
	if(iLabelWidth != 0)	label->setWidth(iLabelWidth);
	if(iLabelHeight != 0)	label->setHeight(iLabelHeight);
	width = label->getContentSize().width;
    
        

	return width;
}


int getLabelHeight(const char *src,int fontSize, bool isBold)
{
	char strFileName[32];
	float fCharWidth = -2;
	int height = 0;
		
    sprintf(strFileName, "nanumgothic.ttf");
    
    
	//auto label = cocos2d::Label::createWithSystemFont(src, strFileName, fontSize);
    auto label = cocos2d::Label::createWithTTF(src, strFileName, fontSize);
	label->setColor(Color3B(255, 255,255));
	if(isBold == true)		label->enableOutline(Color4B(255,255,255,255),2);
	label->setAdditionalKerning(fCharWidth);
	if(iLabelWidth != 0)	label->setWidth(iLabelWidth);
	if(iLabelHeight != 0)	label->setHeight(iLabelHeight);
	height = label->getContentSize().height;
	
	return height;
}

void setLabelWidth(int width)
{
	iLabelWidth = width;
}

void setLabelHeight(int height)
{
	iLabelHeight = height;
}

void setFontSizeORI(int fontSize22)
{
    fontSize = fontSize22;
}

void setFontSize(int fontSize22)
{
    switch(fontSize22)
    {
    case 8:
        fontSize = 14;
        break;
    case 11:
        fontSize = 18;
        break;
    case 14:
        fontSize = 22;
        break;
    case 20:
        fontSize = 25;
        break;
    default:
        fontSize = fontSize22;
        break;
    }
}

