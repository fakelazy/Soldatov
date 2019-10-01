#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
using namespace std;
int main(int argc, char *argv[]){

double start_time, end_time; //расчет времени, затраченного на операцию
int N = atoi(argv[1]); //размер матриц, задается в командной строке
cout << "N= " << N << endl;
double a[N][N], b[N][N], c[N][N]; //задаем квадратные матрицы

int thr=0; //начальное количество нитей
double t1, t2; //параметры времени
int i, j, k;   


// инициализация матриц
	for (i=0; i<N; i++){
        	for (j=0; j<N; j++){
           		 a[i][j]=b[i][j]=(i+1)*(j+1);
        	}
   	}	

//вывод матрицы
	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << a[i][j] << "\t"; 
		cout << endl;
	}*/

	//cout << endl << endl;

	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << b[i][j] << "\t"; 
		cout << endl;
	}*/


//задаем количество нитей thr
    for(thr=1; thr < 10; thr++){
	start_time = omp_get_wtime();

	#pragma omp parallel shared(a, b, c) private(i, j, k) num_threads(thr)

 	#pragma omp for
        for(i=0; i<N; i++){

            for(j=0; j<N; j++){
                c[i][j] = 0.0;
	        for(k=0; k<N; k++) c[i][j]+=a[i][k]*b[k][j];
            }
        }
	
    cout << "thread = " << thr << endl; //порядковый номер нити
    end_time = omp_get_wtime();

	cout << "time= " << end_time-start_time << endl;
       	//cout << "effic= " << fix/(end_time-start_time) << endl; //эффективность: t1/t, где t1 - время перемножения
    }                                                           //одним потоком, t - время перемножения на n потоках.
    

	/*for (i=0; i<N; i++){
		for (j=0; j<N; j++)
		cout << c[i][j] << "\t"; 
		cout << endl;
	}*/
}