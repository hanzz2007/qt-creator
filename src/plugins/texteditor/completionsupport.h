/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
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
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef COMPLETIONSUPPORT_H
#define COMPLETIONSUPPORT_H

#include <texteditor/texteditor_global.h>

#include <QtCore/QObject>

namespace TextEditor {

class CompletionItem;
class ICompletionCollector;
class ITextEditable;

class CompletionSupportPrivate;

/* Completion support is responsible for querying the list of completion collectors
   and popping up the CompletionWidget with the available completions.
 */
class TEXTEDITOR_EXPORT CompletionSupport : public QObject
{
    Q_OBJECT

public:
    virtual ~CompletionSupport();

    static CompletionSupport *instance();

    bool isActive() const;

public slots:
    void autoComplete(TextEditor::ITextEditable *editor, bool forced);
    void quickFix(TextEditor::ITextEditable *editor);

private slots:
    void performCompletion(const TextEditor::CompletionItem &item);
    void cleanupCompletions();

private:
    CompletionSupport();

    QList<CompletionItem> getCompletions() const;
    void autoComplete_helper(ITextEditable *editor, bool forced, bool quickFix);

    QScopedPointer<CompletionSupportPrivate> d;
};

} // namespace TextEditor

#endif // COMPLETIONSUPPORT_H

