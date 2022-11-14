#include <stdio.h>
#include <stdlib.h>

#define R_MAX 65535
#define MODULUS 65537
#define MULTIPLIER 75
#define INCREMENT 1
#define AMOUNT_TO_GENERATE 10000000
#define INITIAL_SEED_X 45
#define INITIAL_SEED_Y 78

#define IS_IN_CIRCLE(x, y) ((x * x) + (y * y)) < 1
#define PI_ESTIMATE_FORMULA(in_circle) (in_circle * 4) / (AMOUNT_TO_GENERATE * 1.0)

int pseudorandom_ZX81(int seed)
{
  return (MULTIPLIER * (seed + INCREMENT) % MODULUS) - INCREMENT;
}

double pi_ZX81()
{
  int seed_x = INITIAL_SEED_X;
  int seed_y = INITIAL_SEED_Y;
  double x_double, y_double;
  int counter = 0;
  for (int i = 0; i < AMOUNT_TO_GENERATE; i++)
  {
    seed_x = pseudorandom_ZX81(seed_x);
    seed_y = pseudorandom_ZX81(seed_y);
    x_double = (double)seed_x / (R_MAX + 1.0);
    y_double = (double)seed_y / (R_MAX + 1.0);
    if (IS_IN_CIRCLE(x_double, y_double))
      counter++;
  }
  return PI_ESTIMATE_FORMULA((double)counter);
}

double pi_c_rand()
{
  int counter = 0;
  double x_double, y_double;
  for (int i = 0; i < AMOUNT_TO_GENERATE; i++)
  {
    x_double = rand() / (RAND_MAX + 1.0);
    y_double = rand() / (RAND_MAX + 1.0);
    if (IS_IN_CIRCLE(x_double, y_double))
      counter++;
  }
  return PI_ESTIMATE_FORMULA((double)counter);
}

int main()
{
  double pi_ZX81_estimation = pi_ZX81();
  double pi_rand_estimation = pi_c_rand();
  printf("Przybliżenie pi wg ZX spectrum wynosi: %lf\n", pi_ZX81_estimation);
  printf("Przybliżenie pi wg funkcji bibliotecznej rand() wynosi: %lf\n", pi_rand_estimation);
}
