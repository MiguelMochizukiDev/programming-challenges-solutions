/**
 * pc110204
 * uva843
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT 1000
#define MAX_WORD_LEN 17
#define MAX_LINE 256
#define MAX_WORDS 128
#define MAX_CAND 1000
#define FAIL_TABLE_SIZE 131071

typedef struct {
	char words[MAX_DICT][MAX_WORD_LEN];
	int size;
} WordList;

typedef struct FailNode {
	char *key;
	struct FailNode *next;
} FailNode;

WordList dict_by_len[17];
FailNode *fail_table[FAIL_TABLE_SIZE];

unsigned long hash_str(const char *s) {
	unsigned long h = 5381;
	while (*s) {
		h = ((h << 5) + h) + (unsigned char)(*s);
		s++;
	}
	return h;
}

int fail_contains(const char *key) {
	unsigned long idx = hash_str(key) % FAIL_TABLE_SIZE;
	FailNode *cur = fail_table[idx];
	while (cur != NULL) {
		if (strcmp(cur->key, key) == 0) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

void fail_insert(const char *key) {
	unsigned long idx = hash_str(key) % FAIL_TABLE_SIZE;
	FailNode *node = (FailNode *)malloc(sizeof(FailNode));
	node->key = (char *)malloc(strlen(key) + 1);
	strcpy(node->key, key);
	node->next = fail_table[idx];
	fail_table[idx] = node;
}

void clear_fail_table(void) {
	for (int i = 0; i < FAIL_TABLE_SIZE; i++) {
		FailNode *cur = fail_table[i];
		while (cur != NULL) {
			FailNode *next = cur->next;
			free(cur->key);
			free(cur);
			cur = next;
		}
		fail_table[i] = NULL;
	}
}

void build_pattern(const char *word, char *out) {
	int first[26];
	for (int i = 0; i < 26; i++) first[i] = -1;
	int next_id = 0;
	int len = (int)strlen(word);

	for (int i = 0; i < len; i++) {
		int ch = word[i] - 'a';
		if (first[ch] == -1) {
			first[ch] = next_id++;
		}
		out[i] = (char)('a' + first[ch]);
	}
	out[len] = '\0';
}

int fits_mapping(const char *enc, const char *plain, int to_plain[26], int to_enc[26]) {
	int len = (int)strlen(enc);
	for (int i = 0; i < len; i++) {
		int e = enc[i] - 'a';
		int p = plain[i] - 'a';
		if ((to_plain[e] != -1 && to_plain[e] != p) || (to_enc[p] != -1 && to_enc[p] != e)) {
			return 0;
		}
	}
	return 1;
}

void apply_mapping(const char *enc, const char *plain, int to_plain[26], int to_enc[26], int changes[32], int *change_count) {
	int len = (int)strlen(enc);
	*change_count = 0;
	for (int i = 0; i < len; i++) {
		int e = enc[i] - 'a';
		int p = plain[i] - 'a';
		if (to_plain[e] == -1) {
			to_plain[e] = p;
			changes[(*change_count)++] = e;
		}
		if (to_enc[p] == -1) {
			to_enc[p] = e;
			changes[(*change_count)++] = 26 + p;
		}
	}
}

void rollback_mapping(int to_plain[26], int to_enc[26], int changes[32], int change_count) {
	for (int i = 0; i < change_count; i++) {
		int v = changes[i];
		if (v < 26) {
			to_plain[v] = -1;
		} else {
			to_enc[v - 26] = -1;
		}
	}
}

void build_state_key(int idx, int to_plain[26], int to_enc[26], char *key) {
	char *p = key;
	p += sprintf(p, "%d|", idx);
	for (int i = 0; i < 26; i++) {
		p += sprintf(p, "%02d", to_plain[i] + 1);
	}
	*p++ = '|';
	for (int i = 0; i < 26; i++) {
		p += sprintf(p, "%02d", to_enc[i] + 1);
	}
	*p = '\0';
}

int solve_topdown(
	char words[MAX_WORDS][MAX_WORD_LEN],
	char patterns[MAX_WORDS][MAX_WORD_LEN],
	int order[MAX_WORDS],
	int word_count,
	int idx,
	int to_plain[26],
	int to_enc[26]
) {
	if (idx == word_count) {
		return 1;
	}

	char key[256];
	build_state_key(idx, to_plain, to_enc, key);
	if (fail_contains(key)) {
		return 0;
	}

	int w_idx = order[idx];
	char *enc_word = words[w_idx];
	char *enc_pattern = patterns[w_idx];
	int len = (int)strlen(enc_word);
	WordList *bucket = &dict_by_len[len];

	for (int i = 0; i < bucket->size; i++) {
		char *cand = bucket->words[i];
		char cand_pattern[MAX_WORD_LEN];
		build_pattern(cand, cand_pattern);
		if (strcmp(enc_pattern, cand_pattern) != 0) {
			continue;
		}

		if (!fits_mapping(enc_word, cand, to_plain, to_enc)) {
			continue;
		}

		int changes[32];
		int change_count;
		apply_mapping(enc_word, cand, to_plain, to_enc, changes, &change_count);

		if (solve_topdown(words, patterns, order, word_count, idx + 1, to_plain, to_enc)) {
			return 1;
		}

		rollback_mapping(to_plain, to_enc, changes, change_count);
	}

	fail_insert(key);
	return 0;
}

void decrypt_line(const char *line, int to_plain[26], char *out) {
	int len = (int)strlen(line);
	for (int i = 0; i < len; i++) {
		char ch = line[i];
		if (ch == ' ') {
			out[i] = ' ';
		} else {
			int m = to_plain[ch - 'a'];
			out[i] = (m == -1) ? '*' : (char)('a' + m);
		}
	}
	out[len] = '\0';
}

int main(void) {
	int n;
	char line[MAX_LINE];

	for (int i = 0; i < 17; i++) {
		dict_by_len[i].size = 0;
	}

	if (scanf("%d", &n) != 1) {
		return 0;
	}
	getchar();

	for (int i = 0; i < n; i++) {
		char word[MAX_WORD_LEN];
		if (fgets(word, sizeof(word), stdin) == NULL) {
			return 0;
		}
		word[strcspn(word, "\r\n")] = '\0';
		int len = (int)strlen(word);
		strcpy(dict_by_len[len].words[dict_by_len[len].size++], word);
	}

	while (fgets(line, sizeof(line), stdin) != NULL) {
		line[strcspn(line, "\r\n")] = '\0';

		char words[MAX_WORDS][MAX_WORD_LEN];
		char patterns[MAX_WORDS][MAX_WORD_LEN];
		int word_count = 0;
		int order[MAX_WORDS];

		char temp[MAX_LINE];
		strcpy(temp, line);
		char *tok = strtok(temp, " ");
		while (tok != NULL) {
			strncpy(words[word_count], tok, MAX_WORD_LEN - 1);
			words[word_count][MAX_WORD_LEN - 1] = '\0';
			build_pattern(words[word_count], patterns[word_count]);
			word_count++;
			tok = strtok(NULL, " ");
		}

		for (int i = 0; i < word_count; i++) {
			order[i] = i;
		}

		for (int i = 0; i < word_count; i++) {
			for (int j = i + 1; j < word_count; j++) {
				int li = (int)strlen(words[order[i]]);
				int lj = (int)strlen(words[order[j]]);
				int ci = dict_by_len[li].size;
				int cj = dict_by_len[lj].size;
				if (cj < ci) {
					int t = order[i];
					order[i] = order[j];
					order[j] = t;
				}
			}
		}

		int to_plain[26];
		int to_enc[26];
		for (int i = 0; i < 26; i++) {
			to_plain[i] = -1;
			to_enc[i] = -1;
		}

		clear_fail_table();
		int ok = solve_topdown(words, patterns, order, word_count, 0, to_plain, to_enc);

		char out[MAX_LINE];
		if (ok) {
			decrypt_line(line, to_plain, out);
		} else {
			int len = (int)strlen(line);
			for (int i = 0; i < len; i++) {
				out[i] = (line[i] == ' ') ? ' ' : '*';
			}
			out[len] = '\0';
		}

		printf("%s\n", out);
	}

	clear_fail_table();
	return 0;
}
