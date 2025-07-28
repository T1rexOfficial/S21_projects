#include "viewer_back.h"

int isDigit(char c) { return (c >= '0' && c <= '9'); }

void convert_string_to_number(char str[], int *pos, char ans[]) {
  int was_point = 0;
  if (str[*pos] == '-') {
    strcat(ans, "-");
    (*pos)++;
  }
  for (; (*pos) < (int)strlen(str); (*pos)++) {
    if (isDigit(str[*pos]) || (str[(*pos)] == '.' && !was_point)) {
      if (str[(*pos)] == '.') was_point = 1;
      strncat(ans, str + (*pos), 1);
    } else {
      (*pos)--;
      break;
    }
  }
}

int get_cnt_char_obj(const char *path, char c) {
  int cnt = 0;
  char str[MAXN];
  FILE *file = fopen(path, "r");
  while (fgets(str, sizeof(str), file) != NULL) {
    if (str[0] == c && str[1] == ' ') cnt++;
    memset(str, '\0', (int)strlen(str));
  }
  fclose(file);
  return cnt;
}

int get_cnt_num_in_line_obj(const char *path, char c) {
  int cnt = 0;
  char str[MAXN];
  FILE *file = fopen(path, "r");
  while (fgets(str, sizeof(str), file) != NULL) {
    if (str[0] == c && str[1] == ' ') {
      int new_num = 1;
      for (int i = 2; i < (int)strlen(str); ++i) {
        if (str[i] == ' ' && !new_num) {
          new_num = 1;
        } else if (((str[i] == '-' && isDigit(str[i + 1])) ||
                    isDigit(str[i])) &&
                   new_num) {
          new_num = 0;
          char res[MAXN] = {0};
          convert_string_to_number(str, &i, res);
          cnt++;
        }
      }
    }
    memset(str, '\0', (int)strlen(str));
  }
  fclose(file);
  return cnt;
}

void init_vertex(vertexes_t *vv, int cnt_v) {
  vv->sz = 0;
  vv->max_len = 0;
  vv->v = (p3f *)malloc((cnt_v + 1) * sizeof(p3f));
}

void clear_vertex(vertexes_t *vv) { free(vv->v); }

void init_facets(facets_t *ff, int cnt_l_f) {
  ff->sz = 0;
  ff->f = (puui *)malloc((cnt_l_f + 1) * sizeof(puui));
}

void clear_facets(facets_t *ff) {
  if (ff->f != NULL) {
    free(ff->f);
    ff->f = NULL;
  }
}

void read_obj(const char *path, vertexes_t *vv, facets_t *ff) {
  FILE *file;
  char str[MAXN];

  if ((file = fopen(path, "r")) != NULL) {
    int cnt_v = get_cnt_char_obj(path, 'v');
    int cnt_l_f = get_cnt_num_in_line_obj(path, 'f');

    init_vertex(vv, cnt_v);
    init_facets(ff, cnt_l_f);
    while (fgets(str, sizeof(str), file) != NULL) {
      if (str[0] == 'v' && str[1] == ' ') {
        // printf("v_out -----> ");
        int cnt3cur = 0;
        for (int i = 2; i < (int)strlen(str); ++i) {
          if ((str[i] == '-' && isDigit(str[i + 1])) || isDigit(str[i])) {
            char res[MAXN] = {0};
            convert_string_to_number(str, &i, res);
            float num = atof(res);
            cnt3cur++;
            if (cnt3cur == 1) {
              vv->v[vv->sz].x = num;
            } else if (cnt3cur == 2) {
              vv->v[vv->sz].y = num;
            } else if (cnt3cur == 3) {
              vv->v[vv->sz].z = num;
              vv->sz++;
            }
          }
        }
        // printf("\n");
      } else if (str[0] == 'f' && str[1] == ' ') {
        int first_num = 0, cur1 = 0, cur2 = 0, first_flag = 0;
        int new_num = 1;
        for (int i = 2; i < (int)strlen(str); ++i) {
          if (str[i] == ' ' && !new_num) {
            new_num = 1;
          } else if (((str[i] == '-' && isDigit(str[i + 1])) ||
                      isDigit(str[i])) &&
                     new_num) {
            new_num = 0;
            char res[MAXN] = {0};
            convert_string_to_number(str, &i, res);
            int num = atoi(res);
            if (!first_flag) {
              first_num = cur1 = num;
              first_flag = 1;
            } else {
              cur2 = num;
              if (cur1 >= 0)
                ff->f[ff->sz].first = (unsigned int)cur1;
              else
                ff->f[ff->sz].first = (unsigned int)((vv->sz) + cur1 + 1);
              if (cur2 >= 0)
                ff->f[ff->sz++].second = (unsigned int)cur2;
              else
                ff->f[ff->sz++].second = (unsigned int)((vv->sz) + cur2 + 1);
              cur1 = cur2;
            }
          }
        }
        //        ff->f[ff->sz].first = (unsigned int)cur2;
        //        ff->f[ff->sz++].second = (unsigned int)first_num;
        if (cur2 >= 0)
          ff->f[ff->sz].first = (unsigned int)cur2;
        else
          ff->f[ff->sz].first = (unsigned int)((vv->sz) + cur2 + 1);
        if (first_num >= 0)
          ff->f[ff->sz++].second = (unsigned int)first_num;
        else
          ff->f[ff->sz++].second = (unsigned int)((vv->sz) + first_num + 1);
        // printf("\n");
      }
      memset(str, '\0', (int)strlen(str));
    }
    fclose(file);
  } else {
    printf("file path error\n");
  }
}

void scale(vertexes_t *vv, float multiplier) {
  p3f center = calc_center(vv);
  // printf("center = %f %f %f\n", center.x, center.y, center.z);
  for (int i = 0; i < (vv->sz); ++i) {
    vv->v[i].x = (vv->v[i].x - center.x) * multiplier + center.x;
    vv->v[i].y = (vv->v[i].y - center.y) * multiplier + center.y;
    vv->v[i].z = (vv->v[i].z - center.z) * multiplier + center.z;
  }
}

void shift(vertexes_t *vv, float dx, float dy, float dz) {
  for (int i = 0; i < (vv->sz); ++i) {
    vv->v[i].x += dx;
    vv->v[i].y += dy;
    vv->v[i].z += dz;
  }
}

void rotate_x(vertexes_t *vv, float angle) {
  p3f center = calc_center(vv);
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);

  for (int i = 0; i < vv->sz; ++i) {
    float y = vv->v[i].y;
    float z = vv->v[i].z;

    vv->v[i].y =
        (y - center.y) * cos_angle - (z - center.z) * sin_angle + center.y;
    vv->v[i].z =
        (y - center.y) * sin_angle + (z - center.z) * cos_angle + center.z;
  }
}

void rotate_y(vertexes_t *vv, float angle) {
  p3f center = calc_center(vv);
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);

  for (int i = 0; i < vv->sz; ++i) {
    float x = vv->v[i].x;
    float z = vv->v[i].z;

    vv->v[i].x =
        (x - center.x) * cos_angle + (z - center.z) * sin_angle + center.x;
    vv->v[i].z =
        (-x + center.x) * sin_angle + (z - center.z) * cos_angle + center.z;
  }
}

void rotate_z(vertexes_t *vv, float angle) {
  p3f center = calc_center(vv);
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);

  for (int i = 0; i < vv->sz; ++i) {
    float x = vv->v[i].x;
    float y = vv->v[i].y;

    vv->v[i].x =
        (x - center.x) * cos_angle - (y - center.y) * sin_angle + center.x;
    vv->v[i].y =
        (x - center.x) * sin_angle + (y - center.y) * cos_angle + center.y;
  }
}

p3f calc_center(vertexes_t *vv) {
  p3f mx = {0}, mn = {0};
  mn.x = mx.x = vv->v[0].x;
  mn.y = mx.y = vv->v[0].y;
  mn.z = mx.z = vv->v[0].z;
  for (int i = 0; i < (vv->sz); ++i) {
    if (vv->v[i].x < mn.x) mn.x = vv->v[i].x;
    if (vv->v[i].x > mx.x) mx.x = vv->v[i].x;
    if (vv->v[i].y < mn.y) mn.y = vv->v[i].y;
    if (vv->v[i].y > mx.y) mx.y = vv->v[i].y;
    if (vv->v[i].z < mn.z) mn.z = vv->v[i].z;
    if (vv->v[i].z > mx.z) mx.z = vv->v[i].z;
  }
  p3f center = {0};
  center.x = (mx.x + mn.x) / 2.0;
  center.y = (mx.y + mn.y) / 2.0;
  center.x = (mx.z + mn.z) / 2.0;
  float res1 = mx.x - mn.x;
  float res2 = mx.y - mn.y;
  float res3 = mx.z - mn.z;
  vv->max_len = res1;
  if ((vv->max_len) < res2) vv->max_len = res2;
  if ((vv->max_len) < res3) vv->max_len = res3;
  return center;
}

void rotate(vertexes_t *vv, char axis, float angle) {
  p3f center = calc_center(vv);
  shift(vv, -center.x, -center.y, -center.z);
  if (axis == 'x') rotate_x(vv, angle);
  if (axis == 'y') rotate_y(vv, angle);
  if (axis == 'z') rotate_z(vv, angle);
  shift(vv, center.x, center.y, center.z);
}

// int main() {
//   char *path =
//   "/Users/vulpixta/Downloads/C8_3DViewer_v1.0-1-develop/src/obj/skull.obj";

//   vertexes_t vv;
//   facets_t ff;

//   read_obj(path, &vv, &ff);

//  // for (int i = 0; i < vv.sz; ++i)
//   //  printf("%f %f %f\n", vv.v[i].x, vv.v[i].y, vv.v[i].z);

//   printf("vv.sz = %d\n", vv.sz);

//   for (int i = 0; i < ff.sz; ++i)
//     printf("%u %u\n", ff.f[i].first, ff.f[i].second);

//   clear_vertex(&vv);
//   clear_facets(&ff);

//   return 0;
// }
