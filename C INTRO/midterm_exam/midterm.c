#include <stdio.h>
int main()
{
  char c;
  do
  {
    int a, n = 1, A = 0, B = 0, C = 0, D = 0, E = 0, F = 0;
    float s, max = 50, min = 10000, sum = 0, avg;

    do
    {
      printf("Please enter the number of employees: ");
      scanf("%d", &a);
      if (a < 3 || a > 10)
        printf("Invalid!\n");
    } while (a < 3 || a > 10);

    while (n <= a)
    {
      do
      {
        printf("Please enter the salary of the emloyee, No. %d: ", n);
        scanf("%f", &s);
        if (s < 50 || s > 10000)
          printf("Invalid!\n");
      } while (s < 50 || s > 10000);
      n++;

      if (s >= 5000 && s <= 10000)
        A++;
      else if (s >= 2000 && s < 5000)
        B++;
      else if (s > 1000 && s < 2000)
        C++;
      else if (s >= 500 && s < 1000)
        D++;
      else if (s >= 100 && s < 500)
        E++;
      else if (s < 100)
        F++;

      if (s < min)
        min = s;
      if (s > max)
        max = s;
      sum += s;
    }
    avg = sum / a;

    printf("Statistics:\n");
    printf("     Salary levels\n");
    printf("          A: %d\n", A);
    printf("          B: %d\n", B);
    printf("          C: %d\n", C);
    printf("          D: %d\n", D);
    printf("          E: %d\n", E);
    printf("          F: %d\n", F);
    printf("     Maximal salary: %.2f\n", max);
    printf("     Worst salary: %.2f\n", min);
    printf("     Average salary: %.2f\n", avg);

    printf("Do you want to repeat the program ? ");

    scanf("%s", &c);

  } while (c == 'y' || c == 'Y');

  return 0;
}
