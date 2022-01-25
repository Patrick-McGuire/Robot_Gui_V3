#!/bin/bash

# Script runs every compile, and finishes some setup tasks
# First argument is the cmake file path

SOURCE_PATH="$1/Assets"
TARGET_PATH="$HOME/.config/RobotGUI"
echo "Copying Asset Files from $SOURCE_PATH to $TARGET_PATH"
cp $SOURCE_PATH/* $TARGET_PATH/