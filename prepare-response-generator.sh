#!/usr/bin/env bash
set -eu
: "$MD_SRC_DIR"
export MD_DEST_DIR=./out/md/
rm -rf "$MD_DEST_DIR"
mkdir -p "$MD_DEST_DIR"
generate-md-assets.sh
CONFIG_FILE=./out/login-response-generator-config.json
if [ ! -f ./out/login-response-generator-config.json ]; then
  cp "$PTD_TOOL_DIR/bin/assets/login-response-generator-config.json" "$CONFIG_FILE"
  echo "Copied config file to $CONFIG_FILE"
else
  echo "Config file already exists at $CONFIG_FILE, skipped copying"
fi
chmod 644 ./out/login-response-generator-config.json
