#ifndef SRC_BACKEND_VIEWER_BACK_H_
#define SRC_BACKEND_VIEWER_BACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2048

typedef struct s21_pair_unsigned_int {
  unsigned int first, second;
} puui;

typedef struct s21_xyz_structure {
  float x, y, z;
} p3f;

typedef struct facets {
  puui *f;
  int sz;
} facets_t;

typedef struct vertexes {
  p3f *v;
  int sz;
  float max_len;
} vertexes_t;

int isDigit(char c);

void convert_string_to_number(char str[], int *pos, char ans[]);
int get_cnt_char_obj(const char *path, char c);
int get_cnt_num_in_line_obj(const char *path, char c);

void init_vertex(vertexes_t *vv, int cnt_v);
void clear_vertex(vertexes_t *vv);
void init_facets(facets_t *ff, int cnt_l_f);
void clear_facets(facets_t *ff);

void read_obj(const char *path, vertexes_t *vv, facets_t *ff);

void scale(vertexes_t *vv, float multiplier);
void shift(vertexes_t *vv, float dx, float dy, float dz);
p3f calc_center(vertexes_t *vv);
void rotate_x(vertexes_t *vv, float angle);
void rotate_y(vertexes_t *vv, float angle);
void rotate_z(vertexes_t *vv, float angle);
void rotate(vertexes_t *vv, char axis, float angle);

#endif  // SRC_BACKEND_VIEWER_BACK_H_
