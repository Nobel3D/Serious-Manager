#include "fetch.h"

Fetch::Fetch(Rcon* stream)
{
    //QMessageLogger("")
    cStream = stream;
}

void Fetch::run()
{
    QString buffer;
    while(cStream->isOnline())
    {
         buffer = cStream->ReadStream();
         if(!buffer.startsWith('>') && buffer != "")
         {
             lines++;
             xsConsole() << buffer;
         }
         if(lines != 0 && buffer == "")
         {
             xsConsole() << "[" << cStream->getAddress() << ":" << cStream->getPort() << "]$ ";
             lines = 0;
         }
    }
}
