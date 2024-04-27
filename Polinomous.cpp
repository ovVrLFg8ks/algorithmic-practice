#include <iostream>
#include <cmath>
#include <string>
#include <io.h> 
#include <fcntl.h>

using namespace std;

class Polynom {
private:
    int n;          // polynomial power
    double * coeff; // array of coefficients
    /*
    Polynom(const int *n) : n(*n) {   // not assign coeffs
        coeff = new double[*n + 1];
    }
    */

    void allocate(int space) {
        n = space;
        coeff = new double[space + 1];
    }

    std::wstring powerToStr(int n) {
        std::wstring str;
        for (int i = 0; n; i++) {
            str = power[n % 10] + str;
            n /= 10;
        }
        return str;
    }

    static const wchar_t power[10];
    
public:
    Polynom() : coeff(NULL), n(-1) { }
    Polynom(int n) : n(n) {
        coeff = new double[n + 1] {0};
    }
    Polynom(const Polynom& poly) : n(poly.n) {
        coeff = new double[n + 1];
        memcpy(coeff, poly.coeff, sizeof(double) * (n + 1));
    }
    Polynom(int power, double *arr) : n(power) {
        coeff = new double[power + 1];
        memcpy(coeff, arr, sizeof(double) * (power + 1));
    }
    ~Polynom() {
        delete[] coeff;
    }

    int getPower() {
        return n;
    }
    double& operator[](int i) const {
        if (i <= n || i >= 0)
            return coeff[i];
        throw std::out_of_range("");
    }
    double getCoefficient(int i) {
        if (i <= n || i >= 0)
            return coeff[i];
        throw std::out_of_range("");
    }
    double calculate(double x) {
        double result = 0;
        for (int i = 0; i <= n; i++)
            result += coeff[i] * pow(x, i);
        return result;
    }
    void graph(int size, int startX, int endX, int startY, int endY) {
        char** out = new char* [size];
        for (int i = 0; i < size; i++) {
            out[i] = new char[size]{0};
        }
        double stepX = double(endX - startX) / size;
        double stepY = double(endY - startY) / size;
        for (int i = 0; i < size; i++) {
            double res = calculate(startX+i*stepX);
            if (res >= startY && res <= endY) {
                out[int((res - startY) / stepY)][i] = '*';
            }
        }

        // drawing
        if (0 >= startY && 0 <= endY && 0 >= startX && 0 <= endX) {
            char &point = out[int((0 - startY) / stepY)][int(-startX / stepX)];
            if (point == '*')
                point = '@';
            else
                point = '+';
        }
        wcout << L"┌";
        for (int j = 1; j <= size; j++)
            wcout << L"──";
        wcout << L"─┐";
        for (int i = size-1; i >= 0; i--) {
            wcout << L"\n│";
            for (int j = 0; j < size; j++) {
                if (out[i][j] == '*')
                    wcout << L" ●";
                else if (out[i][j] == '+')
                    wcout << L" +";
                else if (out[i][j] == '@')
                    wcout << L" ■";
                //else if ((i+j) % 2)
                //    wcout << L" ˖";
                else
                    wcout << L"  ";
            }
            if (i == size-1)
                wcout << L" ├ " << endY;
            else if (i == 0)
                wcout << L" ├ " << startY;
            else
                wcout << L" │";
        }
        wcout << L"\n└┬─";
        for (int j = 2; j <= size; j++)
            wcout << L"──";
        wcout << L"┬┘\n";

        wcout << startX;
        for (int i = 0; i < size-1; i++)
            wcout << L"  ";
        wcout << L" " << endX << L'\n';

        for (int i = 0; i < size; ++i) {
            delete[] out[i];
        }
        delete[] out;
    }

    void print(bool ret = true) {
        int i = n;
        for (; i > 1; i--) {
            if (coeff[i] > 0) {
                if (i == n)
                    std::wcout << coeff[i] << L'x' << powerToStr(i);
                else
                    std::wcout << L" + " << coeff[i] << L'x' << powerToStr(i);
            }
            else if (coeff[i] < 0)
                std::wcout << L" - " << abs(coeff[i]) << L'x' << powerToStr(i);
        }
        if (i == 1) {
            if (coeff[1] > 0)
                std::wcout << L" + " << coeff[i--] << L'x';
            else if (coeff[1] < 0)
                std::wcout << L" - " << abs(coeff[i--]) << L'x';
        }
        if (i == 0) {
            if (coeff[0] > 0)
                std::wcout << L" + " << coeff[0];
            else if (coeff[0] < 0)
                std::wcout << L" - " << abs(coeff[0]);
        }
        if (ret)
            std::wcout << '\n';
    }

    Polynom operator=(const Polynom& poly) {
        if (this != &poly)
        {
            delete[] coeff;
            n = poly.n;
            coeff = new double[n + 1];
            memcpy(coeff, poly.coeff, sizeof(double) * (n + 1));
        }
        return *this;
    }
    Polynom operator+(double val) {
        if (!coeff)
            throw std::out_of_range("Empty polynomial");
        Polynom out(*this);
        out.coeff[0] = coeff[0] + val;
        return out;
    }
    Polynom operator+(const Polynom& poly) {
        Polynom out;
        if (n >= poly.n) {
            out.allocate(n);
            for (int i = 0; i <= poly.n; i++)
                out.coeff[i] = coeff[i] + poly.coeff[i];
            for (int i = poly.n + 1; i <= n; i++)
                out.coeff[i] = coeff[i];
        }
        else {
            out.allocate(poly.n);
            for (int i = 0; i <= n; i++)
                out.coeff[i] = coeff[i] + poly.coeff[i];
            for (int i = n + 1; i <= poly.n; i++)
                out.coeff[i] = poly.coeff[i];
        }
        return out;
    }
    void operator+=(double val) {
        if (!coeff)
            throw std::out_of_range("Empty polynomial");
        coeff[0] += val;
    }
    void operator+=(const Polynom& poly) {
        if (n >= poly.n) {
            for (int i = 0; i <= poly.n; i++)
                coeff[i] = coeff[i] + poly.coeff[i];
        }
        else {
            double* t = new double[poly.n + 1];
            for (int i = 0; i <= n; i++)
                t[i] = coeff[i] + poly.coeff[i];
            for (int i = n + 1; i <= poly.n; i++)
                t[i] = poly.coeff[i];
            n = poly.n;
            delete[] coeff;
            coeff = t;
        }
    }
    
    Polynom operator-(double val) {
        if (!coeff)
            throw std::out_of_range("Empty polynomial");
        Polynom out(*this);
        out.coeff[0] = coeff[0] - val;
        return out;
    }
    Polynom operator-(const Polynom& poly) {
        Polynom out;
        if (n >= poly.n) {
            out.allocate(n);
            for (int i = 0; i <= poly.n; i++)
                out.coeff[i] = coeff[i] - poly.coeff[i];
            for (int i = poly.n + 1; i <= n; i++)
                out.coeff[i] = coeff[i];
        }
        else {
            out.allocate(poly.n);
            for (int i = 0; i <= n; i++)
                out.coeff[i] = coeff[i] - poly.coeff[i];
            for (int i = n + 1; i <= poly.n; i++)
                out.coeff[i] = poly.coeff[i];
        }
        return out;
    }
    void operator-=(double val) {
        if (!coeff)
            throw std::out_of_range("Empty polynomial");
        coeff[0] -= val;
    }
    void operator-=(const Polynom& poly) {
        if (n >= poly.n) {
            for (int i = 0; i <= poly.n; i++)
                coeff[i] = coeff[i] - poly.coeff[i];
        }
        else {
            double* t = new double[poly.n + 1];
            for (int i = 0; i <= n; i++)
                t[i] = coeff[i] - poly.coeff[i];
            for (int i = n + 1; i <= poly.n; i++)
                t[i] = -poly.coeff[i];
            n = poly.n;
            delete[] coeff;
            coeff = t;
        }
    }
    
    Polynom operator*(double val) {
        Polynom out;
        out.allocate(n);
        for (int i = 0; i <= n; i++)
            out.coeff[i] = coeff[i] * val;
        return out;
    }
    Polynom operator*(const Polynom& poly) {
        Polynom out(n + poly.n);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= poly.n; j++) {
                out.coeff[i + j] += coeff[i] * poly.coeff[j];
            }
        }
        return out;
    }
    void operator*=(double val) {
        for (int i = 0; i <= n; i++)
            coeff[i] *= val;
    }
    void operator*=(const Polynom& poly) {
        int oldN = n;
        n = n + poly.n;
        double* t = new double[n + 1] {0};
        for (int i = 0; i < oldN; i++) {
            for (int j = 0; j < poly.n; j++) {
                t[i + j] += coeff[i] * poly.coeff[j];
            }
        }
        delete[] coeff;
        coeff = t;
    }

    Polynom operator/(double val) {
        if (val == 0)
            throw std::invalid_argument("Division by zero");
        Polynom out;
        out.allocate(n);
        for (int i = 0; i <= n; i++)
            out.coeff[i] = coeff[i] / val;
        return out;
    }
    void operator/=(double val) {
        if (val == 0)
            throw std::invalid_argument("Division by zero");
        for (int i = 0; i <= n; i++)
            coeff[i] /= val;
    }
    /*
    Polynom operator/(const Polynom& poly) {
        Polynom out(n + poly.n);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= poly.n; j++) {
                if (coeff[i] == 0 || coeff[j] == 0)
                    continue;
                out.coeff[i + j] += coeff[i] / poly.coeff[j];
            }
        }
        return out;
    }
    */
};

const wchar_t Polynom::power[] = {L'⁰', L'¹', L'²', L'³', L'⁴', L'⁵', L'⁶', L'⁷', L'⁸', L'⁹'};

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    double a1[] = { 2, 3, 5, 7 };
    double a2[] = { 4, 6, 2 };
    //double a7[] = { 2, 3, 5, 7, 11, 13, 17 };
    Polynom p1(3, a1);
    Polynom p2(2, a2);
    wcout << "p1 =       "; p1.print();
    wcout << "p2 =             "; p2.print();

    Polynom p3(p1 + p2);
    wcout << "p1 + p2 =  "; p3.print();

    p3 = p1 - p2;
    wcout << "p1 - p2 =  "; p3.print();

    p3 = p1 * p2;
    wcout << "p1 * p2 =  "; p3.print();

    wcout << "p1 / p2 = not implemented\n";
    p3 /= 4;
    wcout << "p1 * p2 / 4 =  "; p3.print();

    
    
    double a[] = { 1, 1, -1.3, -0.1, 0.1 };
    Polynom pa(4, a);
    pa.print();
    pa.graph(44, -5, 5, -5, 5);

    wcout << "calculate function of "; pa.print();
    wcout << " x  value\n";
    for (int i = -5; i <= 5; i++)
        wcout << i << ": " << pa.calculate(i) << endl;
    
    double b[] = { 0, 0, 1 };
    Polynom pb(2, b);
    pb.print();
    pb.graph(20, -4, 4, 0, 8);
    
}
