SHELL := /bin/sh
MAKEFILE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

.DEFAULT_GOAL := build
.PHONY: build clean help

help:
	@printf "Usage:\n"
	@printf "  make build -- [--chapter pcXX] [--num pcXXXX] [--lang c|cpp|java|python|all]\n"
	@printf "  make clean -- [--chapter pcXX] [--num pcXXXX] [--lang c|cpp|java|python|all]\n"
	@printf "  make help\n\n"
	@printf "Notes:\n"
	@printf "  - Arguments must be passed after '--'.\n"
	@printf "  - If no arguments are provided, all solutions are built.\n"
	@printf "  - Artifacts are created in each language folder under 'bin/'.\n"
	@printf "  - Python uses dry-run compilation to generate __pycache__.\n"

build:
	@sh $(MAKEFILE_DIR)/build.sh $(filter-out $@,$(MAKECMDGOALS))

clean:
	@sh $(MAKEFILE_DIR)/clean.sh $(filter-out $@,$(MAKECMDGOALS))

%:
	@: