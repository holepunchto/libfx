all: \
	edge/bridge.h \
	webkit/bridge.h

edge/bridge.h: bridge.mjs
webkit/bridge.h: bridge.mjs

%.h: %.js
	xxd -i $*.js > $@

%.js: %.mjs
	npx esbuild $*.mjs --bundle --log-level=error --outfile=$@
