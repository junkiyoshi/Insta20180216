#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	int deg_span = 10;
	float radius = 0;
	float radius_span = 30;
	int layer = 35;

	this->fbo.begin();
	ofClear(0);

	for (int deg = 0; deg < 360; deg += deg_span) {

		radius = 0;

		for (int i = 0; i < layer; i++) {

			float noise_value = ofNoise(deg * 0.005, i * 0.005 - ofGetFrameNum() * 0.005);
			ofColor color;
			color.setHsb(noise_value * 255, 255, 255);
			ofSetColor(color);

			ofBeginShape();

			for (int tmp_deg = deg; tmp_deg <= deg + deg_span; tmp_deg += 1) {

				ofVertex(radius * cos(tmp_deg * DEG_TO_RAD) + ofGetWidth() / 2, radius * sin(tmp_deg * DEG_TO_RAD) + ofGetHeight() / 2);
			}

			for (int tmp_deg = deg + deg_span; tmp_deg >= deg; tmp_deg -= 1) {

				ofVertex((radius + radius_span) * cos(tmp_deg * DEG_TO_RAD) + ofGetWidth() / 2, (radius + radius_span) * sin(tmp_deg * DEG_TO_RAD) + ofGetHeight() / 2);
			}

			ofEndShape(true);

			radius += radius_span;
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}