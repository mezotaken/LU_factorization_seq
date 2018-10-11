#include <iostream>
#include <vector>

using namespace std;

void LUfactor(vector <vector <double>> A, vector <vector <double>> &L,
	vector <vector <double>> &U)
{
	U = A;
	int n = A.size();
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			L[j][i] = U[j][i] / U[i][i];

	for (int k = 1; k < n; k++)
	{
		for (int i = k - 1; i < n; i++)
			for (int j = i; j < n; j++)
				L[j][i] = U[j][i] / U[i][i];

		for (int i = k; i < n; i++)
			for (int j = k - 1; j < n; j++)
				U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
	}

}

void Mult(vector <vector <double>> A, vector <vector <double>> B,
	vector <vector <double>> &R)
{
	int n = A.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				R[i][j] += A[i][k] * B[k][j];
}

void show(vector <vector <double>> A)
{
	int n = A.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "\t" << A[i][j] << "\t";
		}
		cout << endl;
	}
}

void solve(vector <vector <double>> A, vector <double> B,vector <double> &R)
{
	int n = A.size();
	vector <vector <double>> L(n), U(n);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			L[i].push_back(0);
			U[i].push_back(0);
		}
	}

	LUfactor(A, L, U);
	for (int i = 0; i < n; i++)
	{
		R[i] = B[i];
		for (int j = 0; j < i; j++)
		{
			R[i] -= L[i][j]*R[j];
		}
		R[i] /= L[i][i];
	}


	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = n - 1; j > i; j--)
		{
			R[i] -= U[i][j]*R[j];
		}
		R[i] /= U[i][i];
	}
}

int main()
{
	int n = 4;
	vector <vector <double>> A(n), L(n), U(n), R(n);
	vector <double> S(n),B(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			L[i].push_back(0);
			U[i].push_back(0);
			R[i].push_back(0);
		}
	}
	A[0].push_back(1);
	A[0].push_back(1);
	A[0].push_back(1);
	A[0].push_back(1);
	A[1].push_back(1);
	A[1].push_back(2);
	A[1].push_back(3);
	A[1].push_back(4);
	A[2].push_back(7);
	A[2].push_back(3);
	A[2].push_back(1);
	A[2].push_back(5);
	A[3].push_back(0);
	A[3].push_back(3);
	A[3].push_back(9);
	A[3].push_back(6);
	B[0] = 1;
	B[1] = 2;
	B[2] = 3;
	B[3] = 4;
	LUfactor(A, L, U);
	cout << "Fisrt matrix" << endl;
	show(A);
	cout << "U matrix" << endl;
	show(U);
	cout << "L matrix" << endl;
	show(L);
	Mult(L, U, R);
	cout << "L*U matrix" << endl;
	show(R);
	solve(A,B,S);
	for (int i = 0; i < n; i++)
	{
		cout << S[i] << endl;
	}
	system("pause");
	return 0;
}