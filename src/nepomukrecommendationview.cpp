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

#include "nepomukrecommendationview.h"
#include "settings.h"

#include <KLocale>
#include <QtGui/QLabel>
#include <Nepomuk/Query/Term>
#include <Nepomuk/Query/Result>
#include <Nepomuk/Query/ResourceTypeTerm>
#include <Nepomuk/Query/ComparisonTerm>
#include <Nepomuk/Query/LiteralTerm>
#include <Nepomuk/Query/QueryServiceClient>
#include <Nepomuk/Vocabulary/PIMO>
#include <Nepomuk/Vocabulary/NCO>
#include <Nepomuk/Vocabulary/NFO>
#include <Soprano/Vocabulary/NAO>
#include <Nepomuk/Vocabulary/NIE>
#include <Nepomuk/Query/QueryParser>
#include <Nepomuk/Variant>




nepomukrecommendationView::nepomukrecommendationView(QWidget *)
{
    ui_nepomukrecommendationview_base.setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
    m_resourceModel = new Nepomuk::Utils::SimpleResourceModel(this);
    ui_nepomukrecommendationview_base.resourceView->setModel(m_resourceModel);
    //resourceQuery();

}

nepomukrecommendationView::~nepomukrecommendationView()
{

}

void nepomukrecommendationView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

void nepomukrecommendationView::settingsChanged()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::col_background());
    pal.setColor( QPalette::WindowText, Settings::col_foreground());
   // ui_nepomukrecommendationview_base.kcfg_sillyLabel->setPalette( pal );

    // i18n : internationalization
    //ui_nepomukrecommendationview_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
    emit signalChangeStatusbar( i18n("Settings changed") );
}
void nepomukrecommendationView::resourceQuery()
{




}



void nepomukrecommendationView::on_searchBox_returnPressed(QString str )
{

    Nepomuk::Query::ComparisonTerm linkTerm(Nepomuk::Vocabulary::NIE::plainTextContent(),
      Nepomuk::Query::LiteralTerm(str));

  //linkTerm.setVariableName(QLatin1String("text"));
  Nepomuk::Query::Query query(linkTerm);
  query.addRequestProperty(Nepomuk::Query::Query::RequestProperty(Nepomuk::Vocabulary::NIE::lastModified()));

  QList<Nepomuk::Query::Result>results = Nepomuk::Query::QueryServiceClient::syncQuery( query );
  QList<Nepomuk::Resource> resource;
  Q_FOREACH( const Nepomuk::Query::Result& result, results ) {
          resource.append( result.resource() );
      }
  m_resourceModel->setResources( resource );
}
#include "nepomukrecommendationview.moc"
