#ifndef _MACHAR_H_

void machar(int *ibeta, int *it, int *irnd, int *ngrd,
	int *machep, int *negep, int *iexp, int *minexp, int *maxexp,
	float *eps, float *epsneg, float *xmin, float *xmax);
void machar_double(int *ibeta, int *it, int *irnd, int *ngrd,
    int *machep, int *negep, int *iexp, int *minexp, int *maxexp,
    double *eps, double *epsneg, double *xmin, double *xmax);

#endif /* _MACHAR_H_ */
