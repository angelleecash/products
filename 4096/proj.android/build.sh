#keytool -genkey -v -keystore prettyshaders.keystore -alias chenliang -keyalg RSA -keysize 2048 -validity 10000
#jarsigner -verbose -storepass 123456 -sigalg SHA1withRSA -digestalg SHA1 -keystore prettyshaders.keystore bin/prettyshaders-release-unsigned.apk chenliang
cd jni
sh mksrc.sh
cd ..
sh build_native.sh && ant release && jarsigner -verbose -storepass 123456 -sigalg SHA1withRSA -digestalg SHA1 -keystore prettyshaders.keystore bin/4096-release-unsigned.apk chenliang && zipalign -f -v 4 bin/4096-release-unsigned.apk 4096.apk



