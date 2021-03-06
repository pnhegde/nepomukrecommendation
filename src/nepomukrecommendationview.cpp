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
#include <QDebug>
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
    m_recommendationModel = new Nepomuk::Utils::SimpleResourceModel(this);
    ui_nepomukrecommendationview_base.resourceView->setModel(m_resourceModel);
    ui_nepomukrecommendationview_base.resourceView->setViewMode(ui_nepomukrecommendationview_base.resourceView->IconMode);
    ui_nepomukrecommendationview_base.recommendationView->setModel(m_recommendationModel);
   // ui_nepomukrecommendationview_base.recommendationView->setViewMode(ui_nepomukrecommendationview_base.recommendationView->IconMode);
    connect(ui_nepomukrecommendationview_base.resourceView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(resourceSelected()));
    resourceQuery();

}

nepomukrecommendationView::~nepomukrecommendationView()
{

}

void nepomukrecommendationView::resourceSelected()
{
    Nepomuk::Resource rsc = m_resourceModel->resourceForIndex(ui_nepomukrecommendationview_base.resourceView->selectionModel()->currentIndex() );
    QList<Nepomuk::Resource> relatedResourceList = rsc.isRelateds();
    if( relatedResourceList.isEmpty() ) {
        m_recommendationModel->setResources(resourceSearch(rsc.label()));
        qDebug()<<rsc.label();
    }
    else {
        m_recommendationModel->setResources(relatedResourceList);
    }

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

    m_resourceModel->clear();
    Nepomuk::Query::Term term = Nepomuk::Query::ResourceTypeTerm( Nepomuk::Vocabulary::PIMO::Person() );
    Nepomuk::Query::Query query( term );
    query.setLimit( 10 );
    QList<Nepomuk::Query::Result>results = Nepomuk::Query::QueryServiceClient::syncQuery( query );
    QList <Nepomuk::Resource> resource;
    Q_FOREACH( const Nepomuk::Query::Result& result, results ) {
        resource.append( result.resource() );
    }
    m_resourceModel->setResources( resource );
}


void nepomukrecommendationView::on_searchBox_returnPressed(QString str )
{

    if( str=="" ) {
        resourceQuery();
    }
    else {
       m_resourceModel->setResources( resourceSearch(str) );
    }
}

QList<Nepomuk::Resource> nepomukrecommendationView::resourceSearch(const QString str)
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
    return resource;

}
#include "nepomukrecommendationview.moc"
