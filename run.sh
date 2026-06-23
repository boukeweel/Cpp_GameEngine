#!/usr/bin/env bash
set -euo pipefail

# Build directory
BUILD_DIR="build"

# Create build directory if needed
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure and build
cmake ..
cmake --build .

# Run the executable
if [ -x "GameEngine" ]; then
  ./GameEngine
elif [ -x "game" ] && [ ! -d "game" ]; then
  ./game
elif [ -x "game/game" ]; then
  ./game/game
else
  echo "No executable found after build."
  exit 1
fi
