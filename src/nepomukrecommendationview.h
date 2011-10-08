/***************************************************************************
 *   Copyright (C) 2011 by Phaneendra Hegde <pnh.pes@gmail.com>                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef NEPOMUKRECOMMENDATIONVIEW_H
#define NEPOMUKRECOMMENDATIONVIEW_H

#include <QtGui/QWidget>

#include "ui_nepomukrecommendationview_base.h"
#include <Nepomuk/Utils/SimpleResourceModel>

class QPainter;
class KUrl;

/**
 * This is the main view class for nepomukrecommendation.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Phaneendra Hegde <pnh.pes@gmail.com>
 * @version 1.0
 */

class nepomukrecommendationView : public QWidget, public Ui::nepomukrecommendationview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    nepomukrecommendationView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~nepomukrecommendationView();
       void resourceQuery();

private:
    Ui::nepomukrecommendationview_base ui_nepomukrecommendationview_base;
    Nepomuk::Utils::SimpleResourceModel *m_resourceModel;

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);


private slots:
    void switchColors();
    void settingsChanged();

    void on_searchBox_returnPressed(QString );
};

#endif // nepomukrecommendationVIEW_H
