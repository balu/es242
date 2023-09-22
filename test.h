#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(NO_COLOR)
#define ANSI_COLOR_RED "\x1b[31;1m"
#define ANSI_COLOR_GREEN "\x1b[32;1m"
#define ANSI_COLOR_RESET "\x1b[0m"
#else
#define ANSI_COLOR_RED ""
#define ANSI_COLOR_GREEN ""
#define ANSI_COLOR_RESET ""
#endif
#define MAX_ASSERTS (100)

#define BEGIN_TEST(name) int test_##name() {      \
    const char *__name = #name;                   \
    int __marks = 0;                              \
    const char *__messages[MAX_ASSERTS] = { 0 };  \
    int __mcount = 0;                             \

#define END_TEST                                              \
    if (__mcount) {                                           \
        fprintf (stderr, "Test %-20s [%sFAIL%s]\n",           \
                 __name, ANSI_COLOR_RED, ANSI_COLOR_RESET);   \
        for (int i = 0; i < __mcount; ++i) {                  \
            fprintf(stderr, "  - %s\n", __messages[i]);       \
        }                                                     \
    } else {                                                  \
        fprintf(stderr, "Test %-20s [%s OK %s]\n",            \
                __name, ANSI_COLOR_GREEN, ANSI_COLOR_RESET);  \
    }                                                         \
    return __marks;                                           \
    }

#define TEST(name) test_##name

#define ASSERT_EQ(expr, expected, message)      \
    do {                                        \
        typeof(expr) __val = (expr);            \
        if (__val == expected) {                \
            ++__marks;                          \
        } else {                                \
            __messages[__mcount++] = message;   \
        }                                       \
    } while (0)

#define ASSERT_ARRAY_EQ(arr, n, expected, message)  \
    do {                                            \
        int __fail = 0;                             \
        for (int i = 0; i < n; i++) {               \
            if (arr[i] != expected[i]) {            \
                __fail = 1;                         \
                __messages[__mcount++] = message;   \
                break;                              \
            }                                       \
        }                                           \
        if(!__fail) ++__marks;                      \
    } while (0)

#define ASSERT_ARRAY_MEMBER(arr, n, elt, message) \
    do {                                          \
        int __success = 0;                        \
        for (int i = 0; i < n; i++) {             \
            if (arr[i] == elt) {                  \
                __success = 1;                    \
                break;                            \
            }                                     \
        }                                         \
        if (!__success) {                         \
            __messages[__mcount++] = message;     \
        }                                         \
    } while (0)                                   \

#define ASSERT_ARRAY_VALUES_EQ(arr, n, message, ...)    \
    do {                                                \
        typeof(arr[0]) __expected[] = { __VA_ARGS__ };  \
        int __fail = 0;                                 \
        for (size_t i = 0; i < n; i++) {                \
            if (arr[i] != __expected[i]) {              \
                __fail = 1;                             \
                __messages[__mcount++] = message;       \
                break;                                  \
            }                                           \
        }                                               \
        if(!__fail) ++__marks;                          \
    } while (0)

#define ASSERT(expr, message)                   \
    do {                                        \
        typeof(expr) __val = (expr);            \
        if (__val) {                            \
            ++__marks;                          \
        } else {                                \
            __messages[__mcount++] = message;   \
        }                                       \
    } while (0)

#define ASSERT_SATISFIES(expr, tester, message) \
    do {                                        \
        typeof(expr) __val = (expr);            \
        if ((tester)(__val)) {                  \
            ++__marks;                          \
        } else {                                \
            __messages[__mcount++] = message;   \
        }                                       \
    } while (0)


typedef int (*test_t)();

static inline int run_tests(test_t tests[])
{
    test_t current = *tests;
    int marks;
    while ((current = *tests++)) {
        marks += (*current)();
    }
    return marks;
}

#endif /* TEST_H */
