#include "StdAfx.h"
#include "Config.h"
// define of config.h

namespace IMesh { 
namespace UI { // namespace IMesh::UI
	
	namespace Config 
	{
		namespace Colors
		{
			const Num::GL::RGBColor RED(1.0f, 0.0f, 0.0f);
			const Num::GL::RGBColor GREEN(0.0f, 1.0f, 0.0f);
			const Num::GL::RGBColor BLUE(0.0f, 0.0f, 1.0f);
			const Num::GL::RGBColor YELLOW(1.0f, 1.0f, 1.0f);
			const Num::GL::RGBColor WHITE(1.0f, 1.0f, 1.0f);
		}

		namespace Navigation
		{
			// For Camera
			const double DEFAULT_ANGLE_X = 15;
			const double DEFAULT_ANGLE_Y = 65;
			const double DEFAULT_MIN_DISTANCE = 0.1;
			const double DEFAULT_DISTANCE = 200;
			const double DEFAULT_MAX_DISTANCE = 5000;

			// For Projection
			const double DEFAULT_BASELINE = 0.5;
			const double DEFAULT_LEFT = -0.5;
			const double DEFAULT_RIGHT = 0.5;
			const double DEFAULT_BOTTOM = -0.5;
			const double DEFAULT_TOP = 0.5;
			const double DEFAULT_NEAR = 1;
			const double DEFAULT_FAR = 1e5;
			const double DEFAULT_MODEL_VIEW_SIZE = 100;

			// For DEG-RAD Transform
			const double DEG2RAD = PI / 180.0;
			const double RAD2DEG = 180.0 / 3.141593;
			const double PI = 3.14159265358979323846;
			const double PI_2 = 1.57079632679489661923;
			const double PI_4 = 0.785398163397448309616;
			const double DIV_1_PI = 0.318309886183790671538;
			const double DIV_2_PI = 0.636619772367581343076;

			// For User Zoom
			const double DEG_PER_ROTATE_RATE = 250;
			const double ZOOM_IN_RATE = 1.1;
			const double ZOOM_OUT_RATE = 1.0 / ZOOM_IN_RATE;
		}


		namespace Animation 
		{
			const double SLOW = 2000;   // million-seconds
			const double NORMAL = 1000; // million-seconds
			const double FAST = 500;    // million-seconds
		}
	}


}}


