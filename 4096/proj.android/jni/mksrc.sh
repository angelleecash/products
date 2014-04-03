#!/bin/bash

echo 'LOCAL_SRC_FILES := hellocpp/main.cpp \' > Sources.mk
#find ../4096/libs/Libjson -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk
#find ../4096/libs/hashlib -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk
find ../../4096/Classes -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk
#find ../../4096/libs -name "*.cpp"|awk '{print $1,"\\"}' >> Sources.mk

echo >> Sources.mk

echo 'LOCAL_C_INCLUDES := \' >Includes.mk
#find ../4096/libs/Libjson -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk
#find ../4096/libs/hashlib -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk

find ../../4096/Classes -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk
#find ../../4096/libs/ -type d -not -wholename '*.svn*'|awk '{printf "$(LOCAL_PATH)/%s \\\n",$1}' >> Includes.mk
echo >> Includes.mk
