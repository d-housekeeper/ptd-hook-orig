#!/usr/bin/env bash
set -eu
rm -rf ./out/Responses/
mkdir -p ./out/Responses/
ptd-tool generate-login-response --decoded-md-dir ./out/md/ --config ./out/login-response-generator-config.json > out/Responses/Login.json
jq . ./out/Responses/Login.json > ./out/Login-formatted.json
for FILE_PATH in ./responses-input/*.json; do
  BASE_FILE_NAME="$(basename "$FILE_PATH")"
  jq -c -j . "$FILE_PATH" > "./out/Responses/$BASE_FILE_NAME"
done
