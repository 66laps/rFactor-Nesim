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
#ifndef INTERNALS_EXAMPLE_H
#define INTERNALS_EXAMPLE_H

#include "InternalsPlugin.hpp"
#include "NetworkInternalsPlugin.hpp"

#include <string>

/**
 * rFactor Plugin.
 */
class NesimPlugin : public InternalsPluginV3
{
public:
    /**
    * Default constructor.
    */
    NesimPlugin() {}

    /**
    * Deconstructor.
    */
    ~NesimPlugin() {}

    /**
    * Plug-in lifecycle methods.
    */
    void Startup();
    void Destroy();

    /**
    * Game lifecycle methods. Realtime mode means driving.
    */
    void EnterRealtime();
    void ExitRealtime();

    /**
    * Receive telemetry updates.
    */
    bool WantsTelemetryUpdates() { return true; }

    /**
    * Called when a new telemetry update is available.
    *
    * @param info The telemetry information.
    */
    void UpdateTelemetry(const TelemInfoV2& info);

    /**
    * Receive scoring updates.
    */
    bool WantsScoringUpdates() { return true; }
  
    /**
    * Called when a new scoring update is available.
    *
    * @param info The scoring info.
    */
    void UpdateScoring(const ScoringInfoV2& info);

    /**
    * Derived from base class PluginObject.
    */
    PluginObjectInfo* GetInfo();
    unsigned GetPropertyCount() const { return 0; }
    PluginObjectProperty* GetProperty(const char*) { return 0; }
    PluginObjectProperty* GetProperty(const unsigned) { return 0; }

private:
    class Configuration* mConfiguration;
    class UdpSocket* mTelemetrySocket;
    class UdpSocket* mScoringSocket;
    class UdpSocket* mVehiclesSocket;

    bool mTelemetryEnabled;
    bool mScoringEnabled;
    bool mVehiclesEnabled;
};

/**
 * Standard plug-in descriptor.
 *
 * Copyright (c) 1996-2007 Image Space Incorporated.
 */
class InternalsPluginInfo : public PluginObjectInfo
{
public:
    /** 
    * Default constructor. 
    */
    InternalsPluginInfo() {}
  
    /**
    * Deconstructor.
    */
    ~InternalsPluginInfo() {}

    // Derived from base class PluginObjectInfo
    virtual const char* GetName() const;
    virtual const char* GetFullName() const;
    virtual const char* GetDesc() const;
    virtual const unsigned GetType() const;
    virtual const char* GetSubType() const;
    virtual const unsigned GetVersion() const;
    virtual void* Create() const;
};

#endif // INTERNALS_EXAMPLE_H
