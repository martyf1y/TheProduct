//
//  realPeople.h
//  The_Product
//
//  Created by Graduate on 31/05/14.
//
//

#ifndef __The_Product__realPeople__
#define __The_Product__realPeople__

#include <iostream>
#include "ofMain.h"
#include "officeObjects.h"




class realPeople : public officeObjects
{
    
public:
    void changeText(string _findInfo);
    void objectDetection(officeObjects** gameObjects, realPeople** characters);
    void followPlayer(int pX, int pY, int playSizeX, int playSizeY);
    void backAwayFromPlayer(int pX, int pY, int playSizeX, int playSizeY);
    void stareAtPlayer(int pX, int pY, int playSizeX, int playSizeY);
    void update(int pX, int pY, int playSizeX, int playSizeY, officeObjects** gameObjects, realPeople** characters);
    void timerDraw();

    string charInRoom;
    int maxChar;
    int charSpeedX;
    int charSpeedY;
    //Timer
    float startTime; // store when we start time timer
    float endTime; // when do want to stop the timer
    bool  bTimerReached; // used as a trigger when we hit the timer
    
    realPeople(ofImage objectImage, string findInfo, string iAm, int whichOne, int charThisOne, int _maxChar, officeObjects** gameObjects, realPeople** characters)//Charrealone is the number label for the characters
    : officeObjects(objectImage,  findInfo, iAm, whichOne, charThisOne, gameObjects)
    {
        charInRoom = findInfo;
        maxChar = _maxChar;
        findInfo = findInfo + "/character" + ofToString(5+charThisOne); //This is the location of the description of the object
        //Now we need to check over the characters to make sure they don't spawn on each other
        for(int check = charWhichOne-1; check >= 0; check--)
        {
           // cout << "This is charWhichOne " << charWhichOne << endl;
           // cout << "This is SAFE " << safe << endl;
            if(safe == true
               && objectX + objectWidth/2 >= characters[check]->objectX - characters[check]->objectWidth/2
               && objectX - objectWidth/2 <= characters[check]->objectX + characters[check]->objectWidth/2
               && objectY + objectHeight/2 >= characters[check]->objectY - characters[check]->objectHeight/2
               && objectY - objectHeight/2 <= characters[check]->objectY + characters[check]->objectHeight/2
               ) //This stops the player from getting outside the space
            {
                safe = false;
                objectX = -1500;//Not the best solution, find a way to make the object not exist or not get updated
                objectY = -1500;
            }
        }
        changeText(findInfo);
        if(charInRoom == "Customer")
        {
             r = 255;
             g = 255;
             b = 10;
        }
        if(charInRoom == "Hall")
        {
            r = 119;
            g = 119;
            b = 119;
        }
        charSpeedX = 2;
        charSpeedY = 2;
        //Timer
        bTimerReached = false;
        startTime = ofGetElapsedTimeMillis();  // get the start time
    }
protected:
};

#endif /* defined(__The_Product__realPeople__) */


