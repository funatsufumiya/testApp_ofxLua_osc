#include "ofApp.h"
#include "ofxOscLua.h"

//--------------------------------------------------------------
void ofApp::setup(){
    lua.init(true);
    ofxOscLua::setup(lua);
    oscReceiver.setup(3000);

    script = "test.lua";
    
    lua.addListener(this);
    lua.doScript(script);
    
    lua.scriptSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
    while(oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        oscReceived(m);
    }

    lua.scriptUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    lua.scriptDraw();
}

//--------------------------------------------------------------
void ofApp::oscReceived(const ofxOscMessage &message) {
    if(!lua.isValid() || !lua.isFunction("oscReceived")) {
        return;
    }
    lua_getglobal(lua, "oscReceived");
    lua.pushobject("ofxOscMessage", new ofxOscMessage(message));
    if(lua_pcall(lua, 1, 0, 0) != 0) {
        std::string line = "Error running oscReceived(): " + (std::string) lua_tostring(lua, -1);
        lua.errorOccurred(line);
    }
}

//--------------------------------------------------------------
void ofApp::errorReceived(std::string& msg) {
    ofLogNotice() << "got a script error: " << msg;
}

//--------------------------------------------------------------
void ofApp::exit(){
    lua.scriptExit();
    lua.clear();
}

//--------------------------------------------------------------
void ofApp::reloadScript(){
    lua.scriptExit();
    lua.init();
    lua.doScript(script);
    lua.scriptSetup();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'r':
            reloadScript();
            break;
    }
    lua.scriptKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    lua.scriptKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    lua.scriptMouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    lua.scriptMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    lua.scriptMousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    lua.scriptMouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    lua.scriptMouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    lua.scriptWindowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    script = dragInfo.files[0];
    reloadScript();
}
