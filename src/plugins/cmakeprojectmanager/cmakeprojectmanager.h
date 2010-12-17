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

#ifndef CMAKEPROJECTMANAGER_H
#define CMAKEPROJECTMANAGER_H

#include <coreplugin/dialogs/ioptionspage.h>
#include <projectexplorer/iprojectmanager.h>
#include <utils/environment.h>
#include <utils/pathchooser.h>
#include <QtCore/QFuture>
#include <QtCore/QStringList>
#include <QtCore/QDir>

QT_FORWARD_DECLARE_CLASS(QProcess)
QT_FORWARD_DECLARE_CLASS(QLabel)

namespace CMakeProjectManager {
namespace Internal {

class CMakeSettingsPage;

class CMakeManager : public ProjectExplorer::IProjectManager
{
    Q_OBJECT
public:
    CMakeManager(CMakeSettingsPage *cmakeSettingsPage);

    virtual Core::Context projectContext() const;
    virtual Core::Context projectLanguage() const;

    virtual ProjectExplorer::Project *openProject(const QString &fileName);
    virtual QString mimeType() const;

    QString cmakeExecutable() const;
    bool isCMakeExecutableValid() const;

    void setCMakeExecutable(const QString &executable);

    void createXmlFile(QProcess *process,
                       const QStringList &arguments,
                       const QString &sourceDirectory,
                       const QDir &buildDirectory,
                       const Utils::Environment &env,
                       const QString &generator);
    bool hasCodeBlocksMsvcGenerator() const;
    static QString findCbpFile(const QDir &);

    static QString findDumperLibrary(const Utils::Environment &env);
private:
    static QString qtVersionForQMake(const QString &qmakePath);
    static QPair<QString, QString> findQtDir(const Utils::Environment &env);
    Core::Context m_projectContext;
    Core::Context m_projectLanguage;
    CMakeSettingsPage *m_settingsPage;
};

class CMakeSettingsPage : public Core::IOptionsPage
{
    Q_OBJECT
public:
    CMakeSettingsPage();
    virtual ~CMakeSettingsPage();
    virtual QString id() const;
    virtual QString displayName() const;
    virtual QString category() const;
    virtual QString displayCategory() const;
    virtual QIcon categoryIcon() const;

    virtual QWidget *createPage(QWidget *parent);
    virtual void apply();
    virtual void finish();

    QString cmakeExecutable() const;
    void setCMakeExecutable(const QString &executable);
    bool isCMakeExecutableValid();
    bool hasCodeBlocksMsvcGenerator() const;
private slots:
    void cmakeFinished();
private:
    void saveSettings() const;
    void startProcess();
    QString findCmakeExecutable() const;
    void updateInfo();

    Utils::PathChooser *m_pathchooser;
    QString m_cmakeExecutable;
    enum STATE { VALID, INVALID, RUNNING } m_state;
    QProcess *m_process;
    QString m_version;
    bool m_hasCodeBlocksMsvcGenerator;
};

} // namespace Internal
} // namespace CMakeProjectManager

#endif // CMAKEPROJECTMANAGER_H
