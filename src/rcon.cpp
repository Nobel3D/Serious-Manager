#include "rcon.h"
#include <xslib/xsconsole.h>
#include <QtNetwork>

Rcon::Rcon()
{
}

Rcon::Rcon(QString _Address, int _Port)
{
    Connect(_Address, _Port);
}

int Rcon::Connect(QString address, int port)
{
    sAddress = address;
    iPort = port;
    LOG("[NET] Connecting to server socket...");
    if (iState == 0)  //Disconnected
    {
        socket.connectToHost(address, port);

        if (!socket.waitForConnected(SEC_TIMEOUT))
        {
            xsConsole() << "Impossible reach host!\n";
            LOG("[NET] Connection timeout!");
            iState = 2; //Timeout
            return -1;
        }
        LOG("[NET] Connected to server!");
        iState = 1; //Connected
        return 0;
    }
    LOG("[NET] Already connected!");
    return -1;
}

int Rcon::Login(QString passwd)
{
    LOG("[NET] Trying to login...");
    QString data;
    do
    {
        data = ReadStream();
    }while(data != "login: \r" && data != "");
    ReadStream();
    ReadStream();
    ReadStream();
    WriteStream(passwd); //gli invio la password
    ReadStream();
    data = ReadStream();//ottengo il risultato della connessione:
    if (data == "login: \r")// se mi richiede il login: vuol dire che è sbagliata la password
    {
        LOG("[NET] Login failed!");
        xsConsole() << "\nWrong Password!\n";
        return -1;
    }
    LOG("[NET] Connection authenticated!");
    return 0;
}

QString Rcon::ReadStream()
{
    char buffer;
    QString strout;
    socket.waitForReadyRead(100);
    while(socket.bytesAvailable() != 0 && buffer != '\r')
    {
    socket.read(&buffer, 1);
    if (buffer >= 0 && buffer <= 127)
        strout.append(buffer);
    }
    return strout;
}

int Rcon::WriteStream(QString send)
{
    send.append("\r");
    socket.write( send.toUtf8() );
    socket.waitForBytesWritten();
    return 0;
}

void Rcon::Close()
{
     LOG("[NET] Closing socket!");
    iState = 0;
    socket.close();
}

bool Rcon::isOnline()
{
    return iState == 1;
}

QString Rcon::getAddress() { return sAddress; }
QString Rcon::getPort() { return QString::number(iPort); }
