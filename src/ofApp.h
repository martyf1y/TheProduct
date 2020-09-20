#pragma once

#include "ofMain.h"
#include "levelArea.h"
#include "textInput.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void playerUpdate();
        void changeNewLevel();
        void restart();

    
    //Character variables
    int posX; //Character position
    int posY;
    int playSizeX;
    int playSizeY;
    int playerSpeed [4];
    int doorExitCount; //Checks to see if the player is in the right space
    int doorEntryCount;
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    bool wait;//This stops the player from moving
    string playerDirection;
    ofImage playerImage;
    
       
    //Level Stuff
    levelArea** myLevel;
    int levelNum;
    int totalLevel;
    int stageUD;//We can go up and down!
    vector <string> thisRoom; //Dancers worthness
       
  
    //Text box
    bool closeToObject;
    bool whatIsThis;
    textInput *textBox;
    int textPlaceY;
    bool OnlyCreateOnce;

};
