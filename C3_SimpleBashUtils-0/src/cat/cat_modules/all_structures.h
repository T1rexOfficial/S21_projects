#ifndef SRC_CAT_ALL_STRUCTURES_H_
#define SRC_CAT_ALL_STRUCTURES_H_

typedef enum bool { false, true } bool;
typedef struct cat_flags {
  bool flag_b, flag_e, flag_n, flag_s, flag_t, flag_v;
} cat_flags;

void set_false(cat_flags *cf);

#endif // SRC_CAT_ALL_STRUCTURES_H_
