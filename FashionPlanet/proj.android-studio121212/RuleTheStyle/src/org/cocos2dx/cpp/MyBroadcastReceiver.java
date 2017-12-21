package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

//푸쉬알람
public class MyBroadcastReceiver extends BroadcastReceiver {

 @Override
 public final void onReceive(Context context, Intent intent) {
     
     String name = intent.getAction();
     
     if(name.equals(AppActivity.pack+".RECEIVE")){
    	 
    	 String title = intent.getStringExtra("TITLE");
    	 String msg = intent.getStringExtra("MSG");

    	 
    	 MyIntentService.runIntentInService(context, intent);
    	 setResult(Activity.RESULT_OK, null, null);






     }
      
 }
}