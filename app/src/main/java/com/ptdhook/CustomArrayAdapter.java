package com.ptdhook;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.FrameLayout;
import android.widget.SpinnerAdapter;
import android.widget.TextView;

public class CustomArrayAdapter extends BaseAdapter implements SpinnerAdapter {

    private String[] mObjects;
    private float mTextSize;

    public CustomArrayAdapter(String[] mItems, float textSize) {
        mObjects = mItems;
        mTextSize = textSize;
    }

    @Override
    public int getCount() {
        return mObjects.length;
    }

    @Override
    public Object getItem(int position) {
        return this.mObjects[position];
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        String item = (String) getItem(position);
        FrameLayout view;
        TextView textView;
        if (convertView == null) {
            Context context = parent.getContext();
            view = new FrameLayout(context);
            textView = new TextView(context);
            textView.setTextSize(mTextSize);
            view.setPadding(10, 10, 10, 10);
            view.addView(textView);
        } else {
            view = (FrameLayout) convertView;
            textView = (TextView) view.getChildAt(0);
        }
        textView.setText(item);

        return view;
    }
}
