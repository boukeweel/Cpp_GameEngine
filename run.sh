#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
TARGET="${1:-TestingProject}"

mkdir -p "$BUILD_DIR"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"

BINARY="$(find "$BUILD_DIR" -type f -executable -name "$TARGET" | head -n 1)"

if [ -z "$BINARY" ]; then
    echo "Executable '$TARGET' not found in $BUILD_DIR"
    exit 1
fi

exec "$BINARY"
