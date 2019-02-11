#include "ofApp.h"
#include "ofxGui/src/ofxGui.h"
#include "ofxRaycaster.h"
#include "of3dGraphics.h"
ofxFloatSlider radius, radius2, centerX, centerY, centerZ, centerX2, centerY2, centerZ2;
ofxButton traceRays, debugArray;
ofxToggle toggleSphere2;
ofxPanel gui;
RayTracing rayTracing;
ofSpherePrimitive sphere;
ofSpherePrimitive sphere2;
ofImage img;
bool sphere2Enabled=false;
//--------------------------------------------------------------
void ofApp::setup(){
	ofColor black(0, 0, 0);
	ofBackground(black);
	traceRays.addListener(this, &ofApp::traceButtonPressed);
	gui.setup();
	gui.add(radius.setup("Radius Sphere 1", 140, 10, 300));
	gui.add(centerX.setup("X Value Sphere 1", ofGetWidth()/2,0, ofGetWidth()));
	gui.add(centerY.setup("Y Value Sphere 1", ofGetHeight() / 2, 0, ofGetHeight()));
	gui.add(centerZ.setup("Z Value Sphere 1", 140, 10, 300));
	gui.add(radius2.setup("Radius Sphere 2", 140, 10, 300));
	gui.add(centerX2.setup("X Value Sphere 2", ofGetWidth() / 2, 0, ofGetWidth()));
	gui.add(centerY2.setup("Y Value Sphere 2", ofGetHeight() / 2, 0, ofGetHeight()));
	gui.add(centerZ2.setup("Z Value Sphere 2", 140, 10, 300));

	gui.add(traceRays.setup("Draw Ray Traced Image"));
	gui.add(toggleSphere2.setup("Add Second Sphere", false));
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	glm::vec3 spherePos = glm::vec3();
	spherePos.x = centerX;
	spherePos.y = centerY;
	spherePos.z = centerZ;
	
	sphere.setRadius(radius);
	sphere.setGlobalPosition(spherePos);

	glm::vec3 sphere2Pos = glm::vec3();
	sphere2Pos.x = centerX2;
	sphere2Pos.y = centerY2;
	sphere2Pos.z = centerZ2;

	sphere2.setRadius(radius2);
	sphere2.setGlobalPosition(sphere2Pos);

	if (!rayTracing.isTracingFinished()) {
		sphere.draw();
		if(toggleSphere2) sphere2.draw();
	}
	else {

		img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		ofPixels &pixels = img.getPixels();

		ofColor yellow(255, 255, 0);
		ofColor green(0, 255, 0);
		ofColor blue(0, 0, 255);
		int** hitArray = rayTracing.hitArray;
		for (int i = 0; i < ofGetHeight(); i++){
			for (int j = 0; j < ofGetWidth(); j++) {
				if (hitArray[j][i] == 1) {
					pixels.setColor(j, i, yellow);
				}
				else if (hitArray[j][i] == 2){
					pixels.setColor(j, i, blue);
				}
				else if (hitArray[j][i] == 3) {
					pixels.setColor(j, i, green);
				}
			}
		}
		img.update();
		img.draw(0, 0);

	}

	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::traceButtonPressed() {
	
	rayTracing.generateRaysAndCheckHits(ofGetWidth(), ofGetHeight(), sphere, sphere2, sphere2Enabled);
}