#include "Matrix.h"


Matrix::Matrix(void)
{
	n = 0;
}

Matrix::Matrix(float a, float b, float c, float w)
{
	//vector init
	v[0][3] = a;
	v[0][2] = b;
	v[0][1] = c;
	v[0][0] = w;
	n = 1;
}

Matrix::~Matrix(void)
{
}

Matrix Matrix::multiply(Matrix m) {
	float col[4];
	Matrix r = Matrix();
		
	if(n ==1) {
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				col[j] = v[0][j]*m.get(i,3) + v[0][j]*m.get(i,2) + v[0][j]*m.get(i,1) + v[0][j]*m.get(i,0);
			}
			r.addColumn(col[0], col[1], col[2], col[3]);
		}
	} else if (n == 4) {
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				col[j] = v[0][j]*m.get(i,3) + v[1][j]*m.get(i,2) + v[2][j]*m.get(i,1) + v[3][j]*m.get(i,0);
			}
			r.addColumn(col[3], col[2], col[1], col[0]);
		}
	}

	return r;
}


Matrix Matrix::cross(Matrix m) {
	Matrix r = Matrix();
	if(n == 1) {
		r.addColumn((v[0][2]*m.get(0,1)) - (v[0][1]*m.get(0,2)),
					(v[0][1]*m.get(0,3)) - (v[0][3]*m.get(0,1)),
					(v[0][3]*m.get(0,2)) - (v[0][2]*m.get(0,3)), 0);
	}
	return r;
}

float Matrix::get(int i, int j) {
	return v[i][j];
}

void Matrix::set(int i, int j, float f) {
	v[i][j] = f;
}

void Matrix::addColumn(float a, float b, float c, float d) {
	v[n][3] = a;
	v[n][2] = b;
	v[n][1] = c;
	v[n][0] = d;
	n++;
}

void Matrix::print() {
	for(int j=3; j>=0; j--) {
		//cout << "[ ";
		for(int i=0; i<n; i++) {
			//cout << v[i][j] << " ";
		}
		//cout << "]\n";
	}
	//cout << "\n";
}