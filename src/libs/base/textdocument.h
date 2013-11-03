/*
* Copyright (C) 2008-2013 The Communi Project
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include <QTextDocument>
#include <QStringList>

class IrcBuffer;
class IrcMessage;
class MessageFormatter;

class TextDocument : public QTextDocument
{
    Q_OBJECT

public:
    explicit TextDocument(IrcBuffer* buffer);

    IrcBuffer* buffer() const;

    int totalCount() const;

    bool isActive() const;
    void setActive(bool active);

    int note() const;
    void setNote(int note);

    void addMarker(int block = -1);
    void removeMarker(int block);

    void addHighlight(int block = -1);
    void removeHighlight(int block);

    void drawMarkers(QPainter* painter, const QRect& bounds);
    void drawHighlights(QPainter* painter, const QRect& bounds);

public slots:
    void append(const QString& text, bool highlight = false);

protected:
    void updateBlock(int number);
    void timerEvent(QTimerEvent* event);

private slots:
    void flushLines();
    void receiveMessage(IrcMessage* message);

private:
    void appendLine(QTextCursor& cursor, const QString& line);

    struct Private {
        int note;
        int dirty;
        bool active;
        IrcBuffer* buffer;
        QStringList lines;
        QList<int> markers;
        QList<int> highlights;
        MessageFormatter* formatter;
    } d;
};

#endif // TEXTDOCUMENT_H
