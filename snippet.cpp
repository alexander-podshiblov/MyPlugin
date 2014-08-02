#include "snippet.h"

Snippet::Snippet()
{
}


QDataStream &operator<<(QDataStream &out, const Snippet &myObj)
{
    out << myObj.getName();
    out << myObj.getKeySequence().toString();
    out << myObj.getCode();

    return out;
}


QDataStream &operator>>(QDataStream &in,  Snippet &myObj)
{
    QString l;

    in >> l;
    myObj.setName(l);

    in >> l;
    myObj.setKeySequence(QKeySequence(l));

    in >> l;
    myObj.setCode(l);

    return in;
}





