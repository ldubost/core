#!/bin/bash

export PATH=`pwd`/depot_tools:"$PATH"

SCRIPT=$(readlink -f "$0" || grealpath "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

os=$(uname -s)
platform=""

case "$os" in
  Linux*)   platform="linux" ;;
  Darwin*)  platform="mac" ;; 
  *)        exit ;;
esac

architecture="x86"
arch=""

case "$architecture" in
  x86_64*)  arch="_64" ;;
  *)        arch="_32" ;;
esac

cd "$SCRIPTPATH/v8"

if [[ "$platform$arch" == "linux_64" ]]
then
gn gen out.gn/linux_64 --args='is_debug=false target_cpu="x64" v8_target_cpu="x64" v8_static_library=true is_component_build=false v8_use_snapshot=false is_clang=false use_sysroot=false'
ninja -C out.gn/linux_64
fi

if [[ "$platform$arch" == "linux_32" ]]
then
gn gen out.gn/linux_32 --args='is_debug=false target_cpu="x86" v8_target_cpu="x86" v8_static_library=true is_component_build=false v8_use_snapshot=false is_clang=false use_sysroot=false'
ninja -C out.gn/linux_32
fi

if [[ "$platform" == "mac" ]]
then
# for new macOS!!!
#sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
gn gen out.gn/mac_64 --args='is_debug=false target_cpu="x64" v8_static_library=true is_component_build=false v8_use_snapshot=false'
ninja -C out.gn/mac_64
fi
