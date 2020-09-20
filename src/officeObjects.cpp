//
//  officeObjects.cpp
//  The_Product
//
//  Created by Graduate on 15/05/14.
//
//

#include "officeObjects.h"

officeObjects::officeObjects(ofImage _objectImage, string _findInfo, string _iAm, int _whichOne, int _charWhichOne, officeObjects** gameObjects)
{
    objectRotate = 0;
    objectImage = _objectImage;
    whichOne = _whichOne;//Labels the object with a number
    charWhichOne = _charWhichOne;//This is pointless for objects, only characters
    iAm = _iAm;//This tells the object what it really is (character maybe)
    objectWidth = objectImage.width;
    objectHeight = objectImage.height;
    objectX = ofRandom(objectWidth/2 + 80 , ofGetWidth() - objectWidth/2 - 80);;
    objectY = ofRandom(objectHeight/2 + 80 + roomSizeY, ofGetHeight() - objectHeight/2 - 80 - roomSizeY);
    findInfo = _findInfo + "/object" + ofToString(whichOne); //This is the location of the description of the object
    string checkRoom = _findInfo;
    safe = true;//This makes sure the object can be placed
    
    //This checks to make sure the scripted room has the correct things in place
    if(stage[cStage] == checkRoom)//change back to stage == checkroom
    {
        ofBuffer buffer = ofBufferFromFile("texts/Stage" + stage[cStage] + "/" + stage[cStage] + "/scriptPos.txt");//Gets the file
        vector<string> allPos;
        allPos = ofSplitString(buffer, "\n");
        //int pos = find(allPos.begin(), allPos.end(), iAm + ofToString(whichOne + charWhichOne)) - allPos.begin();
        
        for(int i = 0; i < allPos.size(); i ++)
        {
            string currentPos = allPos[i];
            if (currentPos.find(iAm + ofToString(whichOne + charWhichOne)) != std::string::npos) {
               // std::cout << "found! at " << i << endl;
                vector<string> thisPos;
                thisPos = ofSplitString(currentPos, " ");
                objectX = ofToInt(thisPos[1]);
                objectY = ofToInt(thisPos[2]);
            }
        }
      //  cout << allPos[0] << " yes" << endl;
      
        
    }
    else
    {
        if(checkRoom == "Hall"
           && objectY + objectHeight/2 >= ofGetHeight() - objectHeight/2 - 80 - roomSizeY
           && objectY - objectHeight/2 <= objectHeight/2 + 80 + roomSizeY) //This stops the object from getting outside the space
        {
            safe = false;
            objectX = -1500;//Not the best solution, find a way to make the object not exist or not get updated
            objectY = -1500;
        }

        for(int check = whichOne-1; check >= 0; check--)
        {
            if(safe == true
                    && objectX + objectWidth/2 >= gameObjects[check]->objectX - gameObjects[check]->objectWidth/2
                    && objectX - objectWidth/2 <= gameObjects[check]->objectX + gameObjects[check]->objectWidth/2
                    && objectY + objectHeight/2 >= gameObjects[check]->objectY - gameObjects[check]->objectHeight/2
                    && objectY - objectHeight/2 <= gameObjects[check]->objectY + gameObjects[check]->objectHeight/2
                    ) //This stops the player from getting outside the space
            {
                safe = false;
                objectX = -1500;//Not the best solution, find a way to make the object not exist or not get updated
                objectY = -1500;
            }
        }
    }
    r = 255;
    g = 255;
    b = 255;
    
}

void officeObjects::update(){
    cout << "What about this" << endl;
}

float officeObjects::checkBoundX(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed, bool moveRight, bool moveLeft)
{
    if(pX + playSizeX/2 >= objectX - objectWidth/2
       && pX <= objectX
       && pY + playSizeY/2 >= objectY - objectHeight/2
       && pY - playSizeY/2 <= objectY + objectHeight/2
       && moveRight
       ) //This stops the player from getting outside the space
    {
        pX -= playerSpeed;
    }
    else if(pX >= objectX
       && pX - playSizeX/2 <= objectX + objectWidth/2
       && pY + playSizeY/2 >= objectY - objectHeight/2
       && pY - playSizeY/2 <= objectY + objectHeight/2
       && moveLeft
       ) //This stops the player from getting outside the space
    {
        pX += playerSpeed;
    }
    return pX;
}

float officeObjects::checkBoundY(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed, bool moveUp, bool moveDown)
{
    if(pY + playSizeY/2 >= objectY - objectHeight/2
       && pY  <= objectY
       && pX + playSizeX/2 >= objectX - objectWidth/2
       && pX - playSizeX/2 <= objectX + objectWidth/2
       && moveDown
       ) //This stops the player from getting outside the space
    {
        pY -= playerSpeed;
    }
    else if(pY >= objectY
       && pY - playSizeY/2 <= objectY + objectHeight/2
       && pX + playSizeX/2 >= objectX - objectWidth/2
       && pX - playSizeX/2 <= objectX + objectWidth/2
       && moveUp
       ) //This stops the player from getting outside the space
    {
        pY += playerSpeed;
    }
    return pY;
}

bool officeObjects::createText(int pX, int pY, int playSizeX, int playSizeY, int playerSpeed)
{
    //Allows the interaction with the checkboxes
    if(pX + playSizeX/2 + playerSpeed +2 >= objectX - objectWidth/2
       && pX - playSizeX/2 - playerSpeed -2 <= objectX + objectWidth/2
       && pY + playSizeY/2 + playerSpeed +2 >= objectY - objectHeight/2
       && pY - playSizeY/2 - playerSpeed -2 <= objectY + objectHeight/2
       )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void officeObjects::draw(){
    ofEnableAlphaBlending();
    ofPushMatrix();
    ofTranslate(objectX, objectY, 0);//move pivot to centre
    ofRotateZ(objectRotate);//rotate from centre
    ofSetColor(r, g, b);
    objectImage.draw(-objectWidth/2,  -objectHeight/2, objectWidth, objectHeight);
    ofPopMatrix();
    ofSetColor(255,255,255);
    string Object = "This is " + ofToString(whichOne)+ "\n";
    //ofDrawBitmapString(Object, objectX - objectWidth/2, objectY - objectHeight/2);
    ofDisableAlphaBlending();
}

