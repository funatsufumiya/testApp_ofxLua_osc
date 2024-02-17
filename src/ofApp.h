#pragma once

#include "ofMain.h"
#include "ofxLua.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp, ofxLuaListener {

	public:
		void setup();
		void update();
		void draw();
        void exit();
        void reloadScript();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // ofxLua error callback
        void errorReceived(std::string &msg);
    
        void oscReceived(const ofxOscMessage &message);
    
        ofxLua lua;
        ofxOscReceiver oscReceiver;
		std::string script;
};
