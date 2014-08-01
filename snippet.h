#ifndef SNIPPET_H
#define SNIPPET_H
#include <QKeySequence>
#include <QString>

class Snippet
{
public:
    Snippet();
    void setName(QString n) {name = n;}
    void setKeySequence(QKeySequence k) {kSeq = k;}
    void setCode(QString c) {code = c;}
    QString getName() {return name;}
    QKeySequence getKeySequence() {return kSeq;}
    QString getCode(){return code;}

private:
    QString name;
    QKeySequence kSeq;
    QString code;
};

#endif // SNIPPET_H
