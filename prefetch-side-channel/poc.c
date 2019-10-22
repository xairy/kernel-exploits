#include <stdio.h>

// Set a few times higher than L2 size.
#define FLUSH_SIZE 4 * 1024 * 2014
unsigned char mem[FLUSH_SIZE];

inline void flush_cache() {
  int i;

  for (i = 0; i < FLUSH_SIZE; i++) {
    mem[i] = i;
  }
}

// You might need to configure these.
#define MAX_MEASURES 128
#define SCORE_MEASURES 16
#define DELAY_THRESHOLD 250

#define ADDR "0xffffffffffffffff"

inline unsigned int measure_once() {
  unsigned int lo1, hi1;
  unsigned int lo2, hi2;
  unsigned int time;

  flush_cache();

  __asm__ __volatile__ ("rdtsc" : "=a"(lo1), "=d"(hi1));
  __asm__ __volatile__ ("prefetcht2 " ADDR);
  __asm__ __volatile__ ("rdtsc" : "=a"(lo2), "=d"(hi2));

  time = (hi2 - hi1) * 0xffffffff - lo1 + lo2;
  return time;
}

inline unsigned int measure_max() {
  int i;
  unsigned int time;
  unsigned int max = 0;

  for (i = 0; i < MAX_MEASURES; i++) {
    time = measure_once();
    if (time > max) {
      max = time;
    }
  }

  return max;
}

inline unsigned int measure_score() {
  int i;
  unsigned int max;
  int score = 0;

  for (i = 0; i < SCORE_MEASURES; i++) {
    max = measure_max();
    if (max >= DELAY_THRESHOLD) {
      score++;
    }
  }

  return score;
}

int main() {
  int score;

  score = measure_score();
  printf("%f\n", (float)score / SCORE_MEASURES);

  return 0;
}
