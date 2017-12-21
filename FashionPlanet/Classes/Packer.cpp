#include "Global.h"



XPACKER xPacker[PACKERMAX];


void setPacker(int packerNum)
{
    
    
	sprintf(strTempS, "packimg%d.png",packerNum);
	loadImg(strTempS, &xPacker[packerNum].img);
	//JSON분석해서 임시 변수에 값넣어주기
	sprintf(strTempS, "packdata%d.dat",packerNum);
	loadData(strTempS, FALSE);
				
    
    
    
    Json::Value root;
    Json::Reader reader;
    bool bIsParsed = reader.parse(bufData, root);
    
    if (!bIsParsed)
    {
        log("parser failed : \n %s", bufData);
    }
    else
    {
        const Json::Value array = root["frames"];
        for (unsigned int i = 0; i < array.size(); ++i)
        {
            xPacker[packerNum].x[i] = array[i]["frame"]["x"].asInt();
            xPacker[packerNum].y[i] = array[i]["frame"]["y"].asInt();
            xPacker[packerNum].w[i] = array[i]["frame"]["w"].asInt();
            xPacker[packerNum].h[i] = array[i]["frame"]["h"].asInt();
        }
    }
}



void drawPacker(int packerCode,int x,int y,int rx,int ry,int rw,int rh,int ank)
{
	int type = packerCode/1000;
	int listNum = packerCode%1000;
	drawImage(&xPacker[type].img,x,y,rx+xPacker[type].x[listNum],ry+xPacker[type].y[listNum],rw,rh,ank);
}