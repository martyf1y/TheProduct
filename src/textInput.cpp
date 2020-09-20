#include "textInput.h"

//--------------------------------------------------------------
textInput::textInput(string _textLocation)
{
    
    nextLetterTime = ofGetElapsedTimeMillis();
    lineCount      = 0;
    letterCount    = 0;
    textLocation = _textLocation;
    nextLine = false;
    repeat = false;
    selected = 1;
    verdana.loadFont("verdana.ttf", 15, true, true);
	verdana.setLineHeight(0.0f);
	verdana.setLetterSpacing(1.035);
    
    // move on to the next line
   // seussLines.push_back(_textDescription);
    cout << "Location " << textLocation << " yup" << endl;
   // this is our buffer to store the text data
    
    ofBuffer buffer = ofBufferFromFile("texts/Stage" + stage[cStage] + "/" + textLocation + ".txt");
    //strWidth = 0;
    
    if(buffer.size()) {
        
        // we now keep grabbing the next line
        // until we reach the end of the file
        while(buffer.isLastLine() == false) {
            
            // move on to the next line
            string line = buffer.getNextLine();
            
            // copy the line to draw later
            // make sure its not an empty line
            if(line.empty() == false) {
                seussLines.push_back(line);
            }
        }
    }
}

//--------------------------------------------------------------
void textInput::update(int pY){
    descSizeY = 16;
    // the total width on the line
    
    strWidth = (seussLines[lineCount].length()*8) + 5;
    
    if (textLocation.find("decider") != std::string::npos || seussLines[0] == "INT3RACT1VE")
    {
        descSizeY = 4;
        strWidth = ofGetWidth();
        interactive();
    }
       if(pY > ofGetHeight()/2)
    {
        y = 0;
    }
    else
    {
        y = ofGetHeight() - ofGetHeight()/descSizeY + 10;
    }
    
    cout << "buffer " << inputBuffer << endl;
    
}

void textInput::interactive()
{
    if (seussLines[lineCount].find("*") != std::string::npos)
    {
        decision = ofSplitString(seussLines[lineCount], "*");
    }
    if (seussLines[lineCount].find("?FIND?") != std::string::npos)//Sees is the line has any consequences
    {
        consequences = ofSplitString(seussLines[lineCount], "?FIND?");//locates the thing wanting to be checked
        
        //Loads the text file from the right directory
        answerbuffer = ofBufferFromFile("texts/answers.txt");//Gets the file
        vector<string> answerVec;//This will contain all answers in an array
        answerVec = ofSplitString(answerbuffer, "\n");
        ofBuffer loadConsequence = ofBufferFromFile("texts/Stage" + stage[cStage] + "/Consequences/" + ofToString(answer[ofToInt(consequences[1])]) + ".txt");//Is one for now but will need to be changed
        int here = 0;//Puts the text stuff in the right place
        if(loadConsequence.size())
        {
            // we now keep grabbing the next line
            // until we reach the end of the file
            while(loadConsequence.isLastLine() == false)
            {
                // move on to the next line
                string Anotherline = loadConsequence.getNextLine();
                // copy the line to draw later
                // make sure its not an empty line
                if(Anotherline.empty() == false)
                {
                    seussLines[lineCount] = "";//This just stops the find consequence txt from showing
                    seussLines.insert(seussLines.begin() + lineCount+1 + here, Anotherline);
                    here ++;
                }
            }
        }
    }
    if (seussLines[lineCount].find("?END?") != std::string::npos)//Sees is the line has any consequences
    {
        bNextStage = true; //Onto the next stage!!
        seussLines[lineCount] = "Next Day...";
        repeat = true;
    }
}

void textInput::textCounter(string dContent)
{
    // this is our timer for grabbing the next letter
    float time = ofGetElapsedTimeMillis() - nextLetterTime;
    
    if(time > 9) {
        // increment the letter count until
        // we reach the end of the line
        if(letterCount < (int)dContent.size()) {
            // move on to the next letter
            letterCount ++;
            
            // store time for next letter type
            nextLetterTime = ofGetElapsedTimeMillis();
            nextLine = false;
        }
        else {
            // wait just a flash then move on
            // to the next line...
            if(time > 300 && nextLine) {
                
                nextLetterTime = ofGetElapsedTimeMillis();
                letterCount = 0;
                lineCount ++;
                lineCount %= seussLines.size();
                //   cout << "lineCount " << lineCount << endl;
            }
            if((lineCount+1) % seussLines.size() == 0)
            {
                // cout << "BAM" << endl;
                repeat = true;
            }
        }
    }
}

//--------------------------------------------------------------
void textInput::draw() {
    // x and y for the drawing
    int x = 0;
    // draw the line
    ofSetColor(0);
    cout << "strWidth " << strWidth << endl;
    cout << "descSizeY " << descSizeY << endl;
    if(strWidth == 0)//Not the best solution
    {
        strWidth = ofGetWidth();
    }
    if(descSizeY == 0)//No it isn't
    {
        descSizeY = 4;
    }

    ofRect(x, y, strWidth*2, ofGetHeight()/descSizeY);
    //strWidth*2
    ofSetColor(255);
    
    if(decision.empty() == true)
    {
    // we are slowy grabbing part of the line
    typedLine = seussLines[lineCount].substr(0, letterCount);
    
    // ofDrawBitmapString(typedLine, x+4, y+11);
    verdana.drawString(typedLine, x+10, y+25);
    textCounter(seussLines[lineCount]);
    }
    else
    {
        int row = 0;
        int stringPos [decision.size()];//This states where the string should be
        stringPos [0] = x+10; //The first non choice string
        verdana.drawString(decision[0].substr(0, letterCount), stringPos[0], y+25);//Just the non-choice part
        textCounter(decision[0]);
        cout << "decision.size() " << decision.size() << endl;
        cout << "selected " << selected << endl;
        for(int i = 1; i < decision.size(); i ++)
        {
            stringPos[i] = stringPos[i-1] + decision[i-1].length()*13 + (500/decision.size());
        // we are slowy grabbing part of the line
        typedLine = decision[i].substr(0, letterCount);
        ofSetColor(255);
        // ofDrawBitmapString(typedLine, x+4, y+11);
            if((decision[i].length()*13) + stringPos[i] > ofGetWidth())//This checks to see if the choice is too far right
            {
                row ++;
                stringPos[i] = stringPos[1];
            }
            //This makes sure it is selected
            typedLine = " " + typedLine;
            if(i == selected)
            {
                typedLine = ">" + typedLine.substr(1, typedLine.size());//This replaces the space with the >
            }
        verdana.drawString(typedLine, stringPos[i], y+25+(50*row));
        textCounter(decision[i]);
    }
    
}
}

//--------------------------------------------------------------
void textInput::keyPressed(int key){
    
}

//--------------------------------------------------------------
void textInput::keyReleased(int key){
    if(key == ' ' && decision.empty())
    {
        cout << "Work" << endl;
        nextLine = true;
    }
    else if(key == ' ')
    {
        cout << "unWork" << endl;
        nextLine = true;
        lineCount ++;
        answer.push_back(decision[selected]);
        inputBuffer.append("\n" + answer[answer.size()-1]);
        decision.clear();//Stops the decision making
        // fill the buffer with something important
        bool fileWritten = ofBufferToFile("texts/answers.txt", inputBuffer);
        selected = 1;
    }
    if(key == OF_KEY_RIGHT && !decision.empty())
    {
        if(selected != decision.size()-1)
        {
        selected ++;
        }
        else
        {
        selected = 1;
        }
    }
    if(key == OF_KEY_LEFT && !decision.empty())
    {
        if(selected != 1)
        {
            selected --;
        }
        else
        {
            selected = decision.size()-1;
        }

    }
}

