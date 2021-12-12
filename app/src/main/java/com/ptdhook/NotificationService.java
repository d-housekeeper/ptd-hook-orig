package com.ptdhook;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.IBinder;

public class NotificationService extends Service {

    private static final String PTDHOOK_SETTINGS_CHANNEL_ID = "PTDHookSettings";
    private static final int PTDHOOK_SETTINGS_NOTIFICATION_ID = 1000;
    private NotificationManager mNotificationManager;

    public static class NotificationServiceConnection implements ServiceConnection {

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {}

        @Override
        public void onServiceDisconnected(ComponentName name) {}
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        mNotificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);

        createNotificationChannel();
        showNotification();
    }

    @Override
    public void onDestroy() {
        mNotificationManager.cancel(PTDHOOK_SETTINGS_NOTIFICATION_ID);
    }

    private void showNotification() {
        Intent notificationIntent = new Intent(this, SettingsActivity.class);
        PackageManager pm = getPackageManager();
        PendingIntent pendingNotificationIntent = PendingIntent.getActivity(
            this,
            0,
            notificationIntent,
            PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
        );

        Notification.Builder builder;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            builder = new Notification.Builder(this, PTDHOOK_SETTINGS_CHANNEL_ID);
        } else {
            builder = new Notification.Builder(this);
        }

        int drawableID = getResources().getIdentifier("ic_stat_notify", "drawable", getPackageName());

        builder
            .setSmallIcon(drawableID)
            .setContentTitle("PTDHook")
            .setContentText("Tap here to open PTDHook Settings")
            .setContentIntent(pendingNotificationIntent);

        if (android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.O) {
            builder.setPriority(Notification.PRIORITY_LOW);
        }

        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        Notification notification = builder.build();
        notification.flags = Notification.FLAG_ONGOING_EVENT;
        notificationManager.notify(PTDHOOK_SETTINGS_NOTIFICATION_ID, notification);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return START_NOT_STICKY;
    }

    private void createNotificationChannel() {
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            CharSequence name = "PTDHook Settings";
            String description = "Notification channel for opening PTDHook Settings";
            int importance = NotificationManager.IMPORTANCE_LOW;
            NotificationChannel channel = new NotificationChannel(PTDHOOK_SETTINGS_CHANNEL_ID, name, importance);
            channel.setDescription(description);
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

    public static NotificationServiceConnection bindService(Activity activity) {
        Intent serviceIntent = new Intent(activity, NotificationService.class);
        NotificationServiceConnection connection = new NotificationServiceConnection();
        activity.bindService(serviceIntent, connection, Service.BIND_AUTO_CREATE);
        return connection;
    }
}
