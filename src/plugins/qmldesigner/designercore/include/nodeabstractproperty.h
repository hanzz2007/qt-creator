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

#ifndef NODEABSTRACTPROPERTY_H
#define NODEABSTRACTPROPERTY_H

#include "abstractproperty.h"

namespace QmlDesigner {

namespace Internal {
    class InternalNodeAbstractProperty;
    typedef QSharedPointer<InternalNodeAbstractProperty> InternalNodeAbstractPropertyPointer;
}

class NodeAbstractProperty : public AbstractProperty
{
    friend class QmlDesigner::ModelNode;
    friend class QmlDesigner::Internal::ModelPrivate;
    friend class QmlDesigner::AbstractProperty;
public:
    NodeAbstractProperty();
    NodeAbstractProperty(const NodeAbstractProperty &property, AbstractView *view);
    void reparentHere(const ModelNode &modelNode);
    bool isEmpty() const;

    QList<ModelNode> allSubNodes();

protected:
    NodeAbstractProperty(const QString &propertyName, const Internal::InternalNodePointer &internalNode, Model *model, AbstractView *view);
    NodeAbstractProperty(const Internal::InternalNodeAbstractPropertyPointer &property, Model *model, AbstractView *view);
    void reparentHere(const ModelNode &modelNode, bool isNodeList);
};

} // namespace QmlDesigner

#endif // NODEABSTRACTPROPERTY_H
