# Configuration
LATEX  := pdflatex
TEXSRC := log_standard.tex
OUTPDF := $(TEXSRC:.tex=.pdf)

# Rules
all: $(OUTPDF)

# FIXME: Run latex twice to make sure TOC and other references are updated.
# If it fails the first time, make SHOULD do the right thing and not run again
$(OUTPDF): $(TEXSRC) Makefile
	$(LATEX) $<
	$(LATEX) $<

.PHONY: clean
clean:
	rm -f $(OUTPDF) *.aux *.log *.out *.toc *.synctec.gz
