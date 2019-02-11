#include "ofxRaycaster.h"
class RayTracing
{
public:
	RayTracing();
	void generateRaysAndCheckHits(int width, int height, ofSpherePrimitive sphere);
	void generateRaysAndCheckHits(int width, int height, ofSpherePrimitive sphere, ofSpherePrimitive sphere2, bool sphere2Enabled);
	int ** setup2DArray(int columns, int rows);
	void printHitArray();
	int** hitArray;
	bool tracingFinished = false;
	bool isTracingFinished();

};

