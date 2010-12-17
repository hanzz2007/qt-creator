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

#ifndef BEHAVIORDIALOG_H
#define BEHAVIORDIALOG_H

#include <modelnode.h>
#include <propertyeditorvalue.h>

#include <QPushButton>
#include <QDialog>
#include <QWeakPointer>
#include <QScopedPointer>
#include <qdeclarative.h>

#include "ui_behaviordialog.h"

namespace QmlDesigner {

class BehaviorDialog;

class BehaviorWidget : public QPushButton
{
    Q_PROPERTY(PropertyEditorNodeWrapper* complexNode READ complexNode WRITE setComplexNode)

    Q_OBJECT

public:

    BehaviorWidget();
    BehaviorWidget(QWidget* parent);

    ModelNode modelNode() const {return m_modelNode; }
    QString propertyName() const {return m_propertyName; }

    PropertyEditorNodeWrapper* complexNode() const;
    void setComplexNode(PropertyEditorNodeWrapper* complexNode);

public slots:
    void buttonPressed(bool);

private:
    ModelNode m_modelNode;
    QString m_propertyName;
    PropertyEditorNodeWrapper* m_complexNode;
    QScopedPointer<BehaviorDialog> m_BehaviorDialog;
};

class BehaviorDialog : public QDialog
{
    Q_OBJECT
public:
    BehaviorDialog(QWidget *parent);
    void setup(const ModelNode &node, const QString propertyName);

public slots:
    virtual void accept();
    virtual void reject();

    static void registerDeclarativeType();

private:
    ModelNode m_modelNode;
    QString m_propertyName;
    QScopedPointer<Ui_BehaviorDialog> m_ui;
};


};

QML_DECLARE_TYPE(QmlDesigner::BehaviorWidget);

#endif// BEHAVIORDIALOG_H
