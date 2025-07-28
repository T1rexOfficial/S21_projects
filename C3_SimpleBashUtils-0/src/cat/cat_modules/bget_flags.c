#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "all_structures.h"
#include "bget_flags.h"

void get_flags(cat_flags *cf, int argc, char **argv) {
  int res, opt_id;
  // opterr = 0;
  const struct option l_opt[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
  };
  while ((res = getopt_long(argc, argv, "+bensvtET", l_opt, &opt_id)) != -1) {
    switch (res) {
    case 'b': {
      cf->flag_b = 1;
      break;
    }
    case 'e': {
      cf->flag_e = 1;
      cf->flag_v = 1;
      break;
    }
    case 'n': {
      cf->flag_n = 1;
      break;
    }
    case 's': {
      cf->flag_s = 1;
      break;
    }
    case 'v': {
      cf->flag_v = 1;
      break;
    }
    case 't': {
      cf->flag_t = 1;
      cf->flag_v = 1;
      break;
    }
    case 'E': {
      cf->flag_e = 1;
      break;
    }
    case 'T': {
      cf->flag_t = 1;
      break;
    }
    default: {
      // fprintf(stderr, "%s: illegal option %s\n", argv[0], argv[opt_id]);
      fprintf(stderr, "usage: cat [-benstuv] [file ...]");
      exit(1);
    }
    }
  }
}
