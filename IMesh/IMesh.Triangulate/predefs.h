#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;


struct int3{
	int first;
	int second;
	int third;

	int3(int f,int s,int t){first = f; second = s; third = t;}
	int3(){first = 0;second = 0;third = 0;}
};

struct point3D{
	double x;
	double y;
	double z;

	point3D(){x=0.0;y=0.0;z=0.0;}
	point3D(double a,double b,double c){x=a;y=b;z=c;}
	static double distance(point3D a, point3D b)
	{
		return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
	}
	static double distance2(point3D a, point3D b)
	{
		return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
	}
};
typedef struct point3D point3D;

struct vect{
	double x;
	double y;
	double z;

	vect(){x=0.0;y=0.0;z=0.0;}
	vect(double a, double b, double c){x=a;y=b;z=c;}
	double norm(){return sqrt(x*x+y*y+z*z);}
	vect normalize(){return vect(x/norm(),y/norm(),z/norm());}
	static double dot(vect a, vect b){return a.x*b.x+a.y*b.y+a.z*b.z;}
	static vect cross(vect a, vect b)
	{
		return vect(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
	}
};
typedef struct vect vect;

struct norm_point{
	point3D position;
	vect norm;
};
typedef struct norm_point norm_point;

struct edge{
	long idx_i;
	long idx_j;
	enum {BOUNDARY,ACTIVE,FROZEN,DELETED}flag;
	struct triangle *sidelink;
	enum {FIRSTPOINT,SECONDPOINT,THIRDPOINT}startpoint; // edge position in three of the edges of the triangle, pointvector(idx_i) will be "startpoint";
	long idx_o;
	point3D ball_center;
	bool ishead;
	//edge **loophead;
	//double ball_radius;

	struct edge *next;
	struct edge *pre;
	edge(long _i,long _j,long _o,point3D bc):ball_center(bc){idx_i = _i;idx_j = _j;flag = ACTIVE;
											sidelink = NULL;startpoint = FIRSTPOINT;idx_o = _o;
											next = NULL;pre = NULL;ishead = false;}//ball_radius = 0;
	~edge(){;}
											
											
};
typedef struct edge edge;

struct triangle{
	long idx_i;
	long idx_j;
	long idx_k;
	struct triangle *t_ij;
	struct triangle *t_jk;
	struct triangle *t_ki;
};
typedef struct triangle triangle;


struct point{
	point3D position;
	vect norm;
	enum {ONFRONT,UNUSED,INNER}flag;
	vector<edge *> outedges;
	vector<edge *> inedges;
	vector<long> tabooPointList;

	point(norm_point np){position = np.position; norm = np.norm; flag = UNUSED;}
	bool isUnused(){return flag == UNUSED;}
	bool isOnfront(){return flag == ONFRONT;}
	bool isInner(){return flag == INNER;}
	void setFlagUnused(){flag = UNUSED;}
	void setFlagOnfront(){flag = ONFRONT;}
	void setFlagInner(){flag = INNER;}
	bool hasTaboo(long index){
		for(size_t i = 0;i<tabooPointList.size();i++)
			if(index == tabooPointList[i])
				return true;
		return false;
	}
	static bool comparePoint(point a, point b)
	{
	if(a.position.x == b.position.x)
		if(a.position.y == b.position.y)
			return a.position.z > b.position.z;
		else
			return a.position.y > b.position.y;
	else
		return a.position.x > b.position.x;
	}
	static bool testNormal(point a, point b, point c ,vect &outnorm)
	{
		vect ab(b.position.x-a.position.x,b.position.y-a.position.y,b.position.z-a.position.z);
		vect ac(c.position.x-a.position.x,c.position.y-a.position.y,c.position.z-a.position.z);
		vect tnorm = vect::cross(ab,ac);
		outnorm = tnorm;
		if(vect::dot(tnorm,a.norm)<=0.0000000001 || vect::dot(tnorm,b.norm)<=0.000000001 || vect::dot(tnorm,c.norm)<=0.000000001)
			return false;
		return true;
	}
};
typedef struct point point;

struct edgefront{
	vector<edge *> loopheads;
	int loopnum;

	edgefront(){loopnum = 0;}
};
typedef struct edgefront edgefront;

struct all_point_list{
	vector<point> points;
	long current_traverse_place; //for seed finding, initially 0

	all_point_list()
	{
		current_traverse_place = 0;
	}
	all_point_list(vector<norm_point> &nps)
	{
		current_traverse_place = 0;
		long ibound = nps.size();
		for(long i = 0; i<ibound; i++)
		{
			points.push_back(point(nps.at(i)));
			printf("\n%ld",i);
		}

	}
};
typedef struct all_point_list all_point_list;

struct cell{
	vector<long> pointindex;
	all_point_list *pointsdatabase;
	int pointnum;
	int currentpointindex;//for seed finding, initially 0
	bool activated;

	cell(all_point_list *_pointsdatabase){pointsdatabase = _pointsdatabase; pointnum = 0;activated = false;currentpointindex = 0;}
	void bucket_sort(int startindex, int endindex);
	void add_pointindex(long _pointindex);
	void activateCell(){activated = true;}
};
typedef struct cell cell;

struct grid{
	vector<vector<vector<cell> > > cells; // cells.at(k).at(i).at(j)
	all_point_list *pointsdatabase;
	double gridwidth;
	int isize,jsize,ksize;
	int currentcellindex;//=k*isize*jsize+i*jsize+j; for seed finding, initially 0

	grid()
	{
		isize = 0;jsize = 0;ksize = 0;
		currentcellindex = 0;
		gridwidth = 0;
		pointsdatabase = NULL;
	}
	grid(int _i, int _j, int _k, all_point_list *_pointsdatabase, double _delta)
	{
		vector<vector<cell> > temp1;
		vector<cell> temp2;

		for(int j = 0;j < _j; j++)
			temp2.push_back(cell(_pointsdatabase));
		for(int i = 0;i < _i; i++)
			temp1.push_back(temp2);
		for(int k = 0;k < _k; k++)
			cells.push_back(temp1);

		pointsdatabase = _pointsdatabase;
		gridwidth = _delta;
		isize = _i;
		jsize = _j;
		ksize = _k;
		currentcellindex = 0;
	}

	void initialize();
	void locatePoint(long _index,int3 &_cellindex);
	void locatePoint(point3D pos,int3 &_cellindex);
	bool pickPointInCell(long &_index,int _cellindex);
	void locateNeighborhood(vector<int3> &neighbors,int cellindex);
	void findNeighborPoints(vector<long> &pointList, double radius, point3D &origin);
	
	point3D getPoint3D(long pointindex)
	{
		return this->pointsdatabase->points[pointindex].position;
	}
	point getPoint(long pointindex)
	{
		return this->pointsdatabase->points[pointindex];
	}
	bool inGrid(int3 index)
	{
		if(index.first<0||index.first>=isize||index.second<0||index.second>=jsize||index.third<0||index.third>=ksize)
			return false;
		return true;
	}
};
typedef struct grid grid;

/*extern vector<triangle *> triangleList;
extern edgefront edfr;
extern deque<edge *> frontEdgeQueue;*///mainly active, some boundary, actually "active queue"
extern class TriangulationHandler;

edge *getActiveEdge(TriangulationHandler *TH);
long ballPivot(edge *edgeaxis,grid *m_grid, double ballradius, TriangulationHandler *TH);


void joinEdge(edge *edgeaxis, long pointindex, grid *m_grid, point3D ballcenter, TriangulationHandler *TH);
void glueEdges(edge *newedge, edge *originedge, point *newedgei, point *newedgej, TriangulationHandler *TH);
bool shouldGlue(edge *newedge, edge *originedge);
void deleteEdge(edge *e, TriangulationHandler *TH);
bool edgeEqual(edge *e1,edge *e2);
void deleteEdgefromPoint(edge *e, point *p, bool oi);//o:true,i:false
///////////
bool findSeedTriangle(grid *m_grid, long &_pointindex1, long &_pointindex2, long &_pointindex3, point3D &ball_center, double ball_radius, TriangulationHandler *TH);

//long pickPoint(all_point_list *apl);

//bool buildTriangle(edge *c_edge, point *newp, grid *m_grid);
bool buildTriangle(grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, point3D &ballcenter, double ballradius,vect outnorm);
bool buildTriangle(point3D ballcenter, double ballradius, grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, TriangulationHandler *TH);

bool testTriangleValidity(grid *m_grid, vector<int3> &neighborhood, point3D ball_center, double ball_radius);
