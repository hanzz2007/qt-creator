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

#ifndef CONSOLEPROCESS_H
#define CONSOLEPROCESS_H

#include "abstractprocess.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/QScopedPointer>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

namespace Utils {
struct ConsoleProcessPrivate;

class QTCREATOR_UTILS_EXPORT ConsoleProcess : public QObject, public AbstractProcess
{
    Q_OBJECT

public:
    enum Mode { Run, Debug, Suspend };
    ConsoleProcess(QObject *parent = 0);
    ~ConsoleProcess();

    bool start(const QString &program, const QStringList &args);
    void stop();

    void setMode(Mode m);
    Mode mode() const;

    bool isRunning() const; // This reflects the state of the console+stub
    qint64 applicationPID() const;

#ifdef Q_OS_WIN
    qint64 applicationMainThreadID() const;
#endif

    int exitCode() const;
    QProcess::ExitStatus exitStatus() const;

#ifdef Q_OS_UNIX
    void setSettings(QSettings *settings);
    static QString defaultTerminalEmulator();
    static QString terminalEmulator(const QSettings *settings);
    static void setTerminalEmulator(QSettings *settings, const QString &term);
#endif

signals:
    void processMessage(const QString &message, bool isError);
    // These reflect the state of the actual client process
    void processStarted();
    void processStopped();

    // These reflect the state of the console+stub
    void wrapperStarted();
    void wrapperStopped();

private slots:
    void stubConnectionAvailable();
    void readStubOutput();
    void stubExited();
#ifdef Q_OS_WIN
    void inferiorExited();
#endif

private:
    static QString modeOption(Mode m);
    static QString msgCommChannelFailed(const QString &error);
    static QString msgPromptToClose();
    static QString msgCannotCreateTempFile(const QString &why);
    static QString msgCannotCreateTempDir(const QString & dir, const QString &why);
    static QString msgUnexpectedOutput(const QByteArray &what);
    static QString msgCannotChangeToWorkDir(const QString & dir, const QString &why);
    static QString msgCannotExecute(const QString & p, const QString &why);

    QString stubServerListen();
    void stubServerShutdown();
#ifdef Q_OS_WIN
    void cleanupStub();
    void cleanupInferior();
#endif

    QScopedPointer<ConsoleProcessPrivate> d;
};

} //namespace Utils

#endif
