#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_sprintf.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  const char* cur = (const char*)str;
  s21_size_t pos = 0;
  while (pos < n) {
    if (cur[pos] == c) break;
    pos++;
  }
  return (pos < n ? (void*)&cur[pos] : s21_NULL);
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t length) {
  char* buffer1 = (char*)str1;
  char* buffer2 = (char*)str2;
  s21_size_t n;
  for (n = 0; n < length && (buffer1[n] == buffer2[n]); n++)
    ;
  return (n == length) ? 0 : (buffer1[n] - buffer2[n]);
}

void* s21_memcpy(void* str1, const void* str2, s21_size_t countSymbols) {
  char* subStringOut = (char*)str1;
  const char* subStringIn = (char*)str2;
  for (s21_size_t i = 0; i < countSymbols; i++)
    *subStringOut++ = *subStringIn++;
  return str1;
}

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  char* aux = (char*)malloc(sizeof(char) * n);
  if (aux) {
    s21_memcpy(aux, ((char*)src), n);
    s21_memcpy(((char*)dest), aux, n);
    free(aux);
  }
  return dest;
}

void* s21_memset(void* str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    ((char*)str)[i] = c;
  }
  return str;
}

char* s21_strcat(char* dest, const char* src) {
  char* chstr = dest;
  while (*dest != '\0') {
    dest++;
  }
  while ((*dest++ = *src++)) {
  }
  return chstr;
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t i, j;
  for (i = 0; dest[i] != '\0'; i++) {
  }
  for (j = 0; j < n; j++) {
    dest[i + j] = src[j];
  }
  dest[i + j] = '\0';
  return dest;
}

char* s21_strchr(const char* str, int c) {
  char* ptr;
  while (str) {
    if (*str == c) {
      ptr = (char*)str;
      break;
    }
    if (*str == '\0') {
      ptr = s21_NULL;
      break;
    }
    str++;
  }
  return ptr;
}

int s21_strcmp(const char* str1, const char* str2) {
  int result = 0;
  if (*str1 < *str2) result = -1;
  if (*str1 > *str2) result = 1;
  return result;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  bool isInequality = false;
  int result = 0;
  for (s21_size_t i = 0; i < n && !isInequality; i++) {
    if (str1[i] < str2[i]) {
      result = -1;
      isInequality = true;
    }
    if (str1[i] > str2[i]) {
      result = 1;
      isInequality = true;
    }
  }
  return result;
}

char* s21_strcpy(char* dest, const char* src) {
  char* chstr = dest;
  while ((*dest++ = *src++)) {
  }
  return chstr;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  char* chstr = dest;
  while (n-- != 0) {
    *dest++ = *src++;
  }
  return chstr;
}

s21_size_t s21_strlen(const char* str) {
  return ((*str) ? s21_strlen(++str) + 1 : 0);
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  bool* was = malloc(ASCII_SIZE * sizeof(bool));
  int len_str1 = (int)s21_strlen(str1), len_str2 = (int)s21_strlen(str2);
  int pos = 0;
  for (int i = 0; i < ASCII_SIZE; ++i) was[i] = false;
  for (int i = 0; i < len_str2; ++i) was[(int)str2[i]] = true;
  while (pos < len_str1 && !was[(int)str1[pos]]) pos++;
  free(was);
  return (s21_size_t)pos;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  bool* was = malloc(ASCII_SIZE * sizeof(bool));
  int len_str1 = (int)s21_strlen(str1), len_str2 = (int)s21_strlen(str2);
  for (int i = 0; i < ASCII_SIZE; ++i) was[i] = false;
  for (int i = 0; i < len_str2; ++i) was[(int)str2[i]] = true;
  bool founded = false;
  int cnt = 0;
  for (int i = 0; ((i < len_str1) && !founded); ++i) {
    if (!was[(int)str1[i]]) {
      cnt++;
    } else {
      founded = true;
    }
  }
  free(was);
  return (founded ? (char*)(str1 + cnt) : s21_NULL);
}

char* s21_strerror(int errnum) {
  static char ans[ASCII_SIZE];
#ifdef __linux__
  const char* linux_errors[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
  if (errnum < 0 || errnum > 133) {
    s21_sprintf(ans, "%s%d", "Unknown error ", errnum);
  } else {
    s21_sprintf(ans, "%s", linux_errors[errnum]);
  }
#elif __APPLE__
  const char* mac_errors[] = {"Undefined error: 0",
                              "Operation not permitted",
                              "No such file or directory",
                              "No such process",
                              "Interrupted system call",
                              "Input/output error",
                              "Device not configured",
                              "Argument list too long",
                              "Exec format error",
                              "Bad file descriptor",
                              "No child processes",
                              "Resource deadlock avoided",
                              "Cannot allocate memory",
                              "Permission denied",
                              "Bad address",
                              "Block device required",
                              "Resource busy",
                              "File exists",
                              "Cross-device link",
                              "Operation not supported by device",
                              "Not a directory",
                              "Is a directory",
                              "Invalid argument",
                              "Too many open files in system",
                              "Too many open files",
                              "Inappropriate ioctl for device",
                              "Text file busy",
                              "File too large",
                              "No space left on device",
                              "Illegal seek",
                              "Read-only file system",
                              "Too many links",
                              "Broken pipe",
                              "Numerical argument out of domain",
                              "Result too large",
                              "Resource temporarily unavailable",
                              "Operation now in progress",
                              "Operation already in progress",
                              "Socket operation on non-socket",
                              "Destination address required",
                              "Message too long",
                              "Protocol wrong type for socket",
                              "Protocol not available",
                              "Protocol not supported",
                              "Socket type not supported",
                              "Operation not supported",
                              "Protocol family not supported",
                              "Address family not supported by protocol family",
                              "Address already in use",
                              "Can't assign requested address",
                              "Network is down",
                              "Network is unreachable",
                              "Network dropped connection on reset",
                              "Software caused connection abort",
                              "Connection reset by peer",
                              "No buffer space available",
                              "Socket is already connected",
                              "Socket is not connected",
                              "Can't send after socket shutdown",
                              "Too many references: can't splice",
                              "Operation timed out",
                              "Connection refused",
                              "Too many levels of symbolic links",
                              "File name too long",
                              "Host is down",
                              "No route to host",
                              "Directory not empty",
                              "Too many processes",
                              "Too many users",
                              "Disc quota exceeded",
                              "Stale NFS file handle",
                              "Too many levels of remote in path",
                              "RPC struct is bad",
                              "RPC version wrong",
                              "RPC prog. not avail",
                              "Program version wrong",
                              "Bad procedure for program",
                              "No locks available",
                              "Function not implemented",
                              "Inappropriate file type or format",
                              "Authentication error",
                              "Need authenticator",
                              "Device power is off",
                              "Device error",
                              "Value too large to be stored in data type",
                              "Bad executable (or shared library)",
                              "Bad CPU type in executable",
                              "Shared library version mismatch",
                              "Malformed Mach-o file",
                              "Operation canceled",
                              "Identifier removed",
                              "No message of desired type",
                              "Illegal byte sequence",
                              "Attribute not found",
                              "Bad message",
                              "EMULTIHOP (Reserved)",
                              "No message available on STREAM",
                              "ENOLINK (Reserved)",
                              "No STREAM resources",
                              "Not a STREAM",
                              "Protocol error",
                              "STREAM ioctl timeout",
                              "Operation not supported on socket",
                              "Policy not found",
                              "State not recoverable",
                              "Previous owner died",
                              "Interface output queue is full"};
  if (errnum < 0 || errnum > 106) {
    s21_sprintf(ans, "%s%d", "Unknown error: ", errnum);
  } else {
    s21_sprintf(ans, "%s", mac_errors[errnum]);
  }
#endif
  return ans;
}

char* s21_strrchr(const char* str, int c) {
  char* pointer = NULL;
  char* buffer = (char*)str;
  for (s21_size_t i = s21_strlen(buffer); i && !pointer; i--) {
    if (buffer[i] == c) pointer = &buffer[i];
  }
  return pointer;
}

s21_size_t s21_strspn(const char* str1, const char* str2) {
  int i;
  int res = 1;
  for (i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != str1[i]; j++) {
      if (str2[j] == '\0') {
        res = 0;
        break;
      }
    }
    if (res == 0) {
      break;
    }
  }
  return i;
}

char* s21_strstr(const char* haystack, const char* needle) {
  size_t n = s21_strlen(needle);
  char* result = NULL;
  while ((*haystack || (haystack[0] == needle[0])) && result == NULL) {
    if (!s21_memcmp(haystack, needle, n)) result = (char*)haystack;
    haystack++;
  }
  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* buffer = s21_NULL;
  char* result = s21_NULL;

  if (str != s21_NULL) {
    buffer = str;
  }

  if (buffer != s21_NULL) {
    buffer += s21_strspn(buffer, delim);

    if (*buffer != '\0') {
      char* const tokenBegin = buffer;
      buffer += s21_strcspn(buffer, delim);

      if (*buffer != '\0') {
        *buffer++ = '\0';
      }
      result = tokenBegin;
    }
  }
  return result;
}

void* s21_to_upper(const char* str) {
  char* ans = s21_NULL;
  if (str != s21_NULL) {
    ans = (char*)calloc(s21_strlen(str) + 1, sizeof(char));
    for (int i = 0; i < (int)s21_strlen(str); ++i) {
      ans[i] = str[i];
      if (str[i] >= 'a' && str[i] <= 'z') ans[i] -= 32;
    }
  }
  return ans;
}

void* s21_to_lower(const char* str) {
  char* ans = s21_NULL;
  if (str != s21_NULL) {
    ans = (char*)calloc(s21_strlen(str) + 1, sizeof(char));
    for (int i = 0; i < (int)s21_strlen(str); ++i) {
      ans[i] = str[i];
      if (str[i] >= 'A' && str[i] <= 'Z') ans[i] += 32;
    }
  }
  return ans;
}

void* s21_trim(const char* src, const char* trim_chars) {
  char* answer = s21_NULL;
  if (src) {
    answer = (char*)src;
    s21_size_t sz = s21_strlen(src);
    bool f = s21_strlen(trim_chars);
    s21_size_t pos = (f ? s21_strspn(src, trim_chars) : s21_strspn(src, " "));
    if (pos != sz) {
      if (f) {
        while (s21_strchr(trim_chars, src[sz - 1])) sz--;
      } else {
        while (s21_strchr(" ", src[sz - 1])) sz--;
      }
    }
    answer = calloc(sz - pos + 1, 1);
    s21_size_t new_pos = 0;
    while (pos < sz) answer[new_pos++] = src[pos++];
  }
  return (void*)answer;
}

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  char* res = s21_NULL;
  if (src && str) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    s21_size_t new_len = src_len + str_len;

    if (start_index <= src_len) {
      res = (char*)calloc(new_len + 1, sizeof(char));

      if (res) {
        s21_strncpy(res, src, start_index);
        src = src + start_index;
        s21_strncat(res, str, str_len);
        s21_strncat(res, src, src_len - start_index);
      }
    }
  } else if (str == s21_NULL && src != s21_NULL) {
    res = calloc(s21_strlen(src) + 1, sizeof(char));
    s21_strcpy(res, src);
  }
  return (void*)res;
}