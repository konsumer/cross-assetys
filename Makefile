# build for native
runtime: src/runtime.c
	clang -o $@ $?

# build for web
docs/runtime.mjs: src/runtime.c
	emcc -O3 -o $@ $? -Isrc -sEXPORTED_FUNCTIONS=_main -sEXPORTED_RUNTIME_METHODS=FS

# local web-server
.PHONY: web
web:
	npx -y live-server docs