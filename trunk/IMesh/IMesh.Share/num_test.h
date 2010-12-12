#pragma once

#include <iostream>
#include <sstream>
#include "vec.h"

#ifndef ASSERT
  #include <assert.h>
  #define ASSERT assert
#endif

namespace IMesh { namespace Num { namespace Test {

class Tester
{
public:
	static void Run()
	{
		TestVec();
	}

protected:

#pragma region test vec

	static void TestVec()
	{
		// test vec.h
		{
			using namespace IMesh::Num;
			Vec3i m1(1);

			ASSERT(m1._x == 1 && m1._y == 1 && m1._z == 1);

			Vec3i m2(-2);
			ASSERT(m2._x == -2 && m2._y == -2 && m2._z == -2);

			Vec3i v1(1, -2, 3);
			ASSERT(v1._x == 1 && v1._y == -2 && v1._z == 3);

			Vec3i m3 = m1 + m2;
			ASSERT(m3._x == -1 && m3._y == -1 && m3._z == -1);

			Vec3i m4 = m3;
			m4.Abs();
			ASSERT(m4._x == 1 && m4._y == 1 && m4._z == 1);

			int i5 = m3.Dot(v1);
			ASSERT(i5 == -2);

			// |i   j    k|
			// |-1  -1  -1|
			// |1   -2   3|
			Vec3i m5 = m3.Cross(v1);
			ASSERT(m5._x == -5 && m5._y == 2 && m5._z == 3);

			ASSERT(v1.Max() == 3);
			ASSERT(v1.Min() == -2);
			ASSERT(v1.SqureSum() == 14);

			std::cout << m5 << std::endl;
			std::stringstream ss;
			ss << m5;
			Vec3i newM5;
			ss >> newM5;
			ASSERT(newM5._x == -5 && newM5._y == 2 && newM5._z == 3);
		}

		{
			using namespace IMesh::Num;
			Vec3i m1;
			ASSERT(m1._x == 0 && m1._y == 0 && m1._z == 0);
			Vec3i m2(-1);
			Vec3i m3(1, 2, 3);

			m1 += m2;
			m1 += m3;
			ASSERT(m1._x == 0 && m1._y == 1 && m1._z == 2);

			Vec3i m4 = -m2;
			ASSERT(m4._x == 1 && m4._y == 1 && m4._z == 1);

			m4 = +m2;
			ASSERT(m4._x == -1 && m4._y == -1 && m4._z == -1);

			m4.Add(5);
			ASSERT(m4._x == 4 && m4._y == 4 && m4._z == 4);

			m4.Add(Vec3i(1, 2, 3));
			ASSERT(m4._x == 5 && m4._y == 6 && m4._z == 7);

			m4.Zeros();
			ASSERT(m4._x == 0 && m4._y == 0 && m4._z == 0);

		}
	}
#pragma endregion test vec

};

} } }
