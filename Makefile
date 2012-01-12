OPTIONS=-s slides.style,manni -b1 --smart-quotes=1 --real-footnotes
slides.pdf: slides.rst slides.style
	rst2pdf $(OPTIONS) slides.rst 

.PHONY: clean
clean:
	rm slides.pdf
