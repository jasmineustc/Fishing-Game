#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"
#include "string.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include <ctype.h>

#include "submarine.h"
#include "ocean.h"
#include "fish.h"
#include "cloud.h"
#include "nameinput.h"

#define LEFT 1
#define RIGHT 2

const double PI=3.1415927;

void Rainbow(int rbx,int rby,int r,int delta)
{
    glColor3ub(255,20,147);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*r;
        double y=rby+sin(angle)*r;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(255,127,80);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*1);
        double y=rby+sin(angle)*(r-delta*1);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(255,215,0);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*2);
        double y=rby+sin(angle)*(r-delta*2);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(152,251,152);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*3);
        double y=rby+sin(angle)*(r-delta*3);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(72,209,204);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*4);
        double y=rby+sin(angle)*(r-delta*4);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(100,149,237);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*5);
        double y=rby+sin(angle)*(r-delta*5);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(147,112,219);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*6);
        double y=rby+sin(angle)*(r-delta*6);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(245,255,250);
    glBegin(GL_POLYGON);
    for(int i=90;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=rbx+cos(angle)*(r-delta*7);
        double y=rby+sin(angle)*(r-delta*7);
        glVertex2d(x,y);
    }
    glEnd();
}

class Interface{
    
protected:
    int initialTime;
    int timeLeft;
    unsigned int accumTime;
    double sunX=820, sunY=600, sunR=70;
    double lightR1=0, lightR2=0;
    double h=1.1;
    int score=0;
    
    int scoreList[5];
    char scorename[5][11]={"","","","",""};
    
    bool scoreListState=false;
    int life=3;
    bool menuState=true;
    bool gameOverMenuState=false;
    int key;
    int mouseX, mouseY;
    int colorSet[3]={0,0,0};
    int gameState=2;  //1=on; 0=over; -1=exit; 2=pause;
    bool gameOverState=false;
    
public:
    char name[11];
    Interface();
    Interface(int timeInSec);
    void finalization(void);
    int getTimeLeft(void);
    void setKey(int keyInput);
    int getScore(void);
    void setScore(int x);
    void drawScore(void);
    void add2ScoreList(void);
    void drawScoreList(void);
    int getLife(void);
    void setLife(int newLife);
    void drawHeart(double x0, double y0, double size);
    void drawLife(void);
    bool getMenuState(void);
    void setMenuState(bool s);
    void drawMenu(void);
    bool getAllMenuState(void);
    bool getGameOverMenuState(void);
    void setGameOverMenuState(bool s);
    void drawGameOverMenu(void);
    void drawTimer(int passedTimeInMilliSec);
    void drawWater(void);
    void drawRect(int x, int y, int w, int h,
                  int r, int g, int b);
    void drawLight(void);
    void drawSun(double x, double y, double r);
    int drawInterface(int passedTimeInMilliSec, int keyInput, int mX, int mY, int mouseE);
    
    int addscorename();
    
    int getGameState(void) {
        return gameState;
    }
    static int int2str(char c[], int x);
    void drawBoard(int bdx,int bdy);
    void drawcircle(int x, int y, int r, int fill);
    void drawfirst(int i, int j);
    void drawsecond(int i, int j);
    void drawthird(int i, int j);
};

Interface::Interface()
{
    score=0;
    accumTime=0;
    timeLeft=60000;
    timeLeft+=200;
    life=3;
    initialTime=timeLeft;
    for(int i=0; i<5; i++) {
        scoreList[i]=0;
    }
}

void Interface::drawBoard(int bdx,int bdy)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(100,149,237,70);
    glBegin(GL_QUADS);
    glVertex2i(bdx,bdy);
    glVertex2i(bdx+450,bdy);
    glVertex2i(bdx+450,bdy+500);
    glVertex2i(bdx,bdy+500);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=110;i<191;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=bdx+48+cos(angle)*50;
        double y=bdy+16+sin(angle)*50;
        glVertex2d(x,y);
    }
    glEnd();
    glDisable(GL_BLEND);
    
    Rainbow(bdx+48,bdy+16,45,5);
}


Interface::Interface(int timeInSec)
{
    score=0;
    accumTime=0;
    timeLeft=timeInSec*1000;
    timeLeft+=200;
    initialTime=timeLeft;
    for(int i=0; i<5; i++) {
        scoreList[i]=0;
    }
}

void Interface::finalization()
{
    timeLeft=0;
    accumTime=initialTime;
    life=3;
    score=0;
}

void Interface::setKey(int keyInput)
{
    key=keyInput;
}

int Interface::getScore()
{
    return score;
}

void Interface::setScore(int x)
{
    score=x;
    if(score<0) {
        score=0;
    }
}

void Interface::drawScore()
{
    char c[12];
    int2str(c, score);
    glColor3ub(0, 0, 0);
    glRasterPos2d(40, 49);
    YsGlDrawFontBitmap16x24("SCORE:");
    YsGlDrawFontBitmap16x24(c);
}

void Interface::add2ScoreList()
{
    if(score<scoreList[4]) {
        return;
    }
    int temp;
    char tempname[11];
    scoreList[4]=score;
    strcpy(scorename[4],name);
    
    for(int i=0; i<5; i++) {
        for(int j=i+1; j<5; j++) {
            if(scoreList[j]>scoreList[i]) {
                temp=scoreList[i];
                scoreList[i]=scoreList[j];
                scoreList[j]=temp;
                
                strcpy(tempname, scorename[i]);
                strcpy(scorename[i],scorename[j]);
                strcpy(scorename[j],tempname);
                
            }
        }
    }
}

void Interface::drawcircle(int x, int y, int r, int fill)
{
    int i;
    int n=36;
    if (fill == 1)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);
    
    for(i=0; i<n; ++i)
        glVertex2i(x+r*sin(PI*10*i/180), (y+r*cos(PI*10*i/180)));
    glEnd();
}


void Interface::drawfirst(int i, int j)
{
    glColor3ub(0xff,0xff,0x00);
    glBegin(GL_POLYGON);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glEnd();
    
    glColor3ub(0xff,0xff,0x00);
    glBegin(GL_POLYGON);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glEnd();
    
    glColor3ub(0xff,0xd7,0x00);
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glVertex2d(i,700-(j-5));
    glEnd();
    
    glColor3ub(199,224,249);
    glBegin(GL_TRIANGLES);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glEnd();
    
    glColor3ub(0xff,0xd7,0x00);
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glVertex2d(i,700-j);
    glEnd();
    
    glColor3ub(0xff,0xff,0x00);
    drawcircle(i-10,700-(j+25),6,1);
    drawcircle(i+12.5,700-(j+25),6,1);
    drawcircle(i+35,700-(j+25),6,1);
    glColor3ub(0xff,0xd7,0x00);
    drawcircle(i-10,700-(j+25),6,0);
    drawcircle(i+12.5,700-(j+25),6,0);
    drawcircle(i+35,700-(j+25),6,0);
}

void Interface::drawsecond(int i, int j)
{
    glColor3ub(0xe8,0xe8,0xe8);
    glBegin(GL_POLYGON);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glEnd();
    
    
    glColor3ub(199,224,249);
    glBegin(GL_TRIANGLES);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glEnd();
    
    glColor3ub(0xcf,0xcf,0xcf);
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glVertex2d(i,700-j);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glVertex2d(i,700-(j-5));
    glEnd();
    
    glColor3ub(0xe8,0xe8,0xe8);
    drawcircle(i-10,700-(j+25),6,1);
    drawcircle(i+12.5,700-(j+25),6,1);
    drawcircle(i+35,700-(j+25),6,1);
    glColor3ub(0xcf,0xcf,0xcf);
    drawcircle(i-10,700-(j+25),6,0);
    drawcircle(i+12.5,700-(j+25),6,0);
    drawcircle(i+35,700-(j+25),6,0);
}

void Interface::drawthird(int i, int j)
{
    glColor3ub(0xee,0xb4,0x22);
    glBegin(GL_POLYGON);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glEnd();
    
    
    glColor3ub(199,224,249);
    glBegin(GL_TRIANGLES);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glEnd();
    
    glColor3ub(0xee,0x9a,0x00);
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-j);
    glVertex2d(i-10,700-(j+25));
    glVertex2d(i+5,700-(j+10));
    glVertex2d(i+12.5,700-(j+25));
    glVertex2d(i+20,700-(j+10));
    glVertex2d(i+35,700-(j+25));
    glVertex2d(i+25,700-j);
    glVertex2d(i,700-j);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(i,700-(j-5));
    glVertex2d(i,700-(j-10));
    glVertex2d(i+25,700-(j-10));
    glVertex2d(i+25,700-(j-5));
    glVertex2d(i,700-(j-5));
    glEnd();
    
    glColor3ub(0xee,0xb4,0x22);
    drawcircle(i-10,700-(j+25),6,1);
    drawcircle(i+12.5,700-(j+25),6,1);
    drawcircle(i+35,700-(j+25),6,1);
    glColor3ub(0xee,0x9a,0x00);
    drawcircle(i-10,700-(j+25),6,0);
    drawcircle(i+12.5,700-(j+25),6,0);
    drawcircle(i+35,700-(j+25),6,0);
}

void Interface::drawScoreList()
{
    if(scoreListState==false) {
        return;
    }
    
    char c[12];
    glColor3ub(0, 0, 0);
    glRasterPos2d(440, 200);
    YsGlDrawFontBitmap20x32("RANKINGS");
    for(int j=0; j<5; j++) {
        int2str(c, scoreList[j]);
        glRasterPos2d(430, 200+80*(j+1));
        YsGlDrawFontBitmap20x32(c);
        glRasterPos2d(500, 200+80*(j+1));
        YsGlDrawFontBitmap20x32(scorename[j]);
    }
    drawfirst(360, 425);
    drawsecond(360, 350);
    drawthird(360, 270);
    
}

bool Interface::getAllMenuState()
{
    return menuState||scoreListState;
}

void Interface::drawHeart(double x0, double y0, double size)
{
    int x, y;
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    x=x0-size;
    while(x<(x0+size)){
        x=x+1;
        y=y0+4*size/5*(sqrt(1-pow((x-x0)/size, 2))+sqrt(fabs(x-x0)/size));
        glVertex2d(x, 700-y);
    }
    while(x>(x0-size)){
        x=x-1;
        y=y0+4*size/5*(-sqrt(1-pow((x-x0)/size, 2))+sqrt(fabs(x-x0)/size));
        glVertex2d(x, 700-y);
    }
    glEnd();
}

int Interface::getLife()
{
    return life;
}

void Interface::setLife(int newLife)
{
    life=newLife;
}

void Interface::drawLife()
{
    glColor3ub(0, 0, 0);
    glRasterPos2d(40, 85);
    YsGlDrawFontBitmap16x24("LIFE:");
    if(life==3) {
        drawHeart(140, 622, 15);
        drawHeart(175, 622, 15);
        drawHeart(210, 622, 15);
    }
    else if(life==2) {
        drawHeart(140, 622, 15);
        drawHeart(175, 622, 15);
    }
    else if(life==1) {
        drawHeart(140, 622, 15);
    }
}

bool Interface::getMenuState()
{
    return menuState;
}

void Interface::setMenuState(bool s)
{
    menuState=s;
}

void Interface::drawMenu()
{
    drawBoard(280, 150);
    glColor3ub(0, 0, 0);
    // Menu Range 400-580, height 40
    if(scoreListState==true) {
        drawScoreList();
        return;
    }
    if(gameOverMenuState==false) {
        glRasterPos2d(420, 250);
        YsGlDrawFontBitmap20x32("M E N U");
        if(colorSet[0]==0) {
            glColor3ub(0, 0, 0);
        }
        else {
            glColor3ub(255, 0, 0);
        }
    }
    else {
        glRasterPos2d(400, 250);
        YsGlDrawFontBitmap20x32("GAME OVER");
        if(colorSet[0]==0) {
            glColor3ub(0, 0, 0);
        }
        else {
            glColor3ub(255, 0, 0);
        }
    }
    
    glRasterPos2d(410, 330);
    YsGlDrawFontBitmap20x32("New Game");
    if(colorSet[1]==0) {
        glColor3ub(0, 0, 0);
    }
    else {
        glColor3ub(255, 0, 0);
    }
    
    glRasterPos2d(450, 400);
    YsGlDrawFontBitmap20x32("RANK");
    if(colorSet[2]==0) {
        glColor3ub(0, 0, 0);
    }
    else {
        glColor3ub(255, 0, 0);
    }
    
    glRasterPos2d(450, 470);
    YsGlDrawFontBitmap20x32("EXIT");
}

bool Interface::getGameOverMenuState()
{
    return gameOverMenuState;
}

void Interface::setGameOverMenuState(bool s)
{
    gameOverMenuState=s;
}

void Interface::drawTimer(int passedTimeInMilliSec)
{
    if (gameState==2) {
        timeLeft=initialTime-accumTime;
    }
    else {
        accumTime+=passedTimeInMilliSec;
        timeLeft=initialTime-accumTime;
    }
    glColor3ub(0, 0, 0);
    glRasterPos2d(350, 49);
    char str[256];
    sprintf(str,"%d",timeLeft/1000);
    YsGlDrawFontBitmap16x24("Time:");
    YsGlDrawFontBitmap16x24(str);
    
    int r,g,b;
    if((double)timeLeft/initialTime>0.5){
        g=255;
        r=2*255*(1-(double)timeLeft/initialTime);
    }
    else{
        r=255;
        g=2*255*(double)timeLeft/initialTime;
    }
    
    b=0;
    drawRect(475, 50, 200*timeLeft/initialTime,25,r,g,b);
}

void Interface::drawWater()
{
    double r=30;
    glColor3ub(0, 200, 250);
    glBegin(GL_POLYGON);
    glVertex2d(0, 250);
    glVertex2d(1000, 250);
    glVertex2d(1000, 700);
    glVertex2d(0, 700);
    glEnd();
}

void Interface::drawRect(int x, int y, int w,
                         int h, int r, int g, int b)
{
    glColor3ub(r, g, b);
    glBegin(GL_QUAD_STRIP);
    glVertex2d(x, y-h);
    glVertex2d(x+w, y-h);
    glVertex2d(x, y);
    glVertex2d(x+w, y);
    glEnd();
}

void Interface::drawLight()
{
    glColor3ub(255, 200, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    glLineWidth(4.5);
    for(int i=0;i<=16;i++){
        glBegin(GL_LINES);
        glVertex2i(sunX+sunR*h*sin(22.5*i/180*PI),
                   610-sunY-sunR*h*cos(22.5*i/180*PI));
        glVertex2i(sunX+sunR*(h+0.5)*sin(22.5*i/180*PI),
                   610-sunY-sunR*(h+0.5)*cos(22.5*i/180*PI));
        glEnd();
    }
    if(h>=1.5){
        h=1.05;
    }
    else{
        h=h+0.01;
    }
}

void Interface::drawSun(double x, double y, double r)
{
    glColor3ub(255, 200, 0);
    glBegin(GL_POLYGON);
    for(int i=0; i<36; i++) {
        glVertex2i(x+r*sin(PI*10*i/180), 600-(y+r*cos(PI*10*i/180)));
    }
    glEnd();
}

int Interface::drawInterface(int passedTimeInMilliSec,int keyInput, int mX, int mY, int mouseE){
    int s;
    
    if(timeLeft<=0 || life<=0 ){
        if(gameOverState==false) {
            s=addscorename();
            add2ScoreList();
            gameOverState=true;
        }
        
        gameOverMenuState=true;
        finalization();
    }
    
    key=keyInput;
    
    switch(key)
    {
        case FSKEY_ESC:
            if(getAllMenuState()) {
                menuState=false;
                scoreListState=false;
            }
            else {
                menuState=true;
            }
            break;
            
        default:
            break;
    }
    
    if(gameOverMenuState==true) {
        menuState=true;
    }
    
    if(menuState==true) {
        gameState=2;
    }
    else {
        gameState=1;
    }
    
    
    drawTimer(passedTimeInMilliSec);
    drawLife();
    drawSun(sunX, sunY, sunR);
    drawLight();
    drawScore();

    
    if(menuState){
        if(mX>=400 && mX<=500 && mY>=260 && mY<=320) {
            colorSet[0]=1;
            colorSet[1]=0;
            colorSet[2]=0;
            if(mouseE==FSMOUSEEVENT_LBUTTONDOWN && scoreListState==false) {
                
                timeLeft=60000;
                accumTime=0;
                score=0;
                life=3;
                menuState=false;
                gameOverMenuState=false;
                gameState=1;
                gameOverState=false;
            }
        }
        else if(mX>=400 && mX<=500 && mY>=320 && mY<=380) {
            colorSet[0]=0;
            colorSet[1]=1;
            colorSet[2]=0;
            if(mouseE==FSMOUSEEVENT_LBUTTONDOWN&& scoreListState==false) {
                scoreListState=true;
            }
        }
        else if(mX>=400 && mX<=500 && mY>=420 && mY<=480) {
            colorSet[0]=0;
            colorSet[1]=0;
            colorSet[2]=1;
            if(mouseE==FSMOUSEEVENT_LBUTTONDOWN&& scoreListState==false) {
                gameState=-1;
            }
        }
        else {
            colorSet[0]=0; colorSet[1]=0; colorSet[2]=0;
        }
        
        drawMenu();
    }
    
    if(menuState||gameOverState||gameOverMenuState||scoreListState) {
        return 1;
    }
    else {
        return 0;
    }
}

int Interface::getTimeLeft()
{
    return timeLeft;
}


int Interface::int2str(char c[], int x)
{
    int y;
    int length=1;
    int digit;
    while(true){
        y=pow(10,length);
        if(x-x%y==0) {
            break;
        }
        else {
            length++;
        }
    }
    
    for(int i=0; i<length; i++) {
        if(i==0) {
            digit=x%10;
        }
        else {
            digit=(x%(int)pow(10,i+1)-x%(int)pow(10,i))/pow(10,i);
        }
        switch (digit) {
            case 0: c[length-1-i]='0'; break;
            case 1: c[length-1-i]='1'; break;
            case 2: c[length-1-i]='2'; break;
            case 3: c[length-1-i]='3'; break;
            case 4: c[length-1-i]='4'; break;
            case 5: c[length-1-i]='5'; break;
            case 6: c[length-1-i]='6'; break;
            case 7: c[length-1-i]='7'; break;
            case 8: c[length-1-i]='8'; break;
            case 9: c[length-1-i]='9'; break;
        }
    }
    c[length]=0;
    return length;
}

int Interface:: addscorename()
{
    if(score<scoreList[4]) {
        return 1;
    }
    int state=0;
    char c[12],longname[100];
    int i;
    int2str(c, score);
    
    TextInput t;
    
    state=t.Input(c);
    strcpy(longname,t.GetString());
    
    for (i=0; i<10; i++) {
        name[i]=longname[i];
    }
    name[10]='\0';
    
   // printf("string copy %s\n",name);
    
    return state;
}







class Bubble
{
public:
    double bux,buy,bur;
    void Initialize(int i);
    void DrawBubble(void);
    void BubblePara(void);
};

void Bubble::Initialize(int i)
{
    
    bux=150*(i+1);
    buy=700-+50*(rand()%5);
    bur=(700-buy)/20;
}

void Bubble::DrawBubble(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(255,255,255,70);
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=bux+cos(angle)*bur;
        double y=buy+sin(angle)*bur;
        glVertex2d(x,y);
    }
    glEnd();
    glDisable(GL_BLEND);
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=bux-(bur/3)+cos(angle)*(bur/4);
        double y=buy-(bur/3)+sin(angle)*(bur/4);
        glVertex2d(x,y);
    }
    glEnd();
}

void Bubble::BubblePara(void)
{
    buy-=10;
    if(buy<300)
    {
        buy=700;
    }
    bur=(700-buy)/20;
}

class Cloud
{
protected:
    YsRawPngDecoder png;
public:
    double x,y;
    double vx;
    int w,h;
    void Initialize(void);
    void draw(void);
    void move(void);
};

void Cloud::Initialize(void)
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_cloud),dat_cloud);
    
    if(YSOK==png.Decode(memInStream1))
    {
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    x = 0;
    y = 110;
    vx = 3;
    w = png.wid;
    h = png.hei;
}

void Cloud::draw(void)
{
    glRasterPos2d(x,y);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}

void Cloud::move(void)
{
    x += vx;
    if (x <= 0 || x >= (1000 + 1 * w))
    {
        vx = -vx;
    }
}

class GameObeject
{
public:
    double x,y;
    int w,h;
    int direction;
};

class Fish1 : public GameObeject
{
protected:
    YsRawPngDecoder png_right;
    YsRawPngDecoder png_left;
public:
    int state;
    int point;
    double vx;
    void initialize(void);
    void move(void);
    void draw(void);
    void bounce(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Fish1::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_fish1),dat_left_fish1);
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_fish1),dat_right_fish1);
    
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    x = 880;
    y = 450;
    w = png_right.wid;
    h = png_right.hei;
    vx = -8;
    point = 3;
    state = 1;
    direction = LEFT;
}

void Fish1::draw()
{
    if (direction == (RIGHT))
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
    }
    else
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
}

void Fish1::move()
{
    if (state == 1)
    {
        x += vx;
        y = 450 + 50 * sin(0.02 * x);
    }
    else
    {
        y -= 10;
    }
}

void Fish1::bounce()
{
    if (x <= 0 || x >= (1000 + 3 * w))
    {
        vx = -vx;
        if (direction == (RIGHT))
        {
            direction = LEFT;
        }
        else
        {
            direction = RIGHT;
        }
    }
}

int Fish1::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score += point;
        state = 0;
        return 1;
    }
    return 0;
}

void Fish1::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}

void Fish1::play()
{
    draw();
    move();
    bounce();
    check_init();
}

class Fish2 : public GameObeject
{
protected:
    YsRawPngDecoder png_right;
    YsRawPngDecoder png_left;
public:
    int state;
    int point;
    double vx;
    void initialize(void);
    void bounce(void);
    void move(void);
    void draw(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Fish2::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_fish2),dat_left_fish2);
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_fish2),dat_right_fish2);
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    x = 862;
    y = 520;
    w = png_right.wid;
    h = png_right.hei;
    vx = -12;
    point = 5;
    state = 1;
    direction = LEFT;
}

void Fish2::draw()
{
    if (direction == (RIGHT))
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
    }
    else
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
}

void Fish2::move()
{
    if (state == 1)
    {
        x += vx;
    }
    else
    {
        y -= 10;
    }
}

void Fish2::bounce()
{
    if (x <= 0 || x >= (1000 + 3 * w))
    {
        vx = -vx;
        if (direction == (RIGHT))
        {
            direction = LEFT;
        }
        else
        {
            direction = RIGHT;
        }
    }
}

int Fish2::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score += point;
        state = 0;
        return 1;
    }
    return 0;
}

void Fish2::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}

void Fish2::play()
{
    draw();
    move();
    bounce();
    check_init();
}

class Fish3 : public GameObeject
{
protected:
    YsRawPngDecoder png;
    YsRawPngDecoder png_right;
    YsRawPngDecoder png_left;
public:
    int state;
    int point;
    double vx;
    void initialize(void);
    void draw(void);
    void move(void);
    void bounce(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Fish3::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_fish3),dat_left_fish3);
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_fish3),dat_right_fish3);
    
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    x = 800;
    y = 540;
    w = png_right.wid;
    h = png_right.hei;
    vx = -15;
    point = 10;
    state = 1;
    direction = LEFT;
}

void Fish3::draw()
{
    if (direction == (RIGHT))
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
    }
    else
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
}

void Fish3::move()
{
    if (state == 1)
    {
        x += vx;
    }
    else
    {
        y -= 10;
    }
}

void Fish3::bounce()
{
    if (x <= 0 || x >= (1000 + 3 * w))
    {
        vx = -vx;
        if (direction == (RIGHT))
        {
            direction = LEFT;
        }
        else
        {
            direction = RIGHT;
        }
    }
}

void Fish3::play()
{
    draw();
    move();
    bounce();
    check_init();
}

int Fish3::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score += point;
        state = 0;
        return 1;
    }
    return 0;
}

void Fish3::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}


class Shrimp : public GameObeject
{
protected:
    YsRawPngDecoder png;
    YsRawPngDecoder png_right;
    YsRawPngDecoder png_left;
public:
    int state;
    int point;
    double vx,vy;
    void initialize(void);
    void move(void);
    void draw(void);
    void bounce(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Shrimp::initialize()
{
    
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_shrimp),dat_left_shrimp);
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_shrimp),dat_right_shrimp);
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
    x = 0;
    y = 450;
    w = png_right.wid;
    h = png_right.hei;
    vx = 15;
    point = 8;
    state = 1;
    direction = RIGHT;
}

void Shrimp::draw()
{
    if (direction == (RIGHT))
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
    }
    else
    {
        glRasterPos2d(x,y);
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
}

void Shrimp::move()
{
    if (state == 1)
    {
        x += vx;
    }
    else
    {
        y -= 10;
    }
}

void Shrimp::bounce()
{
    if (x <= 0 || x >= (1000 + 2 * w))
    {
        vx = -vx;
        if (direction == (RIGHT))
        {
            direction = LEFT;
        }
        else
        {
            direction = RIGHT;
        }
    }
}

int Shrimp::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score += point;
        state = 0;
        return 1;
    }
    return 0;
}

void Shrimp::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}

void Shrimp::play()
{
    draw();
    move();
    bounce();
    check_init();
}

class Star
{
protected:
    YsRawPngDecoder png;
public:
    double x,y;
    int w,h;
    double vx;
    int state;
    int point;
    void initialize(void);
    void bounce(void);
    void move(void);
    void draw(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Star::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_star),dat_star);
    
    if(YSOK==png.Decode(memInStream1))
    {
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    x = 0;
    y = 450;
    w = png.wid;
    h = png.hei;
    vx = 6;
    state = 1;
    point = 1;
}

void Star::draw()
{
    glRasterPos2d(x,y);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}

void Star::move()
{
    if (state == 1)
    {
        x += vx;
        y = 400 + 80 * sin(0.01 * x);
    }
    else
    {
        y -= 10;
    }
}

void Star::bounce()
{
    if (x <= 0 || x >= (1000 + w))
    {
        vx = -vx;
    }
}

int Star::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score += point;
        state = 0;
        return 1;
    }
    return 0;
}

void Star::check_init(void)
{
    if (state==0&&y<=(275+h))
    {
        initialize();
    }
}

void Star::play()
{
    draw();
    move();
    bounce();
    check_init();
}

class Apple
{
protected:
    YsRawPngDecoder png;
public:
    double x,y;
    int w,h;
    double vx;
    int state;
    int point;
    void initialize(void);
    void bounce(void);
    void move(void);
    void draw(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Apple::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_apple),dat_apple);
    
    if(YSOK==png.Decode(memInStream1))
    {
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    x = 0;
    w = png.wid;
    h = png.hei;
    vx = 8;
    state = 1;
    point = 2;
}

void Apple::draw()
{
    glRasterPos2d(x,y);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}

void Apple::move()
{
    if (state == 1)
    {
        x += vx;
        y = 420 + 80 * sin(0.01 * x);
    }
    else
    {
        y -= 10;
    }
}

void Apple::bounce()
{
    if (x <= 0 || x >= (1000 + w))
    {
        vx = -vx;
    }
}

int Apple::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score -= point;
        state = 0;
        return -1;
    }
    return 0;
}

void Apple::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}

void Apple::play()
{
    draw();
    move();
    bounce();
    check_init();
}

class Garbage
{
protected:
    YsRawPngDecoder png;
public:
    double x,y;
    int w,h;
    double vx;
    int state;
    int point;
    void initialize(void);
    void bounce(void);
    void move(void);
    void draw(void);
    int check(double xx, double yy, int &score);
    void check_init(void);
    void play(void);
};

void Garbage::initialize()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_garbage),dat_garbage);
    
    if(YSOK==png.Decode(memInStream1))
    {
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    x = 0;
    y = 400;
    w = png.wid;
    h = png.hei;
    vx = 5;
    state = 1;
    point = 1;
}

void Garbage::draw()
{
    glRasterPos2d(x,y);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}

void Garbage::move()
{
    if (state == 1)
    {
        x += vx;
    }
    else
    {
        y -= 10;
    }
}

void Garbage::bounce()
{
    if (x <= 0 || x >= (1000 + w))
    {
        vx = -vx;
    }
}

int Garbage::check(double xx, double yy, int &score)
{
    if (x<=xx&&xx<=(x+w)&&yy>=(y-h)&&yy<=y&&state==1)
    {
        score -= point;
        state = 0;
        return -1;
    }
    return 0;
}

void Garbage::check_init(void)
{
    if (state==0&&y<=275+h)
    {
        initialize();
    }
}

void Garbage::play()
{
    draw();
    move();
    bounce();
    check_init();
}

Fish1 fish1;
Fish2 fish2;
Fish3 fish3;
Shrimp shrimp;
Star star;
Apple apple;
Garbage garbage;
Cloud cloud;

void Drawocean(int ocean_deep)
{
    glColor3ub(151, 208, 242);
    glBegin(GL_QUADS);
    glVertex2i(0,700-ocean_deep);
    glVertex2i(1000,700-ocean_deep);
    glVertex2i(1000,700);
    glVertex2i(0,700);
    glEnd();
    
}

int check_fish(double xx, double yy, int &score, int &check_state)
{
    int returnvalue = 0;
    while (check_state)
    {
        returnvalue = fish1.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = fish2.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = fish3.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = shrimp.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = star.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = garbage.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        returnvalue = apple.check(xx,yy,score);
        if (returnvalue != 0)
        {
            check_state = 0;
            break;
        }
        break;
    }
    return returnvalue;
}

void play_fish(void)
{
    star.play();
    fish1.play();
    fish2.play();
    fish3.play();
    shrimp.play();
    apple.play();
    garbage.play();
}

////////////////////////////////////////////////////////////////////////////////

class Cat
{
public:
    int cx,cy;
    void initialize(void);
    void Status(int State);
    void DrawFace(void);
    void DrawEyes(void);
    void DrawSmile(void);
    void DrawSad(void);
    void DrawHappy(void);
    void DrawGameOver(void);
    void Position(void);
};

void Cat::initialize(void)
{
    cx=500;
    cy=200;
}
void Cat::Status(int State)
{
    if(State==0)//Wait for action.
    {
        DrawFace();
        DrawSmile();
    }
    
    if(State==1)//Fish catched.
    {
        DrawFace();
        DrawHappy();
    }
    if(State==2)//Trash found.
    {
        DrawFace();
        DrawSad();
    }
    if(State==3)//Time out or shoot by bomb.
    {
        DrawFace();
        DrawGameOver();
    }
    
}

void Cat::DrawFace(void)
{
    //Left ear.
    glColor3ub(255,255,240);//Base
    glBegin(GL_POLYGON);
    glVertex2d(cx-60,cy-75);
    glVertex2d(cx-90,cy-115);
    glVertex2d(cx-95,cy-115);
    glVertex2d(cx-85,cy-55);
    glEnd();
    glColor3ub(255,240,245);//Pink part.
    glBegin(GL_POLYGON);
    glVertex2d(cx-65,cy-75);
    glVertex2d(cx-85,cy-100);
    glVertex2d(cx-80,cy-55);
    glEnd();
    glColor3ub(255,182,193);
    glBegin(GL_LINE_STRIP);//Contour.
    glVertex2d(cx-60,cy-75);
    glVertex2d(cx-90,cy-115);
    glVertex2d(cx-95,cy-115);
    glVertex2d(cx-85,cy-55);
    glEnd();
    
    //Fishrod.
    glColor3ub(188,143,143);
    glBegin(GL_POLYGON);
    glVertex2d(cx-150,cy-100);
    glVertex2d(cx+150,cy-100);
    glVertex2d(cx+150,cy-110);
    glVertex2d(cx-150,cy-110);
    glEnd();
    
    //Right ear.
    glColor3ub(255,255,240);//Base
    glBegin(GL_POLYGON);
    glVertex2d(cx+60,cy-75);
    glVertex2d(cx+90,cy-115);
    glVertex2d(cx+95,cy-115);
    glVertex2d(cx+85,cy-55);
    glEnd();
    glColor3ub(255,240,245);//Pink part.
    glBegin(GL_POLYGON);
    glVertex2d(cx+65,cy-75);
    glVertex2d(cx+85,cy-100);
    glVertex2d(cx+80,cy-55);
    glEnd();
    glColor3ub(255,182,193);//Contour.
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx+60,cy-75);
    glVertex2d(cx+90,cy-115);
    glVertex2d(cx+95,cy-115);
    glVertex2d(cx+85,cy-55);
    glEnd();
    
    //Face.
    glColor3ub(255,255,240);//Base.Semicircle+rectangle.
    glBegin(GL_POLYGON);
    for(int i=100; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)cx+cos(angle)*(double)100;
        double y=(double)cy+sin(angle)*(double)100;
        glVertex2d(x,y);
    }
    glVertex2i(cx+100,cy);
    glVertex2i(cx+100,cy+10);
    glVertex2i(cx-100,cy+10);
    glVertex2i(cx-100,cy);
    glEnd();
    glColor3ub(255,182,193);
    glBegin(GL_LINE_STRIP);//Contour.
    for(int i=100; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)cx+cos(angle)*(double)100;
        double y=(double)cy+sin(angle)*(double)100;
        glVertex2d(x,y);
    }
    glVertex2i(cx+100,cy);
    glVertex2i(cx+100,cy+10);
    glVertex2i(cx-100,cy+10);
    glVertex2i(cx-100,cy);
    glEnd();
    glColor3ub(255,240,245);
    
    glBegin(GL_POLYGON);//Shade.
    glVertex2d(cx,cy);
    for(int i=100; i<150; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)cx+cos(angle)*(double)98;
        double y=(double)cy+sin(angle)*(double)98;
        glVertex2d(x,y);
    }
    glVertex2d(cx-100,cy);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(cx,cy);
    glVertex2i(cx,cy+9);
    glVertex2i(cx-99,cy+9);
    glVertex2i(cx-99,cy);
    glEnd();
    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2d(cx,cy+10);
    for(int i=70; i<150; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)cx+cos(angle)*(double)58;
        double y=(double)(cy-40)+sin(angle)*(double)58;
        glVertex2d(x,y);
    }
    glEnd();
    
    //Beard.
    glColor3ub(0,0,0);//Up-left.
    glBegin(GL_LINES);
    glVertex2d(cx-60,cy-30);
    glVertex2d(cx-80,cy-34);
    glEnd();
    glBegin(GL_LINES);//Up-right.
    glVertex2d(cx+60,cy-30);
    glVertex2d(cx+80,cy-34);
    glEnd();
    glBegin(GL_LINES);//Mid-left.
    glVertex2d(cx-60,cy-22);
    glVertex2d(cx-80,cy-22);
    glEnd();
    glBegin(GL_LINES);//Mid-right.
    glVertex2d(cx+60,cy-22);
    glVertex2d(cx+80,cy-22);
    glEnd();
    glBegin(GL_LINES);//Down-left.
    glVertex2d(cx-60,cy-16);
    glVertex2d(cx-80,cy-12);
    glEnd();
    glBegin(GL_LINES);//Down-right.
    glVertex2d(cx+60,cy-16);
    glVertex2d(cx+80,cy-12);
    glEnd();
    
    //Paws.
    glColor3ub(255,182,193);
    glBegin(GL_POLYGON);
    glVertex2d(cx-48,cy+10);
    for(int i=45; i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx-55)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    for(int i=45;i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx-65)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glVertex2d(cx-73,cy+10);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    for(int i=45; i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx-55)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    for(int i=45;i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx-65)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx-60,cy+20);
    glVertex2d(cx-60,cy+25);
    glEnd();
    glColor3ub(255,182,193);
    glBegin(GL_POLYGON);
    glVertex2d(cx+73,cy+10);
    for(int i=45; i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx+55)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glVertex2d(cx+48,cy+10);
    for(int i=45;i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx+65)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    for(int i=45; i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx+55)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(int i=45;i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx+65)+cos(angle)*(double)sqrt(5*5*2.0);
        double y=(double)(cy+20)+sin(angle)*(double)sqrt(5*5*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx+60,cy+20);
    glVertex2d(cx+60,cy+25);
    glEnd();
}

void Cat::DrawEyes(void)
{
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx-40)+cos(angle)*(double)10;
        double y=(double)(cy-50)+sin(angle)*(double)10;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx+40)+cos(angle)*(double)10;
        double y=(double)(cy-50)+sin(angle)*(double)10;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx-37)+cos(angle)*(double)4;
        double y=(double)(cy-46)+sin(angle)*(double)4;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx+43)+cos(angle)*(double)4;
        double y=(double)(cy-46)+sin(angle)*(double)4;
        glVertex2d(x,y);
    }
    glEnd();
}

void Cat::DrawSmile(void)
{
    glColor3ub(0,0,0);//Mouth.
    glBegin(GL_LINE_STRIP);
    for(int i=45; i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx-25/2)+cos(angle)*(double)sqrt((25/2)*(25/2)*2.0);
        double y=(double)(cy-75/2)+sin(angle)*(double)sqrt((25/2)*(25/2)*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(int i=45;i<135; i++)
    {
        double angle=(double)i*PI/180.0;
        double x=(double)(cx+25/2)+cos(angle)*(double)sqrt((25/2)*(25/2)*2.0);
        double y=(double)(cy-75/2)+sin(angle)*(double)sqrt((25/2)*(25/2)*2.0);
        glVertex2d(x,y);
    }
    glEnd();
    DrawEyes();
}

void Cat::DrawSad(void)
{
    //Mouth.
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx-20,cy-4);
    glVertex2d(cx+5,cy-10);
    glVertex2d(cx+20,cy-4);
    glEnd();
    
    //Tear.
    glColor3ub(100,149,237);
    glBegin(GL_QUADS);
    glVertex2d(cx-36,cy-40);
    glVertex2d(cx-44,cy-40);
    glVertex2d(cx-44,cy+10);
    glVertex2d(cx-36,cy+10);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(cx+36,cy-40);
    glVertex2d(cx+44,cy-40);
    glVertex2d(cx+44,cy+10);
    glVertex2d(cx+36,cy+10);
    glEnd();
    
    DrawEyes();
}

void Cat::DrawHappy(void)
{
    DrawSmile();
    
    glColor3ub(0,0,0);//Fill the white parts in eyes.
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx-40)+cos(angle)*(double)10;
        double y=(double)(cy-50)+sin(angle)*(double)10;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        double angle=(double)i*PI/100.0;
        double x=(double)(cx+40)+cos(angle)*(double)10;
        double y=(double)(cy-50)+sin(angle)*(double)10;
        glVertex2d(x,y);
    }
    glEnd();
    //Stars in eyes.
    double a=3*sqrt(3.0);
    glColor3ub(255,255,0);
    glBegin(GL_POLYGON);
    glVertex2d(cx-43,cy-53);
    glVertex2d(cx-40,cy-53-8);
    glVertex2d(cx-37,cy-53);
    glVertex2d(cx-37+a,cy-50);
    glVertex2d(cx-37,cy-47);
    glVertex2d(cx-40,cy-47+8);
    glVertex2d(cx-43,cy-47);
    glVertex2d(cx-43-a,cy-50);
    glEnd();
    glColor3ub(255,255,0);
    glBegin(GL_POLYGON);
    glVertex2d(cx+43,cy-53);
    glVertex2d(cx+40,cy-53-8);
    glVertex2d(cx+37,cy-53);
    glVertex2d(cx+37-a,cy-50);
    glVertex2d(cx+37,cy-47);
    glVertex2d(cx+40,cy-47+8);
    glVertex2d(cx+43,cy-47);
    glVertex2d(cx+43+a,cy-50);
    glEnd();
}

void Cat::DrawGameOver(void)
{
    //Cross as eyes.
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx-50,cy-60);
    glVertex2d(cx-30,cy-40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx-50,cy-40);
    glVertex2d(cx-30,cy-60);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx+50,cy-60);
    glVertex2d(cx+30,cy-40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx+50,cy-40);
    glVertex2d(cx+30,cy-60);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(cx-10,cy-10);
    glVertex2d(cx+10,cy-10);
    glEnd();
}

void Cat::Position(void)
{
    int lb,mb,rb,mx,my;
    FsGetMouseEvent(lb,mb,rb,mx,my);
    if(mx>200 && mx<800)
    {
        cx=mx;
    }
}


class Boat : public Cat
{
public:
    int bx,by;
    void DrawBoat(int cx,int cy);
};

void Boat::DrawBoat(int cx,int cy)
{
    bx=cx;
    by=cy+28;
    glColor3ub(218,165,32);//Boat body.
    glBegin(GL_POLYGON);
    glVertex2d(bx-200,by);
    glVertex2d(bx+200,by);
    glVertex2d(bx+180,by+50);
    glVertex2d(bx-180,by+50);
    glEnd();
    glColor3ub(0,0,0);//Contour.
    glBegin(GL_LINE_LOOP);
    glVertex2d(bx-200,by);
    glVertex2d(bx+200,by);
    glVertex2d(bx+180,by+50);
    glVertex2d(bx-180,by+50);
    glEnd();
    glBegin(GL_LINES);//Texture.
    glVertex2d(bx-195,by+15);
    glVertex2d(bx-100,by+15);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(bx+10,by+15);
    glVertex2d(bx+120,by+15);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(bx-100,by+35);
    glVertex2d(bx,by+35);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(bx+50,by+25);
    glVertex2d(bx+150,by+25);
    glEnd();
}

class Fishrod : public Cat
{
public:
    int fx,fy,stt,vy;
    void initialize(int cx,int cy);
    void Control(void);
    void HookPosition(int cx,int cy,int key);
    void Pixel(int x,int y);
    void DrawFishhook(int cy);
    void move(int cx,int cy,int &key,double x,double y, int &score,int &check_state, int &facial);
    void play(int cx, int cy, int &key, int &keyinput,double x,double y,int &score,int &check_state,int &facial,int &life,int &cry, int &num);
};

void Fishrod::move(int cx,int cy,int &key,double x,double y,int &score,int &check_state, int &facial)
{
    stt=1;
    fy+=vy;
    int temp = check_fish(x,y,score,check_state);
    if (fy >= 700 || temp != 0)
    {
        if (vy >= 0)
        {
            vy = -vy;
        }
    }
    
    if (temp != 0)
    {
        check_state = 0;
        if (temp == 1)
        {
            facial = 1;
        }
        if (temp == -1)
        {
            facial = 2;
        }
    }
    
    if (fy <= (cy-98))
    {
        vy = -vy;
        initialize(cx,cy);
        key = 0;
        check_state = 1;
    }
}

void Fishrod::initialize(int cx,int cy)
{
    fx=cx-148;
    fy=cy-98;
    stt=0;
    vy=10;
}

void Fishrod::HookPosition(int cx,int cy,int key)
{
    fx=cx-148;
}

void Fishrod::Pixel(int x,int y)
{
    glColor3ub(128,128,128);
    glBegin(GL_POLYGON);
    glVertex2d(x,y);
    glVertex2d(x+3,y);
    glVertex2d(x+3,y+3);
    glVertex2d(x,y+3);
    glEnd();
}

void Fishrod::DrawFishhook(int cy)
{
    glColor3ub(0,0,0);//Fish wire.
    glBegin(GL_LINE_STRIP);
    glVertex2d(fx,fy);
    glVertex2d(fx,cy-100);
    glEnd();
    
    glColor3ub(128,128,128);//Upper fishhook.
    glBegin(GL_POLYGON);
    glVertex2d(fx,fy);
    glVertex2d(fx+3,fy);
    glVertex2d(fx+3,fy-5);
    glVertex2d(fx,fy-5);
    glEnd();
    
    //Fishhook.
    Pixel(fx,fy);
    Pixel(fx+3,fy);
    Pixel(fx+6,fy);
    Pixel(fx+9,fy+2);
    Pixel(fx+12,fy+3);
    Pixel(fx+12,fy+6);
    Pixel(fx+12,fy+9);
    Pixel(fx+12,fy+12);
    Pixel(fx+12,fy+15);
    Pixel(fx+9,fy+16);
    Pixel(fx+6,fy+18);
    Pixel(fx+3,fy+18);
    Pixel(fx,fy+18);
    Pixel(fx-3,fy+17);
    Pixel(fx-3,fy+15);
    Pixel(fx-4,fy+14);
    Pixel(fx-6,fy+12);
}

class CatOnBoat
{
public:
    Cat cat;
    Boat boat;
    Fishrod fishrod;
    
    void CatMainFcn(int State);
};

Cat cat;
Boat boat;
Fishrod fishrod;

////////////////////////////////////////////////////////////////////////////////////

class Torpedor
{
    
protected:
    
    YsRawPngDecoder png_left;
    YsRawPngDecoder png_right;
    
    int winWid, winHei;
    double vx,vy;
    int Tor_oceandeep;
    int tor_state;
    double tor_x, tor_y;
    
public:
    void ReadFirgure();
    int MoveTor(double sub_x, double sub_y,int lauch,double sub_vx);
    void LaunchTor(int state);
    void Tor_initialize(int oceandeep,int sub_x, int sub_y);
    void DrawTor(int vx);
    double return_x();
    double return_y();
    
    
    
};


void Torpedor:: ReadFirgure()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_torpedo),dat_left_torpedo);
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_torpedo),dat_right_torpedo);
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    
}


void Torpedor::Tor_initialize(int oceandeep,int sub_x, int sub_y)
{
    FsGetWindowSize(winWid,winHei);
    tor_state=0;
    vx=10;
    vy=-4;
    Tor_oceandeep=oceandeep;
    
    tor_x=sub_x;
    tor_y=sub_y;
    
}


int Torpedor::MoveTor(double sub_x, double sub_y,int lauch,double sub_vx)
{
    if (tor_state==0) {
        
        tor_x=sub_x+100;
        tor_y=sub_y;
        
    }
    else{
        
        tor_x=tor_x+vx*0.5;
        tor_y=tor_y+vy*0.5;
    }
    
    if(sub_vx<0){
        vx=-10;
    }
    else
        vx=10;
    
    if(tor_x>winWid){
        tor_state=0;
    }
    
    if(tor_x<0){
        tor_state=0;
    }
    
    if(tor_y< 260+png_right.hei)
        tor_state=0;
    
    return tor_state;
}

void Torpedor:: LaunchTor(int state)
{
    tor_state=state;
    
}

void Torpedor:: DrawTor(int vx)
{
    if (tor_state==1 && vx>0) {
        
        glRasterPos2d(tor_x+20,tor_y+png_right.hei-30);
        
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
        
    }
    else if(tor_state==1 && vx<0){
        glRasterPos2d(tor_x-100,tor_y+png_left.hei-30);
        
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
    
}

double Torpedor:: return_x()
{
    return tor_x;
}

double Torpedor:: return_y()
{
    return tor_y;
}

class Pearl{
    
protected:
    double pearl_x;
    double pearl_y;
    YsRawPngDecoder  png_pearl;
    int lauch_pearl_state;
    int winWid, winHei;
    double pearl_vx,pearl_vy;
    double pearl_oceandeep;
    
public:
    void ReadFigure();
    void Pearl_Intialize(int oceandeep,int sub_x, int sub_y);
    void DrawPearl(int vx);
    int MovePearl(double sub_x, double sub_y,int lauch,double sub_vx);
    void Launch(int lauch);
    double return_pearl_x();
    double return_pearl_y();
    
};

void Pearl:: Pearl_Intialize(int oceandeep,int sub_x, int sub_y)
{
    FsGetWindowSize(winWid,winHei);
    lauch_pearl_state=0;
    pearl_vx=10;               //change the x velovity of peral!!!!!!!!!!!!!!!!!
    pearl_vy=-10;              //change the y velovity of peral!!!!!!!!!!!!!!!!!
    pearl_oceandeep=oceandeep;
    
    pearl_x=sub_x;
    pearl_y=sub_y;
    
}

void Pearl::DrawPearl(int vx)
{
    const double YS_PI=3.1415927;
    if (lauch_pearl_state==1) {
        glColor3ub(210, 214, 222);
        glBegin(GL_POLYGON);
        for(int i=0;i<64;i++){
            double angle=(double)i*YS_PI/32.0;  //change the size of pearl
            double x=pearl_x+cos(angle)*13.0;
            double y=pearl_y+sin(angle)*13.0;
            glVertex2d(x,y);
        }
        glEnd();
        
        glColor3ub(240, 241, 244);
        glBegin(GL_POLYGON);
        for(int i=0;i<64;i++){
            double angle=(double)i*YS_PI/32.0;
            double x=pearl_x+cos(angle)*10.0;
            double y=pearl_y+sin(angle)*10.0;
            glVertex2d(x,y);
        }
        glEnd();
        
        glColor3ub(255, 255, 255);
        glBegin(GL_POLYGON);
        for(int i=0;i<64;i++){
            double angle=(double)i*YS_PI/32.0;
            double x=pearl_x+cos(angle)*5.0;
            double y=pearl_y+sin(angle)*5.0;
            glVertex2d(x,y);
        }
        glEnd();
        
    }
    
}

int  Pearl::MovePearl(double sub_x, double sub_y,int lauch,double sub_vx)
{
    
    if (lauch_pearl_state==0) {
        
        pearl_x=sub_x+100;
        pearl_y=sub_y;
        
    }
    else{
        
        pearl_x=pearl_x+pearl_vx*0.5;
        pearl_y=pearl_y+pearl_vy*0.5;
    }
    
    if(sub_vx<0){
        pearl_vx=-10;   //change the x velovity of peral!!!!!!!!!!!!!!!!!
    }
    else
        pearl_vx=10;     //change the x velovity of peral!!!!!!!!!!!!!!!!!
    
    if(pearl_x>winWid){
        lauch_pearl_state=0;
    }
    
    if(pearl_x<0){
        lauch_pearl_state=0;
    }
    
    if(pearl_y< 280+png_pearl.hei)   //**
        lauch_pearl_state=0;
    
    return lauch_pearl_state;
    
}

void Pearl::  Launch(int lauch)
{
    lauch_pearl_state=lauch;
}

double Pearl:: return_pearl_x()
{
    return pearl_x;
}

double Pearl:: return_pearl_y()
{
    return pearl_y;
    
}


class SubMarine{
    
protected:
    int winWid,winHei;
    YsRawPngDecoder png_left;
    YsRawPngDecoder png_right;
    double vx,vy;
    double x,y;
    int Sub_oceandeep;
    int lauch_state;
    Torpedor tor;
    Pearl pear;
    
public:
    void Intialize();
    void ReadFirgure();
    void DrawSub();
    void MoveSub(int lauch_tor, int lauch_pearl);
    void Launch_tor(int lauch);
    void Launch_pearl(int lauch);
    double return_tor_x();
    double return_tor_y();
    double return_pea_x();
    double return_pea_y();
    double return_sub_x();
    int CheckHit_tor(double boat_x,double boat_y,double boat_wid);
    int CheckHit_pea(double boat_x,double boat_y,double boat_wid);
};



void SubMarine:: ReadFirgure()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_left_submarine),dat_left_submarine);
    
    if(YSOK==png_left.Decode(memInStream1))
    {
        png_left.Flip();
    }
    else
    {
        printf("Read Error!\n");
        
    }
    
    YsPngBinaryMemoryStream memInStream2((sizeOfDat_right_submarine),dat_right_submarine);
    
    if(YSOK==png_right.Decode(memInStream2))
    {
        png_right.Flip();
    }
    else
    {
        printf("Read Error!\n");
    }
    tor.ReadFirgure();
}


void SubMarine::DrawSub()
{
    
    if (vx>0){
        glRasterPos2d(x,y+png_right.hei);
        
        glDrawPixels(png_right.wid,png_right.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_right.rgba);
    }
    
    else{
        glRasterPos2d(x,y+png_left.hei);
        
        glDrawPixels(png_left.wid,png_left.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_left.rgba);
    }
    
    tor.DrawTor(vx);
    pear.DrawPearl(vx);
    
}

void SubMarine::Intialize()
{
    FsGetWindowSize(winWid,winHei);
    srand(time(NULL));
    Sub_oceandeep=400;
    x=0;
    y=490;
    
    lauch_state=0;
    vx=10;
    vy=0;
    
    tor.Tor_initialize(Sub_oceandeep, x, y);
    pear.Pearl_Intialize(Sub_oceandeep, x, y);
    
}

void  SubMarine::MoveSub(int lauch_tor,int lauch_pearl)
{
    x=x+vx*0.5;
    
    lauch_state=tor.MoveTor(x, y,lauch_tor,vx);
    pear.MovePearl(x, y, lauch_pearl, vx);
    if (x>winWid){
        vx=-vx;
    }
    if(x<0){
        vx=-vx;
    }
    
    return;
}



void SubMarine::Launch_tor(int lauch)
{
    lauch_state=lauch;
    tor.LaunchTor(lauch_state);
}

void SubMarine::Launch_pearl(int lauch)
{
    pear.Launch(lauch);
}
double SubMarine::return_tor_x()
{
    return tor.return_x();
}

double SubMarine::return_tor_y()
{
    return tor.return_y();
}

double SubMarine:: return_pea_x()
{
    return pear.return_pearl_x();
}

double SubMarine:: return_pea_y()
{
    return pear.return_pearl_y();
}

double SubMarine:: return_sub_x()
{
    return x;
}

int SubMarine::CheckHit_tor(double boat_x,double boat_y,double boat_wid)
{
    double tor_x;
    double tor_y;
    int result=0;
    
    tor_x=tor.return_x();
    tor_y=tor.return_y();
    
    if (boat_x-0.5*boat_wid < tor_x && tor_x < boat_x+0.5*boat_wid) {
        if(tor_y<boat_y){
            result=1;
            Launch_tor(0);
        }
    }
    
    return result;
}

int SubMarine::CheckHit_pea(double boat_x, double boat_y, double boat_wid)
{
    double pea_x;
    double pea_y;
    int result=0;
    
    pea_x=pear.return_pearl_x();
    pea_y=pear.return_pearl_y();
    
    if (boat_x-0.5*boat_wid < pea_x && pea_x < boat_x+0.5*boat_wid) {
        if(pea_y < boat_y){
            result=1;
            Launch_pearl(0);
        }
        
    }
    
    return result;
    
}

SubMarine Sub;

void Initalize()
{
    fish1.initialize();
    fish2.initialize();
    fish3.initialize();
    shrimp.initialize();
    star.initialize();
    apple.initialize();
    garbage.initialize();
    cat.initialize();
    fishrod.initialize(cat.cx,cat.cy);
    cloud.Initialize();
    Sub.ReadFirgure();
    Sub.Intialize();
}

void play_sub(int lauch_tor, int lauch_pearl)
{
    double sub_x;
    sub_x=Sub.return_sub_x();
    
    if(sub_x > 200 && sub_x<210 && lauch_tor==0 ){// the place where lauch torpedo.  200<sub_x<210
        lauch_tor=1;
        Sub.Launch_tor(lauch_tor);
        lauch_tor=0;
    }
    
    if(sub_x > 800 && sub_x<810 && lauch_tor==0 ){// the place where lauch torpedo  800<sub_x<810
        lauch_tor=1;
        Sub.Launch_tor(lauch_tor);
        lauch_tor=0;
    }
    
    if(sub_x > 400 && sub_x<410 && lauch_pearl==0 ){  // the place where lauch pearl  400<sub_x<410
        lauch_pearl=1;
        Sub.Launch_pearl(lauch_pearl);
        lauch_pearl=0;
    }
    
    if(sub_x > 600 && sub_x<610 && lauch_pearl==0 ){   // the place where lauch pearl  600<sub_x<610
        lauch_pearl=1;
        Sub.Launch_pearl(lauch_pearl);
        lauch_pearl=0;
    }
    
    Sub.MoveSub(lauch_tor,lauch_pearl);
    Sub.DrawSub();
}



void Fishrod::play(int cx, int cy, int &key, int &keyinput,double x,double y,int &score, int &check_state,int &facial, int &life,int &cry, int &num)
{
    
    if(FSKEY_SPACE==keyinput)
    {
        key=1;
        check_state = 1;
    }
    
    if (cry == 1)
    {
        num++;
    }
    
    if (num == 20)
    {
        num = 0;
        cry = 0;
    }
    
    if (key == 1)
    {
        move(cx,cy,key,x,y,score,check_state,facial);
    }
    
    
    if (check_state == 1 && cry != 1)
    {
        facial = 0;
    }
    
    if (Sub.CheckHit_tor(cx,cy+120,400) == 1 )
    {
        if (cry == 0)
        {
            cry = 1;
        }
        else
            num = 0;
        
        facial = 3;
        life --;
    }
    
    if (Sub.CheckHit_pea(cx,cy+100,400) == 1 )
    {
        if (cry == 0)
        {
            cry = 1;
        }
        else
            num = 0;
        
        facial = 1;
        score += 10;
    }
    
    
    HookPosition(cx,cy,key);
    DrawFishhook(cy);
}


class Ocean
{
public:
    double x,y;
    YsRawPngDecoder png_ocean;
    
    Ocean();
    void Drawocean_png(void);
    void ReadFigure(void);
};

Ocean::Ocean(){
    x=0;
    y=699;
    
}

void Ocean:: ReadFigure(void)
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_oceanbed),dat_oceanbed);
    if(YSOK==png_ocean.Decode(memInStream1))
    {
        png_ocean.Flip();
    }
    else
    {
        printf("Read Error!\n");
        
    }
}

void Ocean::Drawocean_png(void)
{
    glRasterPos2d(x,y);
    
    glDrawPixels(png_ocean.wid,png_ocean.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_ocean.rgba);
    
}

class Sky
{
public:
    int clx,vx,dummyx;
    void DrawCloud(void);
    void MoveCloud(void);
    void SkyInitialize(void);
    void DrawSky(void);
    void DrawRainbow(void);
};

void Sky::DrawCloud(void)
{
    glColor3ub(100,149,237);
    glBegin(GL_POLYGON);
    glVertex2d(clx-390,140);
    glVertex2d(clx-290,140);
    glVertex2d(clx-290,100);
    glVertex2d(clx-390,100);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-390+cos(angle)*40;
        double y=100+sin(angle)*40;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-340+cos(angle)*60;
        double y=80+sin(angle)*60;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-290+cos(angle)*50;
        double y=90+sin(angle)*50;
        glVertex2d(x,y);
    }
    glEnd();
    
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex2d(clx-390,138);
    glVertex2d(clx-290,138);
    glVertex2d(clx-290,100);
    glVertex2d(clx-390,100);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-390+cos(angle)*38;
        double y=100+sin(angle)*38;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-340+cos(angle)*58;
        double y=80+sin(angle)*58;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-290+cos(angle)*48;
        double y=90+sin(angle)*48;
        glVertex2d(x,y);
    }
    glEnd();
    //cloud2
    glColor3ub(100,149,237);
    glBegin(GL_POLYGON);
    glVertex2d(clx-90,160);
    glVertex2d(clx,160);
    glVertex2d(clx,130);
    glVertex2d(clx-90,130);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-90+cos(angle)*30;
        double y=130+sin(angle)*30;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-50+cos(angle)*40;
        double y=120+sin(angle)*40;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx+cos(angle)*50;
        double y=110+sin(angle)*50;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex2d(clx-90,158);
    glVertex2d(clx,158);
    glVertex2d(clx,130);
    glVertex2d(clx-90,130);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-90+cos(angle)*28;
        double y=130+sin(angle)*28;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx-50+cos(angle)*38;
        double y=120+sin(angle)*38;
        glVertex2d(x,y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<64;i++)
    {
        double angle=(double)i*PI/32.0;
        double x=clx+cos(angle)*48;
        double y=110+sin(angle)*48;
        glVertex2d(x,y);
    }
    glEnd();
}

void Sky::SkyInitialize(void)
{
    clx=0;
    dummyx=0;
    vx=3;
}

void Sky::MoveCloud(void)
{
    dummyx+=vx;
    clx=dummyx%1000;
}

void Sky::DrawSky(void)
{
    glColor3ub(162,248,255);
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=800+cos(angle)*600;
        double y=300+sin(angle)*600;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(225,255,255);
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=400+cos(angle)*630;
        double y=300+sin(angle)*630;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(240,255,255);
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=100+cos(angle)*400;
        double y=300+sin(angle)*400;
        glVertex2d(x,y);
    }
    glEnd();
    glColor3ub(245,255,250);
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        double angle=(double)i*PI/100.0;
        double x=0+cos(angle)*250;
        double y=300+sin(angle)*250;
        glVertex2d(x,y);
    }
    glEnd();
}

void Sky::DrawRainbow(void)
{
    Rainbow(120,180,90,10);
}

int main(void)
{
    int score = 0;
    int ocean_deep = 450;
    int lb,mb,rb,mx,my;
    int key=0;
    int facial = 0;
    int check_state = 1;
    int lauch_tor=0;
    int lauch_pearl=0;
    int life = 3;
    int cry = 0;
    int num = 0;
    int gameState=0; //game on; non-zero, game not on;
    
    Interface myFace;
    myFace=Interface(60);
    int passedTime=0;
    
    Ocean ocean;
    ocean.ReadFigure();
    
    FsOpenWindow(16,16,1000,700,1);
    
    Initalize();
    Bubble BB[5];
    Sky sky;
    sky.SkyInitialize();
    
    for(int i=0;i<5;i++)
    {
        BB[i].Initialize(i);
    }
    
    int keystate=FSKEY_NULL;
    int game_begin=1;
    
    while(game_begin)
    {
        FsPollDevice();
        keystate=FsInkey();
        
        int mouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
        passedTime=FsPassedTime();
        
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        sky.DrawSky();
        sky.MoveCloud();
        sky.DrawCloud();
        
        myFace.setScore(score);
        myFace.setLife(life);
        
        if(life==0)
        {
            life=3;
        }
        
        gameState=myFace.drawInterface(passedTime, keystate, mx, my, mouseEvent);
        score=myFace.getScore();
        
        if(myFace.getGameState()==-1)
        {
            game_begin=0;
        }
        
        if(gameState==0)
        {
            sky.DrawRainbow();
            
            Drawocean(ocean_deep);
            ocean.Drawocean_png();
            
            boat.DrawBoat(cat.cx,cat.cy);
            play_fish();
            play_sub(lauch_tor,lauch_pearl);
            
            fishrod.play(cat.cx,cat.cy,key,keystate,fishrod.fx,fishrod.fy,score,check_state,facial,life,cry,num);
            
            cat.Position();
            cat.Status(facial);
            
            for(int i=0;i<6;i++)
            {
                BB[i].BubblePara();
                BB[i].DrawBubble();
            }
        }
        
        
        FsSwapBuffers();
        FsSleep(50);
    }
    printf("score = %d\n",score);
    return 0;
}












