/*****************************************************************************
 * Copyright (c) 2015 Michael Steenbeek
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * This file is part of OpenRCT2.
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef _CHEATS_H_
#define _CHEATS_H_

#include "common.h"

extern bool gCheatsSandboxMode;
extern bool gCheatsDisableClearanceChecks;
extern bool gCheatsDisableSupportLimits;
extern bool gCheatsShowAllOperatingModes;
extern bool gCheatsShowVehiclesFromOtherTrackTypes;
extern bool gCheatsFastLiftHill;
extern bool gCheatsDisableBrakesFailure;
extern bool gCheatsDisableAllBreakdowns;
extern bool gCheatsUnlockAllPrices;
extern bool gCheatsBuildInPauseMode;
extern bool gCheatsIgnoreRideIntensity;
extern bool gCheatsDisableVandalism;

enum {
	CHEAT_SANDBOXMODE,
	CHEAT_DISABLECLEARANCECHECKS,
	CHEAT_DISABLESUPPORTLIMITS,
	CHEAT_SHOWALLOPERATINGMODES,
	CHEAT_SHOWVEHICLESFROMOTHERTRACKTYPES,
	CHEAT_FASTLIFTHILL,
	CHEAT_DISABLEBRAKESFAILURE,
	CHEAT_DISABLEALLBREAKDOWNS,
	CHEAT_UNLOCKALLPRICES,
	CHEAT_BUILDINPAUSEMODE,
	CHEAT_IGNORERIDEINTENSITY,
	CHEAT_DISABLEVANDALISM,
	CHEAT_INCREASEMONEY,
	CHEAT_CLEARLOAN,
	CHEAT_SETGUESTPARAMETER,
	CHEAT_GENERATEGUESTS,
	CHEAT_REMOVEALLGUESTS,
	CHEAT_EXPLODEGUESTS,
	CHEAT_GIVEALLGUESTS,
	CHEAT_SETGRASSLENGTH,
	CHEAT_WATERPLANTS,
	CHEAT_FIXVANDALISM,
	CHEAT_REMOVELITTER,
	CHEAT_SETSTAFFSPEED,
	CHEAT_RENEWRIDES,
	CHEAT_MAKEDESTRUCTIBLE,
	CHEAT_FIXRIDES,
	CHEAT_RESETCRASHSTATUS,
	CHEAT_10MINUTEINSPECTIONS,
	CHEAT_WINSCENARIO,
	CHEAT_FORCEWEATHER,
	CHEAT_FREEZECLIMATE,
	CHEAT_OPENCLOSEPARK,
	CHEAT_HAVEFUN,
	CHEAT_SETFORCEDPARKRATING
};

enum {
	GUEST_PARAMETER_HAPPINESS,
	GUEST_PARAMETER_ENERGY,
	GUEST_PARAMETER_HUNGER,
	GUEST_PARAMETER_THIRST,
	GUEST_PARAMETER_NAUSEA,
	GUEST_PARAMETER_NAUSEA_TOLERANCE,
	GUEST_PARAMETER_BATHROOM,
	GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY
};

enum {
	OBJECT_MONEY,
	OBJECT_PARK_MAP,
	OBJECT_BALLOON,
	OBJECT_UMBRELLA
};

#define CHEATS_MONEY_INCREMENT MONEY(5000,00)
#define CHEATS_TRAM_INCREMENT 250

extern int park_rating_spinner_value;

void game_command_cheat(int* eax, int* ebx, int* ecx, int* edx, int* esi, int* edi, int* ebp);

void cheats_reset();

#endif
