#pragma once

#include "ofxSpout2Receiver.h"

using namespace ofxSpout2;

Receiver::Receiver() {
	;
}

void Receiver::setup(int width, int height) {
	mReceiver = new SpoutReceiver();
	mbInitialized = false;
	SenderName[0] = 0;
	receiving = false;

	init(width, height);
}

void Receiver::init(int width, int height) {
	mTexture.allocate(width, height, GL_RGBA);
	mbInitialized = true;
}

void Receiver::showSenders() {
	mReceiver->SelectSenderPanel();
}

void Receiver::updateTexture() {
	unsigned int preWidth = mTexture.getWidth();
	unsigned int preHeight = mTexture.getHeight();
	unsigned int width, height;

	if (!receiving) {
		if (mReceiver->CreateReceiver(SenderName, width, height, true)) {
			if (width != preWidth || height != preHeight) { // in case of size change, reallocate
				init(width, height);
			}
			receiving = true;
		}
		else {
			ofLogWarning("ofxSpout", "No sender detected");
		}
	}
	else { // receiving
		if (mReceiver->ReceiveTexture(SenderName, width, height, mTexture.getTextureData().textureID, mTexture.getTextureData().textureTarget)) {
			if (width != preWidth || height != preHeight) { // in case of size change, reallocate
				init(width, height);
			}
		}
		else {
			mReceiver->ReleaseReceiver();
			receiving = false;
		}
	}
}

void Receiver::exit() {
	if(mReceiver != NULL && mbInitialized)
		mReceiver->ReleaseReceiver();
}