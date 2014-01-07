#keytool -genkey -v -keystore prettyshaders.keystore -alias chenliang -keyalg RSA -keysize 2048 -validity 10000
#jarsigner -verbose -storepass 123456 -sigalg SHA1withRSA -digestalg SHA1 -keystore prettyshaders.keystore bin/prettyshaders-release-unsigned.apk chenliang
sh build_native.sh && ant release && jarsigner -verbose -storepass 123456 -sigalg SHA1withRSA -digestalg SHA1 -keystore prettyshaders.keystore bin/prettyshaders-release-unsigned.apk chenliang && zipalign -f -v 4 bin/prettyshaders-release-unsigned.apk prettyshaders.apk



