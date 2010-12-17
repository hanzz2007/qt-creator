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

#ifndef PROJECTEXPLORERSETTINGSPAGE_H
#define PROJECTEXPLORERSETTINGSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>
#include "ui_projectexplorersettingspage.h"

#include <QtCore/QPointer>

namespace ProjectExplorer {
namespace Internal {

struct ProjectExplorerSettings;

class ProjectExplorerSettingsWidget : public QWidget {
    Q_OBJECT
public:
    explicit ProjectExplorerSettingsWidget(QWidget *parent = 0);

    ProjectExplorerSettings settings() const;
    void setSettings(const ProjectExplorerSettings  &s) const;

    QString projectsDirectory() const;
    void setProjectsDirectory(const QString &pd);

    bool useProjectsDirectory();
    void setUseProjectsDirectory(bool v);

    QString searchKeywords() const;

private slots:
    void slotDirectoryButtonGroupChanged();

private:
    void setJomVisible(bool);

    Ui::ProjectExplorerSettingsPageUi m_ui;
};

class ProjectExplorerSettingsPage : public Core::IOptionsPage
{
    Q_OBJECT
public:
    ProjectExplorerSettingsPage();

    virtual QString id() const;
    virtual QString displayName() const;
    virtual QString category() const;
    virtual QString displayCategory() const;
    virtual QIcon categoryIcon() const;

    virtual QWidget *createPage(QWidget *parent);
    virtual void apply();
    virtual void finish();
    virtual bool matches(const QString &s) const;

private:
    QString m_searchKeywords;
    QPointer<ProjectExplorerSettingsWidget> m_widget;
};

} // Internal
} // ProjectExplorer

#endif // PROJECTEXPLORERSETTINGSPAGE_H
