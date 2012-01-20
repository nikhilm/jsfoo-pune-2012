OPTIONS=-s slides.style,manni -b1 --smart-quotes=1 --real-footnotes

all: code slides.pdf

code:
	$(shell for dir in `find . -type d -d 1`; do cd $$dir; node-waf configure build; cd ..; done)

slides.pdf: slides.rst slides.style
	rst2pdf $(OPTIONS) slides.rst

.PHONY: clean
clean:
	rm -f slides.pdf
	find . -name 'build' -type d | xargs rm -rf
