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
         if(!buffer.startsWith('>') && buffer != "")
         {
             lines++;
             QConsole() << buffer;
         }
         if(lines != 0 && buffer == "")
         {
             QConsole() << "[" << cStream->getAddress() << ":" << cStream->getPort() << "]$ ";
             lines = 0;
         }
    }
}
