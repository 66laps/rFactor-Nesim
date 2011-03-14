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
#include "Configuration.hpp"
#include "tinyxml.h"

#include <sstream>
#include <algorithm>

#define kConfigurationRootNode "configuration"
#define kConfigurationOptionNode "option"

Configuration::Configuration(void)
{
    // Initial default values.
    mConfiguration[kConfigurationDestination] = kConfigurationDefaultDestination;
    mConfiguration[kConfigurationTelemetry] = kConfigurationDefaultTelemetry;
    mConfiguration[kConfigurationTelemetryPort] = kConfigurationTelemetryDefaultPort;
    mConfiguration[kConfigurationScoring] = kConfigurationDefaultScoring;
    mConfiguration[kConfigurationScoringPort] = kConfigurationScoringDefaultPort;
    mConfiguration[kConfigurationVehicles] = kConfigurationDefaultVehicles;
    mConfiguration[kConfigurationVehiclesPort] = kConfigurationVehiclesDefaultPort;
}

Configuration::~Configuration(void)
{}

const std::string& Configuration::GetString(std::string key)
{
    return mConfiguration[key];
}

const int Configuration::GetInt(std::string key)
{
    std::stringstream stream(mConfiguration[key]);
    int result;
    stream >> result;
    return result;
}

const bool Configuration::GetBool(std::string key)
{
    std::string value(mConfiguration[key]);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    return (value == "true" || value == "1");
}

void Configuration::Read(std::string filename)
{
    TiXmlDocument doc(filename.c_str());

    if(!doc.LoadFile()) 
        return;

    TiXmlElement* root = doc.RootElement();
    if (strcmp(root->Value(), kConfigurationRootNode) == 0) 
    {
        for(TiXmlElement* node = root->FirstChildElement(); node; 
            node = node->NextSiblingElement()) 
        {
            if (strcmp(node->Value(), kConfigurationOptionNode) == 0)
                parseOptionNode(node);            
        }
    }    
}

void Configuration::parseOptionNode(TiXmlElement* element)
{
    mConfiguration[element->Attribute("key")] = element->Attribute("value");
}
