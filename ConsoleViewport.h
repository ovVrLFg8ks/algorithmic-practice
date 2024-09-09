#pragma once

#include <stdexcept>

#ifdef _WIN32
	#include <Windows.h>
#elif __linux__
	#include <sys/ioctl.h>
#endif


class ConsoleViewport {

private:
#ifdef _WIN32
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif
    int width, height, widthP1, screenSize;


#define WIDECHAR true

#if WIDECHAR
#define CHARTYPE wchar_t
#else
#define CHARTYPE char
#endif
    CHARTYPE* screen;

public:
    ConsoleViewport() {
#ifdef _WIN32
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top;
#elif __linux__
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
#endif // Windows/Linux

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

    void inline SafeScreen(int& x, int& y, CHARTYPE ch) {
        if (x >= width || y >= width)
            throw std::out_of_range("too big index");
        if (x < 0 || y < 0)
            throw std::out_of_range("negative index");
        screen[x + y * widthP1] = ch;
    }

    CHARTYPE inline SafeScreen(int& x, int& y) const {
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
#ifdef _WIN32
        SetConsoleCursorPosition(hStdOut, { 0, 0 });
        WriteConsole(hStdOut, screen, screenSize, NULL, NULL);
#elif __linux__
        printf("%c[0;0f",0x1B);
        printf("%ls", screen);
#endif
    }

    int inline GetWidth() noexcept {
        return width;
    }

    int inline GetHeight() noexcept {
        return height;
    }

#undef WIDECHAR
#undef CHARTYPE
};
