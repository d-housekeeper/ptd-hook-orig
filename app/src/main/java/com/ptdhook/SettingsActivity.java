package com.ptdhook;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.ShortcutInfo;
import android.content.pm.ShortcutManager;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Icon;
import android.os.Build;
import android.os.Bundle;
import android.text.InputType;
import android.view.Gravity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import org.json.JSONException;
import org.json.JSONObject;

public class SettingsActivity extends Activity {

    private static final float TEXT_SIZE = 20.0F;
    private static final String[] FAKE_TIME_TYPES = new String[] {
        "disabled",
        "fixedDateAndTime",
        "fixedDate",
        "fixedYear",
    };
    private static final int DEFAULT_CAMERA_POS_OFFSET_Y = 33;
    private static final int DEFAULT_CAMERA_POS_OFFSET_Z = 0;

    private int mNextViewID;
    private LinearLayout mRootLayout;
    private boolean configLoaded = false;
    private Spinner mFakeTimeSpinner;
    private EditText mFakeTimeValueEditText;
    private Button mPickFakeTimeButton;
    private ToggleButton mEnableUIModToggle;
    private ToggleButton mPortraitHomeSceneToggle;
    private ToggleButton mPortraitMyRoomSceneToggle;
    private ToggleButton mPortraitPhotoModeSceneToggle;
    private ToggleButton mHideHomeSceneUIElementsToggle;
    private ToggleButton mHideMyRoomSceneUIElementsToggle;
    private ToggleButton mAdjustPortraitModeCameraPosToggle;
    private EditText mCameraPosOffsetYEditText;
    private EditText mCameraPosOffsetZEditText;
    private Resources.Theme mTheme;
    private String mOldFakeTimeType;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mNextViewID = 1;
        if (savedInstanceState != null) {
            configLoaded = true;
        }
        Resources resources = getResources();
        int themeID = resources.getIdentifier("Theme.PTDHook", "style", getPackageName());
        setTheme(themeID);
        mTheme = resources.newTheme();
        mTheme.applyStyle(themeID, true);
        ScrollView scrollView = new ScrollView(this);
        mRootLayout = new LinearLayout(this);
        mRootLayout.setPadding(50, 10, 50, 10);
        mRootLayout.setOrientation(LinearLayout.VERTICAL);
        scrollView.addView(mRootLayout);

        addTextViewToLayout("Shortcuts");
        addButtonToLayout("Add a shortcut to home screen", l -> createShortcut());
        addDividerToLayout();

        addTextViewToLayout("Fake time mod settings");
        addTextViewToLayout("Fake time type", true);
        mFakeTimeSpinner =
            addSpinnerToLayout(
                FAKE_TIME_TYPES,
                new AdapterView.OnItemSelectedListener() {
                    @Override
                    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                        updateFakeTimeViews();
                    }

                    @Override
                    public void onNothingSelected(AdapterView<?> parent) {}
                }
            );
        addTextViewToLayout("Fake time value", true);
        addFakeTimeValueEditTextToLayout();

        addDividerToLayout();
        addTextViewToLayout("Optional mods");
        mEnableUIModToggle = addToggleButtonToLayout("Enable UI mod (requires an app restart to take effect)");
        addDividerToLayout();
        addTextViewToLayout("UI mod settings");
        mEnableUIModToggle.setOnClickListener(l -> updateUIModViewsEnabled());
        mPortraitHomeSceneToggle = addToggleButtonToLayout("Force portrait mode in home scene");
        mPortraitMyRoomSceneToggle = addToggleButtonToLayout("Force portrait mode in my room scene");
        mPortraitPhotoModeSceneToggle =
            addToggleButtonToLayout(
                "Force portrait mode in photo mode scene\n(only applies after pressing photograph button)"
            );

        mHideHomeSceneUIElementsToggle = addToggleButtonToLayout("Hide home scene UI elements");
        mHideMyRoomSceneUIElementsToggle = addToggleButtonToLayout("Hide my room scene UI elements");
        mAdjustPortraitModeCameraPosToggle = addToggleButtonToLayout("Adjust camera position in forced portrait mode");
        mAdjustPortraitModeCameraPosToggle.setOnClickListener(l -> updateCameraPosEditTextsEnabled());
        addTextViewToLayout("camera position offset Y", true);
        mCameraPosOffsetYEditText = addIntegerEditTextToLayout(DEFAULT_CAMERA_POS_OFFSET_Y);
        addTextViewToLayout("camera position offset Z", true);
        mCameraPosOffsetZEditText = addIntegerEditTextToLayout(DEFAULT_CAMERA_POS_OFFSET_Z);

        addButtonToLayout("Save", l -> saveConfig());
        loadConfig();
        setContentView(scrollView);
    }

    private void updateFakeTimeViews() {
        String fakeTimeType = (String) mFakeTimeSpinner.getSelectedItem();
        boolean fakeTimeEnabled = !fakeTimeType.equals("disabled");
        mFakeTimeValueEditText.setEnabled(fakeTimeEnabled);
        mPickFakeTimeButton.setEnabled(fakeTimeEnabled);
        try {
            mFakeTimeValueEditText.setText(getNormalizedFakeTimeValue());
        } catch (ParseException ignored) {
            reformatFakeTimeValue(fakeTimeType);
        }
        mOldFakeTimeType = fakeTimeType;
    }

    private void reformatFakeTimeValue(String fakeTimeType) {
        SimpleDateFormat format = getSimpleDateFormatFromFakeTimeType(mOldFakeTimeType);
        SimpleDateFormat newFormat = getSimpleDateFormatFromFakeTimeType(fakeTimeType);
        if (format != null && newFormat != null) {
            String fakeTimeValue = mFakeTimeValueEditText.getText().toString();
            try {
                Date fakeTimeDate = format.parse(fakeTimeValue);
                //noinspection ConstantConditions
                fakeTimeValue = newFormat.format(fakeTimeDate);
                mFakeTimeValueEditText.setText(fakeTimeValue);
            } catch (ParseException ignored) {}
        }
    }

    private void updateUIModViewsEnabled() {
        boolean enabled = mEnableUIModToggle.isChecked();
        mPortraitHomeSceneToggle.setEnabled(enabled);
        mPortraitMyRoomSceneToggle.setEnabled(enabled);
        mPortraitPhotoModeSceneToggle.setEnabled(enabled);
        mHideHomeSceneUIElementsToggle.setEnabled(enabled);
        mHideMyRoomSceneUIElementsToggle.setEnabled(enabled);
        mAdjustPortraitModeCameraPosToggle.setEnabled(enabled);
        updateCameraPosEditTextsEnabled();
    }

    private void updateCameraPosEditTextsEnabled() {
        boolean enabled = mEnableUIModToggle.isChecked() && mAdjustPortraitModeCameraPosToggle.isChecked();
        mCameraPosOffsetYEditText.setEnabled(enabled);
        mCameraPosOffsetZEditText.setEnabled(enabled);
    }

    private String getConfigFilePath() {
        return getExternalFilesDir(null).getPath() + "/ptd-hook-config.json";
    }

    private void openDatePickerDialog() {
        String fakeTimeValue = mFakeTimeValueEditText.getText().toString();
        Calendar cal = Calendar.getInstance();
        String fakeTimeType = mFakeTimeSpinner.getSelectedItem().toString();
        SimpleDateFormat format = getSimpleDateFormatFromFakeTimeType((String) mFakeTimeSpinner.getSelectedItem());
        if (format != null) {
            try {
                //noinspection ConstantConditions
                cal.setTime(format.parse(fakeTimeValue));
            } catch (ParseException ignored) {}
        } else {
            return; // unreachable code
        }

        new DatePickerDialog(
            this,
            (view, year, month, dayOfMonth) -> {
                cal.set(year, month, dayOfMonth);
                cal.set(Calendar.HOUR_OF_DAY, 0);
                cal.set(Calendar.MINUTE, 0);
                cal.set(Calendar.SECOND, 0);

                switch (fakeTimeType) {
                    case "fixedDateAndTime":
                        new TimePickerDialog(
                            this,
                            (view1, hourOfDay, minute) -> {
                                cal.set(Calendar.HOUR_OF_DAY, hourOfDay);
                                cal.set(Calendar.MINUTE, minute);
                                String newFakeTimeValue = format.format(cal.getTime());
                                mFakeTimeValueEditText.setText(newFakeTimeValue);
                            },
                            cal.get(Calendar.HOUR_OF_DAY),
                            cal.get(Calendar.MINUTE),
                            true
                        )
                            .show();
                        break;
                    case "fixedDate":
                    case "fixedYear":
                        String newFakeTimeValue = format.format(cal.getTime());
                        mFakeTimeValueEditText.setText(newFakeTimeValue);
                        break;
                }
            },
            cal.get(Calendar.YEAR),
            cal.get(Calendar.MONTH),
            cal.get(Calendar.DAY_OF_MONTH)
        )
            .show();
    }

    private void loadConfig() {
        if (configLoaded) {
            return;
        }
        configLoaded = true;

        try (InputStream input = new FileInputStream(getConfigFilePath())) {
            int size = input.available();
            byte[] buffer = new byte[size];
            //noinspection ResultOfMethodCallIgnored
            input.read(buffer);
            input.close();
            String json = new String(buffer, StandardCharsets.UTF_8);

            JSONObject obj = new JSONObject(json);
            Object fakeTimeType = obj.get("fakeTimeType");
            for (int i = 0; i < FAKE_TIME_TYPES.length; i++) {
                if (FAKE_TIME_TYPES[i].equals(fakeTimeType)) {
                    mFakeTimeSpinner.setSelection(i);
                    break;
                }
            }
            Object fakeTimeValue = obj.get("fakeTimeValue");
            mFakeTimeValueEditText.setText((fakeTimeValue instanceof String) ? (String) fakeTimeValue : "");
            Object enableUIMod = obj.get("enableUIMod");
            Object portraitHomeScene = obj.get("portraitHomeScene");
            Object portraitMyRoomScene = obj.get("portraitMyRoomScene");
            Object portraitPhotoModeScene = obj.get("portraitPhotoModeScene");
            Object hideHomeSceneUIElements = obj.get("hideHomeSceneUIElements");
            Object hideMyRoomSceneUIElements = obj.get("hideMyRoomSceneUIElements");
            Object adjustPortraitModeCameraPos = obj.get("adjustPortraitModeCameraPos");
            Object cameraPosOffsetY = obj.get("cameraPosOffsetY");
            Object cameraPosOffsetZ = obj.get("cameraPosOffsetZ");

            updateToggleButtonChecked(mEnableUIModToggle, enableUIMod);
            updateToggleButtonChecked(mPortraitHomeSceneToggle, portraitHomeScene);
            updateToggleButtonChecked(mPortraitMyRoomSceneToggle, portraitMyRoomScene);
            updateToggleButtonChecked(mPortraitPhotoModeSceneToggle, portraitPhotoModeScene);
            updateToggleButtonChecked(mHideHomeSceneUIElementsToggle, hideHomeSceneUIElements);
            updateToggleButtonChecked(mHideMyRoomSceneUIElementsToggle, hideMyRoomSceneUIElements);
            updateToggleButtonChecked(mAdjustPortraitModeCameraPosToggle, adjustPortraitModeCameraPos);
            mCameraPosOffsetYEditText.setText(
                (cameraPosOffsetY instanceof Integer) ? "" + cameraPosOffsetY : "" + DEFAULT_CAMERA_POS_OFFSET_Y
            );
            mCameraPosOffsetZEditText.setText(
                (cameraPosOffsetY instanceof Integer) ? "" + cameraPosOffsetZ : "" + DEFAULT_CAMERA_POS_OFFSET_Z
            );
        } catch (FileNotFoundException ignored) {} catch (JSONException | IOException e) {
            Toast.makeText(this, "Failed to load config from file: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
        updateFakeTimeViews();
        updateUIModViewsEnabled();
    }

    private void updateToggleButtonChecked(ToggleButton button, Object value) {
        button.setChecked((value instanceof Boolean) ? (Boolean) value : false);
    }

    private SimpleDateFormat getSimpleDateFormatFromFakeTimeType(String fakeTimeType) {
        switch (fakeTimeType) {
            case "fixedDateAndTime":
                return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US);
            case "fixedDate":
                return new SimpleDateFormat("yyyy-MM-dd", Locale.US);
            case "fixedYear":
                return new SimpleDateFormat("yyyy", Locale.US);
        }

        return null;
    }

    private String getNormalizedFakeTimeValue() throws ParseException {
        String fakeTimeValue = mFakeTimeValueEditText.getText().toString();
        SimpleDateFormat format = getSimpleDateFormatFromFakeTimeType((String) mFakeTimeSpinner.getSelectedItem());
        if (format != null) {
            Date fakeTimeDate = format.parse(fakeTimeValue);
            //noinspection ConstantConditions
            fakeTimeValue = format.format(fakeTimeDate);
        } else {
            fakeTimeValue = "";
        }

        return fakeTimeValue;
    }

    private boolean validateAndNormalizeFakeTimeValue() {
        try {
            mFakeTimeValueEditText.clearFocus();
            mFakeTimeValueEditText.setTextKeepState(getNormalizedFakeTimeValue());
        } catch (ParseException e) {
            SimpleDateFormat format = getSimpleDateFormatFromFakeTimeType((String) mFakeTimeSpinner.getSelectedItem());
            //noinspection ConstantConditions
            mFakeTimeValueEditText.setError("The value must be in format " + format.toPattern());
            mFakeTimeValueEditText.requestFocus();
            return false;
        }

        return true;
    }

    @SuppressLint("SetTextI18n")
    private Integer validateAndNormalizeIntegerEditTextField(EditText editText, int defaultValue) {
        int value;
        try {
            editText.clearFocus();
            value = Integer.parseInt(editText.getText().toString());
            editText.setTextKeepState("" + value);
        } catch (NumberFormatException e) {
            if (!editText.isEnabled()) {
                editText.setTextKeepState("" + defaultValue);
                return defaultValue;
            }

            editText.setError("The value must be an integer");
            editText.requestFocus();
            return null;
        }

        return value;
    }

    private void saveConfig() {
        boolean fakeTimeValueValid = validateAndNormalizeFakeTimeValue();
        Integer cameraPosY = validateAndNormalizeIntegerEditTextField(
            mCameraPosOffsetYEditText,
            DEFAULT_CAMERA_POS_OFFSET_Y
        );
        Integer cameraPosZ = validateAndNormalizeIntegerEditTextField(
            mCameraPosOffsetZEditText,
            DEFAULT_CAMERA_POS_OFFSET_Z
        );
        if (!fakeTimeValueValid || cameraPosY == null || cameraPosZ == null) {
            return;
        }

        mFakeTimeValueEditText.setError(null);
        mCameraPosOffsetYEditText.setError(null);

        try {
            String fakeTimeType = (String) mFakeTimeSpinner.getSelectedItem();
            JSONObject obj = new JSONObject();
            obj.put("fakeTimeType", fakeTimeType);
            obj.put("fakeTimeValue", mFakeTimeValueEditText.getText());
            obj.put("enableUIMod", mEnableUIModToggle.isChecked());
            obj.put("portraitHomeScene", mPortraitHomeSceneToggle.isChecked());
            obj.put("portraitMyRoomScene", mPortraitMyRoomSceneToggle.isChecked());
            obj.put("portraitPhotoModeScene", mPortraitPhotoModeSceneToggle.isChecked());
            obj.put("hideHomeSceneUIElements", mHideHomeSceneUIElementsToggle.isChecked());
            obj.put("hideMyRoomSceneUIElements", mHideMyRoomSceneUIElementsToggle.isChecked());
            obj.put("adjustPortraitModeCameraPos", mAdjustPortraitModeCameraPosToggle.isChecked());
            obj.put("cameraPosOffsetY", cameraPosY.intValue());
            obj.put("cameraPosOffsetZ", cameraPosZ.intValue());

            String filePath = getConfigFilePath();
            File file = new File(filePath);
            Writer output = new BufferedWriter(new FileWriter(file));
            output.write(obj.toString());
            output.close();
            Toast.makeText(this, "Config saved", Toast.LENGTH_LONG).show();
        } catch (JSONException | IOException e) {
            Toast.makeText(this, "Failed to save config to file: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
    }

    private void createShortcut() {
        if (android.os.Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            ShortcutManager shortcutManager = getSystemService(ShortcutManager.class);
            if (!shortcutManager.isRequestPinShortcutSupported()) {
                Toast
                    .makeText(this, "Your launcher does not support requesting pin shortcut", Toast.LENGTH_LONG)
                    .show();
                return;
            }

            Intent intent = new Intent();
            intent.setComponent(new ComponentName(getPackageName(), SettingsActivity.class.getCanonicalName()));
            intent.setAction("LOCATION_SHORTCUT");
            Resources resources = getResources();
            int drawableID = resources.getIdentifier("ic_stat_notify", "drawable", getPackageName());
            @SuppressLint("UseCompatLoadingForDrawables")
            BitmapDrawable drawable = (BitmapDrawable) resources.getDrawable(drawableID, mTheme);
            Icon icon = Icon.createWithBitmap(drawable.getBitmap());
            ShortcutInfo pinShortcutInfo = new ShortcutInfo.Builder(this, "PTDHookSettings")
                .setShortLabel("PTDHook Settings")
                .setIntent(intent)
                .setIcon(icon)
                .build();
            Intent pinnedShortcutCallbackIntent = shortcutManager.createShortcutResultIntent(pinShortcutInfo);

            shortcutManager.requestPinShortcut(pinShortcutInfo, null);
        } else {
            Toast
                .makeText(this, "Shortcut creation is only supported on Android 8.0 or later", Toast.LENGTH_LONG)
                .show();
        }
    }

    private void addTextViewToLayout(String text) {
        addTextViewToLayout(text, false);
    }

    private void addTextViewToLayout(String text, boolean addMargins) {
        TextView textView = new TextView(this);
        textView.setText(text);
        textView.setTextSize(TEXT_SIZE);
        LinearLayout.LayoutParams params = null;

        if (addMargins) {
            params =
                new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT
                );
            params.setMargins(10, 0, 10, 0);
        }

        addViewToLayout(textView, params);
    }

    @SuppressLint("SetTextI18n")
    private void addFakeTimeValueEditTextToLayout() {
        LinearLayout layout = new LinearLayout(this);

        mFakeTimeValueEditText = new EditText(this);
        mFakeTimeValueEditText.setText("2021-10-29 10:00:00");
        mFakeTimeValueEditText.setTextSize(TEXT_SIZE);
        LinearLayout.LayoutParams editTextLayoutParams = new LinearLayout.LayoutParams(
            0,
            LinearLayout.LayoutParams.WRAP_CONTENT,
            0.8f
        );
        editTextLayoutParams.setMargins(5, 0, 5, 0);
        mFakeTimeValueEditText.setLayoutParams(editTextLayoutParams);
        setIdToView(mFakeTimeValueEditText);
        layout.addView(mFakeTimeValueEditText);

        mPickFakeTimeButton = new Button(this);
        mPickFakeTimeButton.setText("...");
        mPickFakeTimeButton.setTextSize(TEXT_SIZE);
        LinearLayout.LayoutParams buttonLayoutParams = new LinearLayout.LayoutParams(
            0,
            LinearLayout.LayoutParams.WRAP_CONTENT,
            0.2f
        );
        buttonLayoutParams.setMargins(5, 0, 5, 0);
        mPickFakeTimeButton.setLayoutParams(buttonLayoutParams);
        mPickFakeTimeButton.setOnClickListener(v -> openDatePickerDialog());
        setIdToView(mPickFakeTimeButton);
        layout.addView(mPickFakeTimeButton);

        addViewToLayout(layout);
    }

    @SuppressWarnings("SameParameterValue")
    private Spinner addSpinnerToLayout(String[] items, AdapterView.OnItemSelectedListener l) {
        Spinner spinner = new Spinner(this);
        CustomArrayAdapter fakeTimeTypeAdapter = new CustomArrayAdapter(items, TEXT_SIZE);
        spinner.setAdapter(fakeTimeTypeAdapter);
        spinner.setOnItemSelectedListener(l);
        setIdToView(spinner);
        addViewToLayout(spinner);

        return spinner;
    }

    private ToggleButton addToggleButtonToLayout(String text) {
        LinearLayout layout = new LinearLayout(this);

        TextView textView = new TextView(this);
        textView.setText(text);
        textView.setTextSize(TEXT_SIZE);
        LinearLayout.LayoutParams textViewLayoutParams = new LinearLayout.LayoutParams(
            0,
            LinearLayout.LayoutParams.WRAP_CONTENT,
            0.8f
        );
        textViewLayoutParams.gravity = Gravity.FILL;
        textView.setLayoutParams(textViewLayoutParams);
        setIdToView(textView);
        layout.addView(textView);

        ToggleButton button = new ToggleButton(this);
        LinearLayout.LayoutParams buttonLayoutParams = new LinearLayout.LayoutParams(
            0,
            LinearLayout.LayoutParams.WRAP_CONTENT,
            0.2f
        );
        buttonLayoutParams.setMargins(5, 0, 5, 0);
        button.setLayoutParams(buttonLayoutParams);
        setIdToView(button);
        layout.addView(button);

        layout.setPadding(10, 10, 10, 10);
        addViewToLayout(layout);

        return button;
    }

    @SuppressLint("SetTextI18n")
    private void addButtonToLayout(String text, View.OnClickListener l) {
        Button button = new Button(this);
        button.setText(text);
        button.setOnClickListener(l);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        params.setMargins(10, 0, 10, 0);
        setIdToView(button);
        addViewToLayout(button, params);
    }

    @SuppressWarnings("SameParameterValue")
    @SuppressLint("SetTextI18n")
    private EditText addIntegerEditTextToLayout(int value) {
        EditText editText = new EditText(this);
        editText.setText("" + value);
        editText.setTextSize(TEXT_SIZE);
        editText.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        params.setMargins(10, 0, 10, 0);
        setIdToView(editText);
        addViewToLayout(editText);

        return editText;
    }

    private void addDividerToLayout() {
        View divider = new View(this);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, 1);
        params.setMargins(0, 20, 0, 20);
        divider.setLayoutParams(params);
        divider.setBackgroundColor(Color.DKGRAY);

        addViewToLayout(divider, params);
    }

    private void addViewToLayout(View child) {
        addViewToLayout(child, null);
    }

    private void addViewToLayout(View child, LinearLayout.LayoutParams params) {
        if (params == null) {
            params =
                new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT
                );
            params.setMargins(0, 5, 0, 5);
        }
        child.setLayoutParams(params);
        mRootLayout.addView(child);
    }

    private void setIdToView(View child) {
        child.setId(++mNextViewID);
    }
}
