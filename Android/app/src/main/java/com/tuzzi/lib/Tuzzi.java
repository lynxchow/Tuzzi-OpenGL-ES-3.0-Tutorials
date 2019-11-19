package com.tuzzi.lib;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.view.Surface;
import android.view.WindowManager;

import java.io.File;

public class Tuzzi {

    private Activity mActivity;

    static {
        System.loadLibrary("TuzziApp");
    }

    public Tuzzi(Activity activity) {
        this.mActivity = activity;
    }

    public int backToHome() {
        Intent home = new Intent(Intent.ACTION_MAIN);
        home.addCategory(Intent.CATEGORY_HOME);
        mActivity.startActivity(home);
        return 0;
    }

    public String getPackagePath() {
        return mActivity.getPackageResourcePath();
    }

    public String getFilesDirPath() {
        File files_dir = mActivity.getExternalFilesDir(null);
        if(files_dir == null) {
            files_dir = mActivity.getFilesDir();
        }
        return files_dir.getAbsolutePath();
    }

    public int quitApplication() {
        mActivity.finish();
        return 0;
    }

    public int keepScreenOn(final boolean enable) {
        mActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(enable) {
                    mActivity.getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
                } else {
                    mActivity.getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
                }
            }
        });
        return 0;
    }

    public native void create(Surface surface, int width, int height, AssetManager assetManager);

    public native void resize(Surface surface, int width, int height);

    public native void draw();

    public native void surfaceDestroy();

    public native void pause();

    public native void resume();

    public native void destroy();

}
