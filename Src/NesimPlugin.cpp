/*
 * This file is part of the rFactor-Nesim.
 *
 * Martin Galpin (m@66laps.com).
 *
 * Copyright(c) 2011 66laps Limited.
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 3 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "NesimPlugin.hpp"
#include "Configuration.hpp"
#include "UdpSocket.hpp"

#include <math.h>
#include <windows.h>

// Constant for the rFactor Internals API version
#define krFactorInternalsVersion 3
#define krFactorPluginSubType "Internals"

#define kPluginName "rFactorNesimPlugin"
#define kPluginDescription "Exposes the Internals API to Nesim via UDP sockets"
#define kPluginVersion 01
#define kPluginObjectCount 1

/****************************************************************************/
/* NesimPlugin definition.                                                  */
/****************************************************************************/

// Plug-in lifecycle methods
void NesimPlugin::Startup()
{
    mConfiguration = new Configuration();
    mConfiguration->Read();

    mTelemetryEnabled = mConfiguration->GetBool(kConfigurationTelemetry);
    mScoringEnabled = mConfiguration->GetBool(kConfigurationScoring);
    mVehiclesEnabled = mConfiguration->GetBool(kConfigurationVehicles);

    mTelemetrySocket = new UdpSocket(
        mConfiguration->GetString(kConfigurationDestination).c_str(),
        mConfiguration->GetInt(kConfigurationTelemetryPort)
    );
    mTelemetrySocket->Open();

    mScoringSocket = new UdpSocket(
        mConfiguration->GetString(kConfigurationDestination).c_str(),
        mConfiguration->GetInt(kConfigurationScoringPort)
    );
    mScoringSocket->Open();

    mVehiclesSocket = new UdpSocket(
        mConfiguration->GetString(kConfigurationDestination).c_str(),
        mConfiguration->GetInt(kConfigurationVehiclesPort)
    );
    mVehiclesSocket->Open();
}

void NesimPlugin::Destroy()
{
    mTelemetrySocket->Close();
    mTelemetrySocket = NULL;
    delete mTelemetrySocket;

    mScoringSocket->Close();
    mScoringSocket = NULL;
    delete mScoringSocket;

    mVehiclesSocket->Close();
    mVehiclesSocket = NULL;
    delete mVehiclesSocket;

    Shutdown();
}

// Game lifecycle methods
void NesimPlugin::EnterRealtime()
{
}

void NesimPlugin::ExitRealtime()
{
}

// Telemetry updates from InternalsPluginV3
void NesimPlugin::UpdateTelemetry( const TelemInfoV2 &info )
{
    if(mTelemetryEnabled)
        mTelemetrySocket->Send((char*)&info, sizeof(TelemInfoV2));
}

// Scoring updates from InternalsPluginV3
void NesimPlugin::UpdateScoring( const ScoringInfoV2 &info )
{
    struct NetworkScoringInfo* netInfo = CreateNetworkScoringInfo(info);

    if(mScoringEnabled)
        mScoringSocket->Send((char*)netInfo, sizeof(NetworkScoringInfo));

    for(long i = 0; i < info.mNumVehicles; i++) 
    {
        VehicleScoringInfoV2 &vinfo = info.mVehicle[i];

        if(mVehiclesEnabled)
            mVehiclesSocket->Send((char*)&vinfo, sizeof(VehicleScoringInfoV2));
    }

    netInfo = NULL;
    delete netInfo;
}

/****************************************************************************/
/* Plug-in descriptors.                                                     */
/* Copyright (c) 1996-2007 Image Space Incorporated.                        */
/****************************************************************************/
InternalsPluginInfo g_PluginInfo;

// interface to plugin information
extern "C" __declspec(dllexport)
const char* __cdecl GetPluginName() 
{ 
    return kPluginName; 
}

extern "C" __declspec(dllexport)
unsigned __cdecl GetPluginVersion() 
{ 
    return kPluginVersion; 
}

extern "C" __declspec(dllexport)
unsigned __cdecl GetPluginObjectCount()
{ 
    return kPluginObjectCount; 
}

extern "C" __declspec(dllexport)
PluginObjectInfo* __cdecl GetPluginObjectInfo( const unsigned uIndex )
{
    switch(uIndex) {
    case 0:
        return  &g_PluginInfo;
    default:
        return 0;
    }
}

const char* InternalsPluginInfo::GetName() const 
{ 
    return kPluginName; 
}

const char* InternalsPluginInfo::GetFullName() const 
{ 
    return kPluginName; 
}

const char* InternalsPluginInfo::GetDesc() const 
{ 
    return kPluginDescription; 
}

const unsigned InternalsPluginInfo::GetType() const 
{ 
    return PO_INTERNALS; 
}

const char* InternalsPluginInfo::GetSubType() const 
{ 
    return krFactorPluginSubType; 
}

const unsigned InternalsPluginInfo::GetVersion() const
{ 
    return krFactorInternalsVersion; 
}

void* InternalsPluginInfo::Create() const 
{
    return new NesimPlugin(); 
}

PluginObjectInfo *NesimPlugin::GetInfo()
{
    return &g_PluginInfo;
}