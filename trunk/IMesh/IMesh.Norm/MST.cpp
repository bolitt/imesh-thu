//MST.cpp
#include "MST.h"


#include<iostream>
using namespace std;



int pre[MAXSIZE]; //���ڵ�i,pre[i] = -num,����num�Ǹ����Ľڵ���Ŀ;

                   //�Ǹ��ڵ�j,pre[j] = k,����k��j�ĸ��ڵ�


int Find(int x){//����+�ǵݹ��·��ѹ��

     int p = x;

     while( pre[p] > 0 )    p = pre[p];

     while( x != p ){

         int temp = pre[x]; pre[x] = p; x = temp;

     }

     return x;

}

void Union(int r1, int r2){

     int a = Find(r1); int b = Find(r2);

     if( a == b ) return ; 

     //��Ȩ����ϲ�

     if( pre[a] < pre[b] ){

         pre[a] += pre[b]; pre[b] = a;

     }

     else {

         pre[b] += pre[a]; pre[a] = b;

     }

}

void Initi(int n)

{

    for( int i=0; i < MAXSIZE; ++i ) pre[i] = -1;

}

void showpre( int n)
{
	for( int i = 0 ; i < n; i++)
		std::cout<<pre[i]<<std::endl;
}