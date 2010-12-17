/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** No Commercial Usage
**
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef PASTEVIEW_H
#define PASTEVIEW_H

#include "ui_pasteview.h"
#include "splitter.h"

#include <QtGui/QDialog>

namespace CodePaster {
class Protocol;
class PasteView : public QDialog
{
    Q_OBJECT
public:
    explicit PasteView(const QList<Protocol *> protocols,
                       const QString &mimeType,
                       QWidget *parent);
    ~PasteView();

    int show(const QString &user, const QString &description, const QString &comment,
             const FileDataList &parts);

    void setProtocol(const QString &protocol);

    QString user() const;
    QString description() const;
    QString comment() const;
    QByteArray content() const;
    QString protocol() const;

    virtual void accept();

private slots:
    void contentChanged();
    void protocolChanged(int);

private:
    const QList<Protocol *> m_protocols;
    const QString m_commentPlaceHolder;
    const QString m_mimeType;

    Ui::ViewDialog m_ui;
    FileDataList m_parts;
};
} // namespace CodePaster
#endif // VIEW_H
