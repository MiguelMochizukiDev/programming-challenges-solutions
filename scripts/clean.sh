#!/usr/bin/env sh
set -e
. "$(dirname "$0")/_common.sh"

print_help() {
  printf "Usage: make clean -- [--chapter pcXX] [--num pcXXXX] [--lang c|cpp|java|python|all]\n"
}

parse_args "$@"
printf "${BLUE}[INFO] Cleaning: chapter='%s' num='%s' lang='%s'${NC}\n" "$chapter" "$num" "$lang"

cleaned=0

clean_problem() {
  num_dir="$1"

  try_rm() {
    if [ -d "$1" ]; then
      rm -rf "$1"
      printf "${GREEN}[OK] Cleaned: %s${NC}\n" "$1"
      cleaned=1
    fi
  }

  if [ "$lang" = all ] || [ "$lang" = c ]; then
    try_rm "$num_dir/c/bin"
  fi

  if [ "$lang" = all ] || [ "$lang" = cpp ]; then
    try_rm "$num_dir/cpp/bin"
  fi

  if [ "$lang" = all ] || [ "$lang" = java ]; then
    try_rm "$num_dir/java/bin"
  fi

  if [ "$lang" = all ] || [ "$lang" = python ]; then
    try_rm "$num_dir/python/__pycache__"
  fi
}

each_problem clean_problem

if [ "$cleaned" -eq 0 ]; then
  printf "${YELLOW}[WARN] Nothing matched the provided filters.${NC}\n"
fi