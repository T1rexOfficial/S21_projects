#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define s21_size_t unsigned long long
#define s21_NULL ((void *)0)

#define ASCII_SIZE 256

typedef enum bool { false, true } bool;

#include <stdlib.h>

#include "s21_sprintf.h"

void *s21_memchr(const void *str, int symbol, s21_size_t length);
int s21_memcmp(const void *str1, const void *str2, s21_size_t length);
void *s21_memcpy(void *str1, const void *str2, s21_size_t countSymbols);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int symbol, s21_size_t lenght);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int ch);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *destination, const char *source);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strerror(int errnum);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

#endif  // SRC_S21_STRING_H_
