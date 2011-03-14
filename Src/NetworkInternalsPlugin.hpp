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
#ifndef NETWORK_INTERNALS_PLUGIN_HPP
#define NETWORK_INTERNALS_PLUGIN_HPP

#include "InternalsPlugin.hpp"

/**
 * This is a fixed length copy of ScoringInfoV2 (see `InternalsPlugin.hpp`) 
 * that is suitable for transmission over a network.
 *
 * It ommits the following variable-length members:
 *   - `ScoringInfoV2::mResultsStream`
 *   - `ScoringInfoV2::mVehicles`
 *
 * Use the utility function `CreateNetworkScoringInfo()` to create a copy.
 */
struct NetworkScoringInfo
{
    char mTrackName[64];           // current track name
    long mSession;                 // current session
    float mCurrentET;              // current time
    float mEndET;                  // ending time
    long  mMaxLaps;                // maximum laps
    float mLapDist;                // distance around track

    long mNumVehicles;             // current number of vehicles

    // Game phases:
    // 0 Before session has begun
    // 1 Reconnaissance laps (race only)
    // 2 Grid walk-through (race only)
    // 3 Formation lap (race only)
    // 4 Starting-light countdown has begun (race only)
    // 5 Green flag
    // 6 Full course yellow / safety car
    // 7 Session stopped
    // 8 Session over
    unsigned char mGamePhase;   

    // Yellow flag states (applies to full-course only)
    // -1 Invalid
    //  0 None
    //  1 Pending
    //  2 Pits closed
    //  3 Pit lead lap
    //  4 Pits open
    //  5 Last lap
    //  6 Resume
    //  7 Race halt (not currently used)
    signed char mYellowFlagState;

    signed char mSectorFlag[3];      // whether there are any local yellows at the moment in each sector (not sure if sector 0 is first or last, so test)
    unsigned char mStartLight;       // start light frame (number depends on track)
    unsigned char mNumRedLights;     // number of red lights in start sequence
    bool mInRealtime;                // in realtime as opposed to at the monitor
    char mPlayerName[32];            // player name (including possible multiplayer override)
    char mPlrFileName[64];           // may be encoded to be a legal filename

    // weather
    float mDarkCloud;                // cloud darkness? 0.0-1.0
    float mRaining;                  // raining severity 0.0-1.0
    float mAmbientTemp;              // temperature (Celsius)
    float mTrackTemp;                // temperature (Celsius)
    TelemVect3 mWind;                // wind speed
    float mOnPathWetness;            // on main path 0.0-1.0
    float mOffPathWetness;           // on main path 0.0-1.0

    // Future use
    unsigned char mExpansion[256];
};

/**
 * @param source the original instance of ScoringInfoV2.
 * @return a copy of ScoringInfoV2 as a fixed length NetworkScoringInfo.
 */
inline struct NetworkScoringInfo* CreateNetworkScoringInfo(const struct ScoringInfoV2 &source)
{
    struct NetworkScoringInfo* copy = new NetworkScoringInfo;

    strcpy(copy->mTrackName, source.mTrackName);
    copy->mSession = source.mSession;
    copy->mCurrentET = source.mCurrentET;
    copy->mEndET = source.mEndET;
    copy->mMaxLaps = source.mMaxLaps;
    copy->mLapDist = source.mLapDist;
    copy->mNumVehicles = source.mNumVehicles;

    copy->mGamePhase = source.mGamePhase;
    copy->mYellowFlagState = source.mYellowFlagState;
    memcpy(copy->mSectorFlag, source.mSectorFlag, sizeof(copy->mSectorFlag));
    copy->mStartLight = source.mStartLight;
    copy->mNumRedLights = source.mNumRedLights;
    copy->mInRealtime = source.mInRealtime;
    strcpy(copy->mPlayerName, source.mPlayerName);
    strcpy(copy->mPlrFileName, source.mPlrFileName);

    copy->mDarkCloud = source.mDarkCloud;
    copy->mRaining = source.mRaining;
    copy->mAmbientTemp = source.mAmbientTemp;
    copy->mTrackTemp = source.mTrackTemp;
    copy->mWind.x = source.mWind.x; 
    copy->mWind.y = source.mWind.y; 
    copy->mWind.z = source.mWind.z;
    copy->mOnPathWetness = source.mOnPathWetness;
    copy->mOffPathWetness = source.mOffPathWetness;

    return copy;
}

#endif // NETWORK_INTERNALS_PLUGIN_HPP