#include <assert.h>
#include <stdlib.h> // abs, malloc
#include <stdio.h>  // printf
#include <string.h> // memset

// #define printf(...) // For profiling
// #define O_N_SQR     // For lower memory usage / comparison with new algorithm

#include "find_route.h"

int ping(unsigned a, unsigned b) // Sample implementation
{
    static unsigned ping_count = 0;
    if (a != 0) {
        ++ping_count;
        // printf("p %u %u\n", a, b);
        return abs(a - b) - 1;
    }
    printf("\n%u pings\n\n", ping_count);
    ping_count = 0;
    return -1;
}

void travelTo(unsigned u) // Sample implementation
{
    printf("%u ", u);
}

#ifdef O_N_SQR
// Lookup table for computers already on the route. If branching is very
// expensive, keeping a sorted array of computers to skip and iterating
// between them may be more efficient than this.
static unsigned char on_route[MAX_COMP_NUM] = {};

static void helper(unsigned a, unsigned b, int dist_a_b, unsigned n)
{
    if (dist_a_b == 0) {
        travelTo(b);
        return;
    }

#define BODY \
    if (on_route[i]) continue; \
\
    int dist_a_i = ping(a, i); \
    if (dist_a_i > dist_a_b) continue; \
\
    int dist_i_b = ping(i, b); \
    if (dist_i_b > dist_a_b) continue; \
\
    if (dist_a_i < dist_a_b || dist_i_b < dist_a_b) { \
        on_route[i] = 1; \
        helper(a, i, dist_a_i, n); \
        helper(i, b, dist_i_b, n); \
        return; \
    }
// Iterate from n to 1 in reverse for better worst case?
    for (unsigned i = a + 1; i <= n; ++i) { BODY }
    for (unsigned i = 1;     i <  a; ++i) { BODY }
#undef BODY
    // Should never get here.
}
#endif // O_N_SQR

void findRoute(unsigned a, unsigned b, unsigned n)
{
    printf("a: %u, b: %u, n: %u\n", a, b, n);

    if (n == 2) {
        travelTo(b);
        return;
    }

#ifdef O_N_SQR
    on_route[a] = 1;
    on_route[b] = 1;
    helper(a, b, ping(a, b), n);
    memset(on_route, 0, n); // Unnecessary if this function will only be called once.

#else // O_N_SQR
    int pab = ping(a, b);
    if (pab == 0) {
        travelTo(b);
        return;
    }

    // 4 million byte (MAX_COMP_NUM**2 * sizeof(unsigned)) static array
    // resulted in segfault.
    unsigned *lut_mem = malloc(pab * n * sizeof(*lut_mem));
    assert(lut_mem);

    unsigned *lut[pab];
    for (unsigned i = 0; i < pab; ++i) lut[i] = lut_mem + (i * n);

    unsigned top[n]; // Top of each ping stack
    memset(top, 0, n * sizeof(*top));

    for (unsigned i = 1; i <= n; ++i) {
        if (i == a || i == b) continue;

        unsigned pib = ping(i, b);
        if (pib >= pab) continue;

        assert(top[pib] < n);
        lut[pib][top[pib]++] = i;
    }

    unsigned cur = a;
    for (int i = pab - 1; i >= 0; --i) {
        for (unsigned j = 0; j < n; ++j) {
            if (ping(cur, lut[i][j]) == 0) {
                cur = lut[i][j];
                travelTo(cur);
                break;
            }
        }
    }
    travelTo(b);
#endif // O_N_SQR
}
