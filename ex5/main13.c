#include <stdio.h>
void f(int i,int j)
{
    if(i>9) return;
    if(j==1)
    {
        printf("%d*%d=%d ",i,j,i*j);
        return;
    }
    f(i,j-1);
    printf("%d*%d=%d ",i,j,i*j);
    if(j==9)
    {
        printf("\n");
        f(i+1,9);
    }
}
int main()
{
    f(1,9);
    return 0;
}
