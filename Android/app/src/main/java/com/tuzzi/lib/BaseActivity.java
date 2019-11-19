package com.tuzzi.lib;

import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class BaseActivity extends AppCompatActivity {

    private final static String TAG = "BaseActivity";

    RelativeLayout mLayout;
    TuzziView mTuzziView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mLayout = new RelativeLayout(this);

        mTuzziView = new TuzziView(this);
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        mLayout.addView(mTuzziView, params);

        this.setContentView(mLayout);
    }

    @Override
    protected void onPause() {
        mTuzziView.onPause();
        super.onPause();
    }

    @Override
    protected void onResume() {
        mTuzziView.onResume();
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        mTuzziView.onDestroy();
        super.onDestroy();
    }


}
