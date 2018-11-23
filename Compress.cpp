#include <cstdio>

char s[20];
unsigned b[13140][19200];

int main(void)
{
    int i, j, k, v;
    FILE *f;

    for(k = 1; k <= 13140; k ++)
    {
        sprintf(s, "%07d.txt", k);
        f = fopen(s, "r");
        for(i = 0; i < 240; i ++)
        {
            for(j = 0; j < 320; j ++)
            {
                fscanf(f, "%d", &v); // 一个像素点的灰度值
                b[k - 1][i * 80 + (j >> 2)] |= v << ((j & 3) << 3);
            }
        }
        fclose(f);
        // fprintf(stderr, "%d\n", k);
    }

    f = fopen("BA.bin", "wb");
    fwrite(b, sizeof(b), 1, f);
    fclose(f);

    return 0;
}
