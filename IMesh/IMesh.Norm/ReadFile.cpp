//ReadFile.cpp

#include "ReadFile.h"
#include "MST.h"

vector<Vector3> vertices,norm;//vertices and norm
int v_num=0;		//number of vertices
int k = 15;				//compute for k nearest neighbours;
double r;				//radious

FILE *m_FileHandler;	//source obj file
FILE *m_out;			//target obj file
char *outname = new char[255]; //output file name

double SquareOfDistance( Vector3 &u, Vector3 &v)
{
	return (u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y)+(u.z-v.z)*(u.z-v.z);
}

Edge::Edge(int i, int j){
		u=i,v=j;
		if( i < vertices.size() && j < vertices.size() )
			length = SquareOfDistance(vertices[i],vertices[j]);
		else
			length = -1;
	}

vector<Edge> edges;


void ReadVertex()
{
	Vector3 vNewVertex;
	fscanf(m_FileHandler, "%lf %lf %lf", &vNewVertex.x, &vNewVertex.y, &vNewVertex.z);
	//if (abs(vNewVertex.x)>10) return;

//	cout<<vNewVertex.x<<" "<<vNewVertex.y<<" "<<vNewVertex.z<<endl;

	vertices.push_back(vNewVertex);
	return;
}


int ReadFile( char *strFileName )
{
	char *str = strFileName;
	int k=0;
	char ch;
	
	m_FileHandler = fopen(strFileName, "r");
	if (!m_FileHandler) {
		cout<<"No such file\n"<<endl;;
		return -1;
	}
	while (*str!='.' && *strFileName!='\0') {
		outname[k]=*str;
		k++;
		*str++;
	}
	outname[k]='\0';
	outname=strcat(outname,"_norm.obj");
	
//	m_out = fopen(outname, "w");

	while(!feof(m_FileHandler))
	{
		// 获得obj文件中的当前行的第一个字符
		ch = fgetc(m_FileHandler);
		switch(ch)
		{
		case 'v':	// 读入的是'v' (后续的数据是顶点)
			// 读入点的信息
			ReadVertex();
			break;

		default:
			
			break;
		}
	}
	fclose(m_FileHandler);

	v_num= vertices.size();

	cout<<"V = "<<v_num<<endl;


	return 0;

}

void Output()
{
	m_out = fopen(outname, "w");
	for ( int i=0; i < v_num; i++) 
	{
		fprintf(m_out, "v %lf %lf %lf norm %lf %lf %lf\n", vertices[i].x, vertices[i].y, vertices[i].z, norm[i].x, norm[i].y, norm[i].z);
			
	}
	fclose(m_out);
	cout<<"Output finished!\n";
}

void Display(vector<Vector3> &v)
{
	for ( int i=0; i < v.size(); i++) 
	{
		cout<<"v "<<v[i].x<<" "<<v[i].y<<" "<<v[i].z<<endl;
			
	}
	cout<<endl;
	//cout<<"Display Finished!\n";
}



static Vector3* origin=NULL;

bool DisCmp( int u, int v)
{
	if ( origin == NULL )
		return false;
	return SquareOfDistance(vertices[u],*origin) < SquareOfDistance(vertices[v],*origin);
}


bool DisCmp1( Vector3 *u, Vector3 *v)
{
	if ( origin == NULL )
		return false;
	return SquareOfDistance(*u,*origin) < SquareOfDistance(*v,*origin);
}

bool DisCmp2( Vector3 &u, Vector3 &v)
{
	if ( origin == NULL )
		return false;
	return SquareOfDistance(u,*origin) < SquareOfDistance(v,*origin);
}

void ShowNeighbour(vector<Vector3*> &v)
{
	for ( int i=0; i < v.size(); i++) 
	{
		cout<<"v "<<v[i]->x<<" "<<v[i]->y<<" "<<v[i]->z<<" "<<SquareOfDistance(*origin,*v[i])<<endl;
			
	}
	cout<<"Finished!\n";
}

void ShowNeighbour(vector<int> &v)
{
	for ( int i=0; i < v.size(); i++) 
	{
		cout<<"v "<<v[i]<<"="<<vertices[v[i]].x<<" "<<vertices[v[i]].y<<" "<<vertices[v[i]].z<<" with distance:"<<SquareOfDistance(*origin,vertices[v[i]])<<endl;
			
	}
	cout<<"Finished!\n";
}



Vector3 ComputeOneNorm( int in )
{
	
/****
Compute the normal of vertex v
****/

	/****
	First, find k nearest neighbours of v, with a heap.
	****/

	//Vector3** neighbour = new Vector3*[k];
	Vector3 v = vertices[in];
	vector<int> neighbour;
	origin = &v;
//	k=4;
	int l = k;
	for( int i = 0 ; i < l ; i++ )
	{
		if( SquareOfDistance(vertices[i], *origin) > 0 )
			neighbour.push_back( i );
		else
			l++;
//		cout<<"i="<<i<<endl;
//		ShowNeighbour( neighbour );
		}
	make_heap(neighbour.begin(), neighbour.end(), DisCmp);

//	ShowNeighbour( neighbour );
	for( int i = l ; i < v_num ; i++ )
	//for( int i = k ; i < k+10 ; i++ )
	{
//		cout<<"new coming "<<SquareOfDistance(*origin, vertices[i])<<endl;
		if( DisCmp2( vertices[i] , vertices[neighbour[0]] ) && SquareOfDistance(vertices[i],*origin) > 0 )
		{
			pop_heap(neighbour.begin(), neighbour.end(), DisCmp);
			neighbour[k-1] = i;
			push_heap(neighbour.begin(), neighbour.end(), DisCmp);
//			ShowNeighbour( neighbour );
		}
	}
//	ShowNeighbour( neighbour );
	origin = NULL;

	/****
	Save index of neighbours to edges
	****/
	for( int i = 0 ; i < neighbour.size(); i++)
		edges.push_back(Edge(in,neighbour[i]));

	/****
	Compute normal wrt the k neighbours
	****/
	Matrix mat(neighbour);
	Vector3 v_norm = mat.Solve();

//	cout<<"v "<<in<<" : "<<v.x<<" "<<v.y<<" "<<v.z<<" norm="<<v_norm.x<<" "<<v_norm.y<<" "<<v_norm.z<<endl;	

	return v_norm;
}

int ComputeNorm()
{
	for( int i = 0 ; i < v_num ; i++ )
		norm.push_back( ComputeOneNorm( i ) );
	return 0;
}



int FindLowestLeftmost()
{
	int low = 0;
	for( int i = 0 ; i < v_num ; i++)
	{
		if( (vertices[i].z < vertices[low].z) || 
			( (vertices[i].z == vertices[low].z) && (vertices[i].y < vertices[low].y) ) ||
			( (vertices[i].z == vertices[low].z) && (vertices[i].y == vertices[low].y) && (vertices[i].x < vertices[low].x) ) )
			low = i;
		
	}
	return low;
}

bool cmplength(Edge e, Edge f)
{
	if ( e.length == f.length )
		if( e.u == f.u )
			return e.v < f.v;
		else
			return e.u < f.u;
	else
		return e.length < f.length;
}

int AdjustNormDirection()
{
/*
	for(int i = 0 ; i < edges.size() ; i++ ){
		cout<<"edge "<<i<<"  "<<edges[i].u<<" -> "<<edges[i].v<<"  length: "<<edges[i].length<<endl;
	}
*/
	sort(edges.begin(),edges.end(),cmplength);
/*
	for(int i = 0 ; i < edges.size() ; i++ ){
		cout<<"edge "<<i<<"  "<<edges[i].u<<" -> "<<edges[i].v<<"  length: "<<edges[i].length<<endl;
	}
*/
	Initi(edges.size());
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
	for( int i = 0 ; i < edges.size() ; i++)
	{	
		x = Find(edges[i].u);
		y = Find(edges[i].v);
		if ( x != y )
		{
//			cout<<cnt++<<" edge "<<i<<"  "<<edges[i].u<<" ("<<vertices[edges[i].u].x<<","<<vertices[edges[i].u].y<<","<<vertices[edges[i].u].z<<") "
//				<<" -> "<<edges[i].v<<" ("<<vertices[edges[i].v].x<<","<<vertices[edges[i].v].y<<","<<vertices[edges[i].v].z<<") "<<"  length: "<<edges[i].length<<endl;
//			neighbour[edges[i].u].push_back(edges[i].v);
//			neighbour[edges[i].v].push_back(edges[i].u);
			norm[edges[i].u].tree_neighbour.push_back(edges[i].v);
			norm[edges[i].v].tree_neighbour.push_back(edges[i].u);
			Union(x,y);
		}

	}
	//showpre(26);
	//bool adj_mat = new bool[edges.size()][edges.size()];
	int low = FindLowestLeftmost();
	cout<<"Lowest then left most "<<low<<endl;
	
	if( norm[low].z > 0 ||( norm[low].z == 0 && norm[low].y > 0 ))
		norm[low].neg();
	
	norm[low].adjusted = true;

	vector<int> stack;
	vector<int> father;

//	stack.push_back(low);
	stack.push_back(0);	//index of q in p's
	father.push_back(-1);	//father of p
	int index = 0;// index of q's neighbour



	int p = low, q = norm[p].tree_neighbour[0];
	while( !stack.empty() ){
		if( norm[p].innerProduct(norm[q]) < 0 )
			norm[q].neg();
		norm[q].adjusted = true;
		
//		cout<<q<<endl;

		//bool adj = vertices[vertices[q].tree_neighbour[index]].adjusted;
		while( norm[q].tree_neighbour.size() > index && norm[norm[q].tree_neighbour[index]].adjusted )
			index++;
		while( norm[q].tree_neighbour.size() <= index && !stack.empty() )
		{
			q = p;
	//		p = *(father.end());
			p = father[father.size()-1];
			father.pop_back();
			index = stack[stack.size()-1];
			stack.pop_back();
			//stack.pop_back();			
			index++;
			while( norm[q].tree_neighbour.size() > index && norm[norm[q].tree_neighbour[index]].adjusted == true)
				index++;

		};
		if( norm[q].tree_neighbour.size() > index )
		{
			stack.push_back(index);
			father.push_back(p);
			p = q, q = norm[q].tree_neighbour[index];
			index = 0;
		}
		
	};

//	for( int i = 0 ; i < v_num ; i++)
//		cout<<"i "<<i<<"  "<<norm[i].adjusted<<endl;

	return 0;
}

void InitFrom( char *strFileName ){
	ReadFile( strFileName );
	
	ComputeNorm();
	AdjustNormDirection();
	
	return;
}