/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kaj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef KAJRESTMODULE_H
#define KAJRESTMODULE_H

#include <QtCore/qglobal.h>
#include <QQmlExtensionPlugin>

#define KAJ_PACKAGE_NAME "Kaj.Rest"
#define KAJ_VERSION_MAJOR 1
#define KAJ_VERSION_MINOR 0

class QQmlEngine;
class KajRestModule : public QQmlExtensionPlugin
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    static void registerTypes();
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};



#endif // KAJRESTMODULE_H
