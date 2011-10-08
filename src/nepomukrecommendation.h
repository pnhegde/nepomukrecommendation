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

#ifndef NEPOMUKRECOMMENDATION_H
#define NEPOMUKRECOMMENDATION_H


#include <KXmlGuiWindow>
#include <Nepomuk/Utils/SimpleResourceModel>
#include "ui_prefs_base.h"

class nepomukrecommendationView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for nepomukrecommendation.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Phaneendra Hegde <pnh.pes@gmail.com>
 * @version 1.0
 */
class nepomukrecommendation : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    nepomukrecommendation();

    /**
     * Default Destructor
     */
    virtual ~nepomukrecommendation();

private slots:
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    nepomukrecommendationView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;

};

#endif // _NEPOMUKRECOMMENDATION_H_
