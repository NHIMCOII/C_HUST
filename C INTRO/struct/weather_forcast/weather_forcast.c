#include <stdio.h>
typedef struct _info_
{
    float total_rainfall,
        high_temp,
        low_temp,
        avg_temp;
} info;

int main()
{
    info m[13];
    int i;
    float avg, total = 0, low, high;
    for (i = 1; i < 13; i++)
    {
        printf("Month No.%d\n", i);
        do{printf("Total rainfall: ");
        scanf("%f", &m[i].total_rainfall);}while(m[i].total_rainfall<0||m[i].total_rainfall>1000);
        do{do
        {
            printf("Highest temperature: ");
            scanf("%f", &m[i].high_temp);
        } while (m[i].high_temp < -40 || m[i].high_temp > 50);
        do
        {
            printf("Lowest temperature: ");
            scanf("%f", &m[i].low_temp);
        } while (m[i].low_temp < -40 || m[i].low_temp > 50);}while (m[i].low_temp>m[i].high_temp);
          
        do
        {
            printf("Average temperature: ");
            scanf("%f", &m[i].avg_temp);
        } while ((m[i].high_temp < m[i].avg_temp) || m[i].low_temp > m[i].avg_temp);
        printf("\n");
    }
    low = m[1].low_temp;
    high = m[1].high_temp;
    int k, t;
    for (i = 1; i < 13; i++)
    {
        total += m[i].total_rainfall;
        if (low > m[i].low_temp)
        {
            low = m[i].low_temp;
            k = i;
        }
        if (high < m[i].high_temp)
        {
            high = m[i].high_temp;
            t = i;
        }
    }
    avg = total / 12;

    printf("Average rainfall: %.2f\n", avg);
    printf("Total rainfall: %.2f\n", total);
    printf("Lowest temperature(No.%d): %.2f\n", k, low);
    printf("Highest temperature(No.%d): %.2f\n", t, high);
    return 0;
}