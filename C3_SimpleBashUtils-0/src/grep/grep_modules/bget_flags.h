#ifndef SRC_GREP_BGET_FLAGS_H_
#define SRC_GREP_BGET_FLAGS_H_

void make_upd(int *need_cnt, char need_upd[], char **argv, char symbol, int *i,
              int *j, int n);
void get_flags(grep_flags *gf, int argc, char **argv, char s[], char f_files[]);
void parse_argv(grep_flags gf, int argc, char **argv, char s[],
                char input_files[], int *cnt_files);

#endif // SRC_GREP_BGET_FLAGS_H_
