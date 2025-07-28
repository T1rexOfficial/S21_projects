#ifndef SRC_CAT_DO_FLAGS_H_
#define SRC_CAT_DO_FLAGS_H_

void do_flags(cat_flags *cf, int argc, char **argv);
void s21_cat(FILE *file, cat_flags *cf);
void try_out_line_number(cat_flags *cf, bool no_empty, int *line_cnt);
void out_end_of_line(cat_flags *cf);
void try_flag_s(cat_flags *cf, bool no_empty, bool first_line, bool *merged,
                int *line_cnt);
void try_flag_v(char file_c);

#endif // SRC_CAT_DO_FLAGS_H_
