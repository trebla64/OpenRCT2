#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#pragma once

#include "../common.h"
#include "../core/List.hpp"

namespace RCT1
{
    colour_t GetColour(colour_t colour);
    uint8 GetTerrain(uint8 terrain);
    uint8 GetTerrainEdge(uint8 terrainEdge);

    uint8 GetRideType(uint8 rideType);
    bool RideTypeUsesVehicles(uint8 rideType);
    bool PathIsQueue(uint8 pathType);
    uint8 NormalisePathAddition(uint8 pathAdditionType);

    const char * GetRideTypeObject(uint8 rideType);
    const char * GetVehicleObject(uint8 vehicleType);
    const char * GetSmallSceneryObject(uint8 smallSceneryType);
    const char * GetLargeSceneryObject(uint8 largeSceneryType);
    const char * GetWallObject(uint8 wallType);
    const char * GetPathObject(uint8 pathType);
    const char * GetPathAddtionObject(uint8 pathAdditionType);
    const char * GetSceneryGroupObject(uint8 sceneryGroupType);

    const List<const char *> GetSceneryObjects(uint8 sceneryType);

	const List<const char *> GetPreferedRideEntryOrder(uint8 rideType);
}
