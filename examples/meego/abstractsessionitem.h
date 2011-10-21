#ifndef ABSTRACTSESSIONITEM_H
#define ABSTRACTSESSIONITEM_H

#include <QObject>
#include <QStringListModel>
#include "messageformatter.h"

class IrcMessage;
class IrcSession;

class AbstractSessionItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IrcSession* session READ session)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)
    Q_PROPERTY(bool busy READ isBusy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(bool current READ isCurrent WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(bool highlighted READ isHighlighted WRITE setHighlighted NOTIFY highlightedChanged)
    Q_PROPERTY(int unread READ unread WRITE setUnread NOTIFY unreadChanged)
    Q_PROPERTY(int unseen READ unseen WRITE setUnseen NOTIFY unseenChanged)
    Q_PROPERTY(QStringList users READ users NOTIFY usersChanged)
    Q_PROPERTY(QObject* messages READ messages)

public:
    explicit AbstractSessionItem(QObject *parent = 0);

    IrcSession* session() const;

    QString title() const;
    QString subtitle() const;
    bool isBusy() const;
    bool isCurrent() const;
    bool isHighlighted() const;
    int unread() const;
    int unseen() const;

    QStringList users() const;
    QObject* messages() const;

    virtual void updateCurrent(AbstractSessionItem* item) = 0;

public slots:
    void setTitle(const QString& title);
    void setSubtitle(const QString& subtitle);
    void setBusy(bool busy);
    void setCurrent(bool current);
    void setHighlighted(bool highlighted);
    void setUnread(int unread);
    void setUnseen(int unseen);

signals:
    void titleChanged();
    void subtitleChanged();
    void busyChanged();
    void currentChanged();
    void highlightedChanged();
    void unreadChanged();
    void unseenChanged();
    void usersChanged();
    void alert(const QString& info);

protected slots:
    virtual void addUser(const QString& user);
    virtual void removeUser(const QString& user);
    virtual void receiveMessage(IrcMessage* message);

protected:
    void setSession(IrcSession* session);

private:
    IrcSession* m_session;
    QString m_title;
    QString m_subtitle;
    bool m_busy;
    bool m_current;
    bool m_highlighted;
    QStringList m_users;
    QStringListModel* m_messages;
    MessageFormatter m_formatter;
    int m_unread;
    int m_unseen;
};

#endif // ABSTRACTSESSIONITEM_H
