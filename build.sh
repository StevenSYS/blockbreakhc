#!/bin/bash
OUTPUT=blockBreak.wasm

clang \
	--target=wasm32 \
	-Os \
	--no-standard-libraries \
	-Wl,--export-all \
	-o "$OUTPUT" \
	-DFONT_HEIGHT=16 \
	-I src/BlockBreakC/src \
	src/*.c \
	src/BlockBreakC/src/*.c