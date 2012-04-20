EXAMPLES_DIR := ./examples
EXAMPLES_OUT_DIR := ./examples-processed
EXAMPLES_IN := $(wildcard $(EXAMPLES_DIR)/*.js)
EXAMPLES_OUT := $(patsubst $(EXAMPLES_DIR)/%.js,$(EXAMPLES_OUT_DIR)/%.js,$(EXAMPLES_IN))

COMPILER := macnjs

tests: $(EXAMPLES_OUT_DIR)/ $(EXAMPLES_OUT)

$(EXAMPLES_OUT_DIR)/%.js: $(EXAMPLES_DIR)/%.js
	$(COMPILER) $^ > $@

%/:
	mkdir -p $@

clean:
	rm -rf $(EXAMPLES_OUT_DIR)

.PHONY: tests clean
