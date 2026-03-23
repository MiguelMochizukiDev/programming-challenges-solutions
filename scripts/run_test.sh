#!/usr/bin/env sh
set -e
. "$(dirname "$0")/_common.sh"

print_help() {
  printf "Usage:\n"
  printf "  ./run_test.sh [--chapter pcXX] [--num pcXXXX] [--lang c|cpp|java|python|all]\n"
  printf "  ./run_test.sh --help\n\n"
  printf "Behavior:\n"
  printf "  - Compiles selected solutions first (if needed).\n"
  printf "  - Runs each solution with sample_data/input.txt.\n"
  printf "  - Compares output to sample_data/output.txt.\n"
}

parse_args "$@"

printf "${BLUE}[INFO] Preparing binaries/classes...${NC}\n"
set -- --lang "$lang"
[ -n "$chapter" ] && set -- --chapter "$chapter" "$@"
[ -n "$num" ]     && set -- --num "$num" "$@"
sh "$(dirname "$0")/build.sh" "$@"

pass=0; fail=0; skip=0

run_one() {
  language="$1"; num_dir="$2"; num_name="$3"
  input="$num_dir/sample_data/input.txt"
  expected="$num_dir/sample_data/output.txt"

  if [ ! -f "$input" ] || [ ! -f "$expected" ]; then
    printf "${YELLOW}[SKIP] %s/%s missing sample_data files${NC}\n" "$num_name" "$language"
    skip=$((skip + 1)); return
  fi

  tmp=$(mktemp)

  case "$language" in
    c|cpp)
      exe="$num_dir/$language/bin/$num_name.o"
      if [ ! -x "$exe" ]; then
        printf "${YELLOW}[SKIP] Missing binary: %s${NC}\n" "$exe"
        rm -f "$tmp"; skip=$((skip + 1)); return
      fi
      "$exe" < "$input" > "$tmp"
      ;;
    java)
      src=$(find "$num_dir/java" -maxdepth 1 -name '*.java' 2>/dev/null | head -n 1)
      if [ -z "$src" ]; then
        printf "${YELLOW}[SKIP] Missing Java source in %s/java${NC}\n" "$num_dir"
        rm -f "$tmp"; skip=$((skip + 1)); return
      fi
      class_name=$(basename "$src" .java)
      pkg=$(sed -n 's/^[[:space:]]*package[[:space:]]\+\([^;]*\);.*/\1/p' "$src" | head -n 1 | tr -d '[:space:]')
      if [ -n "$pkg" ]; then
        fqcn="$pkg.$class_name"
        class_file="$num_dir/java/bin/$(printf "%s" "$fqcn" | tr '.' '/').class"
      else
        fqcn="$class_name"
        class_file="$num_dir/java/bin/$class_name.class"
      fi
      if [ ! -f "$class_file" ]; then
        printf "${YELLOW}[SKIP] Missing class file for %s${NC}\n" "$fqcn"
        rm -f "$tmp"; skip=$((skip + 1)); return
      fi
      java -cp "$num_dir/java/bin" "$fqcn" < "$input" > "$tmp"
      ;;
    python)
      src=$(find "$num_dir/python" -maxdepth 1 -name '*.py' 2>/dev/null | head -n 1)
      if [ -z "$src" ]; then
        printf "${YELLOW}[SKIP] Missing Python source in %s/python${NC}\n" "$num_dir"
        rm -f "$tmp"; skip=$((skip + 1)); return
      fi
      python3 "$src" < "$input" > "$tmp"
      ;;
  esac

  if diff -u "$expected" "$tmp" >/dev/null 2>&1; then
    printf "${GREEN}[PASS] %s/%s${NC}\n" "$num_name" "$language"
    pass=$((pass + 1))
  else
    printf "${RED}[FAIL] %s/%s${NC}\n" "$num_name" "$language"
    diff -u "$expected" "$tmp" || true
    fail=$((fail + 1))
  fi

  rm -f "$tmp"
}

test_problem() {
  num_dir="$1"; num_name="$2"
  if [ "$lang" = all ] || [ "$lang" = c ]; then
    if [ -d "$num_dir/c" ]; then
      run_one c "$num_dir" "$num_name"
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = cpp ]; then
    if [ -d "$num_dir/cpp" ]; then
      run_one cpp "$num_dir" "$num_name"
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = java ]; then
    if [ -d "$num_dir/java" ]; then
      run_one java "$num_dir" "$num_name"
    fi
  fi

  if [ "$lang" = all ] || [ "$lang" = python ]; then
    if [ -d "$num_dir/python" ]; then
      run_one python "$num_dir" "$num_name"
    fi
  fi
}

each_problem test_problem

printf "\n${BLUE}[SUMMARY] pass=%d fail=%d skip=%d${NC}\n" "$pass" "$fail" "$skip"
[ "$fail" -eq 0 ] || exit 1