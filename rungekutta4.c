#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define h  0.02     // 刻み幅
#define t0 0.0      // 初期時刻
#define t_max 15.0  // 最終時刻
#define m 1         // 振り子の質量
#define k 1         // 粘性減衰係数
#define l 0.5       // 糸の長さ
#define g 9.80665   // 重力加速度
#define x0 0.5        // シータの初期値
#define z0 0        // シータ１階微分の初期値

#define filename "4ji_th05.txt"  // 出力ファイル名

double func1(double ti, double xi, double z)
{
	return z;
}

double func2(double ti, double xi, double z)
{
	double temp = 0;

	temp = (-1) * (k * l * z + m * g * sin(xi)) / (m * l);

	return temp;
}

int main()
{
	FILE *fp;
		
	// 初期値
	double xi = x0, zi = z0, ti = t0;
	double ti_1, xi_1, zi_1;
	double kx1, kz1, kx2, kz2;
	double kx3, kz3, kx4, kz4;

	if ((fp = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ファイルのオープンに失敗\n");
		exit(1);
	}
	
	while(1) {				
		kx1 = h * func1(ti, xi, zi);
		kz1 = h * func2(ti, xi, zi);

		kx2 = h * func1(ti + (h / 2.0), xi + (kx1 / 2.0), zi + (kz1 / 2.0));
		kz2 = h * func2(ti + (h / 2.0), xi + (kx1 / 2.0), zi + (kz1 / 2.0));

		kx3 = h * func1(ti + (h / 2.0), xi + (kx2 / 2.0), zi + (kz2 / 2.0));
		kz3 = h * func2(ti + (h / 2.0), xi + (kx2 / 2.0), zi + (kz2 / 2.0));

		kx4 = h * func1(ti + h, xi + kx3, zi + kz3);
		kz4 = h * func2(ti + h, xi + kx3, zi + kz3);

		xi_1 = xi + (1.0 / 6.0) * (kx1 + 2*kx2 + 2*kx3 + kx4);
		zi_1 = zi + (1.0 / 6.0) * (kz1 + 2*kz2 + 2*kz3 + kz4);

		ti_1 = ti + h;

		printf("%lf, %lf\n", ti, xi);
		fprintf(fp, "%lf %lf\n", ti, xi);
		
		if (!(ti <= t_max))
			break;

		xi = xi_1;
		zi = zi_1;
		ti = ti_1;
	}
	
	return 0;
}
