#include "Global.h"

XMEDIA xmedia;
M_Int32 isGetVol;


void checkSound(void)
{
    xmedia.checkFlowTime += xGame.prcSec;
    
    if(xmedia.checkFlowTime == 0)
    {
        return;
    }
    xmedia.checkFlowTime = 0;
    
	xmedia.isLoop = FALSE;
	switch(nowState)
	{
	case GAME_WORLDMAP:
		if(xQuestInfo.totalNum > 0
		   && xQuestInfo.xSlot[0].type == QUEST_TYPE_MAIN
		   && xQuestDataMain[xQuestInfo.xSlot[0].questNum].checkType[0] == 71)
		{
            playSnd(SND_SCENARIO_BG);
		}
        else if(xWorldMap.state == WORLDMAP_STATE_CLUBLOBBY || xWorldMap.state == WORLDMAP_STATE_PANG)
        {
            playSnd(SND_CLUB);
        }
		else if(xWorldMap.state == WORLDMAP_STATE_FASHIONSHOWNEW)
		{
            
            
			if(xFashionShow.state == FASHIONSHOW_STATE_RUNWAY)
				playSnd(SND_FASHIONSHOWGAME_BG);
			else
				playSnd(SND_FASHIONSHOWMENU_BG);
							
		}
		else
		{
			if(xFriendMap.isPlay == FALSE)
            {
				playSnd(xSongSet.songSlot[xSongSet.selectSong]);
                
            }
		}
		break;
	}
}

void playSnd(M_Int32 track)
{
	if(xSave.effVol > 100)
		xSave.effVol = 100;
	if(xSave.bgmVol > 100)
		xSave.bgmVol = 100;
	
    char strFileName[128];
    xmedia.nTrack = track;
    
    if(track < BGM_TRACK)
    {
        
        if(track == xmedia.bgTrack && SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false)
        {
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(xSave.bgmVol*0.01);

            SimpleAudioEngine::getInstance()->playBackgroundMusic(xmedia.strBgmName,false);
        }
        else if(track != xmedia.bgTrack)
        {
            xmedia.bgTrack = xmedia.nTrack;
            if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == true)
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            
            sprintf(strFileName, "snd_%d.ch3", track);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            std::string strFilePath = FileUtils::getInstance()->getWritablePath().append(strFileName);
            sprintf(xmedia.strBgmName, "%s",strFilePath.c_str());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sprintf(xmedia.strBgmName, "/%s%s",xGame.strAndDataPack,strFileName);
#endif
            
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(xSave.bgmVol*0.01);
            SimpleAudioEngine::getInstance()->playBackgroundMusic(xmedia.strBgmName,false);
        }
    }
    else
    {
        
        xmedia.effTrack = xmedia.nTrack;
        sprintf(xmedia.strEffName, "snd_%d.wav", track);
                
        if(xSave.effVol != xSave.tempVol)
        {
            xSave.tempVol = xSave.effVol;
            SimpleAudioEngine::getInstance()->setEffectsVolume(xSave.effVol*0.01);
        }
        SimpleAudioEngine::getInstance()->playEffect(xmedia.strEffName);

    }
}



void stopSnd()
{
    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == true)
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}
