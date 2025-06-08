#!/bin/bash
OUTPUT=BlockBreakC-WASM.wasm

clang \
	--target=wasm32 \
	-O3 \
	--no-standard-libraries \
	-o "$OUTPUT" \
	-DFONT_HEIGHT=16 \
	-I ../src/BlockBreakC/src \
	-Wl,--export-all \
	-Wl,-allow-undefined-file imports.syms \
	../src/*.c \
	../src/BlockBreakC/src/*.c