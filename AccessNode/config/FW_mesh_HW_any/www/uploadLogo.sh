#! /bin/sh

if [ $# -lt 1 ]; then
	echo "usage: $0 sourceFile"
	exit
fi
if [ ! -f "/tmp/upgrade_web/$1" ];then
	echo "No such file:[$1]"
	return 1
fi

fsize="`ls -l "/tmp/upgrade_web/$1" | tr -s ' ' | cut -d ' ' -f 5`"
if [ ${fsize} -gt 10240 ]; then
	echo "Image bigger than 10kB"
	return 2
fi

DEST_DIR="/access_node/firmware/www/wwwroot/app/styles/images"
if [ $# -ge 2 ]; then
	DEST_DIR="${DEST_DIR}/custom"
fi
if [ ! -d $DEST_DIR ]; then
	mkdir -p $DEST_DIR
	[ "$?" != "0" ] && return 3
fi
mv "/tmp/upgrade_web/$1" "${DEST_DIR}/CompanyLogo.png"

