#pragma once

#include <iostream>

// use M_PI
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif

namespace IMesh { namespace Num {
		template<class TValue>
		class Vec3
		{
		public:
			enum { dim = 3 };
		
		public:
			typedef Vec3<TValue>			self_type;
			typedef Vec3<TValue>&			ref_type;
			typedef Vec3<TValue>*			ptr_type;
			typedef const Vec3<TValue>*		const_ptr_type;
			typedef TValue					value_type;

		public:
			union 
			{
				TValue _val[3];
				struct {
					TValue _longtitude;  // x on sphere
					TValue _coLatitude;  // y on sphere
					TValue _radius;      // z on sphere
				};
				struct {
					TValue _x;
					TValue _y;
					TValue _z;
				};
				struct {
					TValue _r;
					TValue _g;
					TValue _b;
				};
				struct {
					TValue _v0;
					TValue _v1;
					TValue _v2;
				};
			};
			Vec3() : _x(TValue()), _y(TValue()), _z(TValue()) {}
			Vec3(TValue tvx, TValue tvy, TValue tvz) : _x(tvx), _y(tvy), _z(tvz) {}
			Vec3(TValue tv) : _x(tv), _y(tv), _z(tv) {}

#pragma region macros
			#define DEFINE_BINARY_OPERATOR(op) \
			friend self_type operator op (const Vec3& v0, const Vec3& v1)  \
			{ self_type vx;                           \
			  vx._x = v0._x op v1._x;          \
			  vx._y = v0._y op v1._y;          \
			  vx._z = v0._z op v1._z;         \
			return vx; }                       

			#define DEFINE_UNARY_OPERATOR(op) \
			self_type operator op () const         \
			{ self_type vx;                        \
				vx._x = op this->_x;          \
				vx._y = op this->_y;          \
				vx._z = op this->_z;          \
			return vx; }

			#define DEFINE_ASSIGN_OPERATOR(op) \
			self_type& operator op (const Vec3& v)  \
			{								\
				this->_x op v._x;			\
				this->_y op v._y;			\
				this->_z op v._z;			\
				return *this;}
#pragma endregion macros

			DEFINE_BINARY_OPERATOR(+)
			DEFINE_BINARY_OPERATOR(-)
			// DEFINE_BINARY_OPERATOR(*) disable v1 * v2 to avoid ambiguity
			DEFINE_BINARY_OPERATOR(/)
			DEFINE_BINARY_OPERATOR(%)
			DEFINE_BINARY_OPERATOR(^)
			DEFINE_BINARY_OPERATOR(&)
			DEFINE_BINARY_OPERATOR(|)
			
			DEFINE_UNARY_OPERATOR(+)
			DEFINE_UNARY_OPERATOR(-)
			DEFINE_UNARY_OPERATOR(!)
			DEFINE_UNARY_OPERATOR(~)

			DEFINE_ASSIGN_OPERATOR(=)
			DEFINE_ASSIGN_OPERATOR(+=)
			DEFINE_ASSIGN_OPERATOR(-=)
			DEFINE_ASSIGN_OPERATOR(*=)
			DEFINE_ASSIGN_OPERATOR(/=)
			DEFINE_ASSIGN_OPERATOR(&=)
			DEFINE_ASSIGN_OPERATOR(^=)
			DEFINE_ASSIGN_OPERATOR(|=)
			
			TValue Dot (const self_type& v) const 
			{
				return (this->_x * v._x) + 
				       (this->_y * v._y) +
				       (this->_z * v._z);
			}

			Vec3 Cross (const self_type& v) const 
			{
				Vec3 vx;
				vx._x = (this->_y * v._z) - (this->_z * v._y);
				vx._y = - (this->_x * v._z) + (this->_z * v._x);
				vx._z = (this->_x * v._y) - (this->_y * v._x);
				return vx;
			}


			TValue Min()
			{
				TValue t = _val[0];
				for (int i = 1; i < dim; ++i) {
					t = (t < _val[i] ? t : _val[i]);
				}
				return t;
			}

			TValue Max()
			{
				TValue t = _val[0];
				for (int i = 1; i < dim; ++i) {
					t = (t > _val[i] ? t : _val[i]);
				}
				return t;
			}

			double Sum()
			{
				double t = 0;
				for (int i = 0; i < dim; ++i) {
					t += _val[i];
				}
				return t;
			}

			double Mean() 
			{
				return (Sum() / dim);
			}
			
			double SqureSum()
			{
				double t = 0;
				for (int i = 0; i < dim; ++i) {
					t += pow((double)_val[i], 2);
				}
				return t;
			}

			double Length()
			{
				return sqrt(SqureSum());
			}
			
			self_type Abs()
			{
				self_type v;
				v._x = abs(this->_x);
				v._y = abs(this->_y);
				v._z = abs(this->_z);
				return v;
			}

			TValue& operator [] (int index) 
			{
				return _val[index];
			}

			friend std::ostream& operator << (std::ostream& stream, const self_type& v) 
			{ 
				stream << "(" << v._x << ", " << v._y << ", " << v._z << ")"
				return stream; 
			} 
			friend std::wostream& operator << (std::wostream& stream, const self_type& v) 
			{ 
				stream << "(" << v._x << ", " << v._y << ", " << v._z << ")"
				return stream; 
			} 
			friend std::istream& operator >> (std::istream& stream, const self_type& v) 
			{ 
				stream >> v._x >> v._y >> v._z; 
				return stream; 
			}
			friend std::wistream& operator >> (std::wistream& stream, const self_type& v) 
			{ 
				stream >> v._x >> v._y >> v._z; 
				return stream;
			}
		};

		typedef Vec3<short> Vec3s;
		typedef Vec3<int> Vec3i;
		typedef Vec3<float> Vec3f;
		typedef Vec3<double> Vec3d;
} } ///:~ namespace IMesh::Num


namespace IMesh { namespace Num { namespace GL {
	//typedef signed char GLbyte;
	//typedef short GLshort;
	//typedef int GLint;
	//typedef unsigned char GLubyte;
	//typedef unsigned short GLushort;
	//typedef unsigned int GLuint;
	//typedef float GLfloat;
	//typedef double GLdouble;
	typedef Vec3<GLbyte> Vec3GLbyte;
	typedef Vec3<GLshort> Vec3GLshort;
	typedef Vec3<GLint> Vec3GLint;
	typedef Vec3<GLubyte> Vec3GLubyte;
	typedef Vec3<GLushort> Vec3GLushort;
	typedef Vec3<GLuint> Vec3GLuint;
	typedef Vec3<GLfloat> Vec3GLfloat;
	typedef Vec3<GLdouble> Vec3GLdouble;


	

} } } ///:~ namespace IMesh::Num::GL
