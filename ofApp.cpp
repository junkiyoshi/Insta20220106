#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255); 
	ofSetLineWidth(2);

	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	vector<ofColor> base_color_list;
	vector<int> hex_list = { 0xf44336, 0x9C27B0, 0x3F51B5, 0x03A9F4, 0x009688, 0x8BC34A, 0xFFEB3B, 0xFF9800 };
	for (auto hex : hex_list) {

		ofColor color;
		color.setHex(hex);
		base_color_list.push_back(color);
	}

	int radius = 28;
	int width = 7;

	for (int x = -radius * 10; x <= radius * 10; x += radius * 2.5) {

		for (int y = -radius * 8; y <= radius * 8; y += radius * 4) {

			auto top = glm::vec3(x + 0, y - radius + width * 0.5, 0);
			auto bottom = glm::vec3(x + 0, y + radius - width * 0.5, 0);

			ofSetColor(255, 64);
			ofDrawCircle(top, radius);
			ofDrawCircle(top, radius - width);

			ofDrawCircle(bottom, radius);
			ofDrawCircle(bottom, radius - width);

			int deg_span = 30;
			int p = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015), 0, 1, 0, 1440);
			int max_i = ofRandom(8, 20);
			for (int i = 0; i < max_i; i++) {

				int param = (p + i * deg_span) % 720;
				ofColor face_color = base_color_list[ofRandom(base_color_list.size())];

				if (param < 360) {

					int deg_start = param / deg_span * deg_span + 270;
					for (int deg = deg_start + 1; deg <= deg_start + deg_span - 1; deg += 1) {

						vector<glm::vec3> vertices;
						vertices.push_back(bottom + glm::vec3((radius - width) * cos(deg * DEG_TO_RAD), (radius - width) * sin(deg * DEG_TO_RAD), 0));
						vertices.push_back(bottom + glm::vec3((radius - width) * cos((deg + 1) * DEG_TO_RAD), (radius - width) * sin((deg + 1) * DEG_TO_RAD), 0));
						vertices.push_back(bottom + glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));
						vertices.push_back(bottom + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));

						ofMesh face, line;
						line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

						face.addVertices(vertices);
						line.addVertices(vertices);

						face.addIndex(0); face.addIndex(1); face.addIndex(2);
						face.addIndex(0); face.addIndex(2); face.addIndex(3);

						line.addIndex(0); line.addIndex(1);
						line.addIndex(2); line.addIndex(3);

						if (deg == deg_start + 1) {

							line.addIndex(0); line.addIndex(3);
						}
						else if (deg == deg_start + deg_span - 1) {

							line.addIndex(1); line.addIndex(2);
						}

						ofSetColor(face_color, 100);
						face.draw();

						ofSetColor(face_color);
						line.drawWireframe();
					}
				}
				else {

					int deg_start = 720 - param / deg_span * deg_span + 90;
					for (int deg = deg_start - 1; deg >= deg_start - deg_span + 1; deg -= 1) {

						vector<glm::vec3> vertices;
						vertices.push_back(top + glm::vec3((radius - width) * cos(deg * DEG_TO_RAD), (radius - width) * sin(deg * DEG_TO_RAD), 0));
						vertices.push_back(top + glm::vec3((radius - width) * cos((deg - 1) * DEG_TO_RAD), (radius - width) * sin((deg - 1) * DEG_TO_RAD), 0));
						vertices.push_back(top + glm::vec3(radius * cos((deg - 1) * DEG_TO_RAD), radius * sin((deg - 1) * DEG_TO_RAD), 0));
						vertices.push_back(top + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));

						ofMesh face, line;
						line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

						face.addVertices(vertices);
						line.addVertices(vertices);

						face.addIndex(0); face.addIndex(1); face.addIndex(2);
						face.addIndex(0); face.addIndex(2); face.addIndex(3);

						line.addIndex(0); line.addIndex(1);
						line.addIndex(2); line.addIndex(3);

						if (deg == deg_start - 1) {

							line.addIndex(0); line.addIndex(3);
						}
						else if (deg == deg_start - deg_span + 1) {

							line.addIndex(1); line.addIndex(2);
						}

						ofSetColor(face_color, 100);
						face.draw();

						ofSetColor(face_color);
						line.drawWireframe();
					}

				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}