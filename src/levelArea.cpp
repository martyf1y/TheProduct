//
//  levelArea.cpp
//  The_Product
//
//  Created by Graduate on 12/05/14.
//
//

#include "levelArea.h"


levelArea::levelArea(int _oldSide, int _whatLevel, string _inRoom, string _nextRoom)
{
    side = ofRandom(4);
    oldSide = _oldSide;
    whatLevel = _whatLevel;//This is to tag the level with its right number
    inRoom = _inRoom;// The name of the room we are in
    nextRoom = _nextRoom;//Just to get the hall right
    entryDoorRotate = 0;
    exitDoorRotate = 0;
    blink = 0;
    blinkAmount = 0;
    nCharacters = 0;//Starts as zero but later on....
    nGameObjects = 0;
    
    if(inRoom == "Hall")
    {
        roomSizeY = 200;//Makes sure the objects are only trying to fit within the right hall space
    }
    else
    {
        roomSizeY = 0;
    }
    
    //Background
    backgroundImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/background.png");
    backgroundHallImage.cropFrom(backgroundImage, 0, roomSizeY, backgroundImage.width, backgroundImage.height - roomSizeY*2-17);
    
    //Door stuff
    doorImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/door.png");
    doorSize = 60;

    doorSetup();

    //office objects
    while(gameObjectImage.isAllocated() || nGameObjects == 0)
    {
        gameObjectImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/object" + ofToString(nGameObjects) + ".png");
        nGameObjects++;
    }
    nGameObjects--;
    gameObjects = new officeObjects*[nGameObjects];
    
       for(int i = 0; i < nGameObjects; i++)
    {
        gameObjectImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/object" + ofToString(i) + ".png");
        int tryCount = 0;
        string iAmA = "object";
        int forCharnum = 0;//This is pointless for objects
        //Set the safe variable first
        gameObjects[i] = new officeObjects(gameObjectImage, inRoom, iAmA, i, forCharnum, gameObjects);//Remember to change this back to a proper description
        while(!gameObjects[i]->safe && tryCount < 101)
        {
            gameObjects[i] = new officeObjects(gameObjectImage, inRoom, iAmA, i, forCharnum, gameObjects);//Remember to change this back to a proper description
            tryCount ++;
        }
       // cout << "this count office " << tryCount << endl;
    }
    
    //A.I Characters
   // if(stage[cStage] == "Board" && inRoom == "Board")
   // {
   // nCharacters = 6;
   // }
   // else
   // {
   // nCharacters = 5;
   // }
    
    //This code is to assign only the right amount of characters
    while(gameObjectImage.isAllocated() || nCharacters == 0)
    {
        cout << "characters2 " << nCharacters << endl;

    gameObjectImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/character" + ofToString(nCharacters+5) + ".png");
    nCharacters++;
    }
    nCharacters--;
    cout << "characters " << nCharacters << endl;

    character = new realPeople*[nCharacters];

    //This is after so we know where the large objects are first
    for(int i = 0; i < nCharacters; i++)
    {
        gameObjectImage.loadImage("images/Stage" + stage[cStage] + "/" + inRoom + "/character" + ofToString(i+5) + ".png");
        int tryCount = 0;
        string iAmA = "character";
        //Set the safe variable first
        character[i] = new realPeople(gameObjectImage, inRoom, iAmA, nGameObjects, i, nCharacters, gameObjects, character);//The reason it is nGameObjects to check against the max amount of office objects
        while(!character[i]->safe && tryCount < 101)
        {
            character[i] = new realPeople(gameObjectImage, inRoom, iAmA, nGameObjects, i, nCharacters, gameObjects, character);//Remember to change this back to a proper description
            tryCount ++;
        }
       // cout << "this count people " << tryCount << endl;
    }
    
}


void levelArea::doorSetup()
{
    
    if(nextRoom == "Hall" || inRoom == "Hall")//Its a lot for just one hallway
    {
        exitDoorY = ofRandom(0 + doorSize + roomSizeY, ofGetHeight() - doorSize - roomSizeY);
        exitDoorX = ofGetWidth();
        exitDoorSide = 'R'; //This gets the right side of the exit
        exitDoorRotate = 90;
        side = 3;
    }
    else if(whatLevel == 5)//This makes sure there is only 5 levels to enter into
    {
        
        exitDoorY = -500;
        exitDoorX = -500;
        exitDoorSide = 'N';//Make sure they are not the same
    }
    else if(side == 0)
    {
        exitDoorY = 0;
        exitDoorX = ofRandom(0 + doorSize, ofGetWidth() - doorSize);
        exitDoorSide = 'U'; //This gets the right side of the exit
        exitDoorRotate = 0;
    }
    else if(side == 1)
    {
        exitDoorY = ofGetHeight();
        exitDoorX = ofRandom(0 + doorSize, ofGetWidth() - doorSize);
        exitDoorSide = 'D';
        exitDoorRotate = 180;
    }
    else if(side == 2)
    {
        exitDoorY = ofRandom(0 + doorSize, ofGetHeight() - doorSize);
        exitDoorX = 0;
        exitDoorSide = 'L';
        exitDoorRotate = -90;
    }
    else if(side == 3)
    {
        exitDoorY = ofRandom(0 + doorSize, ofGetHeight() - doorSize);
        exitDoorX = ofGetWidth();
        exitDoorSide = 'R';
        exitDoorRotate = 90;
    }
   
    //The way the player came in
    if(oldSide == 0)
    {
        entryDoorY = ofGetHeight();
        entryDoorX = ofRandom(0 + doorSize, ofGetWidth() - doorSize);
        entryDoorSide = 'D';
        entryDoorRotate = 180;
    }
    else if(oldSide == 1)
    {
        entryDoorY = 0;
        entryDoorX = ofRandom(0 + doorSize, ofGetWidth() - doorSize);
        entryDoorSide = 'U'; //This gets the right side of the exit
        entryDoorRotate = 0;

    }
    else if(oldSide == 2)
    {
        entryDoorY = ofRandom(0 + doorSize + roomSizeY, ofGetHeight() - doorSize - roomSizeY);//Roomsize is there to make sure door fits in the hallways
        entryDoorX = ofGetWidth();
        entryDoorSide = 'R';
        entryDoorRotate = 90;
    }
    else if(oldSide == 3)
    {
        entryDoorY = ofRandom(0 + doorSize + roomSizeY, ofGetHeight() - doorSize - roomSizeY);
        entryDoorX = 0;
        entryDoorSide = 'L';
        entryDoorRotate = -90;
    }
    else if(oldSide == 4)
    {
        entryDoorY = -500;
        entryDoorX = -500;
        entryDoorSide = 'O';//Make sure they are not the same

    }

    if(entryDoorSide == exitDoorSide) //This makes sure the two doors arent on the same side
    {
        if(exitDoorSide == 'R')
        {
            exitDoorY = ofRandom(0 + doorSize + roomSizeY, ofGetHeight() - doorSize - roomSizeY);
            exitDoorX = 0;
            exitDoorSide = 'L';
            side = 2;
        }
        else
        {
            exitDoorY = ofRandom(0 + doorSize + roomSizeY, ofGetHeight() - doorSize - roomSizeY);
            exitDoorX = ofGetWidth();
            exitDoorSide = 'R';
            side = 3;
        }
    }
}

int levelArea::checkExitBound(int pX, int pY, int playSizeX, int playSizeY)
{
    int doorExitCount = 0;
    //This allows the player to enter the door entry space
    if(pX + playSizeX/2 >= exitDoorX - doorSize/2)
    {
        doorExitCount ++;
    }
    if(pX - playSizeX/2 <= exitDoorX + doorSize/2)
    {
        doorExitCount ++;
    }
    if(pY - playSizeY/2 >= exitDoorY - doorSize/2) //IF YOU WANT FOUR WALLS OF BLOCK CHANGE TO MINUS
    {
        doorExitCount ++;
    }
    if(pY - playSizeY/2 <= exitDoorY + doorSize/2)
    {
        doorExitCount ++;
    }
    return doorExitCount;
}

int levelArea::checkEntryBound(int pX, int pY, int playSizeX, int playSizeY)
{
    int doorEntryCount = 0;
    //This allows the player to enter the door exit space
    if(pX + playSizeX/2 >= entryDoorX - doorSize/2)
    {
        doorEntryCount ++;
    }
    if(pX - playSizeX/2 <= entryDoorX + doorSize/2)
    {
        doorEntryCount ++;
    }
    if(pY - playSizeY/2 >= entryDoorY - doorSize/2) //IF YOU WANT FOUR WALLS OF BLOCK CHANGE TO MINUS
    {
        doorEntryCount ++;
    }
    if(pY - playSizeY/2 <= entryDoorY + doorSize/2)
    {
        doorEntryCount ++;
    }
    return doorEntryCount;
}

void levelArea::indicator(int pX, int pY)
{
    indX = preIndX[cStage];
    indY = preIndY[cStage];
    if(blink >= 255)
    {
        blinkAmount = -5 ;
    }
    else if(blink <= 0)
    {
        blinkAmount = 5;
    }
    if(pX >= indX - 10 && pX <= indX + 10
       && pY >= indY - 10 && pY <= indY + 10)
    {
        finalSpeech = true;
    }
    blink = blink + blinkAmount;
    ofSetColor(255, 250, 205, blink);
    ofCircle(indX, indY, 9);
}

void levelArea::update(int pX, int pY, int playSizeX, int playSizeY){
    for(int i = 0; i < nCharacters; i++)
    {
    character[i]->update(pX, pY, playSizeX, playSizeY, gameObjects, character);
    }
    if(inRoom == "Hall")
    {
        roomSizeY = 200;//Makes sure the objects are only trying to fit within the right hall space
    }
    else
    {
        roomSizeY = 0;
    }
}

void levelArea::draw(int pX, int pY){
    // values for R, G, B

    ofSetColor(255,255,255);
    if(inRoom == "Hall")
    {
        backgroundHallImage.draw(0, roomSizeY+20);
    }
    else
    {
    backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    if(stage[cStage] == inRoom)
    {
        indicator(pX, pY);
    }
    ofEnableAlphaBlending();
    //ofSetColor(100, 200, 200);
    ofSetColor(255, 255, 255);
    
	ofPushMatrix();
    ofTranslate(exitDoorX ,exitDoorY , 0);
    ofRotateZ(exitDoorRotate);
    doorImage.draw(-doorSize/2, -doorSize/2, doorSize, doorSize);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(entryDoorX, entryDoorY, 0);//move pivot to centre
    ofRotateZ(entryDoorRotate);//rotate from centre
    ofSetColor(255, 0, 0);
    doorImage.draw(-doorSize/2, -doorSize/2, doorSize, doorSize);
    ofPopMatrix();
    
    //ofSetColor(255, 20, 20);
    for(int i = 0; i < nGameObjects; i++)
    {
        gameObjects[i]->draw();
    }
    for(int i = 0; i < nCharacters; i++)
    {
    character[i]->draw();
    }

    ofSetColor(255,255,255);
    string LevelInfo = "Level " + ofToString(whatLevel)+ "\n";
    LevelInfo += "Room " + inRoom + "\n";
    LevelInfo += "Next Room " + nextRoom + "\n";
    LevelInfo += "Stage " + stage[cStage] + "\n";
    LevelInfo += "entry " + ofToString(exitDoorX) + " " + ofToString(exitDoorY);
//    ofDrawBitmapString(LevelInfo, 900, 15);
    ofDisableAlphaBlending();

}