#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "all_structures.h"
#include "bget_flags.h"

void make_upd(int *need_cnt, char need_upd[], char **argv, char symbol, int *i,
              int *j, int n) {
  (*need_cnt)++;
  strcat(need_upd, ((*need_cnt) > 1) ? "|" : "");
  if ((*j) != n - 1) {
    strcat(need_upd, (strchr(argv[(*i)], symbol) + 1));
    (*j) = n;
  } else {
    strcat(need_upd, argv[++(*i)]);
  }
}

void get_flags(grep_flags *gf, int argc, char **argv, char s[],
               char f_files[]) {
  bool incorrect_input = false;
  char incorrect_c;
  for (int i = 1; (i < argc && !incorrect_input); ++i) {
    if (argv[i][0] == '-') {
      int cur_sz = (int)strlen(argv[i]);
      for (int j = 1; (j < cur_sz && !incorrect_input); ++j) {
        char c = argv[i][j];
        if (c == 'e') {
          make_upd(&(gf->cnt_e), s, argv, 'e', &i, &j, cur_sz);
          gf->flag_e = 1;
        } else if (c == 'i') {
          gf->flag_i = 1;
        } else if (c == 'v') {
          gf->flag_v = 1;
        } else if (c == 'c') {
          gf->flag_c = 1;
        } else if (c == 'l') {
          gf->flag_l = 1;
        } else if (c == 'n') {
          gf->flag_n = 1;
        } else if (c == 'h') {
          gf->flag_h = 1;
        } else if (c == 's') {
          gf->flag_s = 1;
        } else if (c == 'f') {
          make_upd(&(gf->cnt_f), f_files, argv, 'f', &i, &j, cur_sz);
          gf->flag_f = 1;
        } else if (c == 'o') {
          gf->flag_o = 1;
        } else {
          incorrect_input = true;
          incorrect_c = c;
        }
      }
    }
  }
  if (incorrect_input) {
    fprintf(stderr, "s21_grep: illegal option -- %c", incorrect_c);
    exit(1);
  }
}

void parse_argv(grep_flags gf, int argc, char **argv, char s[],
                char input_files[], int *cnt_files) {
  bool get_temp = false;

  if (gf.cnt_e || gf.cnt_f)
    get_temp = true;

  for (int i = 1; i < argc; ++i) {
    bool prev_strchr = (argv[i - 1][0] == '-');

    int prev_size = (int)strlen(argv[i - 1]);
    char *get_e = strchr(argv[i - 1], 'e');
    char *get_f = strchr(argv[i - 1], 'f');
    bool check_e = (get_e && ((int)(get_e - argv[i - 1] + 1) == prev_size));
    bool check_f = (get_f && ((int)(get_f - argv[i - 1] + 1) == prev_size));

    prev_strchr &= (check_e || check_f);
    bool isFile = ((gf.cnt_e || gf.cnt_f) ? (!prev_strchr ? 1 : 0) : 1);

    if (argv[i][0] != '-') {
      if (!get_temp) {
        strcat(s, argv[i]);
        get_temp = true;
      } else if (isFile) {
        (*cnt_files)++;
        strcat(input_files, ((*cnt_files) > 1) ? "|" : "");
        strcat(input_files, argv[i]);
      }
    }
  }
}