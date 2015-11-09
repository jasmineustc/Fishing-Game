//
//  nameinput.h
//  final project
//
//  Created by mizhang on 11/22/14.
//  Copyright (c) 2014 Mi Zhang. All rights reserved.
//

#ifndef __final_project__nameinput__
#define __final_project__nameinput__

#include <stdio.h>

#endif /* defined(__final_project__nameinput__) */


class TextString
{
protected:
    char *str;
    
public:
    TextString();
    TextString(const char from[]);
    TextString(const TextString &str);
    ~TextString();
    void CleanUp();
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    const TextString &operator=(const TextString &from);
};

class TextInput
{
protected:
    TextString caption;
    TextString str;
public:
    void SetCaption(const char newCaption[]);
    void SetDefaultText(const char defTxt[]);
    const char *GetString(void) const;
    int Input(char score[]);
    void Draw(void);
};

class Ocean2
{
public:
    double x,y;
    YsRawPngDecoder png_ocean;
    
    Ocean2();
    void Drawocean_png(void);
    void ReadFigure(void);
};


class Congratulation
{
public:
    double x,y;
    YsRawPngDecoder png_congratulation;
    
    Congratulation();
    void Drawcongratulation_png(void);
    void ReadFigure(void);
};


