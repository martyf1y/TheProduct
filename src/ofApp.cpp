#include "ofApp.h"
#include "global.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    cStage = 0;
    stage.push_back("Board");
    stage.push_back("Design");
    stage.push_back("Marketing");
    stage.push_back("Customer");
    playerSpeed[0] = 2;
    playerSpeed[1] = 5;
    playerSpeed[2] = 4;
    playerSpeed[3] = 7;
    //X indicator
    preIndX[0] = 370;//YOU WILL NEED TO SET THESE
    preIndX[1] = 370;
    preIndX[2] = 370;
    preIndX[3] = 370;
    //Y
    preIndY[0] = 140;
    preIndY[1] = 140;
    preIndY[2] = 140;
    preIndY[3] = 140;

    restart();
  
}
void ofApp::restart()
{
    posX = 30;
    posY = 30;
    levelNum = 0;
    totalLevel = 1; //Start at level 1
    playerDirection = "rlud";
    playerImage.loadImage("images/Stage" + stage[cStage] + "/Player/p1" + ".png");
    playSizeX = playerImage.width;
    playSizeY = playerImage.height;
    thisRoom.clear();
    for(int i = 0; i < stage.size(); i++)//This adds in the rooms but in a random order with main level last
    {
        if(stage[cStage] != stage[i])
        {
            thisRoom.push_back(stage[i]);
        }
    }
    ofRandomize(thisRoom);
    thisRoom.insert(thisRoom.end(), stage[cStage]);
    thisRoom.insert(thisRoom.begin() + ofRandom(2,3), "Hall"); //CHANGE THIS ARRRRRRGH
    
    myLevel = new levelArea*[5]; // an array of pointers for the objects
    myLevel[0] = new levelArea(4, totalLevel, thisRoom[0], thisRoom[1]);
    textBox = new textInput("empty");
    OnlyCreateOnce = false;
    wait = false;
    whatIsThis = false;
    closeToObject = false;
}

//--------------------------------------------------------------
void ofApp::update(){

    playerUpdate();
    
    if((closeToObject && whatIsThis) || wait)
    {
    textBox->update(posY);//This will be useful for thwe interactive parts
	}
    //Exit doors
    int exitDoorLeft = myLevel[levelNum]->exitDoorX - myLevel[levelNum]->doorSize/2;
    int exitDoorRight = myLevel[levelNum]->exitDoorX + myLevel[levelNum]->doorSize/2;
    int exitDoorUp = myLevel[levelNum]->exitDoorY - myLevel[levelNum]->doorSize/2;
    int exitDoorDown = myLevel[levelNum]->exitDoorY + myLevel[levelNum]->doorSize/2;
    //Entry Doors
    int entryDoorLeft = myLevel[levelNum]->entryDoorX - myLevel[levelNum]->doorSize/2;
    int entryDoorRight = myLevel[levelNum]->entryDoorX + myLevel[levelNum]->doorSize/2;
    int entryDoorUp = myLevel[levelNum]->entryDoorY - myLevel[levelNum]->doorSize/2;
    int entryDoorDown = myLevel[levelNum]->entryDoorY + myLevel[levelNum]->doorSize/2;
    //These allow the player to enter the exit and entry areas
    myLevel[levelNum]->update(posX, posY, playSizeX, playSizeY);//Very important update
    doorExitCount = myLevel[levelNum]->checkExitBound(posX, posY, playSizeX, playSizeY);
    doorEntryCount = myLevel[levelNum]->checkEntryBound(posX, posY, playSizeX, playSizeY);
    
    for(int i = 0; i < playerDirection.length(); i++)
    {
        //Checks to see if the player is in the right space for leaving the level
        if(posX >= exitDoorLeft
           && posX <= exitDoorRight
           && posY >= exitDoorUp
           && posY <= exitDoorDown
           && myLevel[levelNum]->exitDoorSide == playerDirection[i])
        {
            levelNum ++;
        if(levelNum > totalLevel - 1)//LevelNum is always one behind
            {
                changeNewLevel();
            }
            posX = myLevel[levelNum]->entryDoorX; //Changes player position to the right door
            posY = myLevel[levelNum]->entryDoorY;
        }
        if(posX >= entryDoorLeft
           && posX <= entryDoorRight
           && posY >= entryDoorUp
           && posY <= entryDoorDown
           && myLevel[levelNum]->entryDoorSide == playerDirection[i])
        {
            levelNum --;
            posX = myLevel[levelNum]->exitDoorX; //Changes player position to the right door
            posY = myLevel[levelNum]->exitDoorY;
        }
    }

    for(int i = 0; i < myLevel[levelNum]->nGameObjects; i ++)//This does seem like overkill
    {
       // int gameObjectLeft = myLevel[levelNum]->gameObjects[i]->objectX - myLevel[levelNum]->gameObjects[i]->objectWidth/2;
       // int gameObjectRight = myLevel[levelNum]->gameObjects[i]->objectX + myLevel[levelNum]->gameObjects[i]->objectWidth/2;
       // int gameObjectUp = myLevel[levelNum]->gameObjects[i]->objectY - myLevel[levelNum]->gameObjects[i]->objectHeight/2;
       // int gameObjectDown = myLevel[levelNum]->gameObjects[i]->objectY + myLevel[levelNum]->gameObjects[i]->objectHeight/2;
        
        //This checks to see if the player is outside the objects space
        posX = myLevel[levelNum]->gameObjects[i]->checkBoundX(posX, posY, playSizeX, playSizeY, playerSpeed[cStage], moveRight, moveLeft);
        posY = myLevel[levelNum]->gameObjects[i]->checkBoundY(posX, posY, playSizeX, playSizeY, playerSpeed[cStage], moveUp, moveDown);
        
         //This stops the player from getting outside the space
        if(myLevel[levelNum]->gameObjects[i]->createText(posX, posY, playSizeX, playSizeY, playerSpeed[cStage])&& !wait)
        {
            if(!OnlyCreateOnce)
            {
                textBox = new textInput(myLevel[levelNum]->gameObjects[i]->findInfo );
                OnlyCreateOnce = true;//This is to stop a loop of creating the text
            }
            closeToObject = true;
        }
        //This checks to make sure that object is the right one being talked about
        else if (textBox->textLocation == myLevel[levelNum]->gameObjects[i]->findInfo && !wait)
        {
            //textBox->typedLine.clear();//We can see when something happens
            textBox = new textInput("empty");
            closeToObject = false;
            whatIsThis = false;
            OnlyCreateOnce = false;
            //cout << "does this work" << endl;
        }
    }
    
    for(int i = 0; i < myLevel[levelNum]->nCharacters; i ++)//This does seem like overkill
    {
        //This checks to see if the player is outside the objects space
          posX = myLevel[levelNum]->character[i]->checkBoundX(posX, posY, playSizeX, playSizeY, playerSpeed[cStage], moveRight, moveLeft);
          posY = myLevel[levelNum]->character[i]->checkBoundY(posX, posY, playSizeX, playSizeY, playerSpeed[cStage], moveUp, moveDown);
        //This stops the player from getting outside the space
        if(myLevel[levelNum]->character[i]->createText(posX, posY, playSizeX, playSizeY, playerSpeed[cStage]) && !wait)
        {
            if(!OnlyCreateOnce)
            {
                textBox = new textInput(myLevel[levelNum]->character[i]->findInfo);
                OnlyCreateOnce = true;//This is to stop a loop of creating the text
            }
            closeToObject = true;
        }
        //This checks to make sure that object is the right one being talked about
        else if (textBox->textLocation == myLevel[levelNum]->character[i]->findInfo && !wait)
        {
            //textBox->typedLine.clear();//We can see when something happens
            textBox = new textInput("empty");
            closeToObject = false;
            whatIsThis = false;
            OnlyCreateOnce = false;
           // cout << "does this work" << endl;
        }
    }
    if(sayHello.empty() != true)//This forces the player to interact
    {
        if(!OnlyCreateOnce)
        {
            wait = true;
            textBox = new textInput(sayHello);
            OnlyCreateOnce = true;//This is to stop a loop of creating the text
        }
        for(int i = 0; i < myLevel[levelNum]->nCharacters; i ++)//This does seem like overkill
        {
        myLevel[levelNum]->character[i]->bTimerReached = false;
        myLevel[levelNum]->character[i]->startTime = ofGetElapsedTimeMillis();
        }
        closeToObject = true;
    }

    if(textBox->descSizeY == 4)//This is for Int3ract1ve
    {
        wait = true;
    }
    if(thisRoom[levelNum] == stage[cStage] && finalSpeech && !wait)//This is the end of the all stages, boss makes speech then chooses something
    {
        wait = true;
        posX = myLevel[levelNum]->indX;
        posY = myLevel[levelNum]->indY;
          //  cout << "texts/Stage" + stage + "/" + thisRoom[levelNum] + "/decider.txt" << endl;
        textBox = new textInput(thisRoom[levelNum] + "/decider");
        OnlyCreateOnce = true;//This is to stop a loop of creating the text
    }
    if(wait) //Makes sure the person stops moving
    {
        moveRight = false;
        playerDirection[0] = 'r';
        moveLeft = false;
        playerDirection[1] = 'l';
        moveUp = false;
        playerDirection[2] = 'u';
        moveDown = false;
        playerDirection[3] = 'd';
    }
    if(bNextStage)
    {
        if(cStage >= 3)
        {
            stageUD = -1;
        }
        else if(cStage <= 0)
        {
            stageUD = 1;
        }
        cStage += stageUD;//Next stop
        restart(); //Onto the next stage!
        bNextStage = false;
        cout << "Made it" << endl;
    }
}

void ofApp::changeNewLevel()
{
    //Create new level object
    totalLevel ++;
    string nextRoom;
    if(levelNum+1 == 5)
    {
    nextRoom = "NONE";
    }
    else
    {
        nextRoom = thisRoom[levelNum+1];
    }
    myLevel[levelNum] = new levelArea(myLevel[levelNum - 1]->side, totalLevel, thisRoom[levelNum], nextRoom);
    if(thisRoom[levelNum] == stage[cStage])//This is the beginning to the board stuff
    {
        wait = true;
        if(!OnlyCreateOnce)
        {
           // cout << "texts/Stage" + stage + "/" + thisRoom[levelNum] + "/character5.txt" << endl;
            textBox = new textInput(thisRoom[levelNum] + "/enterRoom");
            OnlyCreateOnce = true;//This is to stop a loop of creating the text
        }
    }
}

void ofApp::playerUpdate()
{
            if(moveRight && moveLeft)
            {
                // Suck it!! Do not move
            }
            else if (moveRight)
            {
                if(posX + playSizeX/2 < ofGetWidth())
                {
                    posX += playerSpeed[cStage];
                }
            }
            else if (moveLeft)
            {
                if(posX - playSizeX/2 > 0)
                {
                    posX -= playerSpeed[cStage];
                }
            }
            
            if(moveUp && moveDown)
            {
                // Suck it!! Do not move
            }
            else if (moveUp)
            {
                if(posY - playSizeY/2 > 0 + roomSizeY)
                {
                    posY -= playerSpeed[cStage];
                }
            }
            else if (moveDown)
            {
                if(posY + playSizeY/2 < ofGetHeight() - roomSizeY)
                {
                    posY += playerSpeed[cStage];
                }
            }
            //This stops the player from getting outside the space
            if(posX + playSizeX/2 > ofGetWidth()-21 && doorExitCount<4 && doorEntryCount<4) //20 is for the walls
            {
                posX -= playerSpeed[cStage];
            }
            if(posX - playSizeX/2 < 21 && doorExitCount<4 && doorEntryCount<4)
            {
                posX += playerSpeed[cStage];
            }
            if(posY - playSizeY/2 < 21 && doorExitCount<4 && doorEntryCount<4)
            {
                posY += playerSpeed[cStage];
            }
            if(posY + playSizeY/2 > ofGetHeight()+1 && doorExitCount<4 && doorEntryCount<4)
            {
                posY -= playerSpeed[cStage];
            }
        }

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    myLevel[levelNum]->draw(posX, posY);
       ofSetColor(255, 255, 255);
    string calc = "Am I in distance? " + ofToString(closeToObject) + "\n";
    calc += "Have I located text? " + ofToString(OnlyCreateOnce) + "\n";
    calc += "Am I able to interact? " + ofToString(whatIsThis) + "\n";
   // ofDrawBitmapString(calc, 20, 20);
    ofDisableAlphaBlending();
    
    ofEnableAlphaBlending();
    playerImage.draw(posX - playSizeX/2, posY - playSizeY/2, playSizeX, playSizeY);

    ofSetColor(posX, posY, posX, 20);
    ofCircle(mouseX, mouseY,50);

    ofDisableAlphaBlending();
    //cout << "wait " << wait << endl;
    //cout << "whatIsThis " << whatIsThis << endl;
    if((closeToObject && whatIsThis) || wait)
    {
       // cout << "GGGG " << ofGetElapsedTimef() << endl;
        textBox->draw();
	}

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!wait)
    {
    if(key == OF_KEY_RIGHT)
    {
        moveRight = true;
        playerDirection[0] = 'R';
    }
    if (key == OF_KEY_LEFT)
    {
        moveLeft = true;
        playerDirection[1] = 'L';
    }
    if(key == OF_KEY_UP)
    {
        moveUp = true;
        playerDirection[2] = 'U';
    }
    if (key == OF_KEY_DOWN)
    {
        moveDown = true;
        playerDirection[3] = 'D';
    }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_RIGHT)
    {
        moveRight = false;
        playerDirection[0] = 'r';
    }
    if (key == OF_KEY_LEFT)
    {
        moveLeft = false;
        playerDirection[1] = 'l';
    }
    if(key == OF_KEY_UP)
    {
        moveUp = false;
        playerDirection[2] = 'u';
    }
    if (key == OF_KEY_DOWN)
    {
        moveDown = false;
        playerDirection[3] = 'd';
    }
    textBox->keyReleased(key);

    if ((key == ' ' && closeToObject) || (key == ' ' && wait))
    {
        if(textBox->repeat) //This confirms the description is a repeat and that we can delete it
        {
            textBox = new textInput("empty");
            closeToObject = false;
            whatIsThis = false;
            OnlyCreateOnce = false;
            wait = false;
            finalSpeech = false;
            sayHello.clear();
          //  cout << "IT DOES" << endl;
        }
        else
        {
            whatIsThis = true;
                        }
    }
   if(key == 'q')
   {
       playerImage.loadImage("images/Stage" + stage[cStage] + "/Player/bossDown" + ".png");

   }
    if(key == 'w')
    {
        playerImage.loadImage("images/Stage" + stage[cStage] + "/Player/p1" + ".png");
    }
   
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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