//MST.h

#ifndef MST_H
#define MST_H

#include<vector>
using namespace std;

const int MAXSIZE = 30001;

int pre[MAXSIZE]; //根节点i,pre[i] = -num,其中num是该树的节点数目;

                   //非根节点j,pre[j] = k,其中k是j的父节点

vector<int> child[MAXSIZE];

int Find(int x){//查找+非递归的路径压缩

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

     //加权规则合并

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
		cout<<pre[i]<<endl;
}

#endif	//MST_H