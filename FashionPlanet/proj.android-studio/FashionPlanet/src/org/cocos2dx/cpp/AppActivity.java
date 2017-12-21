/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;


import android.app.Activity;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.media.AudioManager;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.os.StrictMode;
import android.os.SystemClock;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.android.vending.billing.IInAppBillingService;
import com.bluefi.rulethestyle.google.R;
import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.FirebaseApp;
import com.google.firebase.auth.AuthCredential;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.GoogleAuthProvider;
import com.naver.glink.android.sdk.Glink;
import com.skplanet.dodo.IapPlugin;
import com.skplanet.dodo.helper.PaymentParams;
import com.skplanet.dodo.pdu.Response;
import com.tapjoy.TJConnectListener;
import com.tapjoy.Tapjoy;
import com.tapjoy.TapjoyConnectFlag;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONObject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Hashtable;


////////////////////////////////////////////////////////////
//LJW 애드브릭스 페이스북
////////////////////////////////////////////////////////////


public class AppActivity extends Cocos2dxActivity implements
		GoogleApiClient.OnConnectionFailedListener
{
	/////////////////////////////////////
	@Override
	protected void onResume() {


		isPlay = true;
		isPlaySub = false;
		gameResume();


		super.onResume();
	}

	@Override
	protected void onPause() {


		isPlay = false;
		isPlaySub = true;
		super.onPause();
	}
	/////////////////////////////////////
	public static AppActivity mInstance;
	public static int iSDownLoader = 0;
	public static int donwTotalSize = 0;
	public static int downSize = 0;

	public static int originalVolume = -1;

	///////////////////////////////////////////
	public int iUserNum;
	public static final int ALBUM_PICK_REQUEST = 7103;
	public static final int CAMERA_PIC_REQUEST = 2433;		
	public static Handler mHandler;
	public static Handler mHandler22;

	public static boolean isGameStop = false;



	Boolean isProfilePhotoLoadErr = false;
	Uri mImageCaptureUri;
	public static final String myDir = Environment.getExternalStorageDirectory().getAbsolutePath() + "/";

	public String versionName;
	public String DeviceId;


	public static AlertDialog.Builder modifyDlg;
	//패키지명 변경은 이거와,manifest변경만 하면 됩니다.
	public static String pack = "com.bluefi.rulethestyle.google";
	public static String path = "raw";
	public static boolean isSend = false;
	public static String strPushId = null;
	public final static String SENDER_ID = "31711554401";
	public static boolean isPlay = false;
	public static boolean isPlaySub = false;
	int totalPendingIntent;
	private PendingIntent pendingArr[] = new PendingIntent[32];
	private boolean isPending[] = new boolean[32];
	private int iPending[] = new int[32];
	/////////////////////////////////////////////////////////////////



	//////////////원스토어 변수///////
	public static String ONESTOREAPPID = "OA00715905";
	// IapPlugin 레퍼런스 선언
	private IapPlugin mPlugin;
	// 요청결과(쿼리/결제)를 받을 클래스 선언과 생성
	private IapPlugin.AbsRequestCallback mAbsRequestCallback = new IapPlugin.AbsRequestCallback() {
		@Override
		protected void onResponse(Response response)
		{


			final String successCode = "0000"; // 조회 성공코드
			if (successCode.equals(response.result.code))
			{
				recvPurchase(1,response.result.txid,response.result.receipt);
			}
			else
				recvPurchase(0, "DONT", "DONT");
		}

		@Override
		public void onError(String reqid, String errcode, String errmsg) {
			// 에러
			recvPurchase(0, "DONT", "DONT");
		}
	};
	//////////////원스토어 변수///////


	//////////////인앱
	IInAppBillingService mService;
	ServiceConnection mServiceConn = new ServiceConnection() {
		@Override
		public void onServiceDisconnected(ComponentName name) {
			mService = null;
		}

		@Override
		public void onServiceConnected(ComponentName name,
									   IBinder service) {
			mService = IInAppBillingService.Stub.asInterface(service);
		}
	};
	//////////////인앱


	////구글로그인
	private static final int RC_SIGN_IN = 9001;
	private GoogleApiClient mGoogleApiClient;
	private FirebaseAuth mAuth;
	private FirebaseAuth.AuthStateListener mAuthListener;
	////구글로그인








	public static void kakaoToastLog(String strText)
	{

		try {
			final String strToast = strText;

			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(mInstance.getApplicationContext(), strToast, Toast.LENGTH_SHORT).show();
				}
			}, 100);

		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

	}

	public static void naviteToastLog(byte[] bText)
	{
		try {
			final String strToast = new String (bText ,"UTF-8");

			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(mInstance.getApplicationContext(), strToast, Toast.LENGTH_SHORT).show();
				}
			}, 100);

		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	public static void naviteSystemOutLog(byte[] bText)
	{
		try {
			final String strToast = new String (bText ,"UTF-8");

			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					System.out.println("C>>>" + strToast);
				}
			}, 100);

		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	////구글로그인

	@Override
	public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
		// An unresolvable error has occurred and Google APIs (including Sign-In) will not
		// be available.
		Log.d("googleLogin", "onConnectionFailed:" + connectionResult);
		Toast.makeText(this, "Google Play Services error.", Toast.LENGTH_SHORT).show();

	}

	private void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
		Log.d("googleLogin", "firebaseAuthWithGoogle:" + acct.getId());
		Log.d("googleLogin", "firebaseAuthWithGoogle:" + acct.getDisplayName());

		final String strId = acct.getId();
		final String strNickName = acct.getDisplayName();

		// [START_EXCLUDE silent]

		//showProgressDialog();
		// [END_EXCLUDE]

		AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
		mAuth.signInWithCredential(credential)
				.addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
					@Override
					public void onComplete(@NonNull Task<AuthResult> task) {
						recvGoogleSignIn(1,strId,strNickName);
						Log.d("googleLogin", "signInWithCredential:onComplete:" + task.isSuccessful());

						// If sign in fails, display a message to the user. If sign in succeeds
						// the auth state listener will be notified and logic to handle the
						// signed in user can be handled in the listener.
						if (!task.isSuccessful()) {
							recvGoogleSignIn(0,"NULL","NULL");
							Log.w("googleLogin", "signInWithCredential", task.getException());
							kakaoToastLog("Authentication failed.");
						}
						// [START_EXCLUDE]
						//hideProgressDialog();
						// [END_EXCLUDE]
					}
				});
	}
	public static void signIn()
	{
		Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mInstance.mGoogleApiClient);
		AppActivity.mInstance.startActivityForResult(signInIntent, RC_SIGN_IN);
	}
	private static void signOut() {
		// Firebase sign out
		mInstance.mAuth.signOut();

		// Google sign out
		Auth.GoogleSignInApi.signOut(mInstance.mGoogleApiClient).setResultCallback(
				new ResultCallback<Status>() {
					@Override
					public void onResult(@NonNull Status status) {

					}
				});
	}

	private void revokeAccess() {
		// Firebase sign out
		mAuth.signOut();

		// Google revoke access
		Auth.GoogleSignInApi.revokeAccess(mGoogleApiClient).setResultCallback(
				new ResultCallback<Status>() {
					@Override
					public void onResult(@NonNull Status status) {

					}
				});
	}
	////구글로그인





	public Cocos2dxGLSurfaceView onCreateView()
	{
		mInstance = this;
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this); 
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);		
		mHandler = new Handler();
							
		///////////////////////푸쉬 
		initPush();
		isPlay = true;
		///////////////////////

		////구글로그인
		FirebaseApp.initializeApp(this);
		GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
				.requestIdToken(getString(R.string.default_web_client_id))
				.requestId()
				.requestProfile()
				.requestEmail()
				.build();

		mGoogleApiClient = new GoogleApiClient.Builder(this)
				.enableAutoManage(this /* FragmentActivity */, this /* OnConnectionFailedListener */)
				.addApi(Auth.GOOGLE_SIGN_IN_API, gso)
				.build();


		mAuth = FirebaseAuth.getInstance();
		mAuthListener = new FirebaseAuth.AuthStateListener() {
			@Override
			public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth) {
				FirebaseUser user = firebaseAuth.getCurrentUser();
				if (user != null) {
					// User is signed in
					Log.d("googleLogin", "onAuthStateChanged:signed_in:" + user.getUid());
				} else {
					// User is signed out
					Log.d("googleLogin", "onAuthStateChanged:signed_out");
					//gl 1.로그인이 안돼엇을때
				}
			}
		};
		////구글로그인
		versionName = "DONT";

		try {
			PackageInfo pi = getPackageManager().getPackageInfo(getPackageName(), 0);
			versionName = pi.versionName;
			//getDeviceId: Neither user 10495 nor current process has android.permission.READ_PHONE_STATE.
		}
		catch (PackageManager.NameNotFoundException e)
		{
			Log.d("PackageManager", "NameNotFoundException e Errer");
		}

		nativeInit("data/data/" + AppActivity.pack + "/", myDir, versionName);


		///////////////////
		///////루팅탐
		/*
		DetectRoot dr = new DetectRoot(this);
		if (dr.isRooting())
		{		
		}
		*/

		/*
		DetectEmulator de = new DetectEmulator();
		if (de.isEmulator()){
		// 에뮬레이터 탐지 되었을때 코드 입력
		}
		*/
		///////////////////





		
		////////////탭조이///
		initTabjoy();
		///////////////////
		//getAppKeyHash();
		
		File file = new File(myDir+"FridayNight");
		if(!file.exists())
		{		
			try {			
				file.mkdir();
			} catch (Exception e) {			
				e.printStackTrace();
			}
		}

		
		if(android.os.Build.VERSION.SDK_INT > 9) {			
		    StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
		        StrictMode.setThreadPolicy(policy);	        
		}





		//////////////원스토어 변수///////



		// 요청을 위한 객체 생성 및 레퍼런스 저장
		//mPlugin = IapPlugin.getPlugin(mInstance, IapPlugin.DEVELOPMENT_MODE);
		mPlugin = IapPlugin.getPlugin(mInstance, IapPlugin.RELEASE_MODE);
		//////////////원스토어 변수///////




		/////인앱///
		Intent serviceIntent =
				new Intent("com.android.vending.billing.InAppBillingService.BIND");
		serviceIntent.setPackage("com.android.vending");
		boolean isInAppBind = bindService(serviceIntent, mServiceConn, Context.BIND_AUTO_CREATE);
		/////인앱///



		//네이버플러그(초기화)
		final int cafeId = 29022670;
		final String clientId = "D0GEZ3yMPdAQ7Bf_ry2E";
		final String clientSecret = "kLwXCLGlvo";
		Glink.init(this, clientId, clientSecret, cafeId);

		//네이버플러그(초기화)

		/*
		//네이버플러그(스크린샷)
		Glink.setOnWidgetScreenshotClickListener(new Glink.OnWidgetScreenshotClickListener() {
			@Override public void onScreenshotClick() {
				//TODO 화면 캡처 및 네이버 카페 PLUG 실행(아래는 sudo 코드)
				String uri = screenshot();
				Glink.startImageWrite(mInstance, uri);
			}
		});
		//네이버플러그

		//네이버플러그(동영상)
		Glink.setOnRecordFinishListener(new Glink.OnRecordFinishListener() {
			@Override public void onRecordFinished(String uri) {
				Glink.startVideoWrite(mInstance, uri);
			}
		});
		//네이버플러그(동영상)
		*/



		//테스트용 꼭 지워주
		/*
		StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
	.detectDiskReads() .detectDiskWrites() .detectNetwork() .penaltyLog() .build());
		StrictMode.enableDefaults();
		*/
		//테스트용 꼭 지워주			
		return glSurfaceView;
	}



	//네이버플러그(스크린샷)
	public String screenshot() {
		View view =
				mInstance.getWindow().getDecorView().findViewById(android.R.id.content).getRootView();

		view.setDrawingCacheEnabled(true);
		view.buildDrawingCache(true);

		Bitmap screenshot = view.getDrawingCache(true);

		String filename = "screenshot" + System.currentTimeMillis() + ".png";
		String fileUri = null;
		try {
			File f = new File(mInstance.getFilesDir(), filename);

			f.createNewFile();
			fileUri = f.toURI().toString();

			OutputStream outStream = new FileOutputStream(f);
			screenshot.compress(Bitmap.CompressFormat.PNG, 100, outStream);
			outStream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		view.setDrawingCacheEnabled(false);
		return fileUri;
	}
	//네이버플러그(스크린샷)

	//네이버플러그(시작)
	public static void naverPlug(int type)
	{
		try
		{
			switch(type)
			{
			case 0:
				Glink.startNotice(mInstance);
				Glink.showWidgetWhenUnloadSdk(mInstance, false);
				break;
			}
		}
		catch (Exception e)
		{
		}
	}
	//네이버플러그(시작)


	//네이버플러그(게임아이디연동)
	public static void naverGameUserId(byte[] bId)
	{
		try {
			final String strId = new String(bId, "UTF-8");
			Glink.syncGameUserId(mInstance, strId);
			Glink.showWidgetWhenUnloadSdk(mInstance, false);
		}
		catch (Exception e)
		{

		}
	}
	//네이버플러그(게임아이디연동)



	public static void getDeviceId()
	{
		mInstance.DeviceId = "DONT";
		TelephonyManager tm = (TelephonyManager) mInstance.getSystemService(Context.TELEPHONY_SERVICE);
		mInstance.DeviceId = tm.getDeviceId();



		if(mInstance.DeviceId == null)
			mInstance.DeviceId = "NULL";

		nativeDeviceInfo(mInstance.DeviceId);
	}

	public static void openWebView(byte[] bUrl)
	{
		try
		{
			final String strURL = new String (bUrl ,"UTF-8");
			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					try {
						Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(strURL));
						mInstance.startActivity(intent);
					}
					catch (Exception e) {
					}
				}

			}, 100);
		}
		catch (Exception e)
		{
		}
	}

	public static void GET_GCMHEADUP(byte[] bUrl)
	{

		try
		{
			final String strURL = new String (bUrl ,"UTF-8");
			NotificationManager notificationManager = (NotificationManager) mInstance.getSystemService(Context.NOTIFICATION_SERVICE);
			Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(strURL));
			PendingIntent pendingIntent = PendingIntent.getActivity(mInstance, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
			Notification.Builder builder = new Notification.Builder(mInstance);
			builder.setLargeIcon(BitmapFactory.decodeResource(mInstance.getResources(), R.drawable.ic_large));
			builder.setSmallIcon(R.drawable.ic_small);
			builder.setTicker("제3자 정보 수집출처 고지");
			builder.setContentTitle("제3자 정보 수집출처 고지");
			builder.setContentText("클릭 시 내용 보기");
			builder.setWhen(System.currentTimeMillis());
			builder.setPriority(Notification.PRIORITY_MAX);
			builder.setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE);
			builder.setContentIntent(pendingIntent);
			builder.setAutoCancel(true);
			notificationManager.notify(0, builder.build());
		}
		catch (Exception e)
		{
		}
	}



	WakeLock mWakeLock;	
	public static void wakeLock(int isLock)
	{				
		final PowerManager powerMgr = (PowerManager)mInstance.getSystemService(Context.POWER_SERVICE);	
		mInstance.mWakeLock = powerMgr.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, mInstance.getClass().getName());
	
		if(isLock == 1)
		{
			// 슬립모드 설정
			if(mInstance.mWakeLock != null )
			{
				mInstance.mWakeLock.acquire();
				Log.d("maluchi", "SleepMode Locked");
			}
		}
		else
		{
			// 해제	
			if(mInstance.mWakeLock != null)
			{	
				if(mInstance.mWakeLock.isHeld())
				{	
					mInstance.mWakeLock.release();	
					Log.d("maluchi", "SleepMode Unlocked");
				}	
			}	
		}
	}

	public static void soundMute(int isMute,int isGameMute)
	{
		if(isMute == 1)
		{
			AudioManager am = (AudioManager) mInstance.getSystemService(Context.AUDIO_SERVICE);
			if (am.getRingerMode() != AudioManager.RINGER_MODE_NORMAL || isGameMute == 1)
			{
				// 무음이나 진동 모드 일 때
				originalVolume = am.getStreamVolume(AudioManager.STREAM_MUSIC); // 원본 볼륨 정보 저장
				am.setStreamVolume(AudioManager.STREAM_MUSIC, 0, AudioManager.FLAG_PLAY_SOUND); // 미디어 볼륨을 0으로 설정
			}
		}

		if(isMute == 0)
		{

			if (originalVolume != -1) {
				// 볼륨이 조절 된 경우
				AudioManager am = (AudioManager) mInstance.getSystemService(Context.AUDIO_SERVICE);
				am.setStreamVolume(AudioManager.STREAM_MUSIC, originalVolume, AudioManager.FLAG_PLAY_SOUND);
			}
		}
	}





	////////////////////////탭조이 
	private void initTabjoy() 
	{

		// OPTIONAL: For custom startup flags.
		Hashtable<String, Object> connectFlags = new Hashtable<String, Object>();
		connectFlags.put(TapjoyConnectFlag.ENABLE_LOGGING, "false");

		// If you are not using Tapjoy Managed currency, you would set your own user ID here.
		// connectFlags.put(TapjoyConnectFlag.USER_ID, "A_UNIQUE_USER_ID");
		// Connect with the Tapjoy server.  Call this when the application first starts.
		// REPLACE THE SDK KEY WITH YOUR TAPJOY SDK Key.
		String tapjoySDKKey = "j_-w3dYmQFG9pqTZJxUqcQECn1KTNO6YK7sMy9DOPrjRA8jfdw4SrTYsF56u";

		// NOTE: This is the only step required if you're an advertiser.
		Tapjoy.connect(getApplicationContext(), tapjoySDKKey, connectFlags, new TJConnectListener() {
			@Override
			public void onConnectSuccess() {
			}

			@Override
			public void onConnectFailure() {
			}
		});
		
		Tapjoy.setDebugEnabled(false);
		//APIKEY:AIzaSyC-H9obY8uPRSatsc87sI3mCoOr-yCHJbY
		Tapjoy.setGcmSender("970364304520");
	}
	@Override
	protected void onStart() {
	  super.onStart();

		mAuth.addAuthStateListener(mAuthListener);
	  Tapjoy.onActivityStart(this);
	}
	@Override
	protected void onStop() {
	  Tapjoy.onActivityStop(this);
	  super.onStop();

		if (mAuthListener != null) {
			mAuth.removeAuthStateListener(mAuthListener);
		}

	}



	





	public static void setTabjoyUserInfo(int lv,byte[] strId,byte[] strCohort1,byte[] strCohort2,byte[] strCohort3,byte[] strCohort4,byte[] strCohort5)
	{


		String strIdtTab = "IdErr";
		String strCohortTab1 = "Coshort1Err";
		String strCohortTab2 = "Coshort2Err";
		String strCohortTab3 = "Coshort3Err";
		String strCohortTab4 = "Coshort4Err";		
		String strCohortTab5 = "Coshort5Err";
		
		try {
			strIdtTab = new String (strId ,"UTF-8");			
			strCohortTab1 = new String (strCohort1 ,"UTF-8");
			strCohortTab2 = new String (strCohort2 ,"UTF-8");
			strCohortTab3 = new String (strCohort3 ,"UTF-8");
			strCohortTab4 = new String (strCohort4 ,"UTF-8");
			strCohortTab5 = new String (strCohort5 ,"UTF-8");

		} catch (UnsupportedEncodingException e1)
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
				
		Tapjoy.setUserLevel(lv);
		Tapjoy.setUserID(strIdtTab);
		Tapjoy.setUserCohortVariable(1, strCohortTab1);
		Tapjoy.setUserCohortVariable(2, strCohortTab2);
		Tapjoy.setUserCohortVariable(3, strCohortTab3);
		Tapjoy.setUserCohortVariable(4, strCohortTab4);
		Tapjoy.setUserCohortVariable(5, strCohortTab5);
	}
		
	public static void setTabjoyPurchase(byte[] strName,int price)
	{

		String strNameTab = "NameErr";
		try {
			strNameTab = new String (strName ,"UTF-8");						
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		Tapjoy.trackPurchase(strNameTab, "KRW", price, null); //The last term is an integer that lets you specify a campaign ID should you choose to do so.

	}	
	
	public static void setTabjoyEventSM(byte[] strCategory,byte[] strName,byte[] strPar1,byte[] strPar2,int value)
	{

		String strCategoryTab = "0";
		String strNameTab = "0";
		String strPar1Tab = "0";
		String strPar2Tab = "0";
		String strValueTab = "0";
		try {
			strCategoryTab = new String (strCategory ,"UTF-8");
			strNameTab = new String (strName ,"UTF-8");
			strPar1Tab = new String (strPar1 ,"UTF-8");
			strPar2Tab = new String (strPar2 ,"UTF-8");						
			strValueTab = "값";
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		if(strPar1Tab.equals("NULL") == true)
		{
			
		}				
		Tapjoy.trackEvent(strCategoryTab, strNameTab, strPar1Tab, strPar2Tab, strValueTab, value);
	}



	////////////////원스토어//////
	public static void oneStoreInApp(byte[] productId)
	{
		String sku = "0";

		try {
			sku = new String (productId ,"UTF-8");

			// 결제를 위한 PaymentParams 객체 생성
			PaymentParams params = new PaymentParams.Builder(ONESTOREAPPID, sku).build();

			// 결제 요청
			mInstance.mPlugin.sendPaymentRequest(mInstance.mAbsRequestCallback, params);

		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
	////////////////원스토어//////



	///////////인앱
	public static void googleInApp(byte[] productId)
	{
		String sku = "0";
		try {
			for(int i=0;i<5;i++)
			{
				Bundle ownedItems = mInstance.mService.getPurchases(3, mInstance.getPackageName(), "inapp", null);

				int response = ownedItems.getInt("RESPONSE_CODE");
				if (response == 0) {
					ArrayList<String> ownedSkus =
							ownedItems.getStringArrayList("INAPP_PURCHASE_ITEM_LIST");
					ArrayList<String> purchaseDataList =
							ownedItems.getStringArrayList("INAPP_PURCHASE_DATA_LIST");
					ArrayList<String> signatureList =
							ownedItems.getStringArrayList("INAPP_DATA_SIGNATURE_LIST");
					String continuationToken =
							ownedItems.getString("INAPP_CONTINUATION_TOKEN");


					for (int k = 0; k < purchaseDataList.size(); k++)
					{
						String purchaseData = purchaseDataList.get(i);


						try {
							JSONObject jo = new JSONObject(purchaseData);
							String purchaseToken = jo.getString("purchaseToken");
							int result = mInstance.mService.consumePurchase(3, mInstance.getPackageName(), purchaseToken);
						}
						catch (Exception e) {
							//kakaoToastLog("Failed to parse purchase data.");
							e.printStackTrace();
						}
						//구매한 상품의 정보를 이용하여 무언가를 처리하면 됩니다.
						//e.g. 유저가 보유한 상품의 리스트를 업데이트
					}


					if (continuationToken != null) {

					}
					else {
						break;
					}
					// if continuationToken != null, call getPurchases again
					// and pass in the token to retrieve more items
				}
				else {
					break;
				}
			}
		}
		catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		try {
			sku = new String (productId ,"UTF-8");
			Bundle buyIntentBundle = mInstance.mService.getBuyIntent(3, mInstance.getPackageName(),
					sku, "inapp", "iloveclub");

			PendingIntent pendingIntent = buyIntentBundle.getParcelable("BUY_INTENT");
			mInstance.startIntentSenderForResult(pendingIntent.getIntentSender(),
					1001, new Intent(), Integer.valueOf(0), Integer.valueOf(0),
					Integer.valueOf(0));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
	///////////인앱
	
	public static void reStart()
	{			
		PendingIntent i = PendingIntent.getActivity(mInstance.getApplicationContext(), 0, new Intent(mInstance.getIntent()), mInstance.getIntent().getFlags());
		AlarmManager am = (AlarmManager) mInstance.getSystemService(Context.ALARM_SERVICE);
		am.set(AlarmManager.RTC, System.currentTimeMillis() + 300, i);
		mInstance.moveTaskToBack(true); 
		mInstance.finish();
		android.os.Process.killProcess(android.os.Process.myPid());

	}
	
	public static void gameExit()
	{		
		mInstance.moveTaskToBack(true); 
		mInstance.finish();
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	
	public static void startWebView(byte[] strUrl)
	{					
		try {
			final String strUrlTT = new String (strUrl ,"UTF-8");
			
			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					try {							
						Uri uri = Uri.parse(strUrlTT);
						Intent intent = new Intent(Intent.ACTION_VIEW, uri);
						mInstance.startActivity(intent);
					} catch (Exception e) {
						//System.out.println("URLException = " + e);
					}
				}
			}, 100);
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}								
	}		
			
	@Override
	public void onDestroy() {						
		isPlay = false;
		isPlaySub = true;
		super.onDestroy();





		//인앱
		if (mService != null) {
			unbindService(mServiceConn);
		}
		//인앱
	}	
	/////////////////////////////////////////////



	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		
		String strUpUrl;
		byte[] fileBuf = null;

		////구글로그인
		if (requestCode == RC_SIGN_IN) {
			GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
			if (result.isSuccess()) {
				// Google Sign In was successful, authenticate with Firebase
				GoogleSignInAccount account = result.getSignInAccount();
				firebaseAuthWithGoogle(account);
			} else {
				// Google Sign In failed, update UI appropriately
				recvGoogleSignIn(0,"NULL","NULL");
			}
		}
		////구글로그인
		else if(requestCode == 1001)
		{
			int responseCode = data.getIntExtra("RESPONSE_CODE", 0);
			String purchaseData = data.getStringExtra("INAPP_PURCHASE_DATA");
			String dataSignature = data.getStringExtra("INAPP_DATA_SIGNATURE");

			if (resultCode == RESULT_OK)
			{
				//kakaoToastLog("INAPP-OK");
				try {
					JSONObject jo = new JSONObject(purchaseData);
					String sku = jo.getString("productId");
				}
				catch (Exception e) {
					//kakaoToastLog("Failed to parse purchase data.");
					e.printStackTrace();
				}
				recvPurchase(1,purchaseData,dataSignature);
			}
			else
			{
				//kakaoToastLog("INAPP-FAIL");
				if(resultCode==0)
					recvPurchase(0, "DONT", "DONT");
				else
					recvPurchase(2, "구매실패:" + resultCode, "DONT");
			}
		}
		else if(requestCode == ALBUM_PICK_REQUEST)
		{
			if(resultCode == Activity.RESULT_OK)
			{
				try {
					mImageCaptureUri = data.getData();
					File original_file = getImageFile(mImageCaptureUri);

					mImageCaptureUri = createSaveCropFile();
					File cpoy_file = new File(mImageCaptureUri.getPath());


					copyFile(original_file, cpoy_file);


					Intent intent = new Intent("com.android.camera.action.CROP");
					intent.setDataAndType(mImageCaptureUri, "image/*");

					///////////////////////////////
					intent.putExtra("aspectX", 1);
					intent.putExtra("aspectY", 1);
					///////////////////////////////


					intent.putExtra("output", mImageCaptureUri);


					//          intent.putExtra("return-data", true);
					startActivityForResult(intent, CAMERA_PIC_REQUEST);
				}
				catch (Exception ee)
				{
					mInstance.isProfilePhotoLoadErr = true;

					/*
					if()
					mInstance.isProfilePhotoLoadErr = true;
					*/
					openAndroidGalleryRecv(2, null, 0);

					//ee.printStackTrace();
				}
			}
			else if(resultCode == Activity.RESULT_CANCELED)
			{
				openAndroidGalleryRecv(-1, null, 0);
			}
			
		}
		else if(requestCode == CAMERA_PIC_REQUEST)		
		{			
			if(resultCode == Activity.RESULT_OK)
			{
				Uri imgUri = data.getData();
								
//				Cursor c = getContentResolver().query(Uri.parse(imgUri.toString()),	null, null, null, null);
//				c.moveToNext();
				
				String full_path = mImageCaptureUri.getPath();
	            String photo_path = full_path.substring(0, full_path.length());
	            String absolutePath = photo_path;
//				String absolutePath = c.getString(c.getColumnIndex(MediaStore.MediaColumns.DATA));				

				BitmapFactory.Options options = new BitmapFactory.Options(); 
				options.inSampleSize = 1;
				options.inDither = true;
				options.inScaled = true;
				options.inPreferredConfig = Bitmap.Config.ARGB_8888;//important//
				options.inPurgeable = true;			
				
				Bitmap image = BitmapFactory.decodeFile(absolutePath, options);
				Bitmap imageBmp = CreateScaledBitmap(image, 100, 100, false);



				String fileName = "data/data/"+AppActivity.pack+"/"+"profile.png";

				File file = new File(fileName);

			    FileOutputStream fos = null;
			    FileInputStream fis = null;
				try {
					fos = new FileOutputStream(file);

					imageBmp.compress(CompressFormat.PNG, 100, fos);

					fos.flush();
					fos.close();
					
					fis = new FileInputStream(file);
					
					fileBuf = new byte[fis.available()];
					fis.read(fileBuf);
					
					image.recycle();
					imageBmp.recycle();

					file.delete();
					
					openAndroidGalleryRecv(1, fileBuf, fileBuf.length);

				} catch (Exception e)
				{
					e.printStackTrace();
				}          
			}
			
			else if(resultCode == Activity.RESULT_CANCELED)
			{
				//System.out.println("Gallery Canceld");
				//openAndroidGalleryRecv(-1, null, 0);
				openAndroidGallery(iUserNum);
			}
		}
	}
	
	/**
     * Crop�� �̹����� ����� ������ �����.
     * @return Uri
     */
    private Uri createSaveCropFile(){
        Uri uri;
        String url = "scaleimage.jpg";
        uri = Uri.fromFile(new File(Environment.getExternalStorageDirectory(), url));
        return uri;
    }
    
    /**
     * ���õ� uri�� ���� Path�� �����´�.
     * uri �� null ��� �������� ����� ������ �����´�.
     * @param uri
     * @return
     */
    private File getImageFile(Uri uri) {
        String[] projection = { MediaStore.Images.Media.DATA };
        if (uri == null) {
            uri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
        }
 
        Cursor mCursor = getContentResolver().query(uri, projection, null, null, 
                MediaStore.Images.Media.DATE_MODIFIED + " desc");
        if(mCursor == null || mCursor.getCount() < 1) {
            return null; // no cursor or no record
        }
        int column_index = mCursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
        mCursor.moveToFirst();
 
        String path = mCursor.getString(column_index);
 
        if (mCursor !=null ) {
            mCursor.close();
            mCursor = null;
        }
 
        return new File(path);
    }
    
    /**
     * ���� ����
     * @param srcFile : ������ File
     * @param destFile : ����� File
     * @return
     */
    public static boolean copyFile(File srcFile, File destFile) {
        boolean result = false;
        try {
            InputStream in = new FileInputStream(srcFile);
            try {
                result = copyToFile(in, destFile);
            } finally  {
                in.close();
            }
        } catch (IOException e) {
            result = false;
        }
        return result;
    }
    
    /**
     * Copy data from a source stream to destFile.
     * Return true if succeed, return false if failed.
     */
    private static boolean copyToFile(InputStream inputStream, File destFile) {
        try {
            OutputStream out = new FileOutputStream(destFile);
            try {
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = inputStream.read(buffer)) >= 0) {
                    out.write(buffer, 0, bytesRead);
                }
            } finally {
                out.close();
            }
            return true;
        } catch (IOException e) {
            return false;
        }
    }
    
    public static Bitmap CreateScaledBitmap(Bitmap src, int dstWidth, int dstHeight, boolean filter)
	{
	    Matrix m = new Matrix();
	    m.setScale(dstWidth  / (float)src.getWidth(), dstHeight / (float)src.getHeight());
	    Bitmap result = Bitmap.createBitmap(dstWidth, dstHeight, src.getConfig());
	    Canvas canvas = new Canvas(result);

	        Paint paint = new Paint();
	        paint.setFilterBitmap(filter);
	        canvas.drawBitmap(src, m, paint);

	    return result;

	}
	
	public static void openAndroidGallery(int iUserNum)
	{
		iUserNum = iUserNum;
		
		mHandler.postDelayed(new Runnable() {
			@Override
			public void run() {
				try {
					Intent intent = new Intent();
					intent.setAction(Intent.ACTION_PICK);
					intent.setType("image/*");
					AppActivity.mInstance.startActivityForResult(intent, ALBUM_PICK_REQUEST);
				} catch (Exception e) {

				}
			}
		}, 100);
	}

	
	public static void urlFileDownLoad(byte[] path, byte[] url)
	{
		String strPathSub = null;
		String strUrlSub = null;
		try {
			strPathSub = new String (path ,"UTF-8");
			strUrlSub = new String (url ,"UTF-8");
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}



		final String strPath = strPathSub;
		final String strUrl = strUrlSub;


		AsyncTask.execute(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				// 스레드 작업
				urlFileDownLoadSub(strPath, strUrl);
			}
		});


		/*
		mInstance.mHandler.postDelayed(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.sleep(10);

				} catch (Exception e) {
					//System.out.println("SendMessage ExceptionThread = " + e);
				}
			}
		}, 100);
		*/
	}
		
	public static void urlFileDownLoadSub(String path, String url) 
	{				
		int TotalSize = 0;

		FileOutputStream fos = null;
		URL myFileUrl = null;

		try {			
			myFileUrl = new URL(url);
			
			HttpURLConnection conn = (HttpURLConnection) myFileUrl.openConnection();
			conn.setRequestMethod("GET");
			conn.setDoInput(true);		    
			conn.connect();
			
			TotalSize = conn.getContentLength();
			
			File file = new File("data/data/"+AppActivity.pack+"/"+path);
			if (file.exists())
				file.delete();
			file.createNewFile();			
			fos = new FileOutputStream(file);
			
			InputStream is = conn.getInputStream();
			
			
			byte byteArray[] = new byte[1024*1024];
			int readLength = 0;
			donwTotalSize = TotalSize;
			downSize = 0;
			iSDownLoader = 0;
			while ((readLength = is.read(byteArray, 0, byteArray.length)) != -1) {
				fos.write(byteArray, 0, readLength);
				downSize += readLength;
				iSDownLoader = 0;
				urlFileDownLoadRecv(iSDownLoader, donwTotalSize, downSize);
			}
			fos.flush();
			fos.close();			
			is.close();		
			conn.disconnect();
			
			iSDownLoader = 1;
			urlFileDownLoadRecv(iSDownLoader, donwTotalSize, downSize);
			
		} catch (Exception e) {
			iSDownLoader = 2;
			urlFileDownLoadRecv(iSDownLoader, donwTotalSize, downSize);
			System.out.println("WON urlFileDownLoad = " + e);
		}		
	}
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////






	public void initPush()
	{
		for(int i = 0; i < 32; i++)
		{
			isPending[i] = false;
			pendingArr[i] = null;
			iPending[i] = -1;
		}
	}
	
	public void sendPush(int num, int sec, String msg, String sound)
	{
		//푸쉬등록		
        long firstTime = SystemClock.elapsedRealtime();
        firstTime += sec*1000; // add 1 second				
		
		Intent intent = new Intent(this, MyBroadcastReceiver.class);
		intent.putExtra("TITLE", "아이러브패션");
		intent.putExtra("MSG", msg);
		intent.putExtra("SOUND", sound);
		intent.setAction(AppActivity.pack+".RECEIVE");
		
		
		
		AlarmManager alarm = (AlarmManager)getSystemService(ALARM_SERVICE);
		
		for(int i = 0; i < 32; i++)
		{			
			if(isPending[i])
			{
				if(iPending[i] == num)
				{
					alarm.cancel(pendingArr[i]);
					isPending[i] = false;
					pendingArr[i] = null;
					iPending[i] = -1;
					break;
				}
			}				
		}


		for(int i = 0; i < 32; i++)
		{
			if(!isPending[i])
			{
				pendingArr[i] = null;
				pendingArr[i] = PendingIntent.getBroadcast(this,
						num, intent, PendingIntent.FLAG_CANCEL_CURRENT);
				
				iPending[i] = num;
				isPending[i] = true;
				alarm.set(AlarmManager.ELAPSED_REALTIME_WAKEUP, firstTime, pendingArr[i]);
				break;
			}
		}
	}
	
	
	public void canclePush(int id)
	{
		//푸쉬해제
		AlarmManager alarm = (AlarmManager)getSystemService(ALARM_SERVICE);
				
		for(int i = 0; i < 32; i++)
		{
			if(isPending[i])
			{
				if(iPending[i] == id)
				{					
					alarm.cancel(pendingArr[i]);
					isPending[i] = false;
					pendingArr[i] = null;
					iPending[i] = -1;
					break;
				}
			}
		}
	}


	public static void nativeOnOffPush(int state)
	{
		//off
		if(state == 0)
		{
			Tapjoy.setPushNotificationDisabled(true);
		}
		//on
		else
		{
			Tapjoy.setPushNotificationDisabled(false);
		}
	}

	public static void nativeSendPush(int num, int sec, byte[] msg, byte[] sound)
    {
    	String strMsg = null;
    	String strSound = null;
		try {
			strMsg = new String(msg, "utf-8");
			strSound = new String(sound, "utf-8");
		} catch (UnsupportedEncodingException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	AppActivity.mInstance.sendPush(num, sec, strMsg, strSound);
    }
    
    public static void nativeCanclePush(int num)
    {
    	AppActivity.mInstance.canclePush(num);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    public static void nativePopupYesNo(byte[] bText)
	{
		try {
			final String strText = new String (bText ,"UTF-8");
			
			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {

					modifyDlg = new android.support.v7.app.AlertDialog.Builder(mInstance,R.style.AppCompatAlertDialogStyle);
					modifyDlg.setTitle(strText);
					modifyDlg.setPositiveButton("Yes", new android.content.DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog, int which) {
							nativePopupYesNoRecv(1);
						}
					});
					
					modifyDlg.setNeutralButton("No", new android.content.DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog, int which) {
							nativePopupYesNoRecv(0);
						}
					});
					
					modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {
						
						@Override
						public void onCancel(DialogInterface dialog) {
							
							nativePopupYesNoRecv(0);
						}
					});
				
					modifyDlg.setCancelable(true);
					modifyDlg.show();	
				}
			}, 100);
									
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}


	public static void nativeExitYesNo()
	{
		try {


			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {

					modifyDlg = new android.support.v7.app.AlertDialog.Builder(mInstance,R.style.AppCompatAlertDialogStyle);
					modifyDlg.setTitle("게임을 종료 하시겠습니까?");
					modifyDlg.setPositiveButton("예", new android.content.DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog, int which) {
							gameExit();
						}
					});

					modifyDlg.setNeutralButton("아니요", new android.content.DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog, int which) {

						}
					});

					modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {

						@Override
						public void onCancel(DialogInterface dialog) {

						}
					});

					modifyDlg.setCancelable(true);
					modifyDlg.show();
				}
			}, 100);

		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}




	public static void nativePopup(byte[] bText)
	{    	
    	try {
			final String strText = new String (bText ,"UTF-8");
			
			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {						
								
					modifyDlg = new android.support.v7.app.AlertDialog.Builder(mInstance,R.style.AppCompatAlertDialogStyle);
					modifyDlg.setTitle(strText);
					modifyDlg.setPositiveButton("Ok", new android.content.DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog, int which) {

						}
					});
										
					modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {
						
						@Override
						public void onCancel(DialogInterface dialog) {
											
						}
					});
				
					modifyDlg.setCancelable(true);
					modifyDlg.show();	
				}
			}, 100);
									
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}	
	}
        
    public static void nativePopupExit(byte[] bText)
	{    	
    	try {
			final String strText = new String (bText ,"UTF-8");
			
			mInstance.mHandler.postDelayed(new Runnable() {
				@Override
				public void run() {
					modifyDlg = new android.support.v7.app.AlertDialog.Builder(mInstance,R.style.AppCompatAlertDialogStyle);
					modifyDlg.setTitle(strText);
					modifyDlg.setPositiveButton("Ok",new android.content.DialogInterface.OnClickListener()
					{
						@Override
						public void onClick(DialogInterface dialog, int which) 
						{
							gameExit();
						}
					});
										
					modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {						
						@Override
						public void onCancel(DialogInterface dialog) {
							gameExit();				
						}
					});
				
					modifyDlg.setCancelable(true);
					modifyDlg.show();	
				}
			}, 100);
									
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}	
	}
    
    
    public static void nativePopupReStart(byte[] bText)
	{
		String strText = "ERR";
				
		try {
			strText = new String (bText ,"UTF-8");									
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}		
					
		modifyDlg = new android.support.v7.app.AlertDialog.Builder(mInstance,R.style.AppCompatAlertDialogStyle);
		modifyDlg.setTitle(strText);
		modifyDlg.setPositiveButton("Ok",new android.content.DialogInterface.OnClickListener()
		{
			@Override
			public void onClick(DialogInterface dialog, int which) 
			{
				reStart();				
			}
		});
							
		modifyDlg.setOnCancelListener(new android.content.DialogInterface.OnCancelListener() {			
			@Override
			public void onCancel(DialogInterface dialog) {
				reStart();				
			}
		});
		
		modifyDlg.setCancelable(true);
		modifyDlg.show();		
	}
        

    


	//초기화
	//로그인(Game Access Token 받음)
	//게임서버(계정생성 프로토콜)에서 GameAccessToken을 이용해 캐릭터정보얻어오기 없다면 캐릭터 추가(스토브API)
	//캐릭터 관련기획 필요
	
	private void getAppKeyHash()
	{
		try {
			PackageInfo info = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_SIGNATURES);
			for (Signature signature : info.signatures)
			{
				MessageDigest md;
				md = MessageDigest.getInstance("SHA");
				md.update(signature.toByteArray());
				String something = new String(Base64.encode(md.digest(), 0));

				//kakaoToastLog("Hash key"+something);

				Log.d("Hash key", something);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.e("name not found", e.toString());
			//kakaoToastLog("Hash key" + e.toString());
		}
	}


	public static void checkBluetoothPermission()
	{
		if(Build.VERSION_CODES.M >= 23)
		{
			// 권한이 없는 경우..
			if(ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.ACCESS_NETWORK_STATE) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.INTERNET) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.ACCESS_WIFI_STATE) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.WAKE_LOCK) != PackageManager.PERMISSION_GRANTED
					|| ContextCompat.checkSelfPermission(mInstance, android.Manifest.permission.GET_ACCOUNTS) != PackageManager.PERMISSION_GRANTED
					)
			{
				checkBluetoothPermissionRecv(0);
			}
			else
			{
				// 권한이 있는 경우..
				checkBluetoothPermissionRecv(1);
			}
		}
		else
			checkBluetoothPermissionRecv(1);
	}
	public static void startBluetoothPermission()
	{
		// 설명이 필요한 경우 처리, shouldShowRequestPermissionRationale 에 다이얼로그나 토스트로 작성하여 추가..
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.ACCESS_NETWORK_STATE))
		{
			//kakaoToastLog("ACCESS_FINE_LOCATION");
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.INTERNET))
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.ACCESS_WIFI_STATE))
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.READ_PHONE_STATE))			//이놈	//주소록(탭조이)
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.READ_EXTERNAL_STORAGE))		//이놈	//게임내 프로필사진등록
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.WRITE_EXTERNAL_STORAGE))		//이놈	//게임내 프로필사진등록
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.WAKE_LOCK))
		{
		}
		if(ActivityCompat.shouldShowRequestPermissionRationale(mInstance, android.Manifest.permission.GET_ACCOUNTS))				//이놈
		{
		}

		/*
		원할한 게임 진행을 위해 다음의 권한을 사용합니다.
		필수 접근권한
		기기, 사진, 미디어, 파일 엑세스: 게임내 프로필 사진 등록을 위한 용도로만 사용됩니다.
		전화 걸기 및 관리:고객님의 전화 걸기 기능에 영향을 주지 않으며 이벤트보상 및 고객 응대에 필요한 단말기 정보 확인 용도로만 사용됩니다.
		주소록 액세스:고객님의 주소록에는 접근하지 않으며 계정 확인 용도로만 사용됩니다.
		*/

		ActivityCompat.requestPermissions(mInstance, new String[]{
				android.Manifest.permission.ACCESS_NETWORK_STATE
				, android.Manifest.permission.INTERNET
				, android.Manifest.permission.ACCESS_WIFI_STATE
				, android.Manifest.permission.READ_PHONE_STATE
				, android.Manifest.permission.READ_EXTERNAL_STORAGE
				, android.Manifest.permission.WRITE_EXTERNAL_STORAGE
				, android.Manifest.permission.WAKE_LOCK
				, android.Manifest.permission.GET_ACCOUNTS
		}, 0);
	}

	// 권한 획득에 대한 성공/실패에 대한 정보를 담은 Callback, 배열로 전달되므로 필요한 퍼미션이 잘 받아졌는지 확인하여 이후 처리가 가능.
	@Override
	public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
		if (requestCode == 0)
		{
			for(int k=0;k<grantResults.length;k++)
			{
				//kakaoToastLog("result" + grantResults[k]);

				if(grantResults[k] != PackageManager.PERMISSION_GRANTED)
				{
					isGameStop = true;
					setGameStop();
					break;
				}
			}

			if(isGameStop == false)
				checkBluetoothPermissionRecv(1);
		}
	}






	public static native void nativeInit(String strPack, String strDir,String strVerName);
	public static native void nativeDeviceInfo(String DeviceID);
	public static native void recvPurchase(int state,String strPurchase,String strSignature);
	public static native void openAndroidGalleryRecv(int type, byte[] bufArray, int bufSize);
	public static native void urlFileDownLoadRecv(int type, int totalSize, int downSize);
	public static native void nativePopupYesNoRecv(int keyCode);
	public static native void gameResume();
	public static native void setGameStop();
	public static native void recvKakao(int state,int type,int value,String strValue0,String strValue1,String strValue2);
	public static native void recvGoogleSignIn(int state,String strId,String strNickName);
	public static native void checkBluetoothPermissionRecv(int state);

}