#ifndef QCONSOLE_H
#define QCONSOLE_H

#include <QString>
#include <QTextStream>

class QConsole
{
private:

    QTextStream* in;
    QTextStream* out;
public:
    QConsole();

    void Write(QString text);
    void Read(QString& text);
    void setXY(int x, int y);
    void getXY(int& x, int& y);
    QConsole& operator <<(QString text);
    QConsole& operator >>(QString& text);
};

#endif // QCONSOLE_H
