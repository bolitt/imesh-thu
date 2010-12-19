#pragma once

#include "Structures.h"

namespace IMesh { 
namespace UI { // namespace IMesh::UI

	namespace Config
	{
		namespace Colors 
		{
			const extern Num::GL::RGBColor RED;
			const extern Num::GL::RGBColor GREEN;
			const extern Num::GL::RGBColor BLUE;
			const extern Num::GL::RGBColor YELLOW;
			const extern Num::GL::RGBColor WHITE;
		}

		namespace Navigation
		{
			// For Camera
			const extern double DEFAULT_ANGLE_X;
			const extern double DEFAULT_ANGLE_Y;
			const extern double DEFAULT_MIN_DISTANCE;
			const extern double DEFAULT_DISTANCE;
			const extern double DEFAULT_MAX_DISTANCE;

			// For Projection
			const extern double DEFAULT_BASELINE;
			const extern double DEFAULT_LEFT;
			const extern double DEFAULT_RIGHT;
			const extern double DEFAULT_BOTTOM;
			const extern double DEFAULT_TOP;
			const extern double DEFAULT_NEAR;
			const extern double DEFAULT_FAR;
			const extern double DEFAULT_MODEL_VIEW_SIZE;

			// For DEG-RAD Transform
			const extern double DEG2RAD;
			const extern double RAD2DEG;
			const extern double PI;
			const extern double PI_2;
			const extern double PI_4;
			const extern double DIV_1_PI;
			const extern double DIV_2_PI;

			// For User Zoom
			const extern double DEG_PER_ROTATE_RATE;
			const extern double ZOOM_IN_RATE;
			const extern double ZOOM_OUT_RATE;
		}

		namespace Animation 
		{
			const extern double SLOW;
			const extern double NORMAL;
			const extern double FAST;
		}
	}

}} ///:~namespace Mesh::UI
