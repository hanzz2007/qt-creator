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

#ifndef QMLJSCOMPLETIONCONTEXTFINDER_H
#define QMLJSCOMPLETIONCONTEXTFINDER_H

#include "qmljs_global.h"
#include <qmljs/qmljslineinfo.h>

#include <QtCore/QStringList>
#include <QtGui/QTextCursor>

namespace QmlJS {

class QMLJS_EXPORT CompletionContextFinder : public LineInfo
{
public:
    CompletionContextFinder(const QTextCursor &cursor);

    QStringList qmlObjectTypeName() const;
    bool isInQmlContext() const;

    bool isInLhsOfBinding() const;
    bool isInRhsOfBinding() const;

    bool isAfterOnInLhsOfBinding() const;
    QStringList bindingPropertyName() const;

private:
    int findOpeningBrace(int startTokenIndex);
    void getQmlObjectTypeName(int startTokenIndex);
    void checkBinding();

    QTextCursor m_cursor;
    QStringList m_qmlObjectTypeName;
    QStringList m_bindingPropertyName;
    int m_startTokenIndex;
    int m_colonCount;
    bool m_behaviorBinding;
};

} // namespace QmlJS

#endif // QMLJSCOMPLETIONCONTEXTFINDER_H
