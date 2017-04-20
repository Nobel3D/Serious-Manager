#ifndef FETCH_H
#define FETCH_H

#include <QThread>
#include "rcon.h"
#include "xsconsole.h"

class Fetch : public QThread
{
private:
    Rcon* cStream; //current stream
public:
    Fetch(Rcon *stream);
    int lines;
    void run();
};

#endif // FETCH_H
