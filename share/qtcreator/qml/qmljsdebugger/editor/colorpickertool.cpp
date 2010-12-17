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

#include "colorpickertool.h"
#include "qdeclarativeviewobserver.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QRectF>
#include <QRgb>
#include <QImage>
#include <QApplication>
#include <QPalette>

namespace QmlJSDebugger {

ColorPickerTool::ColorPickerTool(QDeclarativeViewObserver *view) :
        AbstractFormEditorTool(view)
{
    m_selectedColor.setRgb(0,0,0);
}

ColorPickerTool::~ColorPickerTool()
{

}

void ColorPickerTool::mousePressEvent(QMouseEvent * /*event*/)
{
}

void ColorPickerTool::mouseMoveEvent(QMouseEvent *event)
{
    pickColor(event->pos());
}

void ColorPickerTool::mouseReleaseEvent(QMouseEvent *event)
{
    pickColor(event->pos());
}

void ColorPickerTool::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
}


void ColorPickerTool::hoverMoveEvent(QMouseEvent * /*event*/)
{
}

void ColorPickerTool::keyPressEvent(QKeyEvent * /*event*/)
{
}

void ColorPickerTool::keyReleaseEvent(QKeyEvent * /*keyEvent*/)
{
}
void ColorPickerTool::wheelEvent(QWheelEvent * /*event*/)
{
}

void ColorPickerTool::itemsAboutToRemoved(const QList<QGraphicsItem*> &/*itemList*/)
{
}

void ColorPickerTool::clear()
{
    view()->setCursor(Qt::CrossCursor);
}

void ColorPickerTool::selectedItemsChanged(const QList<QGraphicsItem*> &/*itemList*/)
{
}

void ColorPickerTool::pickColor(const QPoint &pos)
{
    QRgb fillColor = view()->backgroundBrush().color().rgb();
    if (view()->backgroundBrush().style() == Qt::NoBrush)
        fillColor = view()->palette().color(QPalette::Base).rgb();

    QRectF target(0,0, 1, 1);
    QRect source(pos.x(), pos.y(), 1, 1);
    QImage img(1, 1, QImage::Format_ARGB32);
    img.fill(fillColor);
    QPainter painter(&img);
    view()->render(&painter, target, source);
    m_selectedColor = QColor::fromRgb(img.pixel(0, 0));

    emit selectedColorChanged(m_selectedColor);
}

} // namespace QmlJSDebugger
