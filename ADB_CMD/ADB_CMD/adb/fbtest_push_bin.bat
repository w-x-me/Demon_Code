adb root
adb push fbtest /data/
adb shell "ls /data | grep fbtest"
adb shell chmod +x /data/fbtest
pause