#!/bin/bash
# Rebuild backend and regenerate data with images

echo "Rebuilding backend with image support..."
./build_simple.sh

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Regenerating data with images..."
if [ -f "data/books.txt" ]; then
    rm "data/books.txt"
    echo "Deleted old books.txt"
fi

echo ""
echo "Backend rebuilt! Now run: ./build/BookWiseBackend"

