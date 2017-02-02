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

#ifndef DISABLE_NETWORK

#include <algorithm>
#include "NetworkAction.h"

extern "C"
{
    #include "../game.h"
    #include "../localisation/string_ids.h"
}

sint32 NetworkActions::FindCommand(sint32 command)
{
    auto it = std::find_if(Actions.begin(), Actions.end(), [&command](NetworkAction const &action)
    {
        for (auto it2 = action.Commands.begin(); it2 != action.Commands.end(); it2++)
        {
            if ((*it2) == command)
            {
                return true;
            }
        }
        return false;
    });
    if (it != Actions.end())
    {
        return (sint32)(it - Actions.begin());
    }
    return -1;
}

sint32 NetworkActions::FindCommandByPermissionName(const std::string &permission_name)
{
    auto it = std::find_if(Actions.begin(), Actions.end(), [&permission_name](NetworkAction const &action)
    {
        if (action.PermissionName == permission_name)
        {
            return true;
        }
        return false;
    });
    if (it != Actions.end())
    {
        return (sint32)(it - Actions.begin());
    }
    return -1;
}

const std::vector<NetworkAction> NetworkActions::Actions =
{
    {
        STR_ACTION_CHAT, "PERMISSION_CHAT",
        {
            MISC_COMMAND_CHAT
        }
    }, {
        STR_ACTION_TERRAFORM, "PERMISSION_TERRAFORM",
        {
            GAME_COMMAND_SET_LAND_HEIGHT,
            GAME_COMMAND_RAISE_LAND,
            GAME_COMMAND_LOWER_LAND,
            GAME_COMMAND_EDIT_LAND_SMOOTH,
            GAME_COMMAND_CHANGE_SURFACE_STYLE
        }
    }, {
        STR_ACTION_SET_WATER_LEVEL, "PERMISSION_SET_WATER_LEVEL",
        {
            GAME_COMMAND_SET_WATER_HEIGHT,
            GAME_COMMAND_RAISE_WATER,
            GAME_COMMAND_LOWER_WATER
        }
    }, {
        STR_ACTION_TOGGLE_PAUSE, "PERMISSION_TOGGLE_PAUSE",
        {
            GAME_COMMAND_TOGGLE_PAUSE
        }
    }, {
        STR_ACTION_CREATE_RIDE, "PERMISSION_CREATE_RIDE",
        {
            GAME_COMMAND_CREATE_RIDE
        }
    }, {
        STR_ACTION_REMOVE_RIDE, "PERMISSION_REMOVE_RIDE",
        {
            GAME_COMMAND_DEMOLISH_RIDE
        }
    }, {
        STR_ACTION_BUILD_RIDE, "PERMISSION_BUILD_RIDE",
        {
            GAME_COMMAND_PLACE_TRACK,
            GAME_COMMAND_REMOVE_TRACK,
            GAME_COMMAND_SET_MAZE_TRACK,
            GAME_COMMAND_PLACE_TRACK_DESIGN,
            GAME_COMMAND_PLACE_MAZE_DESIGN,
            GAME_COMMAND_PLACE_RIDE_ENTRANCE_OR_EXIT,
            GAME_COMMAND_REMOVE_RIDE_ENTRANCE_OR_EXIT
        }
    }, {
        STR_ACTION_RIDE_PROPERTIES, "PERMISSION_RIDE_PROPERTIES",
        {
            GAME_COMMAND_SET_RIDE_NAME,
            GAME_COMMAND_SET_RIDE_APPEARANCE,
            GAME_COMMAND_SET_RIDE_STATUS,
            GAME_COMMAND_SET_RIDE_VEHICLES,
            GAME_COMMAND_SET_RIDE_SETTING,
            GAME_COMMAND_SET_RIDE_PRICE,
            GAME_COMMAND_SET_BRAKES_SPEED
        }
    }, {
        STR_ACTION_SCENERY, "PERMISSION_SCENERY",
        {
            GAME_COMMAND_REMOVE_SCENERY,
            GAME_COMMAND_PLACE_SCENERY,
            GAME_COMMAND_SET_BRAKES_SPEED,
            GAME_COMMAND_REMOVE_FENCE,
            GAME_COMMAND_PLACE_FENCE,
            GAME_COMMAND_REMOVE_LARGE_SCENERY,
            GAME_COMMAND_PLACE_LARGE_SCENERY,
            GAME_COMMAND_PLACE_BANNER,
            GAME_COMMAND_REMOVE_BANNER,
            GAME_COMMAND_SET_SCENERY_COLOUR,
            GAME_COMMAND_SET_FENCE_COLOUR,
            GAME_COMMAND_SET_LARGE_SCENERY_COLOUR,
            GAME_COMMAND_SET_BANNER_COLOUR,
            GAME_COMMAND_SET_BANNER_NAME,
            GAME_COMMAND_SET_SIGN_NAME,
            GAME_COMMAND_SET_BANNER_STYLE,
            GAME_COMMAND_SET_SIGN_STYLE
        }
    }, {
        STR_ACTION_PATH, "PERMISSION_PATH",
        {
            GAME_COMMAND_PLACE_PATH,
            GAME_COMMAND_PLACE_PATH_FROM_TRACK,
            GAME_COMMAND_REMOVE_PATH
        }
    }, {
        STR_ACTION_CLEAR_LANDSCAPE, "PERMISSION_CLEAR_LANDSCAPE",
        {
            GAME_COMMAND_CLEAR_SCENERY
        }
    }, {
        STR_ACTION_GUEST, "PERMISSION_GUEST",
        {
            GAME_COMMAND_SET_GUEST_NAME,
            GAME_COMMAND_PICKUP_GUEST,
            GAME_COMMAND_BALLOON_PRESS
        }
    }, {
        STR_ACTION_STAFF, "PERMISSION_STAFF",
        {
            GAME_COMMAND_HIRE_NEW_STAFF_MEMBER,
            GAME_COMMAND_SET_STAFF_PATROL,
            GAME_COMMAND_FIRE_STAFF_MEMBER,
            GAME_COMMAND_SET_STAFF_ORDER,
            GAME_COMMAND_SET_STAFF_COLOUR,
            GAME_COMMAND_SET_STAFF_NAME,
            GAME_COMMAND_PICKUP_STAFF
        }
    }, {
        STR_ACTION_PARK_PROPERTIES, "PERMISSION_PARK_PROPERTIES",
        {
            GAME_COMMAND_SET_PARK_NAME,
            GAME_COMMAND_SET_PARK_OPEN,
            GAME_COMMAND_SET_PARK_ENTRANCE_FEE,
            GAME_COMMAND_SET_LAND_OWNERSHIP,
            GAME_COMMAND_BUY_LAND_RIGHTS,
            GAME_COMMAND_PLACE_PARK_ENTRANCE,
            GAME_COMMAND_REMOVE_PARK_ENTRANCE
        }
    }, {
        STR_ACTION_PARK_FUNDING, "PERMISSION_PARK_FUNDING",
        {
            GAME_COMMAND_SET_CURRENT_LOAN,
            GAME_COMMAND_SET_RESEARCH_FUNDING,
            GAME_COMMAND_START_MARKETING_CAMPAIGN
        }
    }, {
        STR_ACTION_KICK_PLAYER, "PERMISSION_KICK_PLAYER",
        {
            GAME_COMMAND_KICK_PLAYER
        }
    }, {
        STR_ACTION_MODIFY_GROUPS, "PERMISSION_MODIFY_GROUPS",
        {
            GAME_COMMAND_MODIFY_GROUPS
        }
    }, {
        STR_ACTION_SET_PLAYER_GROUP, "PERMISSION_SET_PLAYER_GROUP",
        {
            GAME_COMMAND_SET_PLAYER_GROUP
        }
    }, {
        STR_ACTION_CHEAT, "PERMISSION_CHEAT",
        {
            GAME_COMMAND_CHEAT
        }
    }, {
        STR_ACTION_TOGGLE_SCENERY_CLUSTER, "PERMISSION_TOGGLE_SCENERY_CLUSTER",
        {
            MISC_COMMAND_TOGGLE_SCENERY_CLUSTER
        }
    }, {
        STR_ACTION_PASSWORDLESS_LOGIN, "PERMISSION_PASSWORDLESS_LOGIN",
        {
            MISC_COMMAND_PASSWORDLESS_LOGIN
        }
    },
};

#endif
