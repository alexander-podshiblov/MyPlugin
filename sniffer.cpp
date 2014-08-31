#include "sniffer.h"
#include <QMessageBox>
#include <coreplugin/icore.h>


Sniffer::Sniffer(QObject *parent) :
    QObject(parent)
{
}

Sniffer::Sniffer(QObject *parent, QList<Snippet> *s) :
    QObject(parent)
{
    snippets = s;
}

bool Sniffer::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->modifiers() != Qt::NoModifier)
        {
            int keyInt = keyEvent->key();
            Qt::KeyboardModifiers modifiers = keyEvent->modifiers();

            if(modifiers & Qt::ShiftModifier)
                keyInt += Qt::SHIFT;
            if(modifiers & Qt::ControlModifier)
                keyInt += Qt::CTRL;
            if(modifiers & Qt::AltModifier)
                keyInt += Qt::ALT;
            if(modifiers & Qt::MetaModifier)
                keyInt += Qt::META;


            QKeySequence k(keyInt);

            for (int i = 0; i < snippets->size(); i++)
            {
                if (snippets->at(i).getKeySequence() == k)
                {
                    emit needPrint(i);
                    return true;
                }
                return QObject::eventFilter(obj, event);
            }


        }
        else
        {
            return QObject::eventFilter(obj, event);
        }
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
    return QObject::eventFilter(obj, event);
}
