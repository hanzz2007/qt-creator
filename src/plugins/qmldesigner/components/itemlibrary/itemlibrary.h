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

#ifndef ITEMLIBRARY_H
#define ITEMLIBRARY_H

#include "itemlibraryinfo.h"
#include <QtGui/QFrame>

namespace QmlDesigner {

class ItemLibraryPrivate;
class MetaInfo;
class ItemLibraryEntry;

class ItemLibrary : public QFrame
{
    Q_OBJECT
    Q_DISABLE_COPY(ItemLibrary)

public:
    ItemLibrary(QWidget *parent = 0);
    virtual ~ItemLibrary();

    void setItemLibraryInfo(ItemLibraryInfo *itemLibraryInfo);

public Q_SLOTS:
    void setSearchFilter(const QString &searchFilter);
    void updateModel();
    void updateSearch();

    void setResourcePath(const QString &resourcePath);

    void startDragAndDrop(int itemLibId);
    void showItemInfo(int itemLibId);

protected:
    void wheelEvent(QWheelEvent *event);

signals:
    void itemActivated(const QString& itemName);
    void scrollItemsView(QVariant delta);
    void resetItemsView();

private:
    ItemLibraryPrivate *m_d;
};

}

#endif // ITEMLIBRARY_H

