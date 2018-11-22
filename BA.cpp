#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#define N 13140
#define W 320
#define H 240

HDC d, g;
HBITMAP m;
unsigned f[N][H * (W >> 2)];
DWORD r[H][W];
int c;

void ReadFile(void)
{
    FILE *e;

    system("7z.exe e BA.7z");
    e = fopen("BA.bin", "rb");
    fread(f, sizeof(f), 1, e);
    fclose(e);
    system("cls");
    mciSendString("open BA.mp3 alias BA", NULL, 0, NULL);
    mciSendString("play BA", NULL, 0, NULL);

    return;
}

void RemoveFile(void)
{
    mciSendString("close BA", NULL, 0, NULL);
    system("del BA.bin BA.mp3");

    return;
}

void ConsoleDC(void)
{
    d = GetDC(GetConsoleWindow());
    g = CreateCompatibleDC(d);
    m = CreateCompatibleBitmap(d, W, H);
    SelectObject(g, m);

    return;
}

void HideCC(void)
{
    HANDLE h;
    CONSOLE_CURSOR_INFO c;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    if(GetConsoleCursorInfo(h, &c))
    {
        c.bVisible = FALSE;
        SetConsoleCursorInfo(h, &c);
    }

    return;
}

void Drawframe(int k)
{
    int i, j, t;
    BITMAPINFO b;

    for(i = 0; i < H; i ++)
        for(j = 0; j < W; j ++)
        {
            t = (f[k - 1][i * 80 + (j >> 2)] & ((1ULL << (((j & 3) + 1) << 3)) - 1)) >> ((j & 3) << 3);
            r[H - i - 1][j] = RGB(t, t, t);
        }

    b.bmiHeader.biBitCount = 32;
    b.bmiHeader.biCompression = 0;
    b.bmiHeader.biWidth = W;
    b.bmiHeader.biHeight = H;
    b.bmiHeader.biPlanes = 1;
    b.bmiHeader.biSizeImage = 0;
    b.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SetDIBits(d, m, 0, H, r, (BITMAPINFO *)&b, DIB_RGB_COLORS);
    BitBlt(d, 0, 0, W, H, g, 0, 0, SRCCOPY);

    t = (k / 60) * 1000 + (k % 60) * 16;
    while(clock() - c < t)
        Sleep(1);

    return;
}

int main(void)
{
    int k;

    HideCC();
    ReadFile();
    ConsoleDC();

    c = clock();
    for(k = 1; k <= N; k ++)
        Drawframe(k);
    RemoveFile();

    return 0;
}
