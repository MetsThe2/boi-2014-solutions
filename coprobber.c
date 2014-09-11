#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static unsigned middle_of(bool **A, unsigned N)
{
  // Minimize maximum distance from any intersection.
  return N / 2; // Assuming the intersections are numbered in order.
}

static bool **connected;
static unsigned intersect_num;
static unsigned cop;

int start(unsigned N, bool **A)
{
  if (max_cycle_len(A, N) > 3) return -1;

  const size_t cnct_size = N * N * sizeof(bool);
  connected = malloc(cnct_size);
  assert(connected);
  memcpy(connected, A, cnct_size);

  intersect_num = N;

  return cop = middle_of(A, N);
}

static void move_cop(unsigned robber, unsigned target_dist)
{
  // cop = something
  assert(cop_robber_dist(robber) == target_dist);
}

unsigned nextMove(unsigned R)
{
  const unsigned d = cop_robber_dist(R);
  if (d) {
    move_cop(R, d - 1);
  } else if (connected) {
    free(connected);
    connected = NULL;
  }
  return cop;
}

int main(void)
{
  // How the functions are used.
  
  unsigned N = getN();
  bool **A = getA();
  
  int C = start(N, A);
  if (C == -1) return 1;

  unsigned R;
  do {
    R = getR(N, A, C);
    C = next_move(R);
  } while (C != R);
    
  return 0;
}
