//Matrix.cpp

#include "Matrix.h"

namespace IMesh { //: namespace IMesh
	namespace Norm { //: namespace IMesh::Norm

	Matrix::Matrix(vector<int> &v , vector<Vector3> &vertices){
		int k = v.size();
		Vector3 p(0,0,0);
		for( vector<int>::iterator it=v.begin() ; it < v.end() ; it++ )
		{
			p.x+=vertices[(*it)].x;
			p.y+=vertices[(*it)].y;
			p.z+=vertices[(*it)].z;
		}
		p.x = p.x/k;
		p.y = p.y/k;
		p.z = p.z/k;

		for( int i = 0 ; i < 3 ; i++ )
			for( int j = 0 ; j < 3 ; j++ )
				m_mat[i][j] = 0 ;

		for( int i = 0 ; i < 3 ; i++ )
		{
			for( int j = 0 ; j < 3 ; j++ )
			{
				for( int l = 0 ; l < k ; l++)
				{
					//vertices[v[l]].get(i);
					//vertices[v[l]].get(j);
					m_mat[i][j] += vertices[v[l]].get(i) * vertices[v[l]].get(j);
				}
				m_mat[i][j] = m_mat[i][j]/k - p.get(i)*p.get(j);
			}
		}

	}

	void Matrix::Show()
	{
		for( int i = 0 ; i < 3 ; i++ )
		{
			for( int j = 0 ; j < 3 ; j++ )
				cout<<m_mat[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
		return;
	}


//《常用算法程序集（C语言描述）》
//a   存放n阶实对称阵，返回时对角线存放n个特征值
//n   矩阵阶数
//v   n阶矩阵，第j列为对应第j个特征值的特征向量
//eps 控制精度
//jt 最大迭代次数

//返回值：大于0则计算成功，小于0则失败 

int jacobi(double *a,int n,double *v,double eps,int jt)
{
int i,j,p,q,u,w,t,s,l;
    double fm,cn,sn,omega,x,y,d;
    l=1;
    for (i=0; i<=n-1; i++)
      { v[i*n+i]=1.0;
        for (j=0; j<=n-1; j++)
          if (i!=j) v[i*n+j]=0.0;
      }
    while (1)
      { fm=0.0;
        for (i=1; i<=n-1; i++)
        for (j=0; j<=i-1; j++)
          { d=fabs(a[i*n+j]);
            if ((i!=j)&&(d>fm))
              { fm=d; p=i; q=j;}
          }
        if (fm<eps) return(1);
        if (l>jt) return(-1);
        l=l+1;
        u=p*n+q; w=p*n+p; t=q*n+p; s=q*n+q;
        x=-a[u]; y=(a[s]-a[w])/2.0;
        omega=x/sqrt(x*x+y*y);
        if (y<0.0) omega=-omega;
        sn=1.0+sqrt(1.0-omega*omega);
        sn=omega/sqrt(2.0*sn);
        cn=sqrt(1.0-sn*sn);
        fm=a[w];
        a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
        a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
        a[u]=0.0; a[t]=0.0;
        for (j=0; j<=n-1; j++)
        if ((j!=p)&&(j!=q))
          { u=p*n+j; w=q*n+j;
            fm=a[u];
            a[u]=fm*cn+a[w]*sn;
            a[w]=-fm*sn+a[w]*cn;
          }
        for (i=0; i<=n-1; i++)
          if ((i!=p)&&(i!=q))
            { u=i*n+p; w=i*n+q;
              fm=a[u];
              a[u]=fm*cn+a[w]*sn;
              a[w]=-fm*sn+a[w]*cn;
            }
        for (i=0; i<=n-1; i++)
          { u=i*n+p; w=i*n+q;
            fm=v[u];
            v[u]=fm*cn+v[w]*sn;
            v[w]=-fm*sn+v[w]*cn;
          }
      }
    return(1);
}


Vector3 Matrix::Solve(){
	double v[3][3];

	if( jacobi((double*)m_mat,3,(double*)v,0.0001,100) < 0 )		//Jacobi fails to solve
		return Vector3(0,0,0);
	/*
	cout<<endl;
	for( int i = 0 ; i < 3 ; i++ )
		cout<<m_mat[i][i]<<" ";
	cout<<endl<<endl;

	for( int i = 0 ; i < 3 ; i++ )
	{
		for( int j = 0 ; j < 3 ; j++ )
			cout<<v[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	*/
	if( m_mat[0][0] < m_mat[1][1] && m_mat[0][0] < m_mat[2][2] )
		return Vector3(v[0][0],v[1][0],v[2][0]);
	else if( m_mat[1][1] < m_mat[2][2] )
		return Vector3(v[0][1],v[1][1],v[2][1]);		
	else
		return Vector3(v[0][2],v[1][2],v[2][2]);

	

}


	} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh=======
//Matrix.cpp
