#!/bin/sh
echo ./configure CC="$GSECROOT/games/xpilot-ng-4.7.2/llvm_gcc_script.py" --disable-sdl-client --disable-sdl-gameloop --disable-sdltest --disable-xp-mapedit --disable-replay --disable-sound
./configure CC="$GSECROOT/games/xpilot-ng-4.7.2/llvm_gcc_script.py" --disable-sdl-client --disable-sdl-gameloop --disable-sdltest --disable-xp-mapedit --disable-replay --disable-sound --enable-select-sched

