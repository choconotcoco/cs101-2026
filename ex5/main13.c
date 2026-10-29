#include <stdio.h>
void f(int i,int j)
{
    if(j==1)
    {
        printf("%d*%d=%d\n",i,j,i*j);
        return;
    }
    f(i,j-1);
    printf("%d*%d=%d\n",i,j,i*j);
}
int main()
{
    f(1,9);
    return 0;
}
