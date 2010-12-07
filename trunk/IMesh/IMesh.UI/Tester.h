
#include "vec.h"

namespace IMesh { namespace Num { 

	namespace Test
	{
		class Tester
		{
		protected:
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

					Vec3i m4 = m3.Abs();
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
				}
			}

		public:
			static void Run()
			{
				TestVec();
			}

		};

	}

} }