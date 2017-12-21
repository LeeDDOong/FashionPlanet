
#ifndef _IOS_UTIL_H_
#define _IOS_UTIL_H_




namespace CocosIosUtil {
	
	/**
	 @class          SimpleAudioEngine
	 @brief          Offers a VERY simple interface to play background music & sound effects.
	 @note           Make sure to call SimpleAudioEngine::end() when the sound engine is not needed anymore
	 to release allocated resources.
	 */
	
	class IosUtil
	{
	public:
		static IosUtil* getInstance();
	protected:
		IosUtil();
		virtual ~IosUtil();
        
	public:
		virtual void openIosGallery();
		virtual void startDownLoad(const char *strFileName, const char *strURL);
        virtual void nativePopup(char *strText);        
        virtual void nativePopupExit(char *strText);
        
        

        

        
        
	};
} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_
