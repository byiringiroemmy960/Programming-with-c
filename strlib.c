/*
 * ============================================================================
 *  Assignment: Your Own String Library
 *  Course:     Programming with C
 *
 *  Name:       BYIRINGIRO Emmanuel
 *  Student ID: 29674
 * ============================================================================
 *
 *  HOW TO COMPILE AND RUN
 *      gcc -Wall -Wextra -g strlib.c -o strlib
 *      ./strlib
 *
 *  Fix EVERY warning: the autograder treats any warning as a compile failure.
 *
 *  QUICK RULES (see the README for details)
 *   - No library functions inside the seven functions: no strlen, strcpy,
 *     strcmp, tolower, isspace, printf, malloc, ...
 *   - Do not change any function's name, return type, or parameters.
 *   - Helper functions are encouraged. Give them your own names (my_strlen,
 *     not strlen), and use every helper you write or delete it: an unused
 *     function or variable is a warning, and a warning is a failure.
 *   - Every string is plain ASCII. Pointer arguments are never NULL.
 *
 *  ABOUT THE "YOUR NOTES" BOXES
 *   Each function has a box for you to fill in: your approach, the edge cases
 *   you handled, and how you tested it. The notes are not graded, but writing
 *   them is the best way to check that you understand your own code, and you
 *   may be asked to explain these functions in class or on the exam.
 * ============================================================================
 */

#include <stddef.h>   /* size_t, NULL */
#include <stdio.h>    /* printf: ONLY for testing in main() */


/* ============================================================================
 *  HELPER FUNCTIONS (optional, write your own here)
 * ============================================================================
 *
 *  Ideas that several functions below can share:
 *
 *   - size_t my_strlen(const char *s)
 *       Walk a pointer to the '\0' and return how far it went.
 *       Useful in: str_reverse, str_copy_bounded.
 *
 *   - char my_to_lower(char c)
 *       Turn 'A'..'Z' into 'a'..'z'; return any other character unchanged.
 *       Hint: in ASCII, 'a' - 'A' is the same for every letter.
 *       Useful in: str_compare_ci.
 *
 *   - int is_blank(char c)
 *       1 if c is ' ' or '\t', otherwise 0. Nothing else counts!
 *       Useful in: str_squeeze.
 *
 *   - int matches_at(const char *p, const char *needle)
 *       1 if needle appears starting exactly at p, otherwise 0.
 *       Useful in: str_find_sub. With this helper, the main function becomes
 *       "try every starting position", which is much easier to get right.
 *
 *  Write each helper ABOVE the functions that use it.
 */




/* ============================================================================
 *  1. str_find_char
 * ============================================================================
 *  Returns a pointer to the FIRST occurrence of c in s, or NULL if c does not
 *  appear. Searching for '\0' returns a pointer to s's terminating '\0'.
 *
 *  HINTS
 *   - Walk a pointer through s. At each position, check for c BEFORE you
 *     check for the end of the string. Why does the order matter when
 *     c is '\0'?
 *   - You are returning a position inside s, not a copy of anything.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
const char *str_find_char(const char *s, char c)
{
    while (1)
    {
        if (*s == c)
        {
            return s;
        }

        if (*s == '\0')
        {
            return NULL;
        }

        s++;
    }
}


/* ============================================================================
 *  2. str_reverse
 * ============================================================================
 *  Reverses s in place. Do not use a second array.
 *
 *  HINTS
 *   - Use one pointer at the first character and one at the LAST character
 *     (not at the '\0'). Swap what they point to, then move them toward
 *     each other.
 *   - When should the loop stop? Check by hand for "abc" and "abcd".
 *   - Careful with "": there is no last character. Make sure your end pointer
 *     never goes before the start of the string.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
void str_reverse(char *s)
{
    char *end = s;

    while (*end != '\0')
    {
        end++;
    }

    if (end == s)
    {
        return;
    }

    end--;

    while (s < end)
    {
        char temp = *s;
        *s = *end;
        *end = temp;

        s++;
        end--;
    }
}


/* ============================================================================
 *  3. str_compare_ci
 * ============================================================================
 *  Compares a and b ignoring case. Returns EXACTLY -1, 0, or 1.
 *  Convert uppercase letters to LOWERCASE before comparing (not uppercase).
 *  If one string ends first, the shorter one comes first.
 *
 *  HINTS
 *   - Walk both strings together, one character at a time.
 *   - Stop at the first position where the (lowercased) characters differ,
 *     or when you reach the end of either string.
 *   - When the loop ends, there are three possibilities: both strings ended,
 *     only a ended, or only b ended. Which result does each give?
 *   - Return -1 or 1 yourself. Do not return the difference of two
 *     characters: 'a' - 'z' is -25, not -1.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
int str_compare_ci(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        char char_a = *a;
        char char_b = *b;

        if (char_a >= 'A' && char_a <= 'Z')
        {
            char_a = char_a + ('a' - 'A');
        }

        if (char_b >= 'A' && char_b <= 'Z')
        {
            char_b = char_b + ('a' - 'A');
        }

        if (char_a < char_b)
        {
            return -1;
        }

        if (char_a > char_b)
        {
            return 1;
        }

        a++;
        b++;
    }

    if (*a == '\0' && *b == '\0')
    {
        return 0;
    }

    if (*a == '\0')
    {
        return -1;
    }

    return 1;
}


/* ============================================================================
 *  4. str_copy_bounded
 * ============================================================================
 *  Copies src into dst, where size is the TOTAL number of bytes in dst.
 *   - Copy at most size - 1 characters, then write '\0'.
 *   - If size is 0, write nothing at all.
 *   - Never write past dst[size - 1], and write nothing after the '\0'.
 *   - Return the length of src (NOT the number of characters copied).
 *     The caller detects truncation with: return value >= size.
 *
 *  HINTS
 *   - Your copy loop needs TWO reasons to stop: the end of src, and running
 *     out of room in dst. Which one comes first depends on the input.
 *   - If you move src forward while copying, it no longer points to the
 *     start of the string. Keep a pointer to the start if you need it later.
 *   - size is a size_t, which is unsigned: it can never be negative.
 *     What is size - 1 when size is 0? Handle size 0 before doing any math.
 *   - Draw dst as a row of boxes and fill them in by hand for
 *     ("hello", size 4) before you write any code.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
size_t str_copy_bounded(char *dst, const char *src, size_t size)
{
    size_t length = 0;
    size_t copied = 0;

    while (src[length] != '\0')
    {
        if (size > 0 && copied < size - 1)
        {
            dst[copied] = src[length];
            copied++;
        }

        length++;
    }

    if (size > 0)
    {
        dst[copied] = '\0';
    }

    return length;
}


/* ============================================================================
 *  5. str_find_sub
 * ============================================================================
 *  Returns a pointer to the FIRST place in hay where all of needle appears,
 *  or NULL if it never does. An empty needle is found at the start of hay.
 *
 *  HINTS
 *   - Try every starting position in hay, one at a time. At each one, check
 *     whether the whole needle matches from there (the matches_at helper).
 *   - If a match fails halfway, the next attempt starts ONE position after
 *     the previous START, not where the failure happened. Trace "aaab" and
 *     "aab" by hand to see why.
 *   - Never read past hay's '\0'. What should happen if hay ends while you
 *     are still in the middle of matching needle?
 *   - Pointers here are const char *. Any pointer you create to walk through
 *     hay or needle must be const char * as well, or you'll get a warning.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
const char *str_find_sub(const char *hay, const char *needle)
{
    if (*needle == '\0')
    {
        return hay;
    }

    while (*hay != '\0')
    {
        const char *p = hay;
        const char *q = needle;

        while (*p != '\0' && *q != '\0' && *p == *q)
        {
            p++;
            q++;
        }

        if (*q == '\0')
        {
            return hay;
        }

        hay++;
    }

    return NULL;
}


/* ============================================================================
 *  6. str_squeeze
 * ============================================================================
 *  Cleans up whitespace in s, in place, and returns the new length.
 *  Whitespace means ONLY ' ' and '\t' ('\n' is an ordinary character here).
 *   - Each run of whitespace between other characters becomes ONE space.
 *   - Whitespace at the start and end is removed completely.
 *
 *  HINTS
 *   - Use two pointers into the same array: a READ pointer that visits every
 *     character once, and a WRITE pointer that marks where the next kept
 *     character goes. Write never gets ahead of read. Why not?
 *   - When the read pointer reaches whitespace, skip the WHOLE run first.
 *     Then look at what comes next: more text, or the '\0'?
 *   - Always finish by writing '\0' at the write pointer.
 *   - The new length is how far the write pointer moved.
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
size_t str_squeeze(char *s)
{
    char *read = s;
    char *write = s;

    while (*read == ' ' || *read == '\t')
    {
        read++;
    }

    while (*read != '\0')
    {
        if (*read != ' ' && *read != '\t')
        {
            *write = *read;
            write++;
            read++;
        }
        else
        {
            while (*read == ' ' || *read == '\t')
            {
                read++;
            }

            if (*read != '\0')
            {
                *write = ' ';
                write++;
            }
        }
    }

    *write = '\0';

    return (size_t)(write - s);
}


/* ============================================================================
 *  7. str_split
 * ============================================================================
 *  Splits s into fields separated by delim, in place.
 *   - Replace EVERY delim in s with '\0'.
 *   - Store a pointer to the start of each field in fields[0], fields[1], ...
 *     but store at most max_fields pointers. Leave the rest of fields alone.
 *   - Return the TOTAL number of fields, even if it is more than max_fields.
 *   - A string with k delimiters has exactly k + 1 fields. Empty fields count.
 *
 *  HINTS
 *   - Keep a pointer to where the current field starts. Each time you find a
 *     delimiter, the current field ends there and a new one starts right
 *     after it.
 *   - The last field is never followed by a delimiter. Where does it start,
 *     and when do you store it?
 *   - Before EVERY write to fields[i], check that i < max_fields. Inside this
 *     function you cannot know how big the caller's array is.
 *   - If your logic is right, the empty string "" needs no special case.
 *     It has zero delimiters, so how many fields?
 *
 *  YOUR NOTES
 *   Approach:
 *
 *   Edge cases I handled:
 *
 *   How I tested it:
 *
 */
int str_split(char *s, char delim, char *fields[], int max_fields)
{
    int count = 1;

    if (max_fields > 0)
    {
        fields[0] = s;
    }

    while (*s != '\0')
    {
        if (*s == delim)
        {
            *s = '\0';
            count++;

            if (count <= max_fields)
            {
                fields[count - 1] = s + 1;
            }
        }

        s++;
    }

    return count;
}


/* ============================================================================
 *  main: YOUR testing area. The autograder ignores everything in here.
 * ============================================================================
 *  A few sample calls to get you started. Add your own, especially for the
 *  edge cases in the README. Remember: functions that MODIFY a string need a
 *  char array (char s[] = "..."), not a string literal (char *s = "...").
 */
int main(void)
{
    /* 1. str_find_char: print the offset, or NULL */
    const char *word = "hello";
    const char *pos = str_find_char(word, 'l');
    if (pos != NULL)
        printf("find_char: offset %d (expected 2)\n", (int)(pos - word));
    else
        printf("find_char: NULL (expected offset 2)\n");

    /* 2. str_reverse: needs an array */
    char rev[] = "hello";
    str_reverse(rev);
    printf("reverse: \"%s\" (expected \"olleh\")\n", rev);

    /* 3. str_compare_ci */
    printf("compare_ci: %d (expected -1)\n", str_compare_ci("apple", "Banana"));

    /* 4. str_copy_bounded: truncation */
    char small[4] = "";   /* starts empty, so printing is safe even before you write the function */
    size_t n = str_copy_bounded(small, "hello", sizeof small);
    printf("copy_bounded: returned %d, dst \"%s\" (expected 5, \"hel\")\n",
           (int)n, small);

    /* 5. str_find_sub */
    const char *hay = "aaab";
    const char *found = str_find_sub(hay, "aab");
    if (found != NULL)
        printf("find_sub: offset %d (expected 1)\n", (int)(found - hay));
    else
        printf("find_sub: NULL (expected offset 1)\n");

    /* 6. str_squeeze: brackets make leftover spaces visible */
    char messy[] = "  hello   world  ";
    size_t len = str_squeeze(messy);
    printf("squeeze: returned %d, [%s] (expected 11, [hello world])\n",
           (int)len, messy);

    /* 7. str_split */
    char line[] = "red,green,blue";
    char *fields[5];
    int count = str_split(line, ',', fields, 5);
    printf("split: returned %d (expected 3)\n", count);
    for (int i = 0; i < count && i < 5; i++)
        printf("  fields[%d] = [%s]\n", i, fields[i]);

    return 0;
}
