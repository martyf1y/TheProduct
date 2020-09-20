#include "ofMain.h"
#include "ofEvents.h"

extern vector <string> stage;
extern int cStage;
extern bool bNextStage;
extern vector <string> answer;
extern ofBuffer inputBuffer; //This will only contain the current input


class textInput {
public:
    
    textInput(string textLocation);
    void update(int pY);
    void draw();
    void interactive();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void textCounter(string dContent);
    
    float           nextLetterTime;
    int             lineCount;
    int             letterCount;
    int             descSizeY;
    int             y;//This is the position of the textbox
    vector <string> seussLines;
    vector<string> decision;//This will be the decision array
    vector<string> consequences;//This will be the consequences array
    string textLocation;
    string typedLine;
    bool nextLine;
    bool repeat; //Stop the description from repeating
    ofTrueTypeFont	verdana;
    ofBuffer answerbuffer;// This will always contain all players answers
    int strWidth;
    int selected;
};
