#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<chrono>
using namespace std;
double f(double x) {
    return exp(-x*x);
}
double integrate(double (*function)(double), double a, double b, int N) {
    if (b < a) {
        cout <<"The bounds are wrong\n";
        return -1;
    }
    double dx = b-a;
    int boundN = 10000;
    double max = function(a);
    double min = max;
    double boundDiv = dx/boundN;
    for (int i = 0; i < boundN; i++) {
        double value = function(a+i*boundDiv);
        if (value > max) {
            max = value;
        }
        if (value < min) {
            min = value;
        }
    }
    double dy = max - min;
    int areaSum = 0;
    srand(time(0));
    for (int i = 0; i < N; i++) {
        double ry = min + dy * ((double)rand() / RAND_MAX);
        double rx = a + dx * ((double)rand() / RAND_MAX);
        double y = function(rx);
        if (y > 0 && ry < y && ry > 0) {
            areaSum++;
        }
        if (y < 0 && ry > y && ry < 0) {
            areaSum--;
        }
    }
    return dx*dy*areaSum/N;
}
int main() {
    auto start = chrono::high_resolution_clock::now();
    cout << "Integral: " << integrate(f, -10, 10, 100000000) << endl;
    auto finish = chrono::high_resolution_clock::now();
    cout << "The calculation took " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count()/1000000000.0 << "s\n";
    return 0;
}
