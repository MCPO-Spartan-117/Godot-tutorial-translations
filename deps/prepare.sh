#!/bin/sh
SCRIPTDIR="$PWD"

if [ "$(git rev-parse --show-prefix)" != "deps/" ]; then
	echo "Run in the directory that the script is." && exit 1
fi

if [ ! -f "$SCRIPTDIR/build/extension_api.json" ] || [ ! -f "$SCRIPTDIR/build/gdextension_interface.h" ]; then
	echo "Dumping API info for godot build."
	cd "$SCRIPTDIR/build" || { echo "Failed to cd into 'build'." && exit 1; }
	godot --dump-extension-api --dump-gdextension-interface
fi

if [ ! -f "$SCRIPTDIR/build/GPP-patched" ]; then
	echo "'godot-cpp' isn't patched, patching."
	cd "$SCRIPTDIR"/godot-cpp || exit 1
	git apply "$SCRIPTDIR/Patches/godot-cpp/"*.patch
	touch "$SCRIPTDIR/build/GPP-patched"
fi
