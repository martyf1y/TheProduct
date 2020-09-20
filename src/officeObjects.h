//
//  officeObjects.h
//  The_Product
//
//  Created by Graduate on 15/05/14.
//
//

#ifndef __The_Product__officeObjects__
#define __The_Product__officeObjects__

#include <iostream>
#include "ofMain.h"

extern int roomSizeY;
extern int cStage;
extern string sayHello;
extern vector <string> stage;

class officeObjects {
    
public:
    officeObjects(ofImage objectImage, string findInfo, string iAm, int whichOne, int charWhichOne, officeObjects** gameObjects); // constructor - used to initialize an object, if no properties are passed
    
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    //These functions help find the boundaries of the objects
    float checkBoundX(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed, bool moveRight, bool moveLeft);
    float checkBoundY(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed, bool moveUp, bool moveDown);
    bool createText(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed);
    int objectRotate;
    int objectX;
    int objectY;
    int objectHeight;
    int objectWidth;
    int whichOne;
    int charWhichOne;//For character number value
    int r, g, b;
    string iAm;
    bool safe;//This makes sure the object can be placed
 //The objects image
    ofImage objectImage;

    //Text box
    string findInfo;
  
    
private:
};


#endif /* defined(__The_Product__officeObjects__) */

