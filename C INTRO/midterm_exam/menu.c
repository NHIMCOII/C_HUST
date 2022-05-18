#include <stdio.h>
int main()
{
  int a;
  printf("Bonjour!\nChoisir s'il vous plait!\n");
  printf("--------------------------\n\n");
  do
  {
    printf("1. Ex 8.1(n!)\n2. Ex 8.2(n! with menu)\n3. Ex 8.3(grade p or f)\n4. Ex 8.4(newton)\n5. Ex 8.5(avg grade)\n6. Exit\n\n");
    printf("Enter your choice(1 - 6): ");
    scanf("%d", &a);
    switch (a)
    {

    case 1:
    {
      int i = 1, n, f = 1;
      do
      {
        printf("Enter n: ");
        scanf("%d", &n);

      } while (n < 1);

      while (i <= n)
      {
        f = f * i;
        i++;
      }
      printf("n! = %d\n\n", f);
    }
    break;

    case 2:
    {
      int a;
      do
      {
        printf("1. Calculate n!\n2. Exit\n");
        printf("Enter your choice(1 or 2): ");
        scanf("%d", &a);
        switch (a)
        {

        case 1:
        {
          int i = 1, n, f = 1;
          do
          {
            printf("Enter n: ");
            scanf("%d", &n);

          } while (n < 1);

          while (i <= n)
          {
            f = f * i;
            i++;
          }
          printf("n! = %d\n\n", f);
        }
        break;

        case 2:
          printf("Quit\n\n");
          break;
        }
      } while (a != 2);
    }
    break;

    case 3:
    {
      int a, p = 0, f = 0, i = 1, g, s = 1;
      printf("Enter number of student: ");
      scanf("%d", &a);
      while (i <= a)
      {
        do
        {
          printf("Student number %d 's grade: ", s);
          scanf("%d", &g);
          if (g < 0 || g > 10)
            printf("Invalid input! Try again.\n");
        } while (g < 0 || g > 10);
        i++;
        s++;

        if (g >= 4)
        {
          p++;
        }
        if (g < 4)
        {
          f++;
        }
      }
      printf("------------------------------\n");
      printf("Passed: %d\n", p);
      printf("Failed: %d\n\n", f);
    }
    break;

    case 4:
    {
      float n, x, m, a;
      do
      {
        printf("Enter n: ");
        scanf("%f", &n);
      } while (n <= 0);
      x = n;
      do
      {
        a = (x + n / x) * 0.5;
        m = x;
        x = a;
      } while ((a - m) > 0.0001 || (a - m) < -0.0001);

      printf("Squareroot of %.2f is %.4f\n\n", n, a);
    }
    break;

    case 5:
    {
      int tong = 0, i, s = 1;
      float avg, dem = 0;

      printf("Enter grade list:\n");
      do
      {
        printf("Student number %d 's grade: ", s);
        s++;
        scanf("%d", &i);
        if (i >= 0)
        {
          dem++;
          tong += i;
          avg = tong / dem;
        }
      } while (i >= 0);

      printf("Average grade is %.2f\n\n", avg);
    }

    case 6:
    {
      printf("Au revoir!\n\n");
      break;
    }
    }
  } while (a != 6);
  return 0;
}
