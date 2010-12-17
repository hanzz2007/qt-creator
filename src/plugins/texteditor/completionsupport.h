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

#ifndef COMPLETIONSUPPORT_H
#define COMPLETIONSUPPORT_H

#include <texteditor/texteditor_global.h>

#include <QtCore/QObject>

namespace TextEditor {

class CompletionItem;
class ICompletionCollector;
class ITextEditable;

namespace Internal {

class CompletionWidget;

/* Completion support is responsible for querying the list of completion collectors
   and popping up the CompletionWidget with the available completions.
 */
class TEXTEDITOR_EXPORT CompletionSupport : public QObject
{
    Q_OBJECT

public:
    CompletionSupport();

    static CompletionSupport *instance();

    bool isActive() const;

public slots:
    void autoComplete(TextEditor::ITextEditable *editor, bool forced);
    void quickFix(TextEditor::ITextEditable *editor);

private slots:
    void performCompletion(const TextEditor::CompletionItem &item);
    void cleanupCompletions();

private:
    QList<CompletionItem> getCompletions() const;
    void autoComplete_helper(ITextEditable *editor, bool forced, bool quickFix);

    CompletionWidget *m_completionList;
    int m_startPosition;
    bool m_checkCompletionTrigger;          // Whether to check for completion trigger after cleanup
    ITextEditable *m_editor;
    QList<ICompletionCollector *> m_completionCollectors;
    ICompletionCollector *m_completionCollector;
};

} // namespace Internal
} // namespace TextEditor

#endif // COMPLETIONSUPPORT_H

