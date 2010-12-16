#include <algorithm>
#include <cmath>
#include "Cloud.h"
#include "MST.h"
#include "Matrix.h"

//#include <iostream>
//#include <stdio.h>

namespace IMesh { //: namespace IMesh
	namespace Norm { //: namespace IMesh::Norm

		/*Vector3 Cloud::origin = Vector3();
		std::vector<Vector3>* Cloud::p_vertices = NULL;*/

/*
		bool Cloud::DisCmp( int u, int v)
		{
			return SquareOfDistance((*p_vertices)[u],origin) < SquareOfDistance((*p_vertices)[v], origin);
		}

		bool Cloud::DisCmp2( Vector3 &u, Vector3 &v)
		{
			return SquareOfDistance(u,origin) < SquareOfDistance(v,origin);
		}
*/
		Vector3 Cloud::ComputeOneNorm( int in )
		{
		/****
		Compute the normal of vertex v[in]
		****/

			/****
			First, find k nearest neighbours of v, with a heap.
			****/

			class DisCmpFunctor {
			public:
				Vector3& m_Origin;
				std::vector<Vector3>* m_pVertices;

				DisCmpFunctor(Vector3& origin, std::vector<Vector3>* pVertices) 
							: m_Origin(origin), m_pVertices(pVertices) {}

			public:
				bool operator() ( int u, int v ) {
					return (SquareOfDistance( (*m_pVertices)[u], m_Origin ) < 
						SquareOfDistance( (*m_pVertices)[v], m_Origin) );
				}
			};

			class DisCmp2Functor {
			public:
				Vector3& m_Origin;
				DisCmp2Functor(Vector3& origin) : m_Origin(origin) {}

			public:
				bool operator() (  Vector3 &u, Vector3 &v ) {
					return SquareOfDistance(u, m_Origin) < SquareOfDistance(v, m_Origin);
				}
			};


			//Vector3** neighbour = new Vector3*[k];
			Vector3& origin  = m_vertices[in];
			vector<int> neighbour;
	

			int l = k;
			if ( l > v_num )
				l = v_num;

			for( int i = 0 ; i < l ; i++ )
			{
				if( SquareOfDistance(m_vertices[i], origin) > 0 )
					neighbour.push_back( i );
				else
					l++;
			}

	
			std::vector<Vector3>* p_vertices = &m_vertices;
			DisCmpFunctor DisCmp(origin, p_vertices);
			DisCmp2Functor DisCmp2(origin);

			make_heap(neighbour.begin(), neighbour.end(),DisCmp);
			for( int i = l ; i < v_num ; i++ )
			{
				if( DisCmp2( m_vertices[i] , m_vertices[neighbour[0]] ) && SquareOfDistance(m_vertices[i],origin) > 0 )
				{
					pop_heap(neighbour.begin(), neighbour.end(), DisCmp);
					neighbour[k-1] = i;
					push_heap(neighbour.begin(), neighbour.end(), DisCmp);
				}
			}

		//	origin = NULL;

			/****
			Save index of neighbours to edges
			****/
			for( std::vector<int>::size_type i = 0 ; i < neighbour.size(); i++)
				m_edges.push_back( Edge(in,neighbour[i], SquareOfDistance(m_vertices[in],m_vertices[neighbour[i]])) );

			/****
			Compute normal wrt the k neighbours
			****/
			Matrix mat( neighbour, m_vertices);
			Vector3 v_norm = mat.Solve();

		//	cout<<"v "<<in<<" : "<<v.x<<" "<<v.y<<" "<<v.z<<" norm="<<v_norm.x<<" "<<v_norm.y<<" "<<v_norm.z<<endl;	

			return v_norm;
		}



		int Cloud::ComputeNorm()
		{
			for( int i = 0 ; i < v_num ; i++ )
				m_norm.push_back( ComputeOneNorm( i ) );
			return 0;
		}



		int Cloud::AdjustNormDirection()
		{
										/*
	for(int i = 0 ; i < edges.size() ; i++ ){
		cout<<"edge "<<i<<"  "<<edges[i].u<<" -> "<<edges[i].v<<"  length: "<<edges[i].length<<endl;
	}
*/
			if( m_norm.size() <= 1 )
				return 1;
			sort(m_edges.begin(),m_edges.end(),cmplength);
										/*
	for(int i = 0 ; i < edges.size() ; i++ ){
		cout<<"edge "<<i<<"  "<<edges[i].u<<" -> "<<edges[i].v<<"  length: "<<edges[i].length<<endl;
	}
*/
			Initi(m_edges.size());
			int x,y;
			int cnt = 0;

																/*	
	vector<list<int>> neighbour;
	for( int i = 0 ; i < v_num ; i++)
	{
		list<int> l;
		neighbour.push_back(l);
	}
*/
			for( std::vector<int>::size_type i = 0 ; i < m_edges.size() ; i++)
			{	
				x = Find(m_edges[i].u);
				y = Find(m_edges[i].v);
				if ( x != y )
				{
		//			cout<<cnt++<<" edge "<<i<<"  "<<edges[i].u<<" ("<<vertices[edges[i].u].x<<","<<vertices[edges[i].u].y<<","<<vertices[edges[i].u].z<<") "
		//				<<" -> "<<edges[i].v<<" ("<<vertices[edges[i].v].x<<","<<vertices[edges[i].v].y<<","<<vertices[edges[i].v].z<<") "<<"  length: "<<edges[i].length<<endl;


					m_norm[m_edges[i].u].tree_neighbour.push_back(m_edges[i].v);
					m_norm[m_edges[i].v].tree_neighbour.push_back(m_edges[i].u);
					Union(x,y);
				}

			}

			//bool adj_mat = new bool[edges.size()][edges.size()];
			int low = 0;
			for( int i = 0 ; i < v_num ; i++)
			{
				if( (m_vertices[i].z < m_vertices[low].z) || 
					( (m_vertices[i].z == m_vertices[low].z) && (m_vertices[i].y < m_vertices[low].y) ) ||
					( (m_vertices[i].z == m_vertices[low].z) && (m_vertices[i].y == m_vertices[low].y) && (m_vertices[i].x < m_vertices[low].x) ) )
					low = i;
		
			}

			cout<<"Lowest then left most vertex index is "<<low<<endl;
	
			if( m_norm[low].z > 0 ||( m_norm[low].z == 0 && m_norm[low].y > 0 ))
				m_norm[low].neg();
	
			m_norm[low].adjusted = true;

			vector<int> stack;
			vector<int> father;

		//	stack.push_back(low);
			stack.push_back(0);	//index of q in p's
			father.push_back(-1);	//father of p
			std::vector<int>::size_type index = 0;// index of q's neighbour



			int p = low, q = m_norm[p].tree_neighbour[0];
			while( !stack.empty() ){
				if( m_norm[p].innerProduct(m_norm[q]) < 0 )
					m_norm[q].neg();
				m_norm[q].adjusted = true;

				while( m_norm[q].tree_neighbour.size() > index && m_norm[m_norm[q].tree_neighbour[index]].adjusted )
					index++;
				while( m_norm[q].tree_neighbour.size() <= index && !stack.empty() )
				{
					q = p;

					p = father[father.size()-1];
					father.pop_back();
					index = stack[stack.size()-1];
					stack.pop_back();
		
					index++;
					while( m_norm[q].tree_neighbour.size() > index && m_norm[m_norm[q].tree_neighbour[index]].adjusted == true)
						index++;

				};
				if( m_norm[q].tree_neighbour.size() > index )
				{
					stack.push_back(index);
					father.push_back(p);
					p = q, q = m_norm[q].tree_neighbour[index];
					index = 0;
				}
		
			};

			return 0;
		}

		int Cloud::MoveToZero(){
			double lx = 0,ly = 0,lz = 0;
			double hx = 0, hy = 0, hz = 0;
			for( int i = 0 ; i < v_num ; i++ )
			{
				if( lx > m_vertices[i].x )
					lx = m_vertices[i].x;
				if( ly > m_vertices[i].y )
					ly = m_vertices[i].y;
				if( lz > m_vertices[i].z )
					lz = m_vertices[i].z;
			}
			for( int i = 0 ; i < v_num ; i++ )
			{
				if( hx < m_vertices[i].x )
					hx = m_vertices[i].x;
				if( hy < m_vertices[i].y )
					hy = m_vertices[i].y;
				if( hz < m_vertices[i].z )
					hz = m_vertices[i].z;
			}
			Vector3 v(lx,ly,lz);
			for( int i = 0 ; i < v_num ; i++ )
			{
				m_vertices[i]-=v;
			}
			mx = (lx+hx)/2, my = (ly+hy)/2, mz = (lz+hz)/2;
			mid = Vector3(mx,my,mz);
			density = std::pow((hx-lx) * (hy-ly) * (hz-lz)/v_num, 1.0/3 );//r = 1.5density
			grid_width = density * 4;
			grid_x = (hx-lx)/grid_width + 1;
			grid_y = (hy-ly)/grid_width + 1;
			grid_z = (hz-lz)/grid_width + 1;
			return 0;
		}

	
	} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh