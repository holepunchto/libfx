all: image1.h

%.h: %.rgba
	xxd -i $< > $@

%.rgba: %.jpg
	magick convert $< -depth 8 rgba:$@
