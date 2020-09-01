#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _message Message;

struct _message
{
    int id;
    int sizeOfMessage;
    char* textOfMessage;
};


// Выгружает сообщения из файла
Message* creatMessage(char*, int, int);


void printToFile(FILE*, Message*);


void killMessage(Message*);


int readNextMessage(FILE*, Message*);


void killMassMessage(Message**, int);

#endif //LAB3_MESSAGE_H