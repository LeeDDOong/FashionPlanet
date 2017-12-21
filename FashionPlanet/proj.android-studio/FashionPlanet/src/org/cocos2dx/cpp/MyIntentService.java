package org.cocos2dx.cpp;

import android.app.AlertDialog;
import android.app.IntentService;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.media.RingtoneManager;
import android.os.PowerManager;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import com.bluefi.rulethestyle.google.R;


public class MyIntentService extends IntentService {

    private static PowerManager.WakeLock sWakeLock;
    private static final Object LOCK = MyIntentService.class;
    static Context mContext;
	public AlertDialog.Builder modifyDlg;

	public static String strTitle, strText;

    public MyIntentService()
    {
    	super("MyIntentService");
    }

    static void runIntentInService(Context context, Intent intent) {
    	mContext = context;
        synchronized(LOCK) {
            if (sWakeLock == null) {
                PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
                sWakeLock = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "my_wakelock");
            }
        }
        sWakeLock.acquire();
        intent.setClassName(context, MyIntentService.class.getName());
        context.startService(intent);
    }

    @Override
    public final void onHandleIntent(Intent intent) {
        try {
            String action = intent.getAction();
            if (action.equals("com.google.android.c2dm.intent.REGISTRATION")) {
                handleRegistration(intent);
            } else if (action.equals(AppActivity.pack+".RECEIVE")) {
                handleMessage(intent);
            }
        } finally {
            synchronized(LOCK) {
                sWakeLock.release();
            }
        }
    }

    private void handleRegistration(Intent intent) {
    	AppActivity.strPushId = intent.getStringExtra("registration_id");


        String error = intent.getStringExtra("error");
        String unregistered = intent.getStringExtra("unregistered");

        if (AppActivity.strPushId != null)
        {
        	if(!AppActivity.isSend)
        	{
//        		FashionTown.SendAfreecaGCM();
        		AppActivity.isSend = true;
        	}
        }

        // unregistration succeeded
        if (unregistered != null) {
            // get old registration ID from shared preferences
            // notify 3rd-party server about the unregistered ID
        }

        // last operation (registration or unregistration) returned an error;
        if (error != null) {
            if ("SERVICE_NOT_AVAILABLE".equals(error)) {
               // optionally retry using exponential back-off
               // (see Advanced Topics)
            } else {
                // Unrecoverable error, log it
                Log.i("aaaaa", "Received error: " + error);
            }
        }
    }

    private void handleMessage(Intent intent) {

    	String msg = intent.getStringExtra("MSG");
    	String sound = intent.getStringExtra("SOUND");

    	if(!AppActivity.isPlay)
    	{
	    	GET_GCM("(광고)아이러브패션",msg,sound);

//	    	Intent intent2 = new Intent(mContext, ShowPushActivity.class).setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//	    	mContext.startActivity(intent2);
    	}
    	else
    	{
    		if(AppActivity.isPlaySub)
    			GET_GCM("(광고)아이러브패션",msg,sound);
    	}
    }

    public void GET_GCM(String strTitle,String strText,String strSound) {

    	MyIntentService.strTitle = strTitle;
    	MyIntentService.strText = strText+"(수신거부:설정에서 변경 가능)";

    	//로컬
    	//notification.sound = Uri.parse("android.resource://" + getPackageName() + "/" + this.getApplicationContext().getResources().getIdentifier(strSound, AppActivity.path, AppActivity.pack));
    	//SD카드
    	//notification.sound = Uri.parse(FashionTown.myDir+"fashiontown/"+"push.ogg");

    	NotificationCompat.Builder mBuilder = new NotificationCompat.Builder(this)
    	.setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.ic_large))
        .setSmallIcon(R.drawable.ic_small)
        .setContentTitle("(광고)아이러브패션")
        .setAutoCancel(true)
		.setSound(RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION))
        .setOngoing(false);


		//Intent mIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.naver.com"));
    	Intent mIntent = new Intent(getApplicationContext(), AppActivity.class);
    	mIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_SINGLE_TOP | Intent.FLAG_ACTIVITY_CLEAR_TOP);
    	PendingIntent pendingIntent = PendingIntent.getActivity(getApplicationContext(), 0, mIntent, PendingIntent.FLAG_UPDATE_CURRENT);

    	mBuilder.setContentIntent(pendingIntent);
    	mBuilder.setContentText(MyIntentService.strText);
    	mBuilder.setContentTitle(MyIntentService.strTitle);

    	NotificationManager mNM = (NotificationManager)getSystemService(NOTIFICATION_SERVICE);
    	mNM.notify(999, mBuilder.build());



	}

    public void setPopupPush()
    {
    	modifyDlg = new AlertDialog.Builder(this);
    	modifyDlg.setTitle(strTitle);
    	modifyDlg.setIcon(R.drawable.icon);
    	modifyDlg.setMessage(strText);

    	modifyDlg.setPositiveButton("확인",new android.content.DialogInterface.OnClickListener()
    	{
    		@Override
			public void onClick(DialogInterface dialog, int which)
    		{

    		}
    	});

    	modifyDlg.setNeutralButton("닫기",new android.content.DialogInterface.OnClickListener()
		{
			@Override
			public void onClick(DialogInterface dialog, int which)
			{
				System.exit(0);
			}
		});

    	modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {

    		@Override
    		public void onCancel(DialogInterface dialog) {

    			// TODO Auto-generated method stub
    		}
    	});

    	modifyDlg.setCancelable(true);
    	modifyDlg.show();
    }
}
