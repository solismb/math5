#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define h0 0.001    // 刻み幅
#define t0 0.0      // 初期時刻
#define t_max 15.0  // 最終時刻
#define m 1         // 振り子の質量
#define k 1         // 粘性減衰係数
#define l 0.5       // 糸の長さ
#define g 9.80665   // 重力加速度
#define x0 1        // シータの初期値
#define z0 0        // シータ１階微分の初期値

#define filename "m1_data3.txt"  // 出力ファイル名

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
	
	// 刻み幅 (0.05, 0.02, 0.001)
	double h = h0;
	
	// 初期値
	double xi = x0, zi = z0, ti = t0;
	double ti_1, xi_1, zi_1;

	if ((fp = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ファイルのオープンに失敗\n");
		exit(1);
	}
	
	while(1) {				
		xi_1 = xi + h * func1(ti, xi, zi);
		zi_1 = zi + h * func2(ti, xi, zi);
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
