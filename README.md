# Bad-Apple-Console

在 Windows 的控制台中通过 GDI 直接内存点像素来播放 Bad Apple 。

使用的是 `320 x 240, 60 fps` 的源。

1. 由于作者比较无聊，所以还附送了音频；

2. 由于作者不想压缩，因此直接把原始二进制用 7z 压缩了，凑合着用吧。

![效果](https://i.loli.net/2018/11/22/5bf684e9f0e05.png)

* * *

编译命令：

`g++ -o BA BA.cpp -lgdi32 -lwinmm`

编译成功后直接运行 `BA.exe` 即可。

如果想研究 `BA.bin` 的二进制表示方式，请阅读 `Compress.cpp` 。
