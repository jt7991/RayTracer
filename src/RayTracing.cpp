#include "RayTracing.h"



RayTracing::RayTracing()
{
}


void RayTracing::generateRaysAndCheckHits(int width, int height, ofSpherePrimitive sphere, ofSpherePrimitive sphere2, bool sphere2Enabled) {
	hitArray = setup2DArray(height, width);
	glm::vec3 rayDirection;
	rayDirection = glm::vec3(0, 0, 1);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ofxraycaster::Ray<glm::vec3> ray;
			glm::vec3 position, position2;
			glm::vec3 normal, normal2;
			ray.setup(glm::vec3(j, i, 0), rayDirection);
			if (ray.intersectsSphere(sphere.getGlobalPosition(),
				sphere.getRadius(),
				position,
				normal)) {
				if (sphere2Enabled && ray.intersectsSphere(sphere2.getGlobalPosition(),
					sphere2.getRadius(),
					position2,
					normal2)) {
					hitArray[j][i] = 3;
				}
				else hitArray[j][i] = 1;
			}
			else if(sphere2Enabled && ray.intersectsSphere(sphere2.getGlobalPosition(),
				sphere2.getRadius(),
				position,
				normal)){
				hitArray[j][i] = 2;
			}
			else {
				hitArray[j][i] = 0;
			}
		}
	}
	tracingFinished = true;
}
int** RayTracing::setup2DArray(int columns, int rows) {
	int** array = new int*[rows];
	for (int i = 0; i < rows; ++i) array[i] = new int[columns];
	return array;
}

void RayTracing::printHitArray() {
	for (int i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
			std::cout << hitArray[j][i];
		}
		std::cout << std::endl;
	}
}
bool RayTracing::isTracingFinished() {
	return tracingFinished;
}