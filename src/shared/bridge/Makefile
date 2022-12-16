all: \
	darwin/bridge.h

darwin/bridge.h: bridge.mjs

%.h: %.js
	xxd -i $*.js > $@

%.js: %.mjs
	npx esbuild $*.mjs --bundle --log-level=error --outfile=$@
