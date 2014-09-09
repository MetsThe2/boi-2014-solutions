/* Testing of solution to
https://docs.google.com/viewer?url=http://www.teaduskool.ut.ee/sites/default/
files/teaduskool/olympiaad/rahvusvahelised/boi_2013_14_proov_vork_est.pdf
*/

#include "find_route.h"

#define COMP_NUM 1000
#if COMP_NUM > MAX_COMP_NUM
#error
#endif

int main(void)
{
    /* Previously (maximized at?) 321713 pings with a = 429 and b = COMP_NUM = 1000.
    Takes 1141 after looping order optimization.
    Always takes < COMP_NUM * 2 (and > COMP_NUM) pings after using a sorted (by
    ping(i, b)) lookup table (if ping(i, b) >= ping(a, b), i isn't included in
    the table).
    This solution uses about 5 MB of memory and malloc. Define O_N_SQR for
    the original solution (which takes about 0.3 * COMP_NUM**2 pings). */
    unsigned a = (unsigned)((0.428) * COMP_NUM);
    unsigned b = COMP_NUM;
    if (a == b) ++b;

    findRoute(a, b, COMP_NUM);
    ping(0, 0); // Print number of pings used and reset.

    findRoute(b, a, COMP_NUM);
    ping(0, 0);

    return 0;
}
