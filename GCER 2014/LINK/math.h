// Created on Sun June 15 2014
#ifndef _MATH_HPP_
#define _MATH_HPP_

double dfx(double (*f)(double), double x0) {
    const double delta = 1.0e-6; // or similar
    double x1 = x0 - delta;
    double x2 = x0 + delta;
    double y1 = f(x1);
    double y2 = f(x2);
    return (y2 - y1) / (x2 - x1);
}

double dpt(double errprev, double errnow) {
	const double delta = 1.0e-6

/*
#include <math.h>

double der = derive(sin, 0.0);
printf("%lf\n", der); // should be around 1.0
*/

#endif
