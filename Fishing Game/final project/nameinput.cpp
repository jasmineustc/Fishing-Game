//
//  nameinput.cpp
//  final project
//
//  Created by mizhang on 11/22/14.
//  Copyright (c) 2014 Mi Zhang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"
#include "string.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include <ctype.h>
#include "nameinput.h"
#include "ocean.h"
#include "congratulation.h"

void Drawocean2(int ocean_deep)
{
    glColor3ub(151, 208, 242);
    glBegin(GL_QUADS);
    glVertex2i(0,700-ocean_deep);
    glVertex2i(1000,700-ocean_deep);
    glVertex2i(1000,700);
    glVertex2i(0,700);
    glEnd();
    
}

Ocean2::Ocean2(){
    x=0;
    y=699;
    
}

void Ocean2:: ReadFigure(void)
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

void Ocean2::Drawocean_png(void)
{
    glRasterPos2d(x,y);
    glDrawPixels(png_ocean.wid,png_ocean.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_ocean.rgba);
}

Congratulation::Congratulation()
{
    x=355;
    y=182;
}

void Congratulation:: ReadFigure()
{
    YsPngBinaryMemoryStream memInStream1((sizeOfDat_congratulation),dat_congratulation);
    if(YSOK==png_congratulation.Decode(memInStream1))
    {
        png_congratulation.Flip();
    }
    else
    {
        printf("Read Error!\n");
        
    }
}

void Congratulation:: Drawcongratulation_png()
{
    glRasterPos2d(x,y);
    glDrawPixels(png_congratulation.wid,png_congratulation.hei,GL_RGBA,GL_UNSIGNED_BYTE,png_congratulation.rgba);

}



TextString::TextString() : str(NULL)
{
}

TextString::TextString(const char from[]) : str(NULL)
{
    Set(from);
}

TextString::TextString(const TextString &from) : str(NULL)
{
    Set(from.GetPointer());
}

TextString::~TextString()
{
    CleanUp();
}

void TextString::CleanUp()
{
    if(NULL!=str)
    {
        delete [] str;
        str=NULL;
    }
}

void TextString::Set(const char from[])
{
    if(NULL!=from)
    {
        CleanUp();
        
        const int n=strlen(from);
        str=new char [n+1];
        if(NULL!=str)
        {
            strcpy(str,from);
        }
    }
}

void TextString::Add(const char from[])
{
    if(NULL!=from)
    {
        const int nCurrent=Strlen();
        const int nFrom=strlen(from);
        
        char *newStr=new char [nCurrent+nFrom+1];
        if(NULL!=newStr)
        {
            strcpy(newStr,GetPointer());
            strcpy(newStr+nCurrent,from);
            if(NULL!=str)
            {
                delete [] str;
            }
            str=newStr;
        }
    }
}


void TextString::Add(const char c)
{
    const int nCurrent=Strlen();
    
    char *newStr=new char [nCurrent+2];
    if(NULL!=newStr)
    {
        strcpy(newStr,GetPointer());
        newStr[nCurrent]=c;
        newStr[nCurrent+1]=0;
        if(NULL!=str)
        {
            delete [] str;
        }
        str=newStr;
    }
}

void TextString::BackSpace(void)
{
    if(NULL!=str)
    {
        int n=Strlen();
        if(0<n)
        {
            str[n-1]=0;
        }
    }
}

void TextString::DeleteLastControlCode(void)
{
    int n;
    for(n=strlen(str)-1; 0<=n; n--)
    {
        if(0!=isprint(str[n]))
        {
            break;
        }
        str[n]=0;
    }
}

const char *TextString::Fgets(FILE *fp)
{
    if(NULL!=fp)
    {
        CleanUp();
        
        int firstLine=1;
        const int nBuf=8;
        char buf[nBuf+1];
        
        buf[nBuf]=0;
        for(;;)
        {
            if(NULL==fgets(buf,nBuf,fp))
            {
                if(0!=firstLine)
                {
                    return NULL;
                }
                else
                {
                    break;
                }
            }
            else
            {
                firstLine=0;
                Add(buf);
                
                int nChar=strlen(buf);
                if(buf[nChar-1]=='\n' || buf[nChar-1]=='\a')
                {
                    break;
                }
            }
        }
        
        DeleteLastControlCode();
        return str;
    }
    return NULL;
}

const char *TextString::GetPointer(void) const
{
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const int TextString::Strlen(void) const
{
    return strlen(GetPointer());
}

void TextString::Print(void) const
{
    if(NULL!=str)
    {
        printf("%s\n",str);
    }
}

const TextString &TextString::operator=(const TextString &from)
{
    Set(from.GetPointer());
    return *this;
}


void TextInput::SetCaption(const char newCaption[])
{
    caption.Set(newCaption);
}

void TextInput::SetDefaultText(const char defTxt[])
{
    str.Set(defTxt);
}

const char *TextInput::GetString(void) const
{
    return str.GetPointer();
}

void TextInput::Draw(void)
{
    
    glColor3ub(0,0,0);
    glRasterPos2d(490,250);
    YsGlDrawFontBitmap20x32(str.GetPointer());
    switch(time(NULL)%2)
    {
        case 0:
            YsGlDrawFontBitmap20x32("_");
            break;
        case 1:
            YsGlDrawFontBitmap20x32(" ");
            break;
    }
}

int TextInput::Input(char score[])
{
    Ocean2 ocean;
    ocean.ReadFigure();
    Congratulation cong;
    cong.ReadFigure();
    
    FsPollDevice();
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }
    int count=0;

    for(;;)
    {
        FsPollDevice();
        
        int key=FsInkey();
        
        switch(key)
        {
            case FSKEY_ESC:
                return 0;
            case FSKEY_ENTER:
                return 1;
            case FSKEY_BS:
                str.BackSpace();
                count--;
                break;
        }
        
        const char c=FsInkeyChar();
        
        if(0!=c && 0!=isprint(c) && count<10)
        {
            str.Add(c);
            count++;
        }
       
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        cong.Drawcongratulation_png();
        
        glRasterPos2d(460, 200);
        YsGlDrawFontBitmap20x32("SCORE");

        glRasterPos2d(400, 200+50);
        YsGlDrawFontBitmap20x32(score);
        
        Drawocean2(450);
        ocean.Drawocean_png();
        Draw();
        
        FsSwapBuffers();
        
        FsSleep(20);
    }
    return 0;
}


