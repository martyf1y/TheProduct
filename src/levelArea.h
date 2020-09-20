//
//  levelArea.h
//  The_Product
//
//  Created by Graduate on 12/05/14.
//
//

#ifndef __The_Product__levelArea__
#define __The_Product__levelArea__

#include <iostream>
#include "ofMain.h"
#include "officeObjects.h"
#include "realPeople.h"


extern vector <string> stage;
extern int preIndX [4];
extern int preIndY [4];
extern int cStage;
extern int roomSizeY;
extern bool finalSpeech;
class levelArea {
    
public:
    levelArea(int oldSide, int whatLevel, string inRoom, string nextRoom); // constructor - used to initialize an object, if no properties are passed

    void update(int pX, int pY, int playSizeX, int playSizeY);  // update method, used to refresh your objects properties
    void draw(int pX, int pY);    // draw method, this where you'll do the object's drawing
    void doorSetup();
    void indicator(int pX, int pY);
    int checkEntryBound(int pX, int pY, int playSizeX, int playSizeY);
    int checkExitBound(int pX, int pY, int playSizeX, int playSizeY);
    
    //Door exit and entry
    int exitDoorX;
    int exitDoorY;
    int entryDoorX;
    int entryDoorY;
    int doorSize; //Size of all the doors
    int maxLevel;//This will make sure previous levels are not reset
    int whatLevel;
    int side;
    int oldSide;
    int exitDoorRotate;//This roate the image to be on the right side
    int entryDoorRotate;
    int R, G, B;
    char exitDoorSide;//Gets the right side
    char entryDoorSide;//Gets the right side
    string inRoom;
    string nextRoom;//This is for the hall
    ofImage backgroundImage;//I have given a background for each level area
    ofImage backgroundHallImage;
    ofImage doorImage;
    //Game objects
    officeObjects** gameObjects;
	ofImage gameObjectImage;
    int nGameObjects;
    
    //The other characters
    realPeople** character;
    int nCharacters;
    
    //Flashing Indicator
    int blink;
    int blinkAmount;
    int indX;
    int indY;

private:
};
#endif /* defined(__The_Product__levelArea__) */
