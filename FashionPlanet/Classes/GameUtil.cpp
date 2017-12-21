

#include "Global.h"
#include <sys/stat.h>

#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "external/unzip/unzip.h"

using namespace cocos2d::network;

M_Boolean isCollLineUp;
M_Boolean isCollLineDown;
M_Boolean isCollLineLeft;
M_Boolean isCollLineRight;

M_Int32 rmask;		
M_Int32 gmask;		
M_Int32 bmask;		
M_Uint32 ranDomN;		//∑£¥˝∞™ ¡æ¿⁄
Xscroll xScroll;
M_Int32 ScrollCnt;
XRADIUS xRadius;
XPOPUP xPopup;

XIMG imgRect;


cocos2d::ClippingNode* clip;
cocos2d::DrawNode* shape;

char *openGalleryBuf;


//const float		gcf_ftTexture_ZeroDotFive	= 0.4999990f + 0.0000010f;

float Sintable[360] = { 
	0.000f, 0.017f, 0.035, 0.053, 0.071, 0.089, 0.0107, 0.0124, 0.0142, 0.0160, 0.0177, 0.0195, 0.0212, 0.0230, 0.0247, 0.0265, 0.0282, 0.0299, 0.0316, 0.0333, 0.0350, 0.0366, 0.0383, 0.0400, 0.0416, 0.0432, 
		448, 464, 480, 496, 512, 527, 542, 557, 572, 587, 601, 616, 630, 644, 658, 671, 685, 698, 711, 724, 736, 748, 760, 772,
		784, 795, 806, 817, 828, 838, 848, 858, 868, 877, 886, 895, 904, 912, 920, 928, 935, 942, 949, 955, 962, 968, 973, 979, 
		984, 989, 993, 997, 1001, 1005, 1008, 1011, 1014, 1016, 1018, 1020, 1021, 1022, 1023, 1023, 1024, 1023, 1023, 1022, 1021, 
		1020, 1018, 1016, 1014, 1011, 1008, 1005, 1001, 997, 993, 989, 984, 979, 973, 968, 962, 955, 949, 942, 935, 928, 920, 912,
		904, 895, 886, 877, 868, 858, 848, 838, 828, 817, 806, 795, 784, 772, 760, 748, 736, 724, 711, 698, 685, 671, 658, 644, 
		630, 616, 601, 587, 572, 557, 542, 527, 511, 496, 480, 464, 448, 432, 416, 400, 383, 366, 350, 333, 316, 299, 282, 265, 
		247, 230, 212, 195, 177, 160, 142, 124, 107, 89, 71, 53, 35, 17, 0, -17, -35, -53, -71, -89, -107, -124, -142, -160, -177, 
		-195, -212, -230, -247, -265, -282, -299, -316, -333, -350, -366, -383, -400, -416, -432, -448, -464, -480, -496, -512, -527, 
		-542, -557, -572, -587, -601, -616, -630, -644, -658, -671, -685, -698, -711, -724, -736, -748, -760, -772, -784, -795, 
		-806, -817, -828, -838, -848, -858, -868, -877, -886, -895, -904, -912, -920, -928, -935, -942, -949, -955, -962, -968, 
		-973, -979, -984, -989, -993, -997, -1001, -1005, -1008, -1011, -1014, -1016, -1018, -1020, -1021, -1022, -1023, -1023, 
		-1024, -1023, -1023, -1022, -1021, -1020, -1018, -1016, -1014, -1011, -1008, -1005, -1001, -997, -993, -989, -984, -979, 
		-973, -968, -962, -955, -949, -942, -935, -928, -920, -912, -904, -895, -886, -877, -868, -858, -848, -838, -828, -817, 
		-806, -795, -784, -772, -760, -748, -736, -724, -711, -698, -685, -671, -658, -644, -630, -616, -601, -587, -572, -557, 
		-542, -527, -511, -496, -480, -464, -448, -432, -416, -400, -383, -366, -350, -333, -316, -299, -282, -265, -247, -230, 
		-212, -195, -177, -160, -142, -124, -107, -89, -71, -53, -35, -17
};

float Costable[360] = { 
	1024, 1023, 1023, 1022, 1021, 1020, 1018, 1016, 1014, 1011, 1008, 1005, 1001, 997, 993, 989, 984, 979, 973, 968, 962, 955, 
		949, 942, 935, 928, 920, 912, 904, 895, 886, 877, 868, 858, 848, 838, 828, 817, 806, 795, 784, 772, 760, 748, 736, 724, 
		711, 698, 685, 671, 658, 644, 630, 616, 601, 587, 572, 557, 542, 527, 511, 496, 480, 464, 448, 432, 416, 400, 383, 366, 
		350, 333, 316, 299, 282, 265, 247, 230, 212, 195, 177, 160, 142, 124, 107, 89, 71, 53, 35, 17, 0, -17, -35, -53, -71, 
		-89, -107, -124, -142, -160, -177, -195, -212, -230, -247, -265, -282, -299, -316, -333, -350, -366, -383, -400, -416, 
		-432, -448, -464, -480, -496, -512, -527, -542, -557, -572, -587, -601, -616, -630, -644, -658, -671, -685, -698, -711, 
		-724, -736, -748, -760, -772, -784, -795, -806, -817, -828, -838, -848, -858, -868, -877, -886, -895, -904, -912, -920, 
		-928, -935, -942, -949, -955, -962, -968, -973, -979, -984, -989, -993, -997, -1001, -1005, -1008, -1011, -1014, -1016, 
		-1018, -1020, -1021, -1022, -1023, -1023, -1024, -1023, -1023, -1022, -1021, -1020, -1018, -1016, -1014, -1011, -1008, 
		-1005, -1001, -997, -993, -989, -984, -979, -973, -968, -962, -955, -949, -942, -935, -928, -920, -912, -904, -895, -886, 
		-877, -868, -858, -848, -838, -828, -817, -806, -795, -784, -772, -760, -748, -736, -724, -711, -698, -685, -671, -658,
		-644, -630, -616, -601, -587, -572, -557, -542, -527, -511, -496, -480, -464, -448, -432, -416, -400, -383, -366, -350, 
		-333, -316, -299, -282, -265, -247, -230, -212, -195, -177, -160, -142, -124, -107, -89, -71, -53, -35, -17, 0, 17, 35, 
		53, 71, 89, 107, 124, 142, 160, 177, 195, 212, 230, 247, 265, 282, 299, 316, 333, 350, 366, 383, 400, 416, 432, 448, 464, 
		480, 496, 512, 527, 542, 557, 572, 587, 601, 616, 630, 644, 658, 671, 685, 698, 711, 724, 736, 748, 760, 772, 784, 795,
		806, 817, 828, 838, 848, 858, 868, 877, 886, 895, 904, 912, 920, 928, 935, 942, 949, 955, 962, 968, 973, 979, 984, 989, 
		993, 997, 1001, 1005, 1008, 1011, 1014, 1016, 1018, 1020, 1021, 1022, 1023, 1023
};


void initContext(void)
{
    gSetColor(0,0,0);
	setAlpha(ALPHA_MAX);	
}

void setState(M_Int8 nexts, M_Int8 plays,M_Int8 subplays)
{
	beforState = nowState;
	nextState = nexts;
	nowState = GAME_LOADING;
	playState = plays;
	loadingCnt = 0;
	subStateTemp = subplays;
}

/*
void loadImg(const char*strFileName,XIMG* img)
{
    img->isSdCard = false;
    if(img->texture == NULL && img->w != DONT)
    {
        img->texture = Director::getInstance()->getTextureCache()->addImage(strFileName);
        
        
        if(img->texture != NULL)
        {
            img->w = img->texture->getPixelsWide();
            img->h = img->texture->getPixelsHigh();
            
            if(xGame.isUnAnti == true)
                img->texture->setAliasTexParameters();
        }
        else
            img->w = DONT;
    }
}
*/


void loadImg(const char* strFileName, XIMG* img)
{
    
    memset(xIOStream.strIOFileName, 0, sizeof(xIOStream.strIOFileName));
    sprintf(xIOStream.strIOFileName,"%s",strFileName);
    
    
    if(img->texture == NULL && img->w != DONT)
    {
        loadFileData((char*)xIOStream.strIOFileName, bufData, &bufDataSize);
        
        if(bufDataSize > 0)
        {
            img->image = new (std::nothrow) Image();
            if(img->image->initWithImageData((const unsigned char *)bufData, bufDataSize) == true)
            {
                sprintf(xIOStream.strChache, "%d%s",xIOStream.imgChcheCnt++,xIOStream.strIOFileName);
                img->texture = Director::getInstance()->getTextureCache()->addImage(img->image,xIOStream.strChache);
                
                if(img->texture != NULL)
                {
                    img->w = img->texture->getPixelsWide();
                    img->h = img->texture->getPixelsHigh();
                }
            }
            else
            {
                img->w = DONT;
                CC_SAFE_RELEASE(img->image);
            }
        }
        else
            img->w = DONT;
    }
}



void loadImgCash(const char* strFileName, XIMG* img)
{
    memset(xIOStream.strIOFileName, 0, sizeof(xIOStream.strIOFileName));
    sprintf(xIOStream.strIOFileName,"%s",strFileName);
    
    int len = strlen(xIOStream.strIOFileName);
    xIOStream.strIOFileName[len-1]='p';  //g
    xIOStream.strIOFileName[len-2]='p';  //n
    xIOStream.strIOFileName[len-3]='p';  //p
    
    if(img->texture == NULL && img->w != DONT)
    {
        loadNativeFileData((char*)xIOStream.strIOFileName, bufData, &bufDataSize);
        
        if(bufDataSize > 0)
        {
            img->image = new (std::nothrow) Image();
            if(img->image->initWithImageData((const unsigned char *)bufData, bufDataSize) == true)
            {
                sprintf(xIOStream.strChache, "%d%s",xIOStream.imgChcheCnt++,xIOStream.strIOFileName);
                img->texture = Director::getInstance()->getTextureCache()->addImage(img->image,xIOStream.strChache);
                
                if(img->texture != NULL)
                {
                    img->w = img->texture->getPixelsWide();
                    img->h = img->texture->getPixelsHigh();
                }
            }
            else
            {
                img->w = DONT;
                CC_SAFE_RELEASE(img->image);
            }
        }
        else
            img->w = DONT;
    }
}

void freeImg(XIMG* img)
{
    if(img->texture != NULL)
    {
        CC_SAFE_RELEASE(img->image);
        Director::getInstance()->getTextureCache()->removeTexture(img->texture);
    }
    img->texture = NULL;
    img->w = 0;

}


void gSetColor(M_Int32 r, M_Int32 g, M_Int32 b)
{
	xGame.r = r;
	xGame.g = g;
	xGame.b = b;
}





void setAlpha(M_Int32 alpha)
{
    
    if(alpha < 0)
        alpha = 0;
    else if(alpha > ALPHA_MAX)
        alpha = ALPHA_MAX;
    xGame.alpha = alpha;
}



void gSetClip(bool isClip,M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h)
{
    w = w;
    h = h;
    x = x;
    y = lcdH-y-h;
    
    if(isClip == true)
    {
        shape = DrawNode::create();
        Point pts[4];
        pts[0] = Vec2( 0, 0 + h);
        pts[1] = Vec2( 0 + w, 0 + h);
        pts[2] = Vec2( 0 + w, 0);
        pts[3] = Vec2( 0, 0);
        
        
        shape->drawPolygon(pts, 4, Color4F(1, 1,1, 1), 0, Color4F(1, 1, 1, 1));
        
        // add shape in stencil
        clip = ClippingNode::create();
        clip->setAnchorPoint(Vec2(0.5, 0.5));
        clip->setPosition( x, y );
        clip->setStencil(shape);
    }
    else
    {
        
        if(xGame.isClip == true)
        {
            xGame.layer->addChild(clip,0,100);
        }
    }
    
    
    xGame.isClip = isClip;
    xGame.clipX = x;
    xGame.clipY = y;
    xGame.clipW = w;
    xGame.clipH = h;
}




//DRAW****************************************************************************************************************************************
/***********************************************************
x, y :: ø¯¿« ¡ﬂΩ…¡¬«•
radius :: π›¡ˆ∏ß
***********************************************************/


void fillArc(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h)
{
	M_Int32 i;
	M_Int32 xPos;
	M_Int32 yPos;
	
	for (i=0; i<360; i++) 
	{
		xPos = x + sin(i)*(w/2);
		yPos = y + cos(i)*(w/2);
		fillRect(xPos , yPos, 1, 1);
	}
}

void fillRect(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h)
{
    xGame.isDrawRect = true;
    drawImage(&imgRect, x, y, 0, 0, w, h, TL);
    xGame.isDrawRect = false;
}










void drawImage(XIMG* img,float x,float y,float imgX,float imgY,float imgW,float imgH,int ank)
{
    if(xGame.alpha == 0)
        return;
    
    switch(ank)
    {
    case TL:
        x += imgW/2;
        y += imgH/2;
        ank = VH;
        break;
    case BL:
        x += imgW/2;
        y -= imgH/2;
        ank = VH;
        break;

    }
    
    if(xGame.isSpriteGroupBuf == true)
        y += lcdH-xGame.spriteGroup->getTexture()->getPixelsHigh();
    
    y =lcdH-y;
    
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
    
    if(fscaleX == 0 || fscaleY == 0)
        return;
    
    Sprite* sprite;
    
    if(xGame.isSpriteGroupDraw == true)
        sprite = xGame.spriteGroup;
    else
    {
        sprite = Sprite::createWithTexture(img->texture, Rect(imgX, imgY, imgW, imgH));
    }
    
    /*
    if(xGame.isMask == true)
    {
        Sprite* sprite1 = Sprite::createWithTexture(xGame.imgMask->texture);
        sprite1->setPosition(sprite->getTexture()->getPixelsWide()/2,sprite->getTexture()->getPixelsHigh()/2);
        sprite = maskedSpriteWithSprite(sprite, sprite1);
    }
     */
    
    if(xGame.isClip == true && xGame.isSpriteGroupBuf == false)
    {
        x -= clip->getPosition().x;
        y -= clip->getPosition().y;
    }
    
    sprite->setPosition(x, y);
    
    if(xGame.isDrawRect == true)
        sprite->setColor(Color3B(xGame.r, xGame.g, xGame.b));
    else
        sprite->setColor(Color3B(ALPHA_MAX, ALPHA_MAX, ALPHA_MAX));
    
    if(xGame.isRotate == true)
    {
        if(xGame.rotateNum < 0)
            xGame.rotateNum = 360+xGame.rotateNum;
        if(xGame.rotateNum < 0)
            xGame.rotateNum = 360+xGame.rotateNum;
        if(xGame.rotateNum < 0)
            xGame.rotateNum = 360+xGame.rotateNum;
        
        sprite->setRotation(360-xGame.rotateNum);
    }
    
    if(xGame.isReverse == true)
        sprite->setFlippedX(true);
    else
        sprite->setFlippedX(false);
    
    sprite->setScale(fscaleX, fscaleY);
    
    
    switch(ank)
    {
    case TL:sprite->setAnchorPoint(Vec2(0, 1.0f));break;
    case VL:sprite->setAnchorPoint(Vec2(0, 0.5f));break;
    case VR:sprite->setAnchorPoint(Vec2(1.0f, 0.5f));break;
    case VH:sprite->setAnchorPoint(Vec2(0.5f, 0.5f));break;
    case TH:sprite->setAnchorPoint(Vec2(0.5f, 1.0f));break;
    case BH:sprite->setAnchorPoint(Vec2(0.5f, 0));break;
    case BR:sprite->setAnchorPoint(Vec2(1.0f, 0));break;
    case BL:sprite->setAnchorPoint(Vec2(0, 0));break;
    case TR:sprite->setAnchorPoint(Vec2(1.0f, 1.0f));break;
    }
    
    if(xGame.isBlend == true)
    {
        BlendFunc additive;
        
                
        switch(xGame.blendType)
        {
        case BLEND_ADDP:
            additive = {GL_SRC_ALPHA, GL_ONE};
            sprite->setBlendFunc(additive);
            break;
        case BLEND_SCREEN:
            break;
        case BLEND_MULTIPLY:
            break;
        case BLEND_SHADOW:
            break;
        case BLEND_HARDLIGHT:
        case BLEND_LINEARLIGHT:
            break;
        case BLEND_WHITE:
            sprite->setColor(Color3B(255, 255, 255));
            additive = {GL_ONE, GL_ONE};
            sprite->setBlendFunc(additive);
            break;
        case BLEND_WHITEALPHA:
            sprite->setColor(Color3B(255, 255, 255));
            additive = {GL_ONE, GL_ONE};
            sprite->setBlendFunc(additive);
            sprite->setOpacity(xGame.blendNum);
            break;
        case BLEND_RED:
        case BLEND_REDALPHA:
            sprite->setColor(Color3B(255, 0, 0));
            additive = {GL_ONE, GL_ONE};
            sprite->setBlendFunc(additive);                
            sprite->setOpacity(xGame.blendNum);
            break;
        case BLEND_BLACK:
            sprite->setColor(Color3B(0, 0, 0));
            break;
        case BLEND_BLACK_WHITE:
            sprite->setColor(Color3B(xGame.blendNum, xGame.blendNum, xGame.blendNum));
            break;
        case BLEND_SETCOLOR:
            sprite->setColor(Color3B(xGame.r, xGame.g, xGame.b));
            break;
        default:
            break;
        }
    }
    else if(xGame.alpha != ALPHA_MAX)
    {
        sprite->setOpacity(xGame.alpha);
    }
    
    if(xGame.isSpriteGroupBuf == true)
    {
        xGame.spriteGroup->addChild(sprite,0,100);
    }
    else if(xGame.isClip == true)
    {
        clip->addChild(sprite,0,100);
    }
    else
    {
        xGame.layer->addChild(sprite,0,100);
    }
    
    
}











//πŸ¿Ã∆Æ >> ¿Œ∆Æ«¸¿∏∑Œ
M_Int32 getByteToInt(char data[], M_Int32 idx)
{
	M_Int32 result = 0;
	
	result = 
		((data[idx] & 0xFF)		<< 24) |
		((data[idx+1] & 0xFF)	<< 16) |
		((data[idx+2] & 0xFF)	<<  8) | 
		( data[idx+3] & 0xFF);

	return result;
}
//πŸ¿Ã∆Æ >> ¿Œ∆Æ«¸¿∏∑Œ
M_Int16 getByteToInt16(M_Byte data[], M_Int32 idx)
{
	M_Int16 result = 0;
	
	result = 
		((data[idx] & 0xFF)	<<  8) | 
		( data[idx+1] & 0xFF);
	
	return result;
}
//¿Œ∆Æ >> πŸ¿Ã∆Æ«¸¿∏∑Œ
void getIntToByte(M_Int32 num32, M_Byte data[], M_Int32 idx)
{
	data[idx] = (M_Byte)(num32 >> 24 & 0xFF);
	data[++idx] = (M_Byte)(num32 >> 16 & 0xFF);
	data[++idx] = (M_Byte)(num32 >> 8 & 0xFF);
	data[++idx] = (M_Byte)num32;
}

//¿Œ∆Æ16 >> ¿Œ∆Æ«¸¿∏∑Œ
void getInt16ToByte(M_Int16 num16, M_Byte data[], M_Int32 idx)
{
	data[idx] = (M_Byte)(num16 >> 8 & 0xFF);
	data[idx+1] = (M_Byte)num16;
}


//πŸ¿Ã∆Æ >> ¿Œ∆Æ«¸¿∏∑Œ
M_Int32 getByteToIntRe(char data[], M_Int32 idx)
{
	M_Int32 result = 0;
	
	result = 
		((data[idx+3] & 0xFF)	<< 24) |
		((data[idx+2] & 0xFF)	<< 16) |
		((data[idx+1] & 0xFF)	<<  8) | 
		( data[idx] & 0xFF);
	
	return result;
}

//πŸ¿Ã∆Æ >> ¿Œ∆Æ«¸¿∏∑Œ
M_Int16 getByteToInt16Re(char data[], M_Int32 idx)
{
	M_Int16 result = 0;
	
	result = 
		((data[idx+1] & 0xFF)	<<  8) | 
		( data[idx] & 0xFF);
	
	return result;
}
//¿Œ∆Æ >> πŸ¿Ã∆Æ«¸¿∏∑Œ
void getIntToByteRe(M_Int32 num32, M_Byte data[], M_Int32 idx)
{
	data[idx+3] = (M_Byte)(num32 >> 24 & 0xFF);
	data[idx+2] = (M_Byte)(num32 >> 16 & 0xFF);
	data[idx+1] = (M_Byte)(num32 >> 8 & 0xFF);
	data[idx] = (M_Byte)num32;
}

//¿Œ∆Æ16 >> ¿Œ∆Æ«¸¿∏∑Œ
void getInt16ToByteRe(M_Int16 num16, M_Byte data[], M_Int32 idx)
{
	data[idx+1] = (M_Byte)(num16 >> 8 & 0xFF);
	data[idx] = (M_Byte)num16;
}


 
void drawLoadingBar(M_Int32 cnt)
{
	M_Int32 width = cnt * 150 / 100;
	//∑Œµ˘πŸ
	gSetColor(255,255,255);
	fillRect(cx-76, cy-2+70, 152, 4);
	gSetColor(46,109,105);
	fillRect(cx-75, cy-1+70, width, 2);
}

M_Int32 ranDom(M_Int32 startNum,M_Int32 endNum)
{
	M_Int32 temp = 0;
	M_Int32 temp2 = 0;
	
	
	ranDomN = ranDomN * 1103515245 + 12345 + (M_Int32)xCalendar.nowTime;
	
	
	
	
	
	if(startNum < 0)
	{
		endNum += -startNum;
		temp2 = startNum;
		startNum = 0;
	}
	

	temp = (((M_Uint32)(ranDomN/65536) % 32768)%(endNum-startNum+1)+startNum);

	temp += temp2;

	return temp;
}




void gameSave(M_Int32 slot)
{
	switch(slot)
	{
	case SAVE_SLOT_CONFIG:
        break;
	case SAVE_SLOT_GAME:
        bufDataSize = sizeof(xSave);
        memcpy(bufData, &xSave, bufDataSize);
        writeNativeFileData(SAVE_NAME_GAME, bufData, bufDataSize);
		break;
	case SAVE_SLOT_KAKAO:
        bufDataSize = sizeof(xSaveKakao);
        memcpy(bufData, &xSaveKakao, bufDataSize);
        writeNativeFileData(SAVE_NAME_KAKAO, bufData, bufDataSize);
        break;
	case SAVE_SLOT_KAKAOAPP:
        bufDataSize = sizeof(xSaveKakaoApp);
        memcpy(bufData, &xSaveKakaoApp, bufDataSize);
        writeNativeFileData(SAVE_NAME_KAKAOAPP, bufData, bufDataSize);
		break;
	case SAVE_SLOT_KAKAOHELP:
        bufDataSize = sizeof(xSaveKakaoHelp);
        memcpy(bufData, &xSaveKakaoHelp, bufDataSize);
        writeNativeFileData(SAVE_NAME_KAKAOHELP, bufData, bufDataSize);
		break;
    case SAVE_SLOT_NOTICEPOPUP:
        bufDataSize = sizeof(xSaveNoticePopup);
        memcpy(bufData, &xSaveNoticePopup, bufDataSize);
        writeNativeFileData(SAVE_NAME_NOTICEPOPUP, bufData, bufDataSize);
        break;
    case SAVE_SLOT_PRODUCTION:
        bufDataSize = sizeof(xProductionMenuLatestSave);
        memcpy(bufData, &xProductionMenuLatestSave, bufDataSize);
        writeNativeFileData(SAVE_NAME_PRODUCTION, bufData, bufDataSize);
        break;
	case SAVE_SLOT_SELLSLOT:
		bufDataSize = sizeof(xSellSlotSave);
		memcpy(bufData, &xSellSlotSave, bufDataSize);
		writeNativeFileData(SAVE_NAME_SELLSLOT, bufData, bufDataSize);
		break;
	}
}


bool gameLoad(M_Int8 slot)
{
	switch(slot)
	{
	case SAVE_SLOT_CONFIG:
		break;
	case SAVE_SLOT_GAME:
        loadNativeFileData(SAVE_NAME_GAME, bufData, &bufDataSize);            
        if(bufDataSize == 0)
            return false;
        memcpy(&xSave,bufData,bufDataSize);
		break;
	case SAVE_SLOT_KAKAO:
        loadNativeFileData(SAVE_NAME_KAKAO, bufData, &bufDataSize);
        if(bufDataSize == 0)
            return false;
        memcpy(&xSaveKakao,bufData,bufDataSize);
		break;
	case SAVE_SLOT_KAKAOAPP:
        loadNativeFileData(SAVE_NAME_KAKAOAPP, bufData, &bufDataSize);
        if(bufDataSize == 0)
            return false;
        memcpy(&xSaveKakaoApp,bufData,bufDataSize);
		break;
	case SAVE_SLOT_KAKAOHELP:
        loadNativeFileData(SAVE_NAME_KAKAOHELP, bufData, &bufDataSize);
        if(bufDataSize == 0)
            return false;
        memcpy(&xSaveKakaoHelp,bufData,bufDataSize);
		break;
    case SAVE_SLOT_NOTICEPOPUP:
        loadNativeFileData(SAVE_NAME_NOTICEPOPUP, bufData, &bufDataSize);
        if(bufDataSize == 0)
            return false;
        memcpy(&xSaveNoticePopup,bufData,bufDataSize);
        break;
    case SAVE_SLOT_PRODUCTION:
        loadNativeFileData(SAVE_NAME_PRODUCTION, bufData, &bufDataSize);
        if(bufDataSize == 0)
            return false;
        memcpy(&xProductionMenuLatestSave,bufData,bufDataSize);
        break;
	case SAVE_SLOT_SELLSLOT:
		loadNativeFileData(SAVE_NAME_SELLSLOT, bufData, &bufDataSize);
		if(bufDataSize == 0)
			return false;
		memcpy(&xSellSlotSave,bufData,bufDataSize);
		break;
	}
    return true;
}

void drawNum(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank)
{
	M_Int32 w = img->w/10;
	M_Int32 h = img->h;
	
	M_Int32 retinaW = w;
	M_Int32 retinaH = h;
	
 	M_Int32 z;
	M_Int32 val = 0;			
	M_Int32 div = 1;
	M_Int32 tempN = 0;
	M_Int32 pos = 0;
	M_Int32 len = 0;
	
	if(value == 0)
	{
		switch(ank)
		{
		case VR:
			drawImage(img, x - retinaW-gab, y-retinaH/2,0, 0, w, h,TL);
			break;
		case TR:
			drawImage(img, x - retinaW-gab, y,0, 0, w, h,TL);
			break;
		case TL:
			drawImage(img, x, y,0, 0, w, h,TL);
			break;
		case VL:
			drawImage(img, x, y-retinaH/2,0, 0, w, h,TL);
			break;
		case BL:
			drawImage(img, x, y,0, 0, w, h,BL);
        case BR:
            drawImage(img, x - retinaW-gab, y,0, 0, w, h,BL);

			break;
		case TH:
			drawImage(img, x-(gab/2) - (retinaW/2), y,0, 0, w, h,TL);
			break;
		case VH:
			drawImage(img, x-(gab/2) - (retinaW/2), y-retinaH/2,0, 0, w, h,TL);
			break;
		}
		return;
	}

	val = value * 10;
	while(val >= 10)
	{
		val /= 10;
		div *= 10;
		len++;
	}
	val = value * 10;
	for(z=0; z<len; z++)
	{
		tempN = val / div;				// ∞¢ ¿⁄∏Æ ∞™
		switch(ank)
		{
		case VR:
			drawImage(img, x-(((len)-pos)*(retinaW+gab)), y-(retinaH/2), tempN*w, 0, w, h,TL);	
			break;
		case TR:
			drawImage(img, x-(((len)-pos)*(retinaW+gab)), y, tempN*w, 0, w, h,TL);	
			break;
		case TL:
			drawImage(img, x+(((len)-(len -pos))*(retinaW+gab)), y, tempN*w, 0, w, h,TL);	
			break;
		case VL:
			drawImage(img, x+(((len)-(len -pos))*(retinaW+gab)), y-(retinaH/2), tempN*w, 0, w, h,TL);	
			break;
		case BL:
			drawImage(img, x+(((len)-(len -pos))*(retinaW+gab)), y, tempN*w, 0, w, h,BL);	
			break;
        case BR:
            drawImage(img, x-(((len)-pos)*(retinaW+gab)), y, tempN*w, 0, w, h,BL);	
            break;

		case TH:
			drawImage(img, x-(((len)-pos)*(retinaW+gab)) + ((len)*(retinaW+gab))/2, y, tempN*w, 0, w, h,TL);	
			break;
		case VH:
			drawImage(img, x-(((len)-pos)*(retinaW+gab)) + ((len)*(retinaW+gab))/2, y-(retinaH/2), tempN*w, 0, w, h,TL);	
			break;

		}
		val -= tempN * div;				// √÷¥Î¿⁄∏Æ∞™ ª©±‚
		div /= 10;						// ≥™¥≠ ∞™ ¿⁄∏Æ ¡Ÿ¿Ã±‚
		pos++;							// ¬Ô¿ª ¿ßƒ°∞™ ¿Ãµø
		if( tempN < 0 )
			val = (len - pos) * div;
	}
}

void drawArrow(XIMG *img,M_Int32 x,M_Int32 y,M_Int32 type)
{
	M_Int32 anyPos;
	
	switch(gameCnt%4)
	{
		case 0:
			anyPos = 0;
			break;
		case 1:
			anyPos = 1;
			break;
		case 2:
			anyPos = 2;
			break;
		case 3:
			anyPos = 1;
			break;
	}
	
	switch(type)
	{
		case ARROW_UP:
			drawImage(img, x,y-anyPos,0,0, img->w/4, img->h, VH);
			break;
		case ARROW_DOWN:
			drawImage(img, x,y+anyPos,img->w/4,0, img->w/4, img->h, VH);
			break;
		case ARROW_LEFT:
			drawImage(img, x-anyPos,y,img->w/4*2,0, img->w/4, img->h, VH);
			break;
		case ARROW_RIGHT:
			drawImage(img, x+anyPos,y,img->w/4*3,0, img->w/4, img->h, VH);
			break;
	}
	
	switch(type)
	{
		case ARROW_UP:
			xTouchArrowUp.xPos = x-img->w/4/2;
			xTouchArrowUp.yPos = y-img->h/2;
			xTouchArrowUp.wPos = img->w/4;
			xTouchArrowUp.hPos = img->h;
			break;
		case ARROW_DOWN:
			xTouchArrowDown.xPos = x-img->w/4/2;
			xTouchArrowDown.yPos = y-img->h/2;
			xTouchArrowDown.wPos = img->w/4;
			xTouchArrowDown.hPos = img->h;
			break;
		case ARROW_LEFT:
			xTouchArrowLeft.xPos = x-img->w/4/2;
			xTouchArrowLeft.yPos = y-img->h/2;
			xTouchArrowLeft.wPos = img->w/4;
			xTouchArrowLeft.hPos = img->h;
			break;
		case ARROW_RIGHT:
			xTouchArrowRight.xPos = x-img->w/4/2;
			xTouchArrowRight.yPos = y-img->h/2;
			xTouchArrowRight.wPos = img->w/4;
			xTouchArrowRight.hPos = img->h;
			break;
	}
}

void drawNumComma(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank,XIMG* imgComma,int commagab)
{
	M_Int32 w = img->w/10;
	M_Int32 h = img->h;
	M_Int32 retinaW = w;
	M_Int32 retinaH = h;
	
	M_Int32 retinaCommaW = imgComma->w;


	M_Int32 xPos;
	M_Int32 yPos;

 	M_Int32 z;
	M_Int32 val = 0;			
	M_Int32 div = 1;
	M_Int32 tempN = 0;
	M_Int32 pos = 0;
	M_Int32 len = 0;
	M_Int32 commaW = 0;
	M_Int32 commaMax = 0;
	
	

	
	if(value == 0)
	{
		switch(ank)
		{
			case VR:
				drawImage(img, x - retinaW-gab, y-retinaH/2,0, 0, w, h,TL);
				break;
			case TR:
				drawImage(img, x - retinaW-gab, y,0, 0, w, h,TL);
				break;
			case TL:
				drawImage(img, x, y,0, 0, w, h,TL);
				break;
			case VL:
				drawImage(img, x, y-retinaH/2,0, 0, w, h,TL);
				break;
			case BL:
				drawImage(img, x, y,0, 0, w, h,BL);
			case BR:
				drawImage(img, x - retinaW-gab, y,0, 0, w, h,BL);
				
				break;
			case TH:
				drawImage(img, x-(gab/2) - (retinaW/2), y,0, 0, w, h,TL);
				break;
			case VH:
				drawImage(img, x-(gab/2) - (retinaW/2), y-retinaH/2,0, 0, w, h,TL);
				break;
		}
		return;
	}
	
	val = value * 10;
	while(val >= 10)
	{
		val /= 10;
		div *= 10;
		len++;
	}
	val = value * 10;
	
	commaMax = (len-1)/3;
	
	for(z=0; z<len; z++)
	{
		tempN = val / div;				// ∞¢ ¿⁄∏Æ ∞™
		switch(ank)
		{
			case VR:
				xPos = x-(((len)-pos)*(retinaW+gab))+commaW-(commaMax*((retinaCommaW/2+commagab)*2));
				yPos = y-(retinaH/2);
				
				drawImage(img, xPos, yPos, tempN*w, 0, w, h,TL);
				

				if(z != len-1 && (len-z-1)%3 == 0)
				{
					commaW += retinaCommaW/2+commagab;
					xPos = x-(((len)-pos)*(retinaW+gab))+commaW-(commaMax*((retinaCommaW/2+commagab)*2));
					yPos = y-(retinaH/2);
					drawImage(imgComma, xPos+(retinaW+gab), yPos+retinaH, 0, 0, imgComma->w, imgComma->h, BL);
					commaW += retinaCommaW/2+commagab;
				}
				break;				
		}
		val -= tempN * div;
		div /= 10;
		pos++;
		if( tempN < 0 )
			val = (len - pos) * div;
	}
}



void drawNumDollar(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank,XIMG* imgComma,int commagab)
{
	M_Int32 w = img->w/10;
	M_Int32 h = img->h;
	M_Int32 retinaW = w;
	M_Int32 retinaH = h;
	
	M_Int32 retinaCommaW = imgComma->w;
	
	
	M_Int32 xPos;
	M_Int32 yPos;
	
 	M_Int32 z;
	M_Int32 val = 0;			
	M_Int32 div = 1;
	M_Int32 tempN = 0;
	M_Int32 pos = 0;
	M_Int32 len = 0;
	M_Int32 commaW = 0;
	M_Boolean is99 = FALSE;
	if(value == 99)
	{
		value = 199;
		is99 = TRUE;
	}
		
	
	
	
	if(value == 0)
	{
		switch(ank)
		{
			case VR:
				drawImage(img, x - retinaW-gab, y-retinaH/2,0, 0, w, h,TL);
				break;
			case TR:
				drawImage(img, x - retinaW-gab, y,0, 0, w, h,TL);
				break;
			case TL:
				drawImage(img, x, y,0, 0, w, h,TL);
				break;
			case VL:
				drawImage(img, x, y-retinaH/2,0, 0, w, h,TL);
				break;
			case BL:
				drawImage(img, x, y,0, 0, w, h,BL);
			case BR:
				drawImage(img, x - retinaW-gab, y,0, 0, w, h,BL);
				
				break;
			case TH:
				drawImage(img, x-(gab/2) - (retinaW/2), y,0, 0, w, h,TL);
				break;
			case VH:
				drawImage(img, x-(gab/2) - (retinaW/2), y-retinaH/2,0, 0, w, h,TL);
				break;
		}
		return;
	}
	
	val = value * 10;
	while(val >= 10)
	{
		val /= 10;
		div *= 10;
		len++;
	}
	val = value * 10;
	
	
	for(z=0; z<len; z++)
	{
		tempN = val / div;				// ∞¢ ¿⁄∏Æ ∞™
		switch(ank)
		{
			case VR:
				xPos = x-(((len)-pos)*(retinaW+gab))+commaW-(((retinaCommaW/2+commagab)*2));
				yPos = y-(retinaH/2);
				
				if(is99 == TRUE && z == 0)
					drawImage(img, xPos, yPos, 0, 0, w, h,TL);
				else
					drawImage(img, xPos, yPos, tempN*w, 0, w, h,TL);
				
				
				if(len-z == 3)
				{
					commaW += retinaCommaW/2+commagab;
					xPos = x-(((len)-pos)*(retinaW+gab))+commaW-(((retinaCommaW/2+commagab)*2));
					yPos = y-(retinaH/2);
					drawImage(imgComma, xPos+(retinaW+gab), yPos+retinaH, 0, 0, imgComma->w, imgComma->h, BL);
					commaW += retinaCommaW/2+commagab;
				}
				break;				
		}
		val -= tempN * div;				// √÷¥Î¿⁄∏Æ∞™ ª©±‚
		div /= 10;						// ≥™¥≠ ∞™ ¿⁄∏Æ ¡Ÿ¿Ã±‚
		pos++;							// ¬Ô¿ª ¿ßƒ°∞™ ¿Ãµø
		if( tempN < 0 )
			val = (len - pos) * div;
	}

}




//∞¢µµ ªÃ±‚
//(≈∏¿‘,¿‘ªÁ∞¢)
M_Int32 getReflexRadius(M_Int32 dir,M_Int32 inRad)
{
	M_Int32 rad;
	

	switch(dir)
	{
	case POS_UP:
	case POS_DOWN:
		rad = 180 - inRad;
		if(rad < 0)
			rad = 360 + rad;
		break;
	case POS_LEFT:
	case POS_RIGHT:
		rad = 360 - inRad;
		break;
	}

	return rad;
}


//∞¢µµø° µ˚∏• √÷¡æ ¿Ãµø¿ßƒ°±∏«œ±‚
//(x¡¬«•,y¡¬«•,¿Ãµø∞¢)
void getRadiusPos(float x,float y,float speed,float rad)
{	

	if(rad < 0.f)
		rad = 0.f;
	if(rad > 359.f)
		rad = 359.f;

	
	rad = rad*3.1459f/180.f;
	xRadius.pos[XPOS] = x+((speed * sinf(rad)));
	xRadius.pos[YPOS] = y+((speed * cosf(rad)));
}



//º”µµ ªÃæ∆ø¿±‚
//(x¡¬«•,y¡¬«•,¿¸x¡¬«•,¿¸y¡¬«•,¿Ãµø∞¢)
float getRadiusSpeed(float x,float y,float beforX,float beforY,float rad)
{	
	float speedX;
	float speedY;
	float speed;
	float speedTemp1;
	float speedTemp2;

	speedTemp1 = beforX-x;
	speedTemp2 = beforY-y;
	speedX  = speedTemp1;
	speedY  = speedTemp2;

	speedX = speedX * speedX;
	speedY = speedY * speedY;


	if(speedX < 0)
		speedX = -speedX;
	if(speedY < 0)
		speedY = -speedY;


	speed = Newton_Raphson(speedX+speedY,1);
	return speed;
}

//¡¶∞ˆ±Ÿ ±∏«œ±‚
float getRoot(float num)
{
	float	low = 1;
	float high = num; 
	float mid;
	
	while(TRUE)
	{
		mid = ( low + high ) / 2;
		if( mid == low )
			return mid;
		
		if( mid * mid > num )
			high = mid;
		else if( mid * mid == num )
			return mid;
		else
			low = mid;
	}
}

double Newton_Raphson(double n, double r)
{
	if( r*r-n > -0.5 && r*r-n < 0.5 )
		return r;
	return Newton_Raphson(n,(n/r+r)/2);
}


float getArcTan(float x,float y,float tx,float ty)
{
	M_Int32 i;
	float result;			//∞¢µµ
	float prcTemp0;		//±‚øÔ±‚
	float prcTemp1;
	float prcTemp2;
	float prcTemp3;
	float prcTemp4;
	float prcTemp5;
	float rad;


	//±‚øÔ±‚ ±∏«œ±‚
	prcTemp0 = 0;
	result = 0;
	if(tx-x != 0)
		prcTemp0 = (ty-y)/(tx-x);
	else
		prcTemp0 = 0;
	
	if(prcTemp0 < 0)
		prcTemp0 = -prcTemp0;
	
	for(i=0;i<90;i++)
	{
		rad = i*3.1459f/180.f;

		if(cosf(rad) > 0)
			prcTemp1 = sinf(rad) / cosf(rad);
		else
			prcTemp1 = 0;
		
		rad = (i+1)*3.1459f/180.f;

		if(cosf(rad) > 0)
			prcTemp2 = sinf(rad) / cosf(rad);
		else
			prcTemp2 = 1;
		
		prcTemp3 = prcTemp0 - prcTemp1;
		prcTemp4 = prcTemp0 - prcTemp2;
		
		if(prcTemp3 < 0)
			prcTemp3 = -prcTemp3;
		if(prcTemp4 < 0)
			prcTemp4 = -prcTemp4;
		
		if(prcTemp3 <= prcTemp4)
		{
			prcTemp5 = i;
			break;
		}
	}
	
	if(ty == y && tx == x)		
	{
		result = 0;
	}
	else if(ty == y)
	{
		if(x < tx)
			result = 90;
		else
			result = 270;
	}
	else if(tx == x)
	{
		if(y < ty)
			result = 0;
		else
			result = 180;
	}
	else if(ty < y)		//∏Ò«•∞° ¿ßø°¿÷¿Ω
	{
		if(x == tx)
			result = 0;
		else if(x < tx)
			result = 90+prcTemp5;
		else
			result = 270 - prcTemp5;
	}
	else if(ty > y)		//∏Ò«•∞° æ∆∑°¿’¿Ω
	{
		
		if(x == tx)
			result = 0;
		else if(x < tx)
			result = 90-prcTemp5;
		else
			result = 270 + prcTemp5;
		
	}
	return result;
}

M_Boolean isChungCheck(M_Int32 x,M_Int32 y,M_Int32 w,M_Int32 h,M_Int32 tx,M_Int32 ty,M_Int32 tw,M_Int32 th)
{

	if(((x< tx+tw) && (tx < x+w))
		&& ((y < ty+th) && (ty < y+h)))
		return TRUE;

	return FALSE;
}








//ø¯¿« √Êµπ√º≈©
M_Boolean checkArc(float x1,float y1,float r1,float x2,float y2,float r2)
{
	if(JAEGOB(x1-x2) + JAEGOB(y1-y2) <= JAEGOB((r1)/2+(r2)/2))
		return TRUE;
	else
		return FALSE;
		
}



void getTime(void)
{
    struct tm *tm;
    time_t timep;
    timeval tv;
    gettimeofday(&tv, nullptr);
    
    setlocale(LC_ALL, "Korean");//지역을 한국으로 설정
    timep = tv.tv_sec;
    tm = localtime(&timep);
    
    xCalendar.nowYear = tm->tm_year + 1900;
    
    xCalendar.nowMonth = tm->tm_mon + 1;
    
    xCalendar.nowDay = tm->tm_mday;
    
    xCalendar.nowHour = tm->tm_hour;
    
    xCalendar.nowMinute = tm->tm_min;
    
    xCalendar.nowSec = tm->tm_sec;
    
    xCalendar.nowTime = tv.tv_sec;
    
    xCalendar.nowMilSec = (xCalendar.nowTime*1000)+(tv.tv_usec/1000);
}


bool checkCollLineLine(XLINE v1, XLINE v2, XLINE v3, XLINE v4)
{
	float denom = (float)((v4.y - v3.y) * (v2.x - v1.x)) - ((v4.x - v3.x) * (v2.y - v1.y));
	float numerator = (float)((v4.x - v3.x) * (v1.y - v3.y)) - ((v4.y - v3.y) * (v1.x - v3.x));
	float numerator2 = (float)((v2.x - v1.x) * (v1.y - v3.y)) - ((v2.y - v1.y) * (v1.x - v3.x));
	
	if(denom == 0.0f)
	{
		if(numerator == 0.0f && numerator2 == 0.0f)
		{
			//COINCIDENT;
			return false;
		}
		// PARALLEL
		return false;
	}
	
	float ua = numerator / denom;
	float ub = numerator2/ denom;
	
	return (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f);
}

void loadFileData(char *fileName, char *fileBuf, long *fileSize)
{
    *fileSize = 0;
    unsigned char * buffTemp = FileUtils::getInstance()->getFileData(fileName, "rb", (ssize_t *)fileSize);
    memcpy(fileBuf, buffTemp, (*fileSize));
    free(buffTemp);
}

void loadSdFileData(char *fileName, char *fileBuf, long *fileSize)
{
    *fileSize = 0;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string strFilePath = FileUtils::getInstance()->getWritablePath().append(fileName);
    
    unsigned char * buffTemp = FileUtils::getInstance()->getFileData(strFilePath.c_str(), "rb", (ssize_t *)fileSize);
    memcpy(fileBuf, buffTemp, (*fileSize));
    free(buffTemp);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char strFileName[128];
    sprintf(strFileName, "%s%s%s",xGame.strAndSDCard,SD_DIR,fileName);
    FILE *stream = fopen(strFileName, "rb");
    
    if( stream > 0)
    {
        fseek(stream, 0, SEEK_END);
        *fileSize = ftell(stream);
        fseek( stream, 0, 0);
        fread(fileBuf, 1, *fileSize, stream);
        fclose(stream);
    }
#endif
    
}




void writeSdFileData(char *fileName, char *fileBuf, long fileSize)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string strFilePath = FileUtils::getInstance()->getWritablePath().append(fileName);
    
    FILE *stream = fopen(strFilePath.c_str(), "wb");
    fwrite(fileBuf, 1, fileSize, stream);
    fclose(stream);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char strFileName[128];
    sprintf(strFileName, "%s%s%s",xGame.strAndSDCard,SD_DIR,fileName);
    FILE *stream = fopen(strFileName, "wb");
    
    if( stream > 0)
    {
        fwrite(fileBuf, 1, fileSize, stream);
        fclose(stream);
    }
#endif
}


void loadNativeFileData(char *fileName, char *fileBuf, long *fileSize)
{
    *fileSize = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    loadSdFileData(fileName, fileBuf, fileSize);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char strFileName[128];
    sprintf(strFileName, "%s%s",xGame.strAndDataPack,fileName);
    FILE *stream = fopen(strFileName, "rb");
    
    if(stream == NULL)
    {
        *fileSize = 0;
        return;
    }
    
    fseek(stream, 0, SEEK_END);
    *fileSize = ftell(stream);
    fseek( stream, 0, 0);
    
    fread(fileBuf, 1, (*fileSize), stream);
    fclose(stream);
    
    
#endif
}

void writeNativeFileData(char *fileName, char *fileBuf, long fileSize)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    writeSdFileData(fileName, fileBuf, fileSize);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char strFileName[128];
    sprintf(strFileName, "%s%s",xGame.strAndDataPack,fileName);
    FILE *stream = fopen(strFileName, "wb");
    fwrite(fileBuf, 1, fileSize, stream);
    fclose(stream);
#endif
}


void urlFileDownLoad(char *fileName, char *url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IosUtil::getInstance()->startDownLoad((const char*)fileName, (const char*)url);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "urlFileDownLoad", "([B[B)V")) {
        
        jbyteArray arg1;
        jbyteArray arg2;
        
        arg1 = t.env->NewByteArray(strlen(fileName));
        t.env->SetByteArrayRegion(arg1, 0, strlen(fileName), (jbyte*)fileName);
        
        arg2 = t.env->NewByteArray(strlen(url));
        t.env->SetByteArrayRegion(arg2, 0, strlen(url), (jbyte*)url);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1, arg2);
        
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(arg2);
        
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void startWebView(char *strUrl)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "startWebView", "([B)V"))
    {
        
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strUrl));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strUrl), (jbyte*)strUrl);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void nativePopupExit(char *strText)
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "nativePopupExit", "([B)V")) {
        
        jbyteArray arg1;
        
        
        arg1 = t.env->NewByteArray(strlen(strText));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strText), (jbyte*)strText);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1);
        
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IosUtil::getInstance()->nativePopupExit(strText);
#endif
}

void sendPush(int num, int sec,const char *strText,const char *strSound)
{
    
    if(xSave.isPushOnOff[num] == false)
        return;
    
    
    if(xWorldMap.pushTime[num] == sec)
        return;
    else
    {
        xWorldMap.pushTime[num] = sec;
    }
    
    
    
    int hour = sec/60/60;
    int minute = sec/60%60;
    int hourSum = hour+xCalendar.nowHour;
    int minuteSum = minute+xCalendar.nowMinute;
    
    hourSum+=minuteSum/60;
    int hour24 = hourSum%24;
    
    //printf("hour24>>%d\n",hour24);
    if(hour24 >= 21 || hour24 <= 7)
    {
        canclePush(num);
            return;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "nativeSendPush", "(II[B[B)V")) {
        
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strText));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strText), (jbyte*)strText);
        
        jbyteArray arg2;
        arg2 = t.env->NewByteArray(strlen(strSound));
        t.env->SetByteArrayRegion(arg2, 0, strlen(strSound), (jbyte*)strSound);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,num, sec, arg1, arg2);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void canclePush(int num)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "nativeCanclePush", "(I)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, num);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}



void googleInApp(char *strProductId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "googleInApp", "([B)V"))
    {
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strProductId));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strProductId), (jbyte*)strProductId);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,arg1);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}









void oneStoreInApp(char *strProductId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "oneStoreInApp", "([B)V"))
    {
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strProductId));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strProductId), (jbyte*)strProductId);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,arg1);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void unZip(const char *strFileName)
{
    unzFile zipfile;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string strFilePath = FileUtils::getInstance()->getWritablePath().append(strFileName);
    zipfile = unzOpen(strFilePath.c_str());
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char strFileNameSub[256];
    sprintf(strFileNameSub, "%s%s",xGame.strAndDataPack,strFileName);
    
    zipfile = unzOpen(strFileNameSub);
#endif
    
    
    if (! zipfile)
    {
        CCLOG("can not open downloaded zip file %s", strFileName);
        return;
    }
    
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("can not read file global info of %s", strFileName);
        unzClose(zipfile);
        return;
    }
    
    // Buffer to hold data read from the zip file
    CCLOG("start uncompressing");
    
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[64];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  64,
                                  nullptr,
                                  0,
                                  nullptr,
                                  0) != UNZ_OK)
        {
            CCLOG("can not read file info");
            unzClose(zipfile);
            return;
        }
        
        // Open current file.
        if (unzOpenCurrentFile(zipfile) != UNZ_OK)
        {
            CCLOG("can not open file %s", fileName);
            unzClose(zipfile);
            return;
        }
        
        // Write current file content to destinate file.
        int error = UNZ_OK;
        do
        {
            error = unzReadCurrentFile(zipfile, bufData, 15240000);
            if (error < 0)
            {
                CCLOG("can not read zip file %s, error code is %d", fileName, error);
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return;
            }
            
            if (error > 0)
            {
                writeNativeFileData(fileName, bufData, error);
            }
        } while(error > 0);
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("can not read next file");
                unzClose(zipfile);
                return;
            }
        }
    }
    
    CCLOG("end uncompressing");
    unzClose(zipfile);
}

void openGallery(char *buf, int userNum)
{
    openGalleryBuf = buf;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    printf("openGallery\n");
    IosUtil::getInstance()->openIosGallery();
    
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "openAndroidGallery", "(I)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, userNum);
        
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void googleSignIn()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "signIn", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void googleSignOut()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "signOut", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}



//0:off 1:on
void nativeOnOffPush(int state)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "nativeOnOffPush", "(I)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, state);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}




void nativeExitYesNo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "nativeExitYesNo", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void getDeviceInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "getDeviceId", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}



void naverPlug(int type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "naverPlug", "(I)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, type);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void naverGameUserId(char *strId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "naverGameUserId", "([B)V"))
    {
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strId));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strId), (jbyte*)strId);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,arg1);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


void checkBluetoothPermission()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "checkBluetoothPermission", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif

}
void startBluetoothPermission()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "startBluetoothPermission", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}




#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_nativeInit(JNIEnv* env, jobject thisObj, jstring jDataPack, jstring jSDCard,jstring jVerName)
    {
        const char *strDataPack = env->GetStringUTFChars(jDataPack,0);
        const char *strSDCard = env->GetStringUTFChars(jSDCard,0);
        const char *strVerName = env->GetStringUTFChars(jVerName,0);
        
        sprintf(xGame.strAndDataPack, "%s", strDataPack);
        sprintf(xGame.strAndSDCard, "%s", strSDCard);
        sprintf(xGame.strVerName, "%s", strVerName);
        
        env->ReleaseStringUTFChars(jDataPack, strDataPack);
        env->ReleaseStringUTFChars(jSDCard, strSDCard);
        env->ReleaseStringUTFChars(jVerName, strVerName);
        
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_openAndroidGalleryRecv(JNIEnv* env, jobject thisObj, jint jType, jbyteArray jbufArray, jint jbufSize)
    {
        if(jType == 0)
        {
            xWorldMap.state = WORLDMAP_STATE_PROFILE;           
        }
        else if(jType == 1)
        {
            if(xNetData.userNum > 0)
            {
                jbyte *jbuf = env->GetByteArrayElements(jbufArray, 0);
                for(int i = 0; i < jbufSize; i++)
                {
                    bufData[i] = (char)jbuf[i];
                }
                bufDataSize = jbufSize;
                
                env->ReleaseByteArrayElements(jbufArray, jbuf, 0);
                
                xEventQueueNet.imgBufSize[0] = bufDataSize;
                
                for(int i = 0; i < bufDataSize; i++)
                    xEventQueueNet.imgBuf[i] = bufData[i];
                
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PROFILEPHOTOUPLOAD, FALSE);
            }
            
        }
        else if(jType == 2)
        {
            
            xWorldMap.state = WORLDMAP_STATE_PROFILE;            
            setPopup(POPUP_USERTEXT, playState, playState, 0,DONT);
            sprintf(xPopup.strText, "사진을 불러올수 없습니다.\n(클라우드,임시폴더)");
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_nativeSystemKeyUp(JNIEnv* env, jobject thisObj, jint jKeyCode)
    {
        switch(jKeyCode)
        {
        case 1://백버튼 터치 업
            if(xTextField.state == TEXTFIELD_STATE_PLAY)
            {
                xTextField.textfield->isOpen = false;
            }
            else
            {
                JniMethodInfo t;
                if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "openExitPopUp", "()V")) {
                    
                    t.env->CallStaticVoidMethod(t.classID, t.methodID);
                    t.env->DeleteLocalRef(t.classID);
                }
            }
            break;
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_nativeDeviceInfo(JNIEnv* env, jobject thisObj,jstring jDeviceID)
    {
        const char *strDeviceID = env->GetStringUTFChars(jDeviceID,0);
        sprintf(xGame.strDeviceID, "%s", strDeviceID);
        env->ReleaseStringUTFChars(jDeviceID, strDeviceID);
    }
    
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxTextInputWraper_nativeIsFullScreenEdit(JNIEnv* env, jobject thisObj, jboolean isFullScreenEdit)
    {
        xTextField.textfield->isFullScreenEdit = isFullScreenEdit;
        /*
         if(isFullScreenEdit == true)
         LOGD("isFullScreenEdit = TRUE");
         else
         LOGD("isFullScreenEdit = FALSE");
         */
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_gameResume(JNIEnv* env, jobject thisObj)
    {
        resumeApp();
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_recvPurchase(JNIEnv* env, jobject thisObj,jint state,jstring jStrValue0, jstring jStrValue1)
    {
        const char *strValue0 = env->GetStringUTFChars(jStrValue0,0);
        const char *strValue1 = env->GetStringUTFChars(jStrValue1,0);
        
        //성공
        if(state == 1)
        {
            sprintf(xBill.strReceipt, "%s",strValue0);
            sprintf(xBill.strSignature, "%s",strValue1);
            
            
            if(xPackagePopup.isPlay == true)
            {
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PACKAGEBUY, TRUE);

            }
            else
            {
                switch(xWorldMap.state)
                {
                    case WORLDMAP_STATE_PREPAY:
                        ////////////////////////////////////////////////////////////
                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PREPAYBUY, TRUE);
                        ////////////////////////////////////////////////////////////
                        break;
                    default:
                        ////////////////////////////////////////////////////////////
                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BILL, TRUE);
                        ////////////////////////////////////////////////////////////
                        break;
                }
            }
        }
        //실패
        else
        {
            
            xBill.isBilling = FALSE;
            xWorldMap.isKeyReturn = FALSE;
            xnet.iapState = IAP_STATE_DONT;
            //응답값에 따른 실패처리
            /*
            setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
            sprintf(xPopup.strText, "영수증 검증 실패");
            
            sprintf(strTempRocks, "%d원게임서버실패",xShop.moneyPrice[xShop.selectSlot].oriData);
            sprintf(xRocks.strTemp, "%s",xSaveTemp.strNickName);
            setFiveRocksCustom("인앱",strTempRocks,xRocks.strTemp,"NULL",1);
            
            sprintf(xRocks.strTemp, "%d원",xShop.moneyPrice[xShop.selectSlot].oriData);
            setFiveRocksCustom("인앱","게임서버실패",xRocks.strTemp,"NULL",1);
            */
            
            
            
            
            /*
            xShop.stateP = SHOP_STATE_PLAY;
            setPopup(POPUP_USERTEXT, playState, playState, DONT);
            sprintf(xPopup.strText, "%s",strValue0);
             */
        }
        env->ReleaseStringUTFChars(jStrValue0, strValue0);
        env->ReleaseStringUTFChars(jStrValue1, strValue1);
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_recvGoogleSignIn(JNIEnv* env, jobject thisObj,jint state,jstring jStrValue0, jstring jStrValue1)
    {
        const char *strValue0 = env->GetStringUTFChars(jStrValue0,0);
        const char *strValue1 = env->GetStringUTFChars(jStrValue1,0);
		
		log("KBY_Send GoogleSignInRecv(state:%d)>>>%s\n",state,strValue0);
        
        //실패
        if(state == 0)
        {
            xIdMake.state = IDMAKE_STATE_LOGINKAKAO;
        }
        //성공
        else if(state == 1)
        {
            
            
            
            sprintf(xKakaoData.xUserInfo.strUserId, "%s",strValue0);
            netSend(CMD_LOGIN,DONT);

            /*
            sprintf(xPlayer.strPhotoUrl, "%s","-1");
            sprintf(xPlayer.strNickName, "%s",strValue1);
            netSend(CMD_IDMAKE);
             */
        }
        env->ReleaseStringUTFChars(jStrValue0, strValue0);
        env->ReleaseStringUTFChars(jStrValue1, strValue1);
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_setGameStop(JNIEnv* env, jobject thisObj)
    {
        nativePopupExit("권한설정후 이용가능합니다.");
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_urlFileDownLoadRecv(JNIEnv* env, jobject thisObj, jint jType, jint jTotalSize, jint jDownSize)
    {
        switch (jType)
        {
        case 0://다운중
            break;
        case 1://다운완료
            xDownLoader.state = DOWNLOADER_STATE_SUCCESS;
            break;
        case 2://다운실패
            xDownLoader.state = DOWNLOADER_STATE_ERR;
            break;
        default:
            break;
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_checkBluetoothPermissionRecv(JNIEnv* env, jobject thisObj, jint jState)
    {
        switch (jState)
        {
        case 0://인증미완료상태
            xMainMenu.state = MAINMENU_STATE_PERMISSIONCHECK;
            break;
        case 1://인증완료상태
            startVerCheck();
            break;
        }
    }
}
#endif

