#include <stdio.h>

#include "all_structures.h"

void set_false(cat_flags *cf) {
  cf->flag_b = false;
  cf->flag_e = false;
  cf->flag_n = false;
  cf->flag_s = false;
  cf->flag_t = false;
  cf->flag_v = false;
}
