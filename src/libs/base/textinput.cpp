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

#include "textinput.h"
#include <IrcCommandParser>
#include <IrcBufferModel>
#include <IrcConnection>
#include <IrcBuffer>

TextInput::TextInput(QWidget* parent) : QLineEdit(parent)
{
    setAttribute(Qt::WA_MacShowFocusRect, false);

    d.buffer = 0;
    d.parser = 0;

    connect(this, SIGNAL(returnPressed()), this, SLOT(sendInput()));
}

IrcBuffer* TextInput::buffer() const
{
    return d.buffer;
}

IrcCommandParser* TextInput::parser() const
{
    return d.parser;
}

static void bind(IrcBuffer* buffer, IrcCommandParser* parser)
{
    if (buffer && parser) {
        IrcBufferModel* model = buffer->model();
        QObject::connect(model, SIGNAL(channelsChanged(QStringList)), parser, SLOT(setChannels(QStringList)));
        QObject::connect(buffer, SIGNAL(titleChanged(QString)), parser, SLOT(setTarget(QString)));

        parser->setTarget(buffer->title());
        parser->setChannels(buffer->model()->channels());
    } else if (parser) {
        parser->reset();
    }
}

static void unbind(IrcBuffer* buffer, IrcCommandParser* parser)
{
    if (buffer && parser) {
        IrcBufferModel* model = buffer->model();
        QObject::disconnect(model, SIGNAL(channelsChanged(QStringList)), parser, SLOT(setChannels(QStringList)));
        QObject::disconnect(buffer, SIGNAL(titleChanged(QString)), parser, SLOT(setTarget(QString)));
    }
}

void TextInput::setBuffer(IrcBuffer* buffer)
{
    if (d.buffer != buffer) {
        unbind(d.buffer, d.parser);
        bind(buffer, d.parser);
        d.buffer = buffer;
        emit bufferChanged(buffer);
    }
}

void TextInput::setParser(IrcCommandParser* parser)
{
    if (d.parser != parser) {
        unbind(d.buffer, d.parser);
        bind(d.buffer, parser);
        d.parser = parser;
        emit parserChanged(parser);
    }
}

void TextInput::sendInput()
{
    IrcBuffer* b = buffer();
    IrcCommandParser* p = parser();
    IrcConnection* c = b ? b->connection() : 0;
    if (!c || !p)
        return;

    bool error = false;
    const QStringList lines = text().split(QRegExp("[\\r\\n]"), QString::SkipEmptyParts);
    foreach (const QString& line, lines) {
        if (!line.trimmed().isEmpty()) {
            IrcCommand* cmd = p->parse(line);
            if (cmd) {
                b->sendCommand(cmd);
                if (cmd->type() == IrcCommand::Message || cmd->type() == IrcCommand::Notice || cmd->type() == IrcCommand::CtcpAction)
                    b->receiveMessage(cmd->toMessage(c->nickName(), c));
            } else {
                error = true;
            }
        }
    }
    if (!error)
        clear();
}
