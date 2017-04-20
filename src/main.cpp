#include <QApplication>
#include <QDebug>
#include <QThread>
#include <iostream>
#include <unistd.h>
#include "rcon.h"
#include "xsconsole.h"
#include "fetch.h"

#ifdef WIN32
    #include<conio.h>
    #define ENTER_KEY 13
#endif
#ifdef linux
    #include <termios.h>
    #define ENTER_KEY 10
    int getch(void)
    {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
#endif
#define CERROR(check, text) { if(check) { qWarning() << "[ERR] " << text << endl; \
                                          return -1; }                      }

#define OK 0

#define endl "\n"

using namespace std;

QString sysApp;
QString sysVersion = "0.1";
QString netAddress;
QString netPasswd;
QString netPort;

Rcon* rcClient;
Fetch* input;

QString inputBuffer;

int getArgs(int argc, char **argv)
{

    sysApp = argv[0];
    netAddress = argv[1];
    netPort = argv[2];
    netPasswd = argv[3] != nullptr ? argv[3] : QString("");

    return OK;
}


void getPasswd()
{
    char ch;
    if(netPasswd == "")
    {
        while(true){
            ch = getch();
            if(ch == ENTER_KEY)
                return;
            netPasswd.append(ch);
            xsConsole() << "*";
        }
    }
}

int main(int argc, char **argv)
{
    CERROR(argc < 3, "Insufficient arguments!");
    getArgs(argc,argv);
    xsConsole() << "Serious Manager " << sysVersion << " by Luca \"Nobel3D\" Gasperini" << endl;
    xsConsole() << QString("Trying to connect: ") + netAddress + "\n";
    rcClient = new Rcon;
    if(rcClient->Connect(netAddress, netPort.toInt()) != 0)
        return 0;

    xsConsole() << "Login -> ";
    getPasswd();
    if(rcClient->Login(netPasswd) != 0)
        return 0;
    xsConsole() << endl;

    input = new Fetch(rcClient);
    input->start();

    while(inputBuffer != "quit")
    {
        sleep(1);
        xsConsole() >> inputBuffer;
        rcClient->WriteStream(inputBuffer);
    }
    rcClient->Close();
    return 0;
}
