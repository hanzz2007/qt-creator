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

#ifndef IFILEWIZARDEXTENSION_H
#define IFILEWIZARDEXTENSION_H

#include <coreplugin/core_global.h>

#include <QtCore/QObject>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE
class QWizardPage;
QT_END_NAMESPACE

namespace Core {

class IWizard;
class GeneratedFile;

/*!
  Hook to add generic wizard pages to implementations of IWizard.
  Used e.g. to add "Add to Project File/Add to version control" page
  */
class CORE_EXPORT IFileWizardExtension : public QObject
{
    Q_OBJECT
public:
    /* Return a list of pages to be added to the Wizard (empty list if not
     * applicable). */
    virtual QList<QWizardPage *> extensionPages(const IWizard *wizard) = 0;

    /* Process the files using the extension parameters */
    virtual bool process(const QList<GeneratedFile> &files,
                         bool *removeOpenProjectAttribute,
                         QString *errorMessage) = 0;

public slots:
    /* Notification about the first extension page being shown. */
    virtual void firstExtensionPageShown(const QList<GeneratedFile> &files) {
        Q_UNUSED(files)
        }
};

} // namespace Core

#endif // IFILEWIZARDEXTENSION_H
