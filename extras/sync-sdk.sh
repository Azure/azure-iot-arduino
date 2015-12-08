#!/bin/sh
# Copyright (c) Arduino. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

SDK_DIR=$1
SRC_SDK_DIR=../src/sdk
EXAMPLES_SDK_DIR=../examples/sdk
SDK_METADATA=$SRC_SDK_DIR/metadata.txt

if [ -z "$SDK_DIR" ]
then
	echo "Please specify Azure SDK directory as command line argument!"
	exit 1
fi

if [ ! -d "$SDK_DIR" ]
then
	echo "'$SDK_DIR' does not exist!"
	exit 1
fi

copy_filelist() {
	for file in `cat $1`
	do
		echo "\t$file"
		cp "$2/$file" "$3"
	done
}

echo "Copying SDK C source files over"
copy_filelist "sdk-files.txt" "$SDK_DIR" "$SRC_SDK_DIR"

echo "Copying SDK sample files over"
copy_filelist "iothub-client-sample-http-files.txt" "$SDK_DIR" "$EXAMPLES_SDK_DIR/iothub_client_sample_http"
copy_filelist "simplesample-http-files.txt" "$SDK_DIR" "$EXAMPLES_SDK_DIR/simplesample_http"

echo "Storing SDK metadata"
git --git-dir "$SDK_DIR/.git" ls-remote --get-url > "$SDK_METADATA"
git --git-dir "$SDK_DIR/.git" rev-parse --abbrev-ref HEAD >> "$SDK_METADATA"
git --git-dir "$SDK_DIR/.git" rev-parse HEAD >> "$SDK_METADATA"
cat $SDK_METADATA
