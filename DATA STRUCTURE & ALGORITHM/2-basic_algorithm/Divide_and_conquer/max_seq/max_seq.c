#include <stdio.h>

int a[100] = {4, 7, 3, -6, -5, -7, 10, 2};
int maxLeft(int *a, int l, int r)
{
    int max = -999999;
    int s = 0;
    for (int i = r; i >= l; i--)
    {
        s += a[i];
        if (s > max)
            max = s;
    }
    return max;
}

int maxRight(int *a, int l, int r)
{
    int max = -999999;
    int s = 0;
    for (int i = l; i <= r; i++)
    {
        s += a[i];
        if (s > max)
            max = s;
    }
    return max;
}

int maxSeq(int *a, int l, int r)
{
    if (l == r)
        return a[l];
    int max;
    int mid = (l + r) / 2;
    int mL = maxSeq(a, l, mid);
    int mR = maxSeq(a, mid + 1, r);
    int mLR = maxLeft(a, l, mid) + maxRight(a, mid + 1, r);
    max = mL;
    if (max < mR)
        max = mR;
    if (max < mLR)
        max = mLR;
    return max;
}

int main()
{
    int result = maxSeq(a, 0, 7);
    printf("%d\n", result);
    return 0;
}