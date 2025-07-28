#ifndef SRC_GREP_ALL_STRUCTURES_H_
#define SRC_GREP_ALL_STRUCTURES_H_

#define SMALL_SIZE 4096
#define BIG_SIZE 16384

typedef enum bool { false, true } bool;
typedef struct grep_flags {
  bool flag_e, flag_i, flag_v, flag_c, flag_l;
  bool flag_n, flag_h, flag_s, flag_f, flag_o;
  int cnt_e, cnt_f;
} grep_flags;

void set_false(grep_flags *gf);
void test_out(grep_flags gf, char *s, char *f_files, char *input_files,
              int cnt_files);

#endif // SRC_GREP_ALL_STRUCTURES_H_
