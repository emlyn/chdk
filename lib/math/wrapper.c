#include "math.h"

extern double _pow(double x, double y);
double pow(double x, double y) {
    return d2d( _pow( d2d(x), d2d(y) ) );
}

extern double _log(double x);
double log(double x) {
    return d2d( _log( d2d(x) ) );
}

//extern double _log2(double x);
double log2(double x) {
//    return d2d( _log2( d2d(x) ) );
    return (log10(x)/((double)0.30102999566398119521373889472449));
}

extern double _log10(double x);
double log10(double x) {
    return d2d( _log10( d2d(x) ) );
}

extern double _sqrt(double x);
double sqrt(double x) {
    return d2d( _sqrt( d2d(x) ) );
}
