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

#include "moduleshandler.h"
#include "debuggerengine.h"

#include <utils/qtcassert.h>

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QTextStream>

#include <QtGui/QAction>
#include <QtGui/QMainWindow>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>


//////////////////////////////////////////////////////////////////
//
// ModulesModel
//
//////////////////////////////////////////////////////////////////

namespace Debugger {
namespace Internal {

class ModulesModel : public QAbstractItemModel
{   // Needs tr - context.
    Q_OBJECT
public:
    explicit ModulesModel(ModulesHandler *parent, DebuggerEngine *engine);

    // QAbstractItemModel
    int columnCount(const QModelIndex &parent) const
        { return parent.isValid() ? 0 : 5; }
    int rowCount(const QModelIndex &parent) const
        { return parent.isValid() ? 0 : m_modules.size(); }
    QModelIndex parent(const QModelIndex &) const { return QModelIndex(); }
    QModelIndex index(int row, int column, const QModelIndex &) const
        { return createIndex(row, column); }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void clearModel();
    void addModule(const Module &module);
    void removeModule(const QString &moduleName);
    void setModules(const Modules &modules);
    void updateModule(const QString &moduleName, const Module &module);

    const Modules &modules() const { return m_modules; }

private:
    int indexOfModule(const QString &name) const;

    DebuggerEngine *m_engine;
    Modules m_modules;
};

ModulesModel::ModulesModel(ModulesHandler *parent, DebuggerEngine *engine)
  : QAbstractItemModel(parent), m_engine(engine)
{}

QVariant ModulesModel::headerData(int section,
    Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        static QString headers[] = {
            tr("Module name") + "        ",
            tr("Module path") + "        ",
            tr("Symbols read") + "        ",
            tr("Symbols type") + "        ",
            tr("Start address") + "        ",
            tr("End address") + "        "
        };
        return headers[section];
    }
    return QVariant();
}

QVariant ModulesModel::data(const QModelIndex &index, int role) const
{
    if (role == EngineCapabilitiesRole)
        return m_engine->debuggerCapabilities();

    if (role == EngineActionsEnabledRole)
        return m_engine->debuggerActionsEnabled();

    int row = index.row();
    if (row < 0 || row >= m_modules.size())
        return QVariant();

    const Module &module = m_modules.at(row);

    switch (index.column()) {
        case 0:
            if (role == Qt::DisplayRole)
                return module.moduleName;
            // FIXME: add icons
            //if (role == Qt::DecorationRole)
            //    return module.symbolsRead ? icon2 : icon;
            break;
        case 1:
            if (role == Qt::DisplayRole)
                return module.modulePath;
            break;
        case 2:
            if (role == Qt::DisplayRole)
                switch (module.symbolsRead) {
                    case Module::UnknownReadState: return tr("unknown");
                    case Module::ReadFailed: return tr("no");
                    case Module::ReadOk: return tr("yes");
                }
            break;
        case 3:
            if (role == Qt::DisplayRole)
                switch (module.symbolsType) {
                    case Module::UnknownType: return tr("unknown");
                    case Module::PlainSymbols: return tr("plain");
                    case Module::FastSymbols: return tr("fast");
                }
            break;
        case 4:
            if (role == Qt::DisplayRole)
                return module.startAddress;
            break;
        case 5:
            if (role == Qt::DisplayRole)
                return module.endAddress;
            break;
    }
    return QVariant();
}

bool ModulesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);

    switch (role) {
        case RequestReloadModulesRole:
            m_engine->reloadModules();
            return true;

        case RequestExamineModulesRole:
            m_engine->examineModules();
            return true;

        case RequestModuleSymbolsRole:
            m_engine->loadSymbols(value.toString());
            return true;

        case RequestAllSymbolsRole:
            m_engine->loadAllSymbols();
            return true;

        case RequestOpenFileRole:
            m_engine->openFile(value.toString());
            return true;
    }
    return false;
}

void ModulesModel::addModule(const Module &m)
{
    beginInsertRows(QModelIndex(), m_modules.size(), m_modules.size());
    m_modules.push_back(m);
    endInsertRows();
}

void ModulesModel::setModules(const Modules &m)
{
    m_modules = m;
    reset();
}

void ModulesModel::clearModel()
{
    if (!m_modules.isEmpty()) {
        m_modules.clear();
        reset();
    }
}

int ModulesModel::indexOfModule(const QString &name) const
{
    // Recent modules are more likely to be unloaded first.
    for (int i = m_modules.size() - 1; i >= 0; i--)
        if (m_modules.at(i).moduleName == name)
            return i;
    return -1;
}

void ModulesModel::removeModule(const QString &moduleName)
{
    const int index = indexOfModule(moduleName);
    QTC_ASSERT(index != -1, return);
    beginRemoveRows(QModelIndex(), index, index);
    m_modules.removeAt(index);
    endRemoveRows();
}

void ModulesModel::updateModule(const QString &moduleName, const Module &module)
{
    const int index = indexOfModule(moduleName);
    QTC_ASSERT(index != -1, return);
    m_modules[index] = module;
    reset();
}

//////////////////////////////////////////////////////////////////
//
// ModulesHandler
//
//////////////////////////////////////////////////////////////////

ModulesHandler::ModulesHandler(DebuggerEngine *engine)
{
    m_model = new ModulesModel(this, engine);
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
}

QAbstractItemModel *ModulesHandler::model() const
{
    return m_proxyModel;
}

void ModulesHandler::removeAll()
{
    m_model->clearModel();
}

void ModulesHandler::addModule(const Module &module)
{
    m_model->addModule(module);
}

void ModulesHandler::removeModule(const QString &moduleName)
{
    m_model->removeModule(moduleName);
}

void ModulesHandler::updateModule(const QString &moduleName, const Module &module)
{
    m_model->updateModule(moduleName, module);
}

void ModulesHandler::setModules(const Modules &modules)
{
    m_model->setModules(modules);
}

Modules ModulesHandler::modules() const
{
    return m_model->modules();
}

} // namespace Internal
} // namespace Debugger

#include "moduleshandler.moc"
