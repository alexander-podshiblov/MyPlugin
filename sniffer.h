#ifndef SNIFFER_H
#define SNIFFER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include "snippet.h"

class Sniffer : public QObject
{
    Q_OBJECT
public:
    Sniffer(QObject *parent = 0);
    Sniffer(QObject *parent, QList<Snippet> *s);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void needPrint(int i);

public slots:
private:
    QList<Snippet> *snippets;

};

#endif // SNIFFER_H
