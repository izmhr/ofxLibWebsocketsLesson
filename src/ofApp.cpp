#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
	options.port = 9092;
	options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
	bSetup = server.setup( options );

	// this adds your app as a listener for the server
	server.addListener(this);

	// libwebsocket内蔵のウェブサーバ機能を使って、ブラウザにクライアントページを開く
	// server.setup() 時点でウェブサーバが起動している。
    string url = "http";
    url += "://localhost:" + ofToString( server.getPort() );
    ofLaunchBrowser(url);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 0, 0);
	ofCircle(circlePos.x, circlePos.y, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	Json::FastWriter	writer;
	Json::Value			value;
	value["x"] = x;
	value["y"] = y;
	std::string message =  writer.write(value);
	server.send(message);
	cout << "mouseMoved : " << message;

	circlePos.x = x;
	circlePos.y = y;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
	cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
	cout<<"new connection open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
	cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
	cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
	cout<<"got message "<<args.message<<endl;
	
	// trace out string messages or JSON messages!
	if ( !args.json.isNull() ){
		cout << "New message: " + args.json.toStyledString() + " from " + args.conn.getClientName();
		circlePos.x = args.json["x"].asFloat();
		circlePos.y = args.json["y"].asFloat();
	}
		
	// echo server = send message right back!
	//args.conn.send( args.message );
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
	cout<<"got broadcast "<<args.message<<endl;    
}