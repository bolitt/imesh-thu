//ReadFile.h

#include <windows.h>
#include<vector>
#include<list>
#include<math.h>
#include<fstream>
#include<stdio.h>
#include<iostream>
#include<algorithm>

using namespace std;


#include "Matrix.h"



int ReadFile( char *strFileName );

int ComputeNorm();
int AdjustNormDirection();
Vector3 ComputeOneNorm(int );

void Output();
void Display(vector<Vector3> &v);

void InitFrom( char *strFileName );