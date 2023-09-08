runtime: src/runtime.c
	clang -o $@ $?

web/runtime.mjs: src/runtime.c
	emcc -O3 -o $@ $? -Isrc -sEXPORTED_FUNCTIONS=_main -sEXPORTED_RUNTIME_METHODS=FS

.PHONY: web
web:
	npx -y live-server web