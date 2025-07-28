#include <stdio.h>

#include "all_structures.h"

void set_false(grep_flags *gf) {
  gf->flag_e = false;
  gf->flag_i = false;
  gf->flag_v = false;
  gf->flag_c = false;
  gf->flag_l = false;
  gf->flag_n = false;
  gf->flag_h = false;
  gf->flag_s = false;
  gf->flag_f = false;
  gf->flag_o = false;
  gf->cnt_e = 0;
  gf->cnt_f = 0;
}

void test_out(grep_flags gf, char *s, char *f_files, char *input_files,
              int cnt_files) {
  printf("s = %s\n", s);
  printf("f_files = %s\n", f_files);
  printf("%d: input_files = %s\n", cnt_files, input_files);

  printf("flag_e = %d\n", gf.flag_e);
  printf("flag_i = %d\n", gf.flag_i);
  printf("flag_v = %d\n", gf.flag_v);
  printf("flag_c = %d\n", gf.flag_c);
  printf("flag_l = %d\n", gf.flag_l);
  printf("flag_n = %d\n", gf.flag_n);
  printf("flag_h = %d\n", gf.flag_h);
  printf("flag_s = %d\n", gf.flag_s);
  printf("flag_f = %d\n", gf.flag_f);
  printf("flag_o = %d\n", gf.flag_o);
}