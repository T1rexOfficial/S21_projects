#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "all_structures.h"
#include "do_flags.h"

void do_lc(grep_flags gf, char *file_name, int founded_lines, bool few_files) {
  if (gf.flag_l) {
    if (founded_lines)
      printf("%s\n", file_name);
  } else if (gf.flag_c) {
    if (few_files && !gf.flag_h)
      printf("%s:", file_name);
    printf("%d\n", founded_lines);
  }
}

void s21_grep_with_o(FILE *file, char *file_name, grep_flags gf, char *s,
                     bool few_files) {
  int cflags = REG_EXTENDED;

  if (gf.flag_i)
    cflags |= REG_ICASE;

  const size_t nmatch = 1;
  regmatch_t pmatch[1];
  regex_t reg;

  regcomp(&reg, s, cflags);

  char str[SMALL_SIZE] = {0}, c = '\0', prev_c = '\0';
  int id = 0, line = 0, founded_lines = 0;

  char temp[SMALL_SIZE] = {0};
  int temp_sz = 0;

  do {
    prev_c = c;
    c = fgetc(file);
    if (c == '\n' || c == EOF) {
      line++;

      int status = regexec(&reg, str, nmatch, pmatch, 0);
      bool need_plus = !((status != REG_NOMATCH) ^ (!gf.flag_v));
      need_plus &= (c != EOF || (c == EOF && prev_c != '\n'));
      founded_lines += need_plus;

      int start = -1, finish = -1;
      bool need_while = !(gf.flag_c || gf.flag_l || gf.flag_v);

      while (status != REG_NOMATCH && need_while) {
        start = pmatch[0].rm_so;
        finish = pmatch[0].rm_eo;
        if (few_files && !gf.flag_h)
          printf("%s:", file_name);
        if (gf.flag_n)
          printf("%d:", line);
        for (int i = start; i < finish; ++i)
          printf("%c", str[i]);
        printf("\n");
        for (int i = 0; i < temp_sz; ++i)
          temp[i] = '\0';
        temp_sz = 0;
        for (int i = finish; i < id; ++i)
          temp[temp_sz++] = str[i];
        for (int i = 0; i < id; ++i)
          str[i] = '\0';
        id = temp_sz;
        for (int i = 0; i < id; ++i)
          str[i] = temp[i];
        status = regexec(&reg, str, nmatch, pmatch, 0);
      }
      for (int i = 0; i < id; ++i)
        str[i] = '\0';
      id = 0;
    } else {
      str[id++] = c;
    }
  } while (c != EOF);
  do_lc(gf, file_name, founded_lines, few_files);
  regfree(&reg);
}

void s21_grep_without_o(FILE *file, char *file_name, grep_flags gf, char *s,
                        bool few_files) {
  int cflags = REG_EXTENDED;

  if (gf.flag_i)
    cflags |= REG_ICASE;

  const size_t nmatch = 1;
  regmatch_t pmatch[1];
  regex_t reg;

  regcomp(&reg, s, cflags);

  char str[SMALL_SIZE] = {0}, c = '\0', prev_c = '\0';
  int id = 0, line = 0, founded_lines = 0;

  do {
    prev_c = c;
    c = fgetc(file);
    if (c == '\n' || c == EOF) {
      line++;
      int status = regexec(&reg, str, nmatch, pmatch, 0);
      bool need_out = !((status != REG_NOMATCH) ^ (!gf.flag_v));
      need_out &= (c != EOF || (c == EOF && prev_c != '\n'));
      founded_lines += need_out;
      need_out &= !(gf.flag_c || gf.flag_l);
      if (need_out) {
        if (few_files && !gf.flag_h)
          printf("%s:", file_name);
        if (gf.flag_n)
          printf("%d:", line);
        printf("%s\n", str);
        // printf((c != EOF) ? "\n" : (prev_c != '\n' ? "\n" : ""));
      }
      for (int i = 0; i < id; ++i)
        str[i] = '\0';
      id = 0;
    } else {
      str[id++] = c;
    }
  } while (c != EOF);
  do_lc(gf, file_name, founded_lines, few_files);
  regfree(&reg);
}

void prepare_s21_grep(grep_flags gf, char *s, char *f_files, char *input_files,
                      int cnt_files) {
  bool few_files = (cnt_files > 1);

  FILE *file;
  char *istr;

  bool f_error = false;

  if (gf.flag_f) {
    istr = strtok(f_files, "|");

    int n = (int)strlen(s);

    while (istr != NULL && !f_error) {
      file = fopen(istr, "r");
      if (file) {
        if (n)
          s[n++] = '|';
        char c = fgetc(file);
        while (c != EOF) {
          s[n++] = (c != '\n' ? c : '|');
          c = fgetc(file);
        }
        fclose(file);
      } else {
        fprintf(stderr, "grep: %s: No such file or directory\n", istr);
        f_error = true;
      }
      istr = strtok(NULL, "|");
    }
  }

  // test_out(gf, s, f_files, input_files, cnt_files);

  istr = strtok(input_files, "|");

  while (istr != NULL && !f_error) {
    file = fopen(istr, "r");
    if (file) {
      if (gf.flag_o)
        s21_grep_with_o(file, istr, gf, s, few_files);
      else
        s21_grep_without_o(file, istr, gf, s, few_files);
      fclose(file);
    } else if (!gf.flag_s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", istr);
    }
    istr = strtok(NULL, "|");
  }
}