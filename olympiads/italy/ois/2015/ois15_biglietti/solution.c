#include <stdio.h>
#include <sys/param.h>

int compra(n, m, a, b) 
    int n;
    int m;
    int a;
    int b;
{
    return n/m*MIN(a*m, b) + MIN(a*(n%m), b);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);

    int (*susptr)(int, int, int, int) = compra;

    int cost;

    asm(
        "mov    %1, %%edi;"
        "mov    %2, %%esi;"
        "mov    %3, %%edx;"
        "mov    %4, %%ecx;"
        "call   *%5;"
        "mov    %%eax, %0;"
        : "=r" (cost)
        : "r" (n), "r" (m), "r" (a), "r" (b), "r" (susptr)
        : "rax", "rdi", "rsi", "rdx", "r10"
    );

    printf("%d\n", cost);
}