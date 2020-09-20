//
//  realPeople.cpp
//  The_Product
//
//  Created by Graduate on 31/05/14.
//
//

#include "realPeople.h"

//MATT WHEN YOU MAKE THE UPDATES MAKES SURE ANY CHARACTERS WHO COULD NOT GO ON SCREEN ARE NOT UPDATED

//To do
//Make the functions have variables that can be easy changed
//one would be the distance from the player makes them move out of the way
//Another is to make sure the walls are considered for them moving
//The rotation of the ceo people can be changed
void realPeople::update(int pX, int pY, int playSizeX, int playSizeY, officeObjects** gameObjects, realPeople** characters)
{
    if(safe == true)//Stops unwelcomed offboard pieces
    {
        //BOARD STAGE STUFF
    if(charInRoom == "Customer" && stage[cStage] == "Board")
    {
        if(bTimerReached)
        {
        followPlayer(pX, pY, playSizeX, playSizeY);
        }
        else //Should make sure it is only timed at the right time
        {
            timerDraw();
        }
    }
        if((charInRoom == "Design" && stage[cStage] == "Board") || (charInRoom == "Marketing" && stage[cStage] == "Board"))
    {
        backAwayFromPlayer(pX, pY, playSizeX, playSizeY);
    }
    if(charInRoom == "Board" && stage[cStage] == "Board")
    {
        if(bTimerReached)
        {
            stareAtPlayer(pX, pY, playSizeX, playSizeY);
        }
        timerDraw();
        
    }
        //DESIGN STAGE STUFF
        if(charInRoom == "Customer" && stage[cStage] == "Design")
        {
            if(charWhichOne >= 3)//Go tell the designer off!!!
            {
            backAwayFromPlayer(pX, pY, playSizeX, playSizeY);
            }
        }
        //DESIGN STAGE STUFF
        if(charInRoom == "Design" && stage[cStage] == "Design")
        {
            if(bTimerReached)
            {
            followPlayer(pX, pY, playSizeX, playSizeY);
            }
            else //Should make sure it is only timed at the right time
            {
                timerDraw();
            }
        }
    //DESIGN STAGE STUFF
    if(charInRoom == "Board" && stage[cStage] == "Design")
    {
        if(bTimerReached)
        {
            if(charWhichOne == 0)//Go tell the designer off!!!
            {
                followPlayer(pX, pY, playSizeX, playSizeY);
            }
            else
            {
                stareAtPlayer(pX, pY, playSizeX, playSizeY); 
            }
        }
        if(sayHello.empty() == true)//Should make sure it is only timed at the right time
        {
            timerDraw();
        }
    }
    }
    objectDetection(gameObjects, characters);//Makes sure the object doesn't go through other things

}

void realPeople::changeText(string _findInfo)
{
    findInfo = _findInfo;
}

void realPeople::followPlayer(int pX, int pY, int playSizeX, int playSizeY)
{
    
    if(objectX < pX - playSizeX - 20)
    {
        objectX += charSpeedX;
    }
    else if(objectX > pX + playSizeX + 20)
    {
        objectX -= charSpeedX;
    }
    
    if(objectY < pY - playSizeY - 20)
    {
        objectY += charSpeedY;
    }
    else if(objectY > pY + playSizeY + 20)
    {
        objectY -= charSpeedY;
    }
    if(pX + playSizeX/2 +22 >= objectX - objectWidth/2
       && pX - playSizeX/2 -22 <= objectX + objectWidth/2
       && pY + playSizeY/2 +22 >= objectY - objectHeight/2
       && pY - playSizeY/2 -22 <= objectY + objectHeight/2)//maketext say hello!
    {
        sayHello = findInfo;
    }
}
void realPeople::backAwayFromPlayer(int pX, int pY, int playSizeX, int playSizeY)
{
    if(objectX > pX - playSizeX - 20 && objectX < pX
       && objectY > pY - playSizeY/2 - 20 && objectY < pY + playSizeY/2 + 20
       )
    {
        objectX -= charSpeedX;
    }
    else if(objectX < pX + playSizeX + 20 && objectX > pX
        && objectY > pY - playSizeY/2 - 20 && objectY < pY + playSizeY/2 + 20)
    {
        objectX += charSpeedX;
    }
    
    if(objectY > pY - playSizeY - 20 && objectY < pY
        && objectX > pX - playSizeX/2  - 20 && objectX < pX + playSizeX/2 + 20)
    {
        objectY -= charSpeedY;
    }
    else if(objectY < pY + playSizeY + 20 && objectY > pY
        && objectX > pX - playSizeX/2 -20 && objectX < pX + playSizeX/2 + 20)
    {
        objectY += charSpeedY;
    }
}

void realPeople::stareAtPlayer(int pX, int pY, int playSizeX, int playSizeY)
{
        //FIX THIS
    ofDrawBitmapString("mouse angle: " + ofToString(ofRadToDeg(atan2(pX,pY)), 3),30,30);
    ofVec2f v1(objectX, objectY);
    ofVec2f v2(pX, pY);
    float angle = atan2(v1.y - v2.y, v1.x - v2.x) ;
    angle = ofRadToDeg(angle) + 90;
   
    //Ask Jenna
    if(objectRotate >= 270)
    {
        objectRotate -= 359;
    }
    if(objectRotate <= -90)
    {
        objectRotate += 359;
    }
    if(objectRotate - angle < 180)
    {
        if(objectRotate >= angle )
            {
                objectRotate -= 2;
            }
    }
    else
    {
        objectRotate += 2;
    }
    if(angle - objectRotate  < 180)
    {
            if(objectRotate <= angle)
            {
                objectRotate += 2;
            }
    }
    else
    {
        objectRotate -= 2;
    }
    
}
void realPeople::objectDetection(officeObjects** gameObjects, realPeople** characters)
{
    for(int i = 0; i < whichOne; i ++)//This does seem like overkill
    {
    if(objectX + objectWidth/2 + charSpeedX*2>= gameObjects[i]->objectX - gameObjects[i]->objectWidth/2
       && objectX <= gameObjects[i]->objectX
       && objectY + objectHeight/2 >= gameObjects[i]->objectY - gameObjects[i]->objectHeight/2
       && objectY - objectHeight/2 <= gameObjects[i]->objectY + gameObjects[i]->objectHeight/2
       ) //This stops the player from getting outside the space
    {
        objectX -= charSpeedX;
    }
    if(objectX >= gameObjects[i]->objectX
       && objectX - objectWidth/2 - charSpeedX*2<= gameObjects[i]->objectX + gameObjects[i]->objectWidth/2
       && objectY + objectHeight/2 >= gameObjects[i]->objectY - gameObjects[i]->objectHeight/2
       && objectY - objectHeight/2 <= gameObjects[i]->objectY + gameObjects[i]->objectHeight/2
       ) //This stops the player from getting outside the space
    {
        objectX += charSpeedX;
    }
    
    if(objectY + objectHeight/2 + charSpeedY*2>= gameObjects[i]->objectY - gameObjects[i]->objectHeight/2
       && objectY  <= gameObjects[i]->objectY
       && objectX + objectWidth/2 >= gameObjects[i]->objectX - gameObjects[i]->objectWidth/2
       && objectX - objectWidth/2 <= gameObjects[i]->objectX + gameObjects[i]->objectWidth/2
       ) //This stops the player from getting outside the space
    {
        objectY -= charSpeedY;
    }
    if(objectY >= gameObjects[i]->objectY
       && objectY - objectHeight/2 - charSpeedY*2<= gameObjects[i]->objectY + gameObjects[i]->objectHeight/2
       && objectX + objectWidth/2 >= gameObjects[i]->objectX - gameObjects[i]->objectWidth/2
       && objectX - objectWidth/2 <= gameObjects[i]->objectX + gameObjects[i]->objectWidth/2
       ) //This stops the player from getting outside the space
    {
        objectY += charSpeedY;
    }
    }
    for(int i = 0; i < maxChar; i ++)//This does seem like overkill
    {
        //cout << "I " << i << endl;
        if((objectX + objectWidth/2 + charSpeedX*2>= characters[i]->objectX - characters[i]->objectWidth/2
           && objectX <= characters[i]->objectX
           && objectY + objectHeight/2 >= characters[i]->objectY - characters[i]->objectHeight/2
           && objectY - objectHeight/2 <= characters[i]->objectY + characters[i]->objectHeight/2)
           || objectX + objectWidth/2 > ofGetWidth() - 50) //This stops the player from getting outside the space
        {
            objectX -= charSpeedX;
        }
        if((objectX >= characters[i]->objectX
           && objectX - objectWidth/2 - charSpeedX*2<= characters[i]->objectX + characters[i]->objectWidth/2
           && objectY + objectHeight/2 >= characters[i]->objectY - characters[i]->objectHeight/2
           && objectY - objectHeight/2 <= characters[i]->objectY + characters[i]->objectHeight/2)
           || objectX - objectWidth/2 < 50) //This stops the player from getting outside the space
        {
            objectX += charSpeedX;
        }
        
        if((objectY + objectHeight/2 + charSpeedY*2>= characters[i]->objectY - characters[i]->objectHeight/2
           && objectY  <= characters[i]->objectY
           && objectX + objectWidth/2 >= characters[i]->objectX - characters[i]->objectWidth/2
           && objectX - objectWidth/2 <= characters[i]->objectX + characters[i]->objectWidth/2)
           || objectY + objectHeight/2 > ofGetHeight() - 50) //This stops the player from getting outside the space
        {
            objectY -= charSpeedY;
        }
        if((objectY >= characters[i]->objectY
           && objectY - objectHeight/2 - charSpeedY*2<= characters[i]->objectY + characters[i]->objectHeight/2
           && objectX + objectWidth/2 >= characters[i]->objectX - characters[i]->objectWidth/2
           && objectX - objectWidth/2 <= characters[i]->objectX + characters[i]->objectWidth/2)
           || objectY - objectHeight/2 < 50) //This stops the player from getting outside the space
        {
            objectY += charSpeedY;
        }
    }
   // objectX += charSpeedX;
   // objectY += charSpeedY;
}

//If the player is out of the playing space then they go to the next level, if they are
void realPeople::timerDraw()
{
    endTime = 1000; // in milliseconds
    //Timer
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    if(timer >= endTime && !bTimerReached) {
         bTimerReached = true;
    }
}