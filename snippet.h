#ifndef SNIPPET_H
#define SNIPPET_H
#include <QKeySequence>
#include <QString>
#include <QMetaType>

class Snippet
{
public:
    Snippet();
    void setName(QString n) {name = n;}
    void setKeySequence(QKeySequence k) {kSeq = k;}
    void setCode(QString c) {code = c;}
    QString getName() const {return name;}
    QKeySequence getKeySequence() const {return kSeq;}
    QString getCode() const {return code;}



private:
    QString name;
    QKeySequence kSeq;
    QString code;
};

typedef QList<Snippet> SnippetList;

QDataStream &operator<<(QDataStream &out, const Snippet &myObj);
QDataStream &operator>>(QDataStream &in,  Snippet &myObj);



Q_DECLARE_METATYPE(SnippetList)
Q_DECLARE_METATYPE(Snippet)

#endif // SNIPPET_H
