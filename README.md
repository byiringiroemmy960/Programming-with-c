# StringLibrary

**INSY 8212: Programming with C**. **Due Thursday 12 November 2026, 23:59 (Africa/Kigali time).**

## Overview

# Assignment 2: Your Own String Library

**Course:** Programming with C **Due:** 11th November 2026, 11:59:59 CAT **Submit:** `strlib_<your_student_id>.zip` only, via google form **Points:** 100

---

## Why this assignment exists

Over the last two weeks you learned that a string in C is nothing magical: it is an array of characters ending with `'\0'`, and a pointer can walk through it one character at a time. In this assignment you will write seven string functions **from scratch**, using nothing but loops, pointers, and your own reasoning.

C already has a standard library (`<string.h>`) with functions similar to some of these. You are **NOT** allowed to use it here, and that is the whole point. Data Structures, the course after this one, assumes you can think clearly about memory, pointers, and edge cases. The way to build that skill is to do the work yourself, get it wrong, find out why, and fix it.

### About getting help

Asking for help is **NOT** cheating. You may ask me, your classmates, the internet, or an AI tool. Use whatever helps you **understand**. The rule is simple:

> **You must be able to explain and reason about every line you submit.**

If you can't trace your own function by hand on a small input, or explain why it handles an edge case correctly, you haven't learned what this assignment is meant to teach, even if the tests pass. Remember, the final exam will test whether you really wrote the code yourself.

A good way to use help: when you're stuck, ask *why* your code fails on a specific input, not "write this function for me." Struggle a little first; that struggle is where the learning happens.

---

## Getting started

The github repo has a starter file, `strlib.c`, containing:

- all seven functions with their exact signatures and a placeholder body,
- a `main` function at the bottom for your own experiments.

Compile with the command `make` and run it:

```
make
./strlib
```

Or test your with the command ==> `make test` ---

## Rules

1. **No library functions inside the seven functions.** That means no `strlen`, `strcpy`, `strcmp`, `strchr`, `strstr`, `strtok`, `tolower`, `isspace`, `printf`, or anything else from any library. The autograder checks this automatically, and a submission that calls any library function gets **zero** for the affected checks. (You *may* use `printf` inside `main` for testing; `main` is ignored by the autograder.) 
2. **Write your own helper functions** if you want to (for example, your own function to compute a string's length). Helpers are encouraged, however do not give them the same name as their `string.h` versions. You should not create a function called `strlen` or `strcmp` use a custom name like my_strlen or something. 
3. **Do not change the name, return type, or parameters** of any of the seven functions. The autograder calls them exactly as written. 
4. **Remove debug `printf` calls from the seven functions** before you submit. See rule 1. 
5. All strings in this assignment contain only standard ASCII characters (values 0 to 127). 
6. Unless a function's description says otherwise, **pointer arguments are never `NULL`**. You don't need to check for it. 
7. Warnings count as errors therefore you code might not compile just because you have an unused variable. Keep an eye out for such things. 
8. Match const when walking a string. If a parameter is `const char *s`, any pointer you use to walk through it must also be `const char *`. Otherwise you’ll get a warning, and rule [warnings] applies.

### A common trap: string literals are read-only

Functions that **modify** a string (`str_reverse`, `str_squeeze`, `str_split`) must be given a character **array**, not a string literal:

```
char ok[] = "hello";     /* an array you own: safe to modify */
char *bad = "hello";     /* points to a literal: modifying it crashes */

str_reverse(ok);         /* fine */
str_reverse(bad);        /* undefined behavior, usually a crash */
```

---

## The functions

The functions are listed roughly from easiest to hardest. The examples show **happy cases** (typical input), **sad cases** (nothing found, input that doesn't fit), and **edge cases** (empty strings, boundaries). The autograder tests many more inputs than the ones shown, so think carefully about cases beyond these.

### 1. `str_find_char` (9 points)

```
const char *str_find_char(const char *s, char c);
```

Returns a pointer to the **first** occurrence of character `c` in string `s`, or `NULL` if `c` doesn't appear.

Searching for `'\0'` is allowed: it returns a pointer to the terminating null character of `s`.

```
const char *s = "hello";

/* happy */
str_find_char(s, 'l');      /* returns s + 2   (points to "llo") */
str_find_char(s, 'h');      /* returns s + 0   (points to "hello") */

/* sad */
str_find_char(s, 'z');      /* returns NULL */
str_find_char(s, 'H');      /* returns NULL    (case matters) */

/* edge */
str_find_char(s, '\0');     /* returns s + 5   (points to the terminating '\0') */
str_find_char("", 'a');     /* returns NULL */
str_find_char("", '\0');    /* returns a pointer to that empty string's '\0' */
```

> **Think about it:** this function returns a *position inside the original string*, not a copy. What does that let the caller do?

---

### 2. `str_reverse` (9 points)

```
void str_reverse(char *s);
```

Reverses the string `s` **in place**. Don't use a second array.

```
char a[] = "hello";     str_reverse(a);    /* a is now "olleh" */
char b[] = "ab cd";     str_reverse(b);    /* b is now "dc ba" */

/* edge */
char c[] = "ab";        str_reverse(c);    /* c is now "ba" */
char d[] = "a";         str_reverse(d);    /* d is still "a" */
char e[] = "";          str_reverse(e);    /* e is still "" */
char f[] = "racecar";   str_reverse(f);    /* f is still "racecar" */
```

> **Hint:** two pointers, one at each end, moving toward each other. When should they stop? Check your answer for both odd and even lengths.

---

### 3. `str_compare_ci` (11 points)

```
int str_compare_ci(const char *a, const char *b);
```

Compares two strings **case-insensitively**. Returns **exactly**:

- `-1` if `a` comes before `b`,
- `0` if they are equal (ignoring case),
- `1` if `a` comes after `b`.

Not "a negative number" or "a positive number": exactly `-1`, `0`, or `1`.

**How to compare:** walk both strings in step. Convert each character to **lowercase** if it is an uppercase letter (`'A'` to `'Z'`); leave every other character alone. Compare the resulting values. The first position where they differ decides the result. If one string ends first and the other doesn't, the shorter one comes first.

```
/* happy */
str_compare_ci("Hello", "hello");     /*  0 */
str_compare_ci("apple", "Banana");    /* -1   ('a' < 'b') */
str_compare_ci("Zebra", "apple");     /*  1   ('z' > 'a') */

/* prefix */
str_compare_ci("abc", "ab");          /*  1   ("ab" ends first) */
str_compare_ci("AB", "abc");          /* -1 */

/* edge */
str_compare_ci("", "");               /*  0 */
str_compare_ci("", "a");              /* -1 */
str_compare_ci("123", "123");         /*  0   (digits are not letters) */

/* why "lowercase" matters */
str_compare_ci("a_b", "aBb");         /* -1   ('_' is 95, 'b' is 98) */
```

> **Think about it:** the last example would give a *different* answer if you converted to uppercase instead. Look up the ASCII values of `'_'`, `'B'`, and `'b'` and work out why. Follow the spec exactly.

---

### 4. `str_copy_bounded` (14 points)

```
size_t str_copy_bounded(char *dst, const char *src, size_t size);
```

Copies `src` into `dst`, where `size` is the **total number of bytes available** in `dst`.

- Copy at most `size - 1` characters, then write a `'\0'`, so `dst` is **always** a valid string when `size > 0`.
- If `size` is `0`, write **nothing at all**.
- Never write beyond `dst[size - 1]`. Write only the copied characters and one `'\0'`; leave any bytes after that untouched.
- **Return the length of `src`**, not the number of characters copied.

Because of the return value, the caller can detect truncation: **if the return value is `>= size`, the copy was cut short.**

```
char dst[10];

/* happy: fits */
str_copy_bounded(dst, "hello", 10);   /* dst is "hello",  returns 5 */

/* sad: doesn't fit, gets truncated */
char small[4];
str_copy_bounded(small, "hello", 4);  /* small is "hel",  returns 5  (5 >= 4: truncated) */

/* edge: exact boundaries */
str_copy_bounded(dst, "abc", 4);      /* dst is "abc",    returns 3  (just fits) */
str_copy_bounded(dst, "abc", 3);      /* dst is "ab",     returns 3  (truncated by one) */
str_copy_bounded(dst, "hello", 1);    /* dst is "",       returns 5  (room only for '\0') */
str_copy_bounded(dst, "hello", 0);    /* dst untouched,   returns 5 */
str_copy_bounded(dst, "", 10);        /* dst is "",       returns 0 */
```

> **Think about it:** draw the `small` array as four boxes and fill them in by hand for the truncation example. Which box gets the `'\0'`?

---

### 5. `str_find_sub` (14 points)

```
const char *str_find_sub(const char *hay, const char *needle);
```

Returns a pointer to the **first** place in `hay` where the whole string `needle` appears, or `NULL` if it never does.

An **empty** `needle` is found at the very start: return `hay`.

```
const char *h = "hello world";

/* happy */
str_find_sub(h, "world");                 /* returns h + 6 */
str_find_sub(h, "o");                     /* returns h + 4  (the first 'o') */
str_find_sub(h, "hello world");           /* returns h + 0  (the whole string) */

/* sad */
str_find_sub(h, "World");                 /* returns NULL   (case matters) */
str_find_sub("abc", "abcd");              /* returns NULL   (needle longer than hay) */

/* tricky: overlapping partial matches */
const char *m = "mississippi";
str_find_sub(m, "issip");                 /* returns m + 4 */
const char *a = "aaab";
str_find_sub(a, "aab");                   /* returns a + 1 */

/* edge */
str_find_sub("abc", "");                  /* returns a pointer to the start of "abc" */
str_find_sub("", "");                     /* returns a pointer to the start of "" */
str_find_sub("", "a");                    /* returns NULL */
```

> **Think about it:** in `"aaab"`, a match for `"aab"` starts at index 0, fails at the third character, and the real match starts at index 1. If your code jumps ahead to where the failed match ended, it will miss it. Trace your code on this input by hand.

---

### 6. `str_squeeze` (16 points)

```
size_t str_squeeze(char *s);
```

Cleans up whitespace in `s` **in place** and returns the new length.

For this function, **whitespace means only the space `' '` and the tab `'\t'`.** Every other character, including newline `'\n'`, is an ordinary character.

- Each run of one or more whitespace characters **between** other characters becomes a **single space** `' '`.
- Whitespace at the **start** and **end** of the string is removed completely.

```
/* happy */
char a[] = "  hello   world  ";    /* becomes "hello world",  returns 11 */
char b[] = "a\t\tb";               /* becomes "a b",          returns 3  (tabs become one space) */
char c[] = "one two";              /* unchanged "one two",    returns 7 */

/* edge: nothing to keep */
char d[] = "   ";                  /* becomes "",             returns 0 */
char e[] = "";                     /* stays "",               returns 0 */
char f[] = " \t a \t ";            /* becomes "a",            returns 1 */

/* edge: newline is NOT whitespace here */
char g[] = "a  \n  b";             /* becomes "a \n b",       returns 5 */
```

> **Hint:** use two pointers into the same array: one that **reads** every character and one that **writes** the characters you keep. The write pointer never gets ahead of the read pointer. Why is that guaranteed?

---

### 7. `str_split` (17 points)

```
int str_split(char *s, char delim, char *fields[], int max_fields);
```

Splits `s` into **fields** separated by the character `delim`, **in place**:

- Every occurrence of `delim` in `s` is replaced with `'\0'`, cutting the string into pieces. **All** delimiters are replaced, even if there are more fields than `max_fields`.
- `fields[0]`, `fields[1]`, ... are set to point to the **start of each piece**, in order, inside `s` itself. At most `max_fields` pointers are stored; entries of `fields` beyond that are not touched.
- **Returns the total number of fields** in the string, which may be larger than `max_fields`.

Fields are counted strictly: **a string with `k` delimiters always has `k + 1` fields.** That means:

- two delimiters in a row produce an **empty field** between them,
- a delimiter at the start or end produces an empty field there,
- an empty string has **one** field: the empty string.

`delim` will never be `'\0'`.

```
char *f[5];

/* happy */
char a[] = "red,green,blue";
str_split(a, ',', f, 5);     /* returns 3:  f[0]="red"  f[1]="green"  f[2]="blue" */

/* empty fields */
char b[] = "a,,b";
str_split(b, ',', f, 5);     /* returns 3:  f[0]="a"  f[1]=""  f[2]="b" */
char c[] = ",a,";
str_split(c, ',', f, 5);     /* returns 3:  f[0]=""  f[1]="a"  f[2]="" */

/* sad: more fields than room */
char d[] = "w,x,y,z";
str_split(d, ',', f, 2);     /* returns 4:  f[0]="w"  f[1]="x"  (f[2] onward untouched) */

/* edge */
char e[] = "no delimiters";
str_split(e, ',', f, 5);     /* returns 1:  f[0]="no delimiters" */
char g[] = "";
str_split(g, ',', f, 5);     /* returns 1:  f[0]="" */
char h[] = "a,b";
str_split(h, ',', f, 0);     /* returns 2:  nothing stored in f */
```

After splitting `"red,green,blue"`, the array `a` looks like this in memory:

```
r  e  d \0  g  r  e  e  n \0  b  l  u  e \0
^           ^                 ^
f[0]        f[1]              f[2]
```

No new memory is created: each `fields[i]` points **into** the original array.

> **Be careful:** C's standard `strtok` behaves differently (it skips empty fields). Follow *this* spec, not what you remember from elsewhere.

---

## Grading

| Function | Points | 
|---|---| 
| `str_find_char` | 9 | 
| `str_reverse` | 9 | 
| `str_compare_ci` | 11 | 
| `str_copy_bounded` | 14 | 
| `str_find_sub` | 14 | 
| `str_squeeze` | 16 | 
| `str_split` | 17 | 
| memory | 10 | 
| **Total** | **100** |

- Each function's points are split across many tests, so partial credit is possible.
- A test fails if your result is wrong, **or** if the valgrind detects a memory error (for example, reading or writing outside an array), **or** if your code crashes. The autograder runs your code under valgrind, a tool that detects memory mistakes. Reading or writing even one byte outside a string counts as a failed test, even if your result looks correct. If you have valgrind (Linux or WSL), you can check yourself with `valgrind ./strlib`.
- The examples above are only some of the cases tested. Before submitting, write your own tests in `main` for every case you can think of.
- Calling any library function inside the seven functions results in zero for the affected checks (see Rules).

## Suggested approach

1. Start with `str_find_char` and `str_reverse` to get comfortable walking strings with pointers. You'll probably want a length helper for `str_reverse`; write your own. 
2. For every function, **trace it by hand on paper** with the edge cases before running it. If you can't predict what your code will do, you don't understand it yet. 
3. Test as you go. Don't write all seven and then compile. 
4. Start `str_squeeze` and `str_split` early. They are worth the most points and take the most thought.

Good luck, and enjoy it. This is the week you stop *using* strings and start *understanding* them.

## Input

Your program should not worry about reading user input. The autograder calls the functions directly.

## Output

Your functions should not print any output, any calls to `printf` in your functions are illegal. You can use `printf` in your `main()` function and even then for debugging purposes.

## Invalid input and edge cases

Edge cases are defined the assignment writeup, read it carefully to figure out the expected output.

## What you may and may not use

**Not allowed:**

- `stdio.h` -> allowed only in the `main()` function
- `string.h`
- `stdlib.h`
- `ctype.h`

## Getting started

1. Open the template repository (https://github.com/Kabera192/strlib-template) and click **Use this template > Create a new repository**. Make it **private** (a public repo lets anyone copy your work).
2. Clone your new repository to your computer and work there. Commit and push as often as you like; this is for your own version control and is **not** your submission.
3. Write your code in `strlib.c`.

## Compiling

Your code is graded with exactly this command (gcc on Linux):

```
gcc -std=c11 -Wall -Wextra -g -DAUTOGRADER -Werror driver.c -o strlib
```

Or just type `make`. **Warnings count as errors:** if gcc prints any warning, your program does not compile and every test scores 0. Fix every warning before you submit.

## Testing your work

Run the tests with `make test` (or `python3 tests/run_tests.py`). They show exactly how your output differs from what is expected, with invisible characters marked. The visible tests are:

`tests/run_tests.py` needs Python 3. On Windows, use WSL (recommended) or MSYS2 so that `gcc` and `make` are available.

## Submitting

**Only the Google Form counts.** Pushing to GitHub is not a submission.

1. Make a zip file named `strlib_STUDENTID.zip`, replacing STUDENTID with your numeric student ID, containing `strlib.c`. The easiest way: `make zip ID=12345` or `python3 tests/make_zip.py 12345` (with your ID). This also checks that your code compiles.
2. To zip by hand instead: Windows: select the file(s), right-click > Send to > Compressed (zipped) folder. macOS: select the file(s), right-click > Compress. Linux/WSL: `zip strlib_STUDENTID.zip strlib.c`. Zip the files themselves, not a folder around them (a folder is tolerated, but not required).
3. Do not include compiled programs, and do not use .rar or .7z.
4. Open the submission form (https://forms.gle/i3UZzr5AutEGhqN2A), sign in with your Google account, enter your full name and numeric student ID exactly, and upload the zip.
5. You may submit again as many times as you like (see the late policy below for how we choose which one to grade).

## How your grade is computed

| Category | Points | How it is graded |
|---|---|---|
| Compiles cleanly (no warnings) | 0 | Compiles with the command above with no warnings |
| str_find_char | 9 | 13 visible test(s); partial credit per test |
| str_reverse | 9 | 11 visible test(s); partial credit per test |
| str_compare_ci | 11 | 18 visible test(s); partial credit per test |
| str_copy_bounded | 14 | 13 visible test(s); partial credit per test |
| str_find_sub | 14 | 18 visible test(s); partial credit per test |
| str_squeeze | 16 | 16 visible test(s); partial credit per test |
| str_split | 17 | 16 visible test(s); partial credit per test |
| Memory safety (valgrind) | 10 | No memory errors or leaks reported by valgrind |
| Total | 100 |  |

If your program does not compile, all test-based categories score 0. Within a category, tests can carry different weights. The final score is rounded to the nearest 0.5. You will receive a feedback report by email listing every test, what went wrong, and your points per category.

## Deadline and late submissions

Deadline: Thursday 12 November 2026, 23:59 Africa/Kigali time (UTC+02:00; = 2026-11-12 21:59 UTC).

Grace period: submissions up to 15 minutes after the deadline count as on time. After that, lateness is measured from the deadline itself.

Late submissions are accepted without penalty so long as you still have valid grace days.

Submissions more than 3 day(s) late receive 0.

You may submit as many times as you like. We grade your latest on-time submission AND your latest submission overall (with its late penalty), and you receive whichever final score is higher.

| Submitted after the deadline by | Penalty |
|---|---|
| 10 minutes | 0 (on time) |
| 3 hours | -0% |
| 1 day 1 hour | -0% |
| 2.5 days | -0% |
| 4 days | score = 0 |

If you need an extension, communicate as early as possible.

## Academic integrity

This is an individual assignment. You may discuss ideas with classmates, but the code you submit must be written by you. All submissions are compared with each other by software, and unusually similar pairs are reviewed by the instructor. Similar code alone is never treated as proof of copying; you will always be asked to explain your work first.
