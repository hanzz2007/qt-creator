/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef DEBUGGERLANGUAGECHOOSER_H
#define DEBUGGERLANGUAGECHOOSER_H

#include "utils_global.h"

#include <QtGui/QWidget>

QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSpinBox)

namespace Utils {

class QTCREATOR_UTILS_EXPORT DebuggerLanguageChooser : public QWidget
{
    Q_OBJECT
public:
    explicit DebuggerLanguageChooser(QWidget *parent = 0);

    bool cppChecked() const;
    bool qmlChecked() const;
    uint qmlDebugServerPort() const;

    void setCppChecked(bool value);
    void setQmlChecked(bool value);
    void setQmlDebugServerPort(uint port);

signals:
    void cppLanguageToggled(bool value);
    void qmlLanguageToggled(bool value);
    void qmlDebugServerPortChanged(uint port);

private slots:
    void useCppDebuggerToggled(bool toggled);
    void useQmlDebuggerToggled(bool toggled);
    void onDebugServerPortChanged(int port);

private:
    QCheckBox *m_useCppDebugger;
    QCheckBox *m_useQmlDebugger;
    QSpinBox *m_debugServerPort;
    QLabel *m_debugServerPortLabel;
};

} // namespace Utils

#endif // DEBUGGERLANGUAGECHOOSER_H
