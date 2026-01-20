# ========================
# Project configuration
# ========================
BUILD_DIR := cmake-build-debug
LABS := 1 2 3 4 5 6

# ========================
# Meta targets
# ========================

.PHONY: help
help:
	@echo "Targets:"
	@echo "  make build        - Configure and build all labs"
	@echo "  make clean        - Remove build directory"
	@echo "  make lab<N>       - Run Laboratory N (1-6)"
	@echo "  make rebuild      - Clean and rebuild everything"

# ========================
# Build targets
# ========================
.PHONY: build
build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

.PHONY: rebuild
rebuild: clean build

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# ========================
# Run targets
# ========================
$(foreach N,$(LABS),$(eval \
lab$(N): ;\
	@echo "Running Laboratory $(N) ..." ;\
	if [ ! -f $(BUILD_DIR)/Laboratory$(N)/lab$(N) ]; then \
		echo "lab$(N) not built. Run 'make build' first."; \
		exit 1; \
	fi ;\
	./$(BUILD_DIR)/Laboratory$(N)/lab$(N) \
))