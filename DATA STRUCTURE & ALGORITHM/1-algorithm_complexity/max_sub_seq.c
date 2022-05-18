#include <stdio.h>
#include <limits.h>
// 
int start, end;// 2 đầu của chuỗi con cần tìm

int maxSubSeq3(int *array, int n)
{
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int s = 0;
            for (int k = i; k <= j; k++)
            {
                s += array[k];
            }
            if (s > ans)
            {
                ans = s;
                start = i;
                end = j;
            }
        }
    }
    return ans;
}

int maxSubSeq2(int *array, int n)
{
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int s = 0;
        for (int j = i; j < n; j++)
        {
            s += array[j];
            if (s > ans)
            {
                ans = s;
                start = i;
                end = j;
            }
        }
    }
    return ans;
}

int maxSubSeq1(int *array, int n)
{
    int s[n];
    s[0] = array[0];
    int ans = s[0];
    for (int i = 1; i < n; i++)
    {
        if (s[i - 1] > 0)
            s[i] = s[i - 1] + array[i];
        else{
            s[i] = array[i];
        }
        if (ans < s[i])
        {
            ans = s[i];
            end = i;
        }
    }
// tìm điểm đầu chuỗi con
    int best=INT_MIN,sum=0;
    int current_start =0;
    for(int i=0;i<n;i++){
        if(sum+array[i]<array[i]){
            current_start=i;
            sum=array[i];
        }
        else{
            sum+=array[i];
        }

        if(best<sum){
            best=sum;
            start=current_start;
        }
    }
     return ans;
}

// Input case: 2 -10 11 -4 13 -5 2 (n=7)
// Input case: 4 5 2 6 1 8 3 6     (n=8)
// Input case: -8 -4 -6 -3 -5 -7   (n=6)
// Input case: -1 10 -11 4 -5 8 -5 (n=7)
// Input case: -1 10 -11 4 6 8 -5  (n=7)
// Input case: 4 7 3 -6 -5 -7 10 2 (n=8)

int main()
{
    int array[100];
    int n;

    printf("\nEnter n: ");
    scanf("%d", &n);
    printf("Input > ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    // thay đổi hàm maxSubSeq?() để chọn các cách(1,2,3)
    int result = maxSubSeq2(array, n);//trọng số của chuỗi con lớn nhất

    printf("Max subsequence: \n");
    for (int i = start; i <= end; i++)//in ra chuỗi con lớn nhất
    {
        printf("%d ", array[i]);
    }
    printf("=> %d\n\n", result);// in trọng số của chuỗi con lớn nhất
    return 0;
}
