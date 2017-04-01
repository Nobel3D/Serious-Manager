#ifndef NETFETCH_H
#define NETFETCH_H

#include <QThread>
#include "RemoteConsole.h"
#include "QConsole.h"

class NetFetch : public QThread
{
private:
    RemoteConsole* cStream; //current stream
public:
    NetFetch(RemoteConsole* stream);
    int lines;
    void run();
};

#endif // NETFETCH_H
