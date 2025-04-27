emcmake cmake -B build -DBUILD_TARGET=web
cp -r assets build/ #for --preload-file
cp -r shell.html build/ #for --shell-file
emmake cmake --build build