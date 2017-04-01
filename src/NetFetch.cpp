#include "NetFetch.h"

NetFetch::NetFetch(RemoteConsole* stream)
{
    //QMessageLogger("")
    cStream = stream;
}

void NetFetch::run()
{
    QString buffer;
    while(cStream->isOnline())
    {
         buffer = cStream->ReadStream();
         if(!buffer.startsWith('>'))
         {
             lines++;
             QConsole() << buffer;
         }
    }
}
