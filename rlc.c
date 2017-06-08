#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define h 0.001
#define R 2
#define L 1
#define C 1
#define u 1
#define t0 0.0
#define t_max 10.0
#define y0 0
#define z0 0

#define filename "rlc_data3.txt"

double func1(double ti, double yi, double zi)
{
	return zi;
}

double func2(double ti, double yi, double zi)
{
	double temp = 0;

	temp = (-R * C * zi - yi + u) / (L * C);

	return temp;
}

int main()
{
	FILE *fp;

	// 初期値
	double yi = y0, zi = z0, ti = t0;
	double ti_1, yi_1, zi_1;

	if ((fp = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ファイルのオープンに失敗\n");
		exit(1);
	}

	while(1) {
		yi_1 = yi + h * func1(ti, yi, zi);
		zi_1 = zi + h * func2(ti, yi, zi);
		ti_1 = ti + h;

		printf("%lf, %lf\n", ti, yi);
		fprintf(fp, "%lf %lf\n", ti, yi);

		if (!(ti <= t_max))
			break;

		yi = yi_1;
		zi = zi_1;
		ti = ti_1;
	}

	return 0;
}
