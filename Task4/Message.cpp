#pragma once
#pragma warning(disable:4996)

#include "Message.h"

Message* creatMessage(char* message, int id, int sizeOfMessage)
{
    Message* newNode = (Message*)malloc(sizeof(Message));

    newNode->id = id;
    newNode->sizeOfMessage = sizeOfMessage;
    newNode->textOfMessage = (char*)malloc(sizeOfMessage + 1);
    strcpy(newNode->textOfMessage, message);

    return newNode;
}


void printToFile(FILE* filOut, Message* message)
{
    fprintf(filOut, "%d %d %s", message->id,
        message->sizeOfMessage,
        message->textOfMessage);
}


void killMessage(Message* message)
{
    if (message == NULL)
    {
        return;
    }

    if (message->textOfMessage != NULL)
    {
        free(message->textOfMessage);
    }

    free(message);
}


int readNextMessage(FILE* fout, Message* message)
{
    if (feof(fout))
    {
        return -1;
    }

    char bufChar[BUFSIZ],
        bufCh,
        * pbuf = bufChar;

    fscanf(fout, "%d", &message->id);
    fscanf(fout, "%d", &message->sizeOfMessage);

    message->textOfMessage = (char*)malloc(message->sizeOfMessage + 1);

    fscanf(fout, "%s", message->textOfMessage);

    return 0;
}


void killMassMessage(Message** mass, int numberOfMass)
{
    if (mass == NULL)
    {
        return;
    }

    for (int i = 0; i < numberOfMass; ++i)
    {
        killMessage(mass[i]);
    }

    free(mass);
}