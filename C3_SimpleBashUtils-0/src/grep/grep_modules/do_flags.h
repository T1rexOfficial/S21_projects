#ifndef SRC_GREP_DO_FLAGS_H_
#define SRC_GREP_DO_FLAGS_H_

void do_lc(grep_flags gf, char *file_name, int founded_lines, bool few_files);
void s21_grep_with_o(FILE *file, char *file_name, grep_flags gf, char *s,
                     bool few_files);
void s21_grep_without_o(FILE *file, char *file_name, grep_flags gf, char *s,
                        bool few_files);
void prepare_s21_grep(grep_flags gf, char *s, char *f_files, char *input_files,
                      int cnt_files);

#endif // SRC_GREP_DO_FLAGS_H_
