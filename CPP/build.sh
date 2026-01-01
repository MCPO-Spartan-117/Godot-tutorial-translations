#!/bin/sh
SCRIPTDIR="$PWD"
CPUCORES=
STATIC="true"
PLATFORM="linux"
TARGET="template_release"
DEBUG=

if [ "$(git rev-parse --show-prefix)" != "CPP/" ]; then
	echo "Run in the directory that the script is." && exit 1
fi

for args in "$@"; do
	case "$args" in
	--cpucores )
		shift
		CPUCORES="$1"
		shift
		;;
	--dynamic )
		shift
		STATIC="false"
		;;
	--debug )
		shift
		TARGET="template_debug"
		DEBUG="dev_build=true optimize=debug"
	esac
done

for args in "$@"; do
	case "$args" in
	--platform )
		shift
		if [ $1 = "windows" ]; then
			STATIC="true"
		fi
		PLATFORM=$1
		shift
		;;
	esac
done

if [ -z "$CPUCORES" ]; then
	CPUCORES="$(($(nproc) / 2))"
fi

cd ../deps || exit 1
./prepare.sh
cd "$SCRIPTDIR" || exit 1
scons platform=$PLATFORM gdextension_dir="$SCRIPTDIR/../deps/build" target=$TARGET $DEBUG -j"$CPUCORES" use_static_cpp=$STATIC symbols_visibility=visible "$@"
