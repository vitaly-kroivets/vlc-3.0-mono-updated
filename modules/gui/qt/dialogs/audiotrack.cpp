/*****************************************************************************
 * audiotrack.cpp : Audio Track Controls
 ****************************************************************************
 * Copyright (C) 2007-2008 the VideoLAN team
 *
 * Authors: Antoine Lejeune <phytos@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dialogs/audiotrack.hpp"
#include "input_manager.hpp"

#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>

// #include "vlcplugin.h"
// #include "npolibvlc.h"



AudioTrackDialog::AudioTrackDialog( intf_thread_t *_p_intf ):QVLCFrame( _p_intf )
{
    b_ignore_updates = false;
    setWindowFlags( Qt::Tool );
    setWindowOpacity( var_InheritFloat( p_intf, "qt-opacity" ) );
    setWindowTitle( qtr( "Audio Tracks Mix" ) );
    setWindowRole( "vlc-audiotracks" );

    // VlcPluginBase* p_plugin = getPrivate<VlcPluginBase>();
    // auto &mp = p_plugin->getMD();

    QGridLayout *mainLayout = new QGridLayout( this );

    int trackCount = 2;

    for(int i = 0; i < trackCount; i++) {
        trackBox[i] = new QGroupBox("", this);
        // Set the position and size
        trackBox[i]->setGeometry(10, 10 + 90 * i, 400, 80);

        trackLabel[i * 4 + 0] = new QLabel("0", trackBox[i]);
        trackLabel[i * 4 + 0]->setGeometry(20, 60, 21, 16);
        trackLabel[i * 4 + 0]->show();

        trackLabel[i * 4 + 1] = new QLabel("100", trackBox[i]);
        trackLabel[i * 4 + 1]->setGeometry(174, 60, 31, 16);
        trackLabel[i * 4 + 1]->show();

        trackSlider[i * 2] = new QSlider(Qt::Horizontal, trackBox[i]);
        trackSlider[i * 2]->setGeometry(35, 60, 135, 16);
        trackSlider[i * 2]->setRange(0, 100);
        trackSlider[i * 2]->setValue(50);
        trackSlider[i * 2]->show();

        trackLabel[i * 4 + 2] = new QLabel("L", trackBox[i]);
        trackLabel[i * 4 + 2]->setGeometry(215, 60, 21, 16);
        trackLabel[i * 4 + 2]->show();

        trackLabel[i * 4 + 3] = new QLabel("R", trackBox[i]);
        trackLabel[i * 4 + 3]->setGeometry(379, 60, 21, 16);
        trackLabel[i * 4 + 3]->show();
        
        trackSlider[i * 2 + 1] = new QSlider(Qt::Horizontal, trackBox[i]);
        trackSlider[i * 2 + 1]->setGeometry(230, 60, 145, 16);
        trackSlider[i * 2 + 1]->show();

        infoLabel[i * 2] = new QLabel(QString::number(i + 1) + "." + "Track", trackBox[i]);
        infoLabel[i * 2]->setGeometry(20, 25, 150, 16);
        infoLabel[i * 2]->show();

        infoLabel[i * 2 + 1] = new QLabel("44.1khz Stereo PCM", trackBox[i]);
        infoLabel[i * 2 + 1]->setGeometry(215, 25, 150, 16);
        infoLabel[i * 2 + 1]->show();

        trackBox[i]->show();
        mainLayout->addWidget(trackBox[i]);
    }

    restoreWidgetPosition( "AudioTracks", QSize( 435, 90 * trackCount + 10 ) );
    updateGeometry();
}

AudioTrackDialog::~AudioTrackDialog()
{
    saveWidgetPosition( "AudioTracks" );
}

void AudioTrackDialog::toggleVisible()
{
    /* Update, to show existing bookmarks in case a new playlist
       was opened */
    QVLCFrame::toggleVisible();
}
