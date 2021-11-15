cd /data/local/tmp/
PTD_LIB_PATH=/data/data/com.square_enix.android_googleplay.PTD/lib/
mv libhook.so libmain.so lib__57d5__.so "$PTD_LIB_PATH"
cd "$PTD_LIB_PATH"
chown system:system libhook.so libmain.so lib__57d5__.so
chmod 755 libhook.so libmain.so lib__57d5__.so
chcon u:object_r:apk_data_file:s0 libhook.so libmain.so lib__57d5__.so
