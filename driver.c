/*
 * driver.c - autograder driver for the StringLibrary assignment.
 * 
 * DO NOT MODIFY THIS FILE!
 */

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== 2. Stand-ins for banned functions. ================================== */

static _Noreturn void ag_forbidden(const char *name)
{
    printf("FORBIDDEN: your code called %s(), which is not allowed in this "
           "assignment\n", name);
    fflush(stdout);
    exit(3);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#define AG_BAN(ret, name, params) \
    static ret ag_banned_##name params { ag_forbidden(#name); }

/* <string.h> */
AG_BAN(size_t, strlen,  (const char *s))
AG_BAN(char *, strcpy,  (char *d, const char *s))
AG_BAN(char *, strncpy, (char *d, const char *s, size_t n))
AG_BAN(char *, strcat,  (char *d, const char *s))
AG_BAN(char *, strncat, (char *d, const char *s, size_t n))
AG_BAN(int,    strcmp,  (const char *a, const char *b))
AG_BAN(int,    strncmp, (const char *a, const char *b, size_t n))
AG_BAN(char *, strchr,  (const char *s, int c))
AG_BAN(char *, strrchr, (const char *s, int c))
AG_BAN(char *, strstr,  (const char *h, const char *n))
AG_BAN(char *, strtok,  (char *s, const char *d))
AG_BAN(size_t, strspn,  (const char *s, const char *a))
AG_BAN(size_t, strcspn, (const char *s, const char *r))
AG_BAN(char *, strpbrk, (const char *s, const char *a))
AG_BAN(void *, memcpy,  (void *d, const void *s, size_t n))
AG_BAN(void *, memmove, (void *d, const void *s, size_t n))
AG_BAN(void *, memset,  (void *d, int c, size_t n))
AG_BAN(int,    memcmp,  (const void *a, const void *b, size_t n))
AG_BAN(void *, memchr,  (const void *s, int c, size_t n))
/* <ctype.h> */
AG_BAN(int, isalnum, (int c))
AG_BAN(int, isalpha, (int c))
AG_BAN(int, isblank, (int c))
AG_BAN(int, isdigit, (int c))
AG_BAN(int, islower, (int c))
AG_BAN(int, isupper, (int c))
AG_BAN(int, isspace, (int c))
AG_BAN(int, ispunct, (int c))
AG_BAN(int, isprint, (int c))
AG_BAN(int, tolower, (int c))
AG_BAN(int, toupper, (int c))
/* <stdio.h> */
AG_BAN(int, printf,   (const char *f, ...))
AG_BAN(int, fprintf,  (FILE *fp, const char *f, ...))
AG_BAN(int, sprintf,  (char *d, const char *f, ...))
AG_BAN(int, snprintf, (char *d, size_t n, const char *f, ...))
AG_BAN(int, puts,     (const char *s))
AG_BAN(int, fputs,    (const char *s, FILE *fp))
AG_BAN(int, putchar,  (int c))
AG_BAN(int, scanf,    (const char *f, ...))
AG_BAN(int, getchar,  (void))
/* <stdlib.h> */
AG_BAN(void *, malloc,  (size_t n))
AG_BAN(void *, calloc,  (size_t n, size_t sz))
AG_BAN(void *, realloc, (void *p, size_t n))
AG_BAN(void,   free,    (void *p))

#pragma GCC diagnostic pop

/* ===== 3. Rename banned calls, compile the student's file, then restore. === */
#undef strlen
#undef strcpy
#undef strncpy
#undef strcat
#undef strncat
#undef strcmp
#undef strncmp
#undef strchr
#undef strrchr
#undef strstr
#undef strtok
#undef strspn
#undef strcspn
#undef strpbrk
#undef memcpy
#undef memmove
#undef memset
#undef memcmp
#undef memchr
#undef isalnum
#undef isalpha
#undef isblank
#undef isdigit
#undef islower
#undef isupper
#undef isspace
#undef ispunct
#undef isprint
#undef tolower
#undef toupper
#undef printf
#undef fprintf
#undef sprintf
#undef snprintf
#undef puts
#undef fputs
#undef putchar
#undef scanf
#undef getchar
#undef malloc
#undef calloc
#undef realloc
#undef free

#define strlen   ag_banned_strlen
#define strcpy   ag_banned_strcpy
#define strncpy  ag_banned_strncpy
#define strcat   ag_banned_strcat
#define strncat  ag_banned_strncat
#define strcmp   ag_banned_strcmp
#define strncmp  ag_banned_strncmp
#define strchr   ag_banned_strchr
#define strrchr  ag_banned_strrchr
#define strstr   ag_banned_strstr
#define strtok   ag_banned_strtok
#define strspn   ag_banned_strspn
#define strcspn  ag_banned_strcspn
#define strpbrk  ag_banned_strpbrk
#define memcpy   ag_banned_memcpy
#define memmove  ag_banned_memmove
#define memset   ag_banned_memset
#define memcmp   ag_banned_memcmp
#define memchr   ag_banned_memchr
#define isalnum  ag_banned_isalnum
#define isalpha  ag_banned_isalpha
#define isblank  ag_banned_isblank
#define isdigit  ag_banned_isdigit
#define islower  ag_banned_islower
#define isupper  ag_banned_isupper
#define isspace  ag_banned_isspace
#define ispunct  ag_banned_ispunct
#define isprint  ag_banned_isprint
#define tolower  ag_banned_tolower
#define toupper  ag_banned_toupper
#define printf   ag_banned_printf
#define fprintf  ag_banned_fprintf
#define sprintf  ag_banned_sprintf
#define snprintf ag_banned_snprintf
#define puts     ag_banned_puts
#define fputs    ag_banned_fputs
#define putchar  ag_banned_putchar
#define scanf    ag_banned_scanf
#define getchar  ag_banned_getchar
#define malloc   ag_banned_malloc
#define calloc   ag_banned_calloc
#define realloc  ag_banned_realloc
#define free     ag_banned_free

#define main ag_student_main
#include "strlib.c"
#undef main

#undef strlen
#undef strcpy
#undef strncpy
#undef strcat
#undef strncat
#undef strcmp
#undef strncmp
#undef strchr
#undef strrchr
#undef strstr
#undef strtok
#undef strspn
#undef strcspn
#undef strpbrk
#undef memcpy
#undef memmove
#undef memset
#undef memcmp
#undef memchr
#undef isalnum
#undef isalpha
#undef isblank
#undef isdigit
#undef islower
#undef isupper
#undef isspace
#undef ispunct
#undef isprint
#undef tolower
#undef toupper
#undef printf
#undef fprintf
#undef sprintf
#undef snprintf
#undef puts
#undef fputs
#undef putchar
#undef scanf
#undef getchar
#undef malloc
#undef calloc
#undef realloc
#undef free

/* ===== 4. The required signatures. A student who changed one gets a clear
 *          "conflicting types" compile error pointing at their function.    */
const char *str_find_char(const char *s, char c);
void        str_reverse(char *s);
int         str_compare_ci(const char *a, const char *b);
size_t      str_copy_bounded(char *dst, const char *src, size_t size);
const char *str_find_sub(const char *hay, const char *needle);
size_t      str_squeeze(char *s);
int         str_split(char *s, char delim, char *fields[], int max_fields);

/* ===== 5. Driver internals (all prefixed ag_ to avoid name clashes). ======= */

#define AG_MAX_LINE     4096
#define AG_MAX_SIZE     4096    /* largest size accepted for copy_bounded */
#define AG_MAX_FIELDS   1000    /* largest max_fields accepted for split   */
#define AG_GUARD_BYTES  8       /* untouchable bytes after copy dst         */
#define AG_EXTRA_FIELDS 3       /* untouchable entries after fields[max-1]  */
#define AG_FILL         '#'     /* fill byte for dst and its guard bytes    */

static char ag_sentinel;        /* "untouched" marker for split's fields[]  */

static _Noreturn void ag_die(const char *msg)
{
    fprintf(stderr, "DRIVER ERROR: %s\n", msg);
    exit(2);
}

static void *ag_alloc(size_t n)
{
    void *p = malloc(n ? n : 1);
    if (p == NULL)
        ag_die("out of memory");
    return p;
}

/* Reads one line without its line ending. Returns false at end of input. */
static bool ag_read_raw(char *out)
{
    if (fgets(out, AG_MAX_LINE, stdin) == NULL)
        return false;
    size_t n = strlen(out);
    if (n > 0 && out[n - 1] == '\n')
        out[--n] = '\0';
    else if (!feof(stdin))
        ag_die("input line too long");
    if (n > 0 && out[n - 1] == '\r')
        out[--n] = '\0';
    return true;
}

/* Decodes escapes from in into out; returns the decoded length. */
static size_t ag_decode(const char *in, char *out)
{
    size_t n = 0;
    for (const char *p = in; *p != '\0'; p++) {
        if (*p != '\\') {
            out[n++] = *p;
            continue;
        }
        p++;
        switch (*p) {
        case 'n':  out[n++] = '\n'; break;
        case 't':  out[n++] = '\t'; break;
        case '\\': out[n++] = '\\'; break;
        case '0':  out[n++] = '\0'; break;
        default:   ag_die("unknown escape in test input (use \\n \\t \\\\ \\0)");
        }
    }
    return n;
}

/* Reads a string argument into a heap buffer of exactly len + 1 bytes. */
static char *ag_read_string(size_t *len_out)
{
    char raw[AG_MAX_LINE], dec[AG_MAX_LINE];
    if (!ag_read_raw(raw))
        ag_die("missing string argument");
    size_t n = ag_decode(raw, dec);
    if (memchr(dec, '\0', n) != NULL)
        ag_die("\\0 is only allowed in char arguments");
    char *s = ag_alloc(n + 1);
    memcpy(s, dec, n);
    s[n] = '\0';
    if (len_out)
        *len_out = n;
    return s;
}

static char ag_read_char(void)
{
    char raw[AG_MAX_LINE], dec[AG_MAX_LINE];
    if (!ag_read_raw(raw))
        ag_die("missing char argument");
    if (ag_decode(raw, dec) != 1)
        ag_die("a char argument must be exactly one character");
    return dec[0];
}

static unsigned long ag_read_number(unsigned long max)
{
    char raw[AG_MAX_LINE];
    if (!ag_read_raw(raw))
        ag_die("missing number argument");
    if (raw[0] == '\0')
        ag_die("empty number argument");
    unsigned long v = 0;
    for (const char *p = raw; *p != '\0'; p++) {
        if (*p < '0' || *p > '9')
            ag_die("number argument must be decimal digits only");
        v = v * 10 + (unsigned long)(*p - '0');
        if (v > max)
            ag_die("number argument too large");
    }
    return v;
}

/* Prints n bytes as a C-like literal body (no quotes). */
static void ag_print_bytes(const char *p, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        unsigned char c = (unsigned char)p[i];
        switch (c) {
        case '\0': fputs("\\0", stdout);  break;
        case '\n': fputs("\\n", stdout);  break;
        case '\t': fputs("\\t", stdout);  break;
        case '\r': fputs("\\r", stdout);  break;
        case '\\': fputs("\\\\", stdout); break;
        case '"':  fputs("\\\"", stdout); break;
        default:
            if (c >= 32 && c < 127)
                putchar(c);
            else
                printf("\\x%02X", c);
        }
    }
}

static void ag_print_quoted(const char *s)
{
    putchar('"');
    ag_print_bytes(s, strlen(s));
    putchar('"');
}

static void ag_print_char(char c)
{
    putchar('\'');
    if (c == '\'')
        fputs("\\'", stdout);
    else
        ag_print_bytes(&c, 1);
    putchar('\'');
}

/* Prints the string starting at p, never reading past end (exclusive). */
static void ag_print_bounded(const char *p, const char *end)
{
    size_t n = 0;
    while (p + n < end && p[n] != '\0')
        n++;
    if (p + n == end) {
        fputs("(no '\\0' terminator inside the string's memory)", stdout);
        return;
    }
    putchar('"');
    ag_print_bytes(p, n);
    putchar('"');
}

/* Is p within [base, base + len]? (Compared as integers: no UB.) */
static bool ag_inside(const char *p, const char *base, size_t len)
{
    uintptr_t u = (uintptr_t)p, b = (uintptr_t)base;
    return u >= b && u <= b + len;
}

static void ag_print_position(const char *ret, const char *base, size_t len)
{
    if (ret == NULL)
        puts("NULL");
    else if (ag_inside(ret, base, len))
        printf("offset %zu\n", (size_t)(ret - base));
    else
        puts("(pointer outside the string)");
}

/* ===== 6. One handler per function. ======================================== */

static void ag_find_char(void)
{
    size_t len;
    char *s = ag_read_string(&len);
    char c = ag_read_char();

    printf("str_find_char(");
    ag_print_quoted(s);
    printf(", ");
    ag_print_char(c);
    printf(") -> ");
    fflush(stdout);
    ag_print_position(str_find_char(s, c), s, len);
    free(s);
}

static void ag_reverse(void)
{
    size_t len;
    char *s = ag_read_string(&len);

    printf("str_reverse(");
    ag_print_quoted(s);
    printf(") -> ");
    fflush(stdout);
    str_reverse(s);
    ag_print_bounded(s, s + len + 1);
    putchar('\n');
    free(s);
}

static void ag_compare_ci(void)
{
    char *a = ag_read_string(NULL);
    char *b = ag_read_string(NULL);

    printf("str_compare_ci(");
    ag_print_quoted(a);
    printf(", ");
    ag_print_quoted(b);
    printf(") -> ");
    fflush(stdout);
    printf("%d\n", str_compare_ci(a, b));
    free(a);
    free(b);
}

static void ag_copy_bounded(void)
{
    char *src = ag_read_string(NULL);
    size_t size = (size_t)ag_read_number(AG_MAX_SIZE);
    char *dst = ag_alloc(size + AG_GUARD_BYTES);
    memset(dst, AG_FILL, size + AG_GUARD_BYTES);

    printf("str_copy_bounded(dst, ");
    ag_print_quoted(src);
    printf(", %zu) -> ", size);
    fflush(stdout);
    printf("returns %zu\n", str_copy_bounded(dst, src, size));
    printf("dst (%zu bytes): \"", size);
    ag_print_bytes(dst, size);
    printf("\"\nbytes after dst: \"");
    ag_print_bytes(dst + size, AG_GUARD_BYTES);
    printf("\"\n");
    free(src);
    free(dst);
}

static void ag_find_sub(void)
{
    size_t len;
    char *hay = ag_read_string(&len);
    char *needle = ag_read_string(NULL);

    printf("str_find_sub(");
    ag_print_quoted(hay);
    printf(", ");
    ag_print_quoted(needle);
    printf(") -> ");
    fflush(stdout);
    ag_print_position(str_find_sub(hay, needle), hay, len);
    free(hay);
    free(needle);
}

static void ag_squeeze(void)
{
    size_t len;
    char *s = ag_read_string(&len);

    printf("str_squeeze(");
    ag_print_quoted(s);
    printf(") -> ");
    fflush(stdout);
    printf("returns %zu\n", str_squeeze(s));
    printf("s is now: ");
    ag_print_bounded(s, s + len + 1);
    putchar('\n');
    free(s);
}

static void ag_split(void)
{
    size_t len;
    char *s = ag_read_string(&len);
    char delim = ag_read_char();
    int max = (int)ag_read_number(AG_MAX_FIELDS);
    if (delim == '\0')
        ag_die("split delimiter must not be \\0");

    size_t slots = (size_t)max + AG_EXTRA_FIELDS;
    char **fields = ag_alloc(slots * sizeof *fields);
    for (size_t i = 0; i < slots; i++)
        fields[i] = &ag_sentinel;

    printf("str_split(");
    ag_print_quoted(s);
    printf(", ");
    ag_print_char(delim);
    printf(", fields, %d) -> ", max);
    fflush(stdout);
    printf("returns %d\n", str_split(s, delim, fields, max));

    printf("buffer is now: \"");
    ag_print_bytes(s, len + 1);
    printf("\"\n");

    for (size_t i = 0; i < slots; i++) {
        printf("fields[%zu]: ", i);
        if (fields[i] == &ag_sentinel)
            fputs("(untouched)", stdout);
        else if (fields[i] == NULL)
            fputs("NULL", stdout);
        else if (!ag_inside(fields[i], s, len))
            fputs("(pointer outside the string)", stdout);
        else
            ag_print_bounded(fields[i], s + len + 1);
        putchar('\n');
    }
    free(fields);
    free(s);
}

/* ===== 7. Command loop. ==================================================== */

int main(void)
{
    char cmd[AG_MAX_LINE];
    while (ag_read_raw(cmd)) {
        if (cmd[0] == '\0')
            continue;                       /* blank line between commands */
        if      (strcmp(cmd, "find_char") == 0)    ag_find_char();
        else if (strcmp(cmd, "reverse") == 0)      ag_reverse();
        else if (strcmp(cmd, "compare_ci") == 0)   ag_compare_ci();
        else if (strcmp(cmd, "copy_bounded") == 0) ag_copy_bounded();
        else if (strcmp(cmd, "find_sub") == 0)     ag_find_sub();
        else if (strcmp(cmd, "squeeze") == 0)      ag_squeeze();
        else if (strcmp(cmd, "split") == 0)        ag_split();
        else
            ag_die("unknown command (expected find_char, reverse, compare_ci, "
                   "copy_bounded, find_sub, squeeze or split)");
        fflush(stdout);
    }
    return 0;
}
