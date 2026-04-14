"""
pc110204
uva843
"""

import sys
from functools import lru_cache


def pattern_of(word):
    first = {}
    next_id = 0
    out = []
    for ch in word:
        if ch not in first:
            first[ch] = next_id
            next_id += 1
        out.append(chr(ord('a') + first[ch]))
    return ''.join(out)


def state_key(idx, to_plain, to_enc):
    return (idx, tuple(to_plain), tuple(to_enc))


def solve_line(line, dict_by_len):
    words = line.split()
    patterns = [pattern_of(w) for w in words]
    order = list(range(len(words)))
    order.sort(key=lambda i: len(dict_by_len[len(words[i])]))

    to_plain = [-1] * 26
    to_enc = [-1] * 26
    failed = set()

    def solve_top_down(idx):
        if idx == len(order):
            return True

        key = state_key(idx, to_plain, to_enc)
        if key in failed:
            return False

        widx = order[idx]
        enc_word = words[widx]
        enc_pattern = patterns[widx]

        for cand in dict_by_len[len(enc_word)]:
            if pattern_of(cand) != enc_pattern:
                continue

            ok = True
            for e_ch, p_ch in zip(enc_word, cand):
                e = ord(e_ch) - 97
                p = ord(p_ch) - 97
                if (to_plain[e] != -1 and to_plain[e] != p) or (to_enc[p] != -1 and to_enc[p] != e):
                    ok = False
                    break
            if not ok:
                continue

            changed_plain = []
            changed_enc = []
            for e_ch, p_ch in zip(enc_word, cand):
                e = ord(e_ch) - 97
                p = ord(p_ch) - 97
                if to_plain[e] == -1:
                    to_plain[e] = p
                    changed_plain.append(e)
                if to_enc[p] == -1:
                    to_enc[p] = e
                    changed_enc.append(p)

            if solve_top_down(idx + 1):
                return True

            for e in changed_plain:
                to_plain[e] = -1
            for p in changed_enc:
                to_enc[p] = -1

        failed.add(key)
        return False

    if solve_top_down(0):
        out = []
        for ch in line:
            if ch == ' ':
                out.append(' ')
            else:
                m = to_plain[ord(ch) - 97]
                out.append('*' if m == -1 else chr(97 + m))
        return ''.join(out)

    return ''.join('*' if ch != ' ' else ' ' for ch in line)


def main():
    data = sys.stdin.read().splitlines()
    if not data:
        return

    n = int(data[0].strip())
    dict_by_len = [[] for _ in range(17)]

    idx = 1
    for _ in range(n):
        w = data[idx].strip()
        dict_by_len[len(w)].append(w)
        idx += 1

    out = []
    for i in range(idx, len(data)):
        out.append(solve_line(data[i], dict_by_len))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
