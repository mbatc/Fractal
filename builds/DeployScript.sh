#!/bin/sh

# Create directory to copy the artifact to
mkdir builds/artifact

# Copy binaries
cp builds/bin/FractalEditor.exe builds/artifact/
cp builds/bin/FractalPlayer.exe builds/artifact/
cp builds/bin/FractalEngine.dll builds/artifact/
cp builds/bin/glew32.dll builds/artifact/
