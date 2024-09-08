#pragma once

#include <Windows.h>
#include <stdexcept>

class ConsoleViewport {
private:
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, height, widthP1, screenSize;

#define WIDECHAR true
#if WIDECHAR
#define CHARTYPE wchar_t
    CHARTYPE* screen;
#else
#define CHARS char
    CHARS* screen;
#endif

public:
    ConsoleViewport() {
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top;
        widthP1 = width + 1;
        screenSize = widthP1 * height;
        screen = new CHARTYPE[screenSize];
        for (int i = 0; i < height; i++) {
            screen[width + widthP1 * i] = '\n';
        }
        screen[screenSize - 1] = '\0';
    }

    ~ConsoleViewport() {
        delete[] screen;
    }

    void inline SafeScreen(int& x, int& y, CHARTYPE ch) noexcept {
        if (x >= width || y >= width)
            throw std::out_of_range("too big index");
        if (x < 0 || y < 0)
            throw std::out_of_range("negative index");
        screen[x + y * widthP1] = ch;
    }

    CHARTYPE inline SafeScreen(int& x, int& y) const noexcept {
        if (x >= width || y >= width)
            throw std::out_of_range("too big index");
        if (x < 0 || y < 0)
            throw std::out_of_range("negative index");
        return screen[x + y * widthP1];
    }

    void inline Screen(int& x, int& y, CHARTYPE ch) noexcept {
        screen[x + y * widthP1] = ch;
    }

    CHARTYPE inline Screen(int& x, int& y) const noexcept {
        return screen[x + y * widthP1];
    }

    void inline Update() {
        SetConsoleCursorPosition(hStdOut, { 0, 0 });
#if WIDECHAR
        WriteConsoleW(hStdOut, screen, screenSize, NULL, NULL);
#else
        printf(screen);
#endif
    }

    int inline GetWidth() noexcept {
        return width;
    }

    int inline GetHeight() noexcept {
        return height;
    }

#undef WIDECHAR
#undef CHARS
};
