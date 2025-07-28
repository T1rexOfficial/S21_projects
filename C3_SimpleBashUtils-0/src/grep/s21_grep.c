// By Vulpixta
#include <stdio.h>

#include "grep_modules/all_structures.h"
#include "grep_modules/bget_flags.h"
#include "grep_modules/do_flags.h"

int main(int argc, char **argv) {
  grep_flags gf;
  set_false(&gf);

  char s[SMALL_SIZE] = {0}, f_files[SMALL_SIZE] = {0},
       input_files[BIG_SIZE] = {0};
  get_flags(&gf, argc, argv, s, f_files);

  int cnt_files = 0;
  parse_argv(gf, argc, argv, s, input_files, &cnt_files);

  prepare_s21_grep(gf, s, f_files, input_files, cnt_files);
  return 0;
}
