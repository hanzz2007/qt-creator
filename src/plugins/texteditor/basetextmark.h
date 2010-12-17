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

#ifndef BASETEXTMARK_H
#define BASETEXTMARK_H

#include "itexteditor.h"
#include <QtGui/QIcon>

namespace TextEditor {

class ITextMarkable;

namespace Internal {
class InternalMark;
}

class TEXTEDITOR_EXPORT BaseTextMark : public QObject
{
    friend class Internal::InternalMark;
    Q_OBJECT

public:
    BaseTextMark(const QString &filename, int line);
    ~BaseTextMark();

    // return your icon here
    virtual QIcon icon() const = 0;

    // called if the linenumber changes
    virtual void updateLineNumber(int lineNumber) = 0;

    // called whenever the text of the block for the marker changed
    virtual void updateBlock(const QTextBlock &block) = 0;

    // called if the block containing this mark has been removed
    // if this also removes your mark call this->deleteLater();
    virtual void removedFromEditor() = 0;
    // call this if the icon has changed.
    void updateMarker();
    // access to internal data
    QString fileName() const { return m_fileName; }
    int lineNumber() const { return m_line; }

    void moveMark(const QString &filename, int line);

private slots:
    void init();
    void editorOpened(Core::IEditor *editor);
    void documentReloaded();

private:
    void childRemovedFromEditor(Internal::InternalMark *mark);
    void documentClosingFor(Internal::InternalMark *mark);
    void removeInternalMark();

    ITextMarkable *m_markableInterface;
    Internal::InternalMark *m_internalMark;

    QString m_fileName;
    int m_line;
    bool m_init;
};

namespace Internal {

class InternalMark : public ITextMark
{
public:
    InternalMark(BaseTextMark *parent)
        : m_parent(parent)
    {
    }

    ~InternalMark()
    {
    }

    virtual QIcon icon() const
    {
        return m_parent->icon();
    }

    virtual void updateLineNumber(int lineNumber)
    {
        return m_parent->updateLineNumber(lineNumber);
    }

    virtual void updateBlock(const QTextBlock &block)
    {
        return m_parent->updateBlock(block);
    }

    virtual void removedFromEditor()
    {
        m_parent->childRemovedFromEditor(this);
    }

    virtual void documentClosing()
    {
        m_parent->documentClosingFor(this);
    }
private:
    BaseTextMark *m_parent;
};

} // namespace Internal
} // namespace TextEditor

#endif // BASETEXTMARK_H
