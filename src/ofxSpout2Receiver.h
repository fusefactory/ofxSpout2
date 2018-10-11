#pragma once

#include "ofMain.h"
#include "Spout.h"

namespace ofxSpout2 {
	class Receiver {
	public:
		Receiver();

		void setup(int width, int height);
		bool isInitialized() { return mbInitialized; }

		// show the panel for possible senders and select one
		void showSenders();

		void updateTexture();

		// call updateTexture() in a draw() call before (not in update())
		ofTexture &getTexture() { return mTexture; }

		// call in ofApp::exit()
		void exit();

	private:
		SpoutReceiver *mReceiver;
		void init(int width, int height);
		bool mbInitialized;
		bool receiving;
		char SenderName[256];
		ofTexture mTexture;
	};
}