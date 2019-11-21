package com.tuzzi.lib;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.LinkedList;

public class TuzziView extends SurfaceView implements SurfaceHolder.Callback {

    private final static String TAG = "TuzziView";

    private Tuzzi mTuzzi;
    private Thread mRenderThread;
    boolean mEngineCreated = false;
    volatile boolean mStopRenderThread = false;
    volatile boolean mPaused = false;
    final Object mLock = new Object();
    LinkedList<Runnable> mActions = new LinkedList<>();

    public TuzziView(Context context) {
        super(context);

        mTuzzi = new Tuzzi((Activity) context);
        mRenderThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (!mStopRenderThread) {
                    synchronized (mLock) {
                        for (int i = 0; i < mActions.size(); ++i) {
                            Runnable r = mActions.get(i);
                            if (r != null) {
                                r.run();
                            }
                        }
                        mActions.clear();
                    }

                    if (!mPaused) {
                        if (mEngineCreated) {
                            mTuzzi.draw();
                        }
                    }
                }
            }
        });
        mRenderThread.start();


        this.getHolder().setFormat(PixelFormat.RGB_888);
        this.getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        postEvent(new Runnable() {
            @Override
            public void run() {
                SurfaceHolder holder = TuzziView.this.getHolder();
                Rect rect = holder.getSurfaceFrame();

                if (!mEngineCreated) {
                    mEngineCreated = true;
                    mTuzzi.create(holder.getSurface(), rect.width(), rect.height(), getContext().getAssets());
                } else {
                    mTuzzi.resize(holder.getSurface(), rect.width(), rect.height());
                }
            }
        });

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        postEvent(new Runnable() {
            @Override
            public void run() {
                mStopRenderThread = true;
                if (mEngineCreated) {
                    mTuzzi.destroy();
                    mPaused = true;
                    mEngineCreated = false;
                }
            }
        });
    }

    public void postEvent(Runnable r) {
        synchronized (mLock) {
            mActions.addLast(r);
        }
    }

    public void onPause() {
        this.postEvent(new Runnable() {
            @Override
            public void run() {
                mPaused = true;
                if (mEngineCreated) {
                    mTuzzi.pause();
                }
            }
        });
    }

    public void onResume() {
        this.postEvent(new Runnable() {
            @Override
            public void run() {
                mPaused = false;
                if (mEngineCreated) {
                    mTuzzi.resume();
                }
            }
        });
    }

    public void onDestroy() {

    }

}
