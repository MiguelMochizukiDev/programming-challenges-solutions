#!/usr/bin/env sh
set -e
. "$(dirname "$0")/_common.sh"

print_help() {
  printf "Usage: make build -- [--chapter pcXX] [--num pcXXXX] [--lang c|cpp|java|python|all]\n"
}

parse_args "$@"
printf "${BLUE}[INFO] Building: chapter='%s' num='%s' lang='%s'${NC}\n" "$chapter" "$num" "$lang"

built=0

build_problem() {
  num_dir="$1"; num_name="$2"

  if [ "$lang" = all ] || [ "$lang" = c ]; then
    src=$(find "$num_dir/c" -maxdepth 1 -type f -name '*.c' 2>/dev/null | head -n 1)
    if [ -n "$src" ]; then
      mkdir -p "$num_dir/c/bin"
      out="$num_dir/c/bin/$num_name.o"
      if [ ! -f "$out" ] || [ "$src" -nt "$out" ]; then
        gcc -std=c11 -O2 "$src" -o "$out"
        printf "${GREEN}[OK] C built: %s${NC}\n" "$out"
      else
        printf "${YELLOW}[SKIP] C up-to-date: %s${NC}\n" "$out"
      fi
      built=1
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = cpp ]; then
    src=$(find "$num_dir/cpp" -maxdepth 1 -type f -name '*.cpp' 2>/dev/null | head -n 1)
    if [ -n "$src" ]; then
      mkdir -p "$num_dir/cpp/bin"
      out="$num_dir/cpp/bin/$num_name.o"
      if [ ! -f "$out" ] || [ "$src" -nt "$out" ]; then
        g++ -std=c++17 -O2 "$src" -o "$out"
        printf "${GREEN}[OK] C++ built: %s${NC}\n" "$out"
      else
        printf "${YELLOW}[SKIP] C++ up-to-date: %s${NC}\n" "$out"
      fi
      built=1
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = java ]; then
    src=$(find "$num_dir/java" -maxdepth 1 -type f -name '*.java' 2>/dev/null | head -n 1)
    if [ -n "$src" ]; then
      mkdir -p "$num_dir/java/bin"
      class_name=$(basename "$src" .java)
      pkg=$(sed -n 's/^[[:space:]]*package[[:space:]]\+\([^;]*\);.*/\1/p' "$src" | head -n 1 | tr -d '[:space:]')
      if [ -n "$pkg" ]; then
        fqcn="$pkg.$class_name"
        out="$num_dir/java/bin/$(printf "%s" "$fqcn" | tr '.' '/').class"
      else
        fqcn="$class_name"
        out="$num_dir/java/bin/$class_name.class"
      fi
      if [ ! -f "$out" ] || [ "$src" -nt "$out" ]; then
        javac -d "$num_dir/java/bin" "$src"
        printf "${GREEN}[OK] Java built: %s${NC}\n" "$out"
      else
        printf "${YELLOW}[SKIP] Java up-to-date: %s${NC}\n" "$out"
      fi
      built=1
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = python ]; then
    src=$(find "$num_dir/python" -maxdepth 1 -type f -name '*.py' 2>/dev/null | head -n 1)
    if [ -n "$src" ]; then
      python3 -m py_compile "$src"
      printf "${GREEN}[OK] Python dry-run compiled: %s${NC}\n" "$src"
      built=1
    fi
  fi
}

each_problem build_problem

if [ "$built" -eq 0 ]; then
  printf "${YELLOW}[WARN] Nothing matched the provided filters.${NC}\n"
fi