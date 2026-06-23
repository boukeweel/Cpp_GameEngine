#!/usr/bin/env bash
set -euo pipefail

echo "Installing C++ Game Engine dependencies..."

# Update package lists
sudo apt update

# Install build tools
echo "Installing build tools..."
sudo apt install -y build-essential cmake pkg-config

# Install SDL2 and variants
echo "Installing SDL2 and variants..."
sudo apt install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    libsdl2-ttf-dev

echo "✓ All dependencies installed successfully!"
echo "You can now run: ./run.sh"
