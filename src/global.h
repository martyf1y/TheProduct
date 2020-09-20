//
//  global.h
//  The_Product
//
//  Created by Marty on 20/10/13.
//
//

#ifndef ExperienceCanvas_global_h
#define ExperienceCanvas_global_h

vector <string> stage; //Dancers worthness
vector <string> answer;//This is all the answers the person has answered with.
int cStage;
int roomSizeY; //This will help make the hallway
int preIndX [4];//These are for where the player has to go each stage
int preIndY [4];
bool finalSpeech;
bool bNextStage;
string sayHello;//Gosh i have a lot of variables, this makes the player interact with the object/character.
ofBuffer inputBuffer; //This will contain all the current inputs

#endif

//Ask Jenna about rotation error
//Truetype font not showing text characters
