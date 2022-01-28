MARKDOWN := pandoc --from gfm --to html --standalone --shift-heading-level-by=-1

IN_DIR := .
OUT_DIR := .

CSS := style.css
ALL_SRC := $(wildcard $(IN_DIR)/*.md)
ALL_OUT := $(patsubst $(IN_DIR)/%, $(OUT_DIR)/%, $(ALL_SRC:.md=.html))
MD_OPT := -t html5 --toc -c $(CSS)

.PHONY: clean

all: $(OUT_DIR) $(CSS) $(ALL_OUT)
	

clean:
	rm -rf $(ALL_OUT)
	
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.css: $(IN_DIR)/%.css
	cp -f $< $@

$(OUT_DIR)/%.html: $(IN_DIR)/%.md
	$(MARKDOWN) $(MD_OPT) $< --output $@