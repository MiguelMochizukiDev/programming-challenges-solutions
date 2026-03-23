#!/usr/bin/env sh
# Sourced by build.sh, clean.sh, and run_test.sh — never executed directly.

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

# Resolve project root based on this file location, so scripts work from any CWD.
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
ROOT_DIR=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)

# Sets $chapter, $num, $lang from CLI arguments.
# Calls print_help (defined by the caller) on --help/-h.
parse_args() {
  chapter=""; num=""; lang="all"
  while [ "$#" -gt 0 ]; do
    case "$1" in
      --chapter=*) chapter="${1#*=}"; shift ;;
      --chapter)   chapter="$2";      shift 2 ;;
      --num=*)     num="${1#*=}";      shift ;;
      --num)       num="$2";           shift 2 ;;
      --lang=*)    lang="${1#*=}";     shift ;;
      --lang)      lang="$2";          shift 2 ;;
      --help|-h)   print_help; exit 0 ;;
      --)          shift ;;
      *) printf "${RED}[ERROR] Unknown argument: %s${NC}\n" "$1"; exit 1 ;;
    esac
  done
  case "$lang" in
    c|cpp|java|python|all) ;;
    *) printf "${RED}[ERROR] Invalid --lang: %s${NC}\n" "$lang"; exit 1 ;;
  esac
}

# Iterates over matched chapter/problem directories, calling $1 with (num_dir, num_name).
each_problem() {
  callback="$1"
  for chapter_dir in "$ROOT_DIR"/chapters/pc*; do
    [ -d "$chapter_dir" ] || continue
    if [ -n "$chapter" ] && [ "$(basename "$chapter_dir")" != "$chapter" ]; then
      continue
    fi
    for num_dir in "$chapter_dir"/pc*; do
      [ -d "$num_dir" ] || continue
      num_name=$(basename "$num_dir")
      if [ -n "$num" ] && [ "$num_name" != "$num" ]; then
        continue
      fi
      "$callback" "$num_dir" "$num_name"
    done
  done
}