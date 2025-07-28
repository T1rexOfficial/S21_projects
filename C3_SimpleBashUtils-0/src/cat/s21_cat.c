// By Vulpixta
#include <stdio.h>

#include "cat_modules/all_structures.h"
#include "cat_modules/bget_flags.h"
#include "cat_modules/do_flags.h"

int main(int argc, char **argv) {
  cat_flags cf;
  set_false(&cf);
  get_flags(&cf, argc, argv);
  do_flags(&cf, argc, argv);
  return 0;
}
