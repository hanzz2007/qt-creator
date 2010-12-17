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


#ifndef DESIGNERSETTINGS_H
#define DESIGNERSETTINGS_H

#include <QtCore/QtGlobal>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

namespace QmlDesigner {

class DesignerSettings {
public:
    DesignerSettings();

    void fromSettings(QSettings *);
    void toSettings(QSettings *) const;

    bool equals(const DesignerSettings &other) const;
    bool openDesignMode;
    int itemSpacing;
    int snapMargin;    
};

inline bool operator==(const DesignerSettings &s1, const DesignerSettings &s2)
{ return s1.equals(s2); }
inline bool operator!=(const DesignerSettings &s1, const DesignerSettings &s2)
{ return !s1.equals(s2); }

} // namespace QmlDesigner

#endif // DESIGNERSETTINGS_H
