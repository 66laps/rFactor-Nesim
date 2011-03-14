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
#pragma once
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#define kDefaultConfigurationFile "nesim.xml"

#define kConfigurationDestination "Destination"
#define kConfigurationDefaultDestination "127.0.0.1"

#define kConfigurationTelemetry "Telemetry"
#define kConfigurationDefaultTelemetry "True"

#define kConfigurationTelemetryPort "TelemetryPort"
#define kConfigurationTelemetryDefaultPort "4150"

#define kConfigurationScoring "Scoring"
#define kConfigurationDefaultScoring "True"

#define kConfigurationScoringPort "ScoringPort"
#define kConfigurationScoringDefaultPort "4151"

#define kConfigurationVehicles "Vehicles"
#define kConfigurationDefaultVehicles "True"

#define kConfigurationVehiclesPort "VehiclesPort"
#define kConfigurationVehiclesDefaultPort "4152"

#include <string>
#include <unordered_map>

/**
 * This is a very basic configuration class that reads from a simple
 * XML configuration file. See "OpenMotorsport.xml" for more details.
 *
 * Mandatory configuration options have default values thus the existence of
 * the XML file is not strictly necessary for a dependant to continue working.
 */
class Configuration
{
public:
    Configuration(void);
    ~Configuration(void);
    void Read(std::string filename = kDefaultConfigurationFile);

    const std::string& GetString(std::string key);
    const int GetInt(std::string key);
    const bool GetBool(std::string key);
private:
    typedef std::tr1::unordered_map<std::string, std::string> ConfigurationMap;
    ConfigurationMap mConfiguration;
private:
    void Configuration::parseOptionNode(class TiXmlElement* element);
};


#endif /* CONFIGURATION_HPP */
