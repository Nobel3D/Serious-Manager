#include "QConsole.h"
#include <unistd.h>
#ifdef LINUX
    #include <term.h>
    #include <sys/ioctl.h>
#endif
QConsole::QConsole()
{
    out = new QTextStream(stdout, QIODevice::WriteOnly);
    in = new QTextStream(stdin);
}

void QConsole::Write(QString text)
{
    *out << text;
    out->flush();
}

void QConsole::Read(QString& text)
{
    text = in->readLine();
}

#ifdef LINUX
void QConsole::setXY(int x, int y)
{
  int err;
  if (!cur_term)
    if (setupterm( NULL, STDOUT_FILENO, &err ) == err)
      return;
  putp( tparm( tigetstr( "cup" ), y, x, 0, 0, 0, 0, 0, 0, 0 ) );
}
void QConsole::getXY(int& x, int& y)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    y = w.ws_row;
    x = w.ws_col;
}
#endif
QConsole& QConsole::operator <<(QString text)
{
    Write(text);
    return *this;
}

QConsole& QConsole::operator >>(QString& text)
{
    Read(text);
    return *this;
}
