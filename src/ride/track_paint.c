/*****************************************************************************
* Copyright (c) 2014 Ted John
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

#include "../addresses.h"
#include "../config.h"
#include "../drawing/drawing.h"
#include "../drawing/supports.h"
#include "../interface/viewport.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../sprites.h"
#include "../world/map.h"
#include "../world/sprite.h"
#include "ride_data.h"
#include "track_data.h"
#include "track_paint.h"

/**
 *
 *  rct2: 0x0076687C
 */
static void top_spin_paint_tile_0(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22137 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 112;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/* rct2: 0x007667AE */
static rct_xy16 loc_7667AE[] = {
	{ .x = 0,  .y = -1 },
	{ .x = 1,  .y = 0 },
	{ .x = 0,  .y = 1},
	{ .x = -1, .y = 0 },
};

/* rct2: 0x007667AC */
static rct_xy16 loc_7667AC[] = {
	{ .x = -1, .y = 0 },
	{ .x = 0,  .y = -1 },
	{ .x = 1,  .y = 0 },
	{ .x = 0,  .y = 1 },
};

/**
 *
 *  rct2: 0x0142811C
 * Can be calculated as Rounddown(34*sin(x)+0.5)
 * where x is in 7.5 deg segments.
 */
static sint8 TopSpinSeatPositionOffset[] = {
	  0,   4,   9,  13,  17,  21,  24,  27,  29,  31,  33,  34,  34,  34,  33,  31,
	 29,  27,  24,  21,  17,  13,   9,   4,   0,  -3,  -8, -12, -16, -20, -23, -26,
	-28, -30, -32, -33, -33, -33, -32, -30, -28, -26, -23, -20, -16, -12,  -8,  -3,
	  0
};

/**
 *
 *  rct2: 0x0076750D
 */
static void top_spin_paint_vehicle(sint8 al, sint8 cl, uint8 rideIndex, uint8 direction, int height, rct_map_element* mapElement) {
	// As we will be drawing a vehicle we need to backup the mapElement that
	// is assigned to the drawings.
	rct_map_element* curMapElement = RCT2_GLOBAL(0x009DE578, rct_map_element*);

	height += 3;

	rct_ride* ride = get_ride(rideIndex);
	rct_ride_entry* rideEntry = get_ride_entry(ride->subtype);
	rct_vehicle* vehicle = NULL;

	uint8 seatRotation = 0;
	sint8 armRotation = 0;

	if (ride->lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK &&
		ride->vehicles[0] != SPRITE_INDEX_NULL) {
		vehicle = GET_VEHICLE(ride->vehicles[0]);

		RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8) = VIEWPORT_INTERACTION_ITEM_SPRITE;
		RCT2_GLOBAL(0x009DE578, rct_vehicle*) = vehicle;

		armRotation = vehicle->vehicle_sprite_type;
		seatRotation = vehicle->bank_rotation;
	}

	RCT2_GLOBAL(0x009DEA52, sint16) = al + 16;
	RCT2_GLOBAL(0x009DEA54, sint16) = cl + 16;
	RCT2_GLOBAL(0x009DEA56, sint16) = height;

	//di
	uint8 lengthX = 24;
	//si
	uint8 lengthY = 24;

	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	if (image_id == 0x20000000) {
		image_id =
			0xA0000000 |
			(ride->track_colour_main[0] << 19) |
			(ride->track_colour_supports[0] << 24);
	}

	image_id += (direction & 1) << 1;
	image_id += rideEntry->vehicles[0].base_image_id;
	// Left back bottom support
	image_id += 572;

	sub_98197C(image_id, al, cl, lengthX, lengthY, 90, height, get_current_rotation());

	image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	if (image_id == 0x20000000) {
		image_id =
			0xA0000000 |
			(ride->track_colour_main[0] << 19) |
			(ride->track_colour_additional[0] << 24);
	}

	sint32 var_1F = armRotation;
	if (direction & 2) {
		var_1F = -var_1F;
		if (var_1F != 0)
			var_1F += 48;
	}
	image_id += var_1F;
	image_id += (direction & 1) * 48;
	image_id += rideEntry->vehicles[0].base_image_id;
	// Left hand arm
	image_id += 380;

	sub_98199C(
		image_id,
		al,
		cl,
		lengthX,
		lengthY,
		90,
		height,
		0);

	uint32 seatImageId;

	if (vehicle != NULL && vehicle->restraints_position >= 64) {
		// Open Restraints
		image_id = (vehicle->restraints_position - 64) >> 6;
		image_id += direction * 3;
		image_id += rideEntry->vehicles[0].base_image_id;
		image_id += 64;
		seatImageId = image_id;
	}
	else {
		image_id = direction * 16;
		// Var_20 Rotation of seats
		image_id += seatRotation;
		image_id += rideEntry->vehicles[0].base_image_id;
		seatImageId = image_id;
	}

	image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	if (image_id == 0x20000000) {
		image_id =
			0xA0000000 |
			(ride->vehicle_colours[0].body_colour << 19) |
			(ride->vehicle_colours[0].trim_colour << 24);
	}
	image_id += seatImageId;

	rct_xyz16 seatCoords = {
		.x = al,
		.y = cl,
		.z = height
	};
	seatCoords.z += RCT2_ADDRESS(0x14280BC, sint16)[armRotation];

	assert(armRotation < sizeof(TopSpinSeatPositionOffset));
	switch (direction) {
	case 0:
		seatCoords.x -= TopSpinSeatPositionOffset[armRotation];
		break;
	case 1:
		seatCoords.y += TopSpinSeatPositionOffset[armRotation];
		break;
	case 2:
		seatCoords.x += TopSpinSeatPositionOffset[armRotation];
		break;
	case 3:
		seatCoords.y -= TopSpinSeatPositionOffset[armRotation];
		break;
	}

	RCT2_GLOBAL(0x014280B8, sint8) = (sint8)seatCoords.x;
	RCT2_GLOBAL(0x014280B9, sint8) = (sint8)seatCoords.y;
	RCT2_GLOBAL(0x014280BA, sint16) = seatCoords.z;

	sub_98199C(
		image_id,
		(sint8)seatCoords.x,
		(sint8)seatCoords.y,
		lengthX,
		lengthY,
		90,
		seatCoords.z,
		0);

	rct_drawpixelinfo* dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);
	if (dpi->zoom_level < 2 && vehicle != NULL && vehicle->num_peeps != 0) {
		image_id =
			(vehicle->peep_tshirt_colours[0] << 19) |
			(vehicle->peep_tshirt_colours[1] << 24);
		image_id += seatImageId;
		image_id += 0xA0000000;
		image_id += 76;

		sub_98199C(image_id, (sint8)seatCoords.x, (sint8)seatCoords.y, lengthX, lengthY, 90, seatCoords.z, 0);

		if (vehicle->num_peeps > 2) {
			image_id =
				(vehicle->peep_tshirt_colours[2] << 19) |
				(vehicle->peep_tshirt_colours[3] << 24);
			image_id += seatImageId;
			image_id += 0xA0000000;
			image_id += 152;

			sub_98199C(image_id, (sint8)seatCoords.x, (sint8)seatCoords.y, lengthX, lengthY, 90, seatCoords.z, 0);
		}

		if (vehicle->num_peeps > 4) {
			image_id =
				(vehicle->peep_tshirt_colours[4] << 19) |
				(vehicle->peep_tshirt_colours[5] << 24);
			image_id += seatImageId;
			image_id += 0xA0000000;
			image_id += 228;

			sub_98199C(image_id, (sint8)seatCoords.x, (sint8)seatCoords.y, lengthX, lengthY, 90, seatCoords.z, 0);
		}

		if (vehicle->num_peeps > 6) {
			image_id =
				(vehicle->peep_tshirt_colours[6] << 19) |
				(vehicle->peep_tshirt_colours[7] << 24);
			image_id += seatImageId;
			image_id += 0xA0000000;
			image_id += 304;

			sub_98199C(image_id, (sint8)seatCoords.x, (sint8)seatCoords.y, lengthX, lengthY, 90, seatCoords.z, 0);
		}
	}

	image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	if (image_id == 0x20000000) {
		image_id =
			0xA0000000 |
			(ride->track_colour_main[0] << 19) |
			(ride->track_colour_additional[0] << 24);
	}

	image_id += var_1F;
	image_id += (direction & 1) * 48;
	image_id += rideEntry->vehicles[0].base_image_id;
	// Right hand arm
	image_id += 476;

	sub_98199C(
		image_id,
		al,
		cl,
		lengthX,
		lengthY,
		90,
		height,
		0);

	image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	if (image_id == 0x20000000) {
		image_id =
			0xA0000000 |
			(ride->track_colour_main[0] << 19) |
			(ride->track_colour_supports[0] << 24);
	}

	image_id += (direction & 1) << 1;
	image_id += rideEntry->vehicles[0].base_image_id;
	// Right back bottom support
	image_id += 573;

	sub_98199C(
		image_id,
		al,
		cl,
		lengthX,
		lengthY,
		90,		
		height,
		0);

	RCT2_GLOBAL(0x009DE578, rct_map_element*) = curMapElement;
	RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8) = VIEWPORT_INTERACTION_ITEM_RIDE;
}

/**
 *
 *  rct2: 0x0076693F
 */
static void top_spin_paint_tile_1(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22137 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint16 entranceLoc =
		((x / 32) + loc_7667AE[get_current_rotation()].x) |
		(((y / 32) + loc_7667AE[get_current_rotation()].y) << 8);

	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22141 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 32, 1, 7, height, 0);
	}

	entranceLoc =
		((x / 32) + loc_7667AC[get_current_rotation()].x) |
		(((y / 32) + loc_7667AC[get_current_rotation()].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22138 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 1, 32, 7, height, 0);
	}

	top_spin_paint_vehicle(32, 32, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9B6, uint16) = 32;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9CA, uint16) = 32;
	RCT2_GLOBAL(0x141E9CC, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9CE, uint16) = 32;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x00767033
 */
static void top_spin_paint_tile_2(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22137 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint16 entranceLoc =
		((x / 32) + loc_7667AC[get_current_rotation()].x) |
		(((y / 32) + loc_7667AC[get_current_rotation()].y) << 8);

	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22138 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 0;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 1, 32, 7, height, 0);
	}

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x0076718D
 */
static void top_spin_paint_tile_4(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22137 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint16 entranceLoc =
		((x / 32) + loc_7667AE[get_current_rotation()].x) |
		(((y / 32) + loc_7667AE[get_current_rotation()].y) << 8);

	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22141 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 32, 1, 7, height, 0);
	}

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x00766B4C
 */
static void top_spin_paint_tile_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22136 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint16 entranceLoc =
		((x / 32) + loc_7667AC[get_current_rotation()].x) |
		(((y / 32) + loc_7667AC[get_current_rotation()].y) << 8);

	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22138 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 0;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 1, 32, 7, height, 0);
	}

	entranceLoc =
		((x / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].x) |
		(((y / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22139 | RCT2_GLOBAL(0x00F441A0, uint32);

		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 30;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;
		sub_98197C(image_id, 0, 0, 32, 1, 7, height, get_current_rotation());
	}

	top_spin_paint_vehicle(32, -32, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9BE, uint16) = 32;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9CE, uint16) = 32;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9D6, uint16) = 32;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x007672E7
 */
static void top_spin_paint_tile_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22136 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	uint16 entranceLoc =
		((x / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].x) |
		(((y / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {
		image_id = 22139 | RCT2_GLOBAL(0x00F441A0, uint32);

		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 30;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;
		sub_98197C(image_id, 0, 0, 32, 1, 7, height, get_current_rotation());
	}

	top_spin_paint_vehicle(0, -32, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 112;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x00766D09
 */
static void top_spin_paint_tile_6(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22135 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint16 entranceLoc =
		((x / 32) + loc_7667AE[get_current_rotation()].x) |
		(((y / 32) + loc_7667AE[get_current_rotation()].y) << 8);

	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22141 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98199C(image_id, 0, 0, 32, 1, 7, height, 0);
	}

	entranceLoc =
		((x / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].x) |
		(((y / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22140 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 30;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98197C(image_id, 0, 0, 1, 32, 7, height, get_current_rotation());
	}

	top_spin_paint_vehicle(-32, 32, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9BA, uint16) = 32;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9CA, uint16) = 32;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9D2, uint16) = 32;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x00766EC6
 */
static void top_spin_paint_tile_7(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22134 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	uint16 entranceLoc =
		((x / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].x) |
		(((y / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22140 | RCT2_GLOBAL(0x00F441A0, uint32);

		RCT2_GLOBAL(0x009DEA52, uint16) = 29;
		RCT2_GLOBAL(0x009DEA54, uint16) = 0;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 3;
		sub_98197C(image_id, 0, 0, 1, 28, 7, height, get_current_rotation());
	}

	entranceLoc =
		((x / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].x) |
		(((y / 32) + loc_7667AC[(get_current_rotation() + 3) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22139 | RCT2_GLOBAL(0x00F441A0, uint32);

		RCT2_GLOBAL(0x009DEA52, uint16) = 0;
		RCT2_GLOBAL(0x009DEA54, uint16) = 29;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 3;
		sub_98197C(image_id, 0, 0, 28, 1, 7, height, get_current_rotation());
	}

	top_spin_paint_vehicle(-32, -32, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9C2, uint16) = 32;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9D2, uint16) = 32;
	RCT2_GLOBAL(0x141E9D4, uint16) = height + 2;
	RCT2_GLOBAL(0x141E9D6, uint16) = 32;

	height += 110;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x007673FA
 */
static void top_spin_paint_tile_8(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	uint32 image_id = RCT2_GLOBAL(0x00F441A0, uint32);
	wooden_a_supports_paint_setup(direction & 1, 0, height, image_id, NULL);

	image_id = 22135 | RCT2_GLOBAL(0x00F44198, uint32);

	RCT2_GLOBAL(0x009DEA52, uint16) = 0;
	RCT2_GLOBAL(0x009DEA54, uint16) = 0;
	RCT2_GLOBAL(0x009DEA56, uint16) = height;
	sub_98197C(image_id, 0, 0, 32, 32, 1, height, get_current_rotation());

	sint16 x = RCT2_GLOBAL(0x009DE56A, sint16), y = RCT2_GLOBAL(0x009DE56E, sint16);
	uint8 entranceId = (mapElement->properties.track.sequence & 0x70) >> 4;
	rct_ride* ride = get_ride(rideIndex);

	uint16 entranceLoc =
		((x / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].x) |
		(((y / 32) + loc_7667AE[(get_current_rotation() + 1) & 3].y) << 8);

	if (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc) {

		image_id = 22140 | RCT2_GLOBAL(0x00F441A0, uint32);
		RCT2_GLOBAL(0x009DEA52, uint16) = 30;
		RCT2_GLOBAL(0x009DEA54, uint16) = 0;
		RCT2_GLOBAL(0x009DEA56, uint16) = height + 2;

		sub_98197C(image_id, 0, 0, 1, 32, 7, height, get_current_rotation());
	}
	top_spin_paint_vehicle(-32, 0, rideIndex, direction, height, mapElement);

	RCT2_GLOBAL(0x141E9B4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9B8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9BC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C4, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9C8, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9CC, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D0, uint16) = 0xFFFF;
	RCT2_GLOBAL(0x141E9D4, uint16) = 0xFFFF;

	height += 112;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height;
		RCT2_GLOBAL(0x141E9DA, uint8) = 32;
	}
}

/**
 *
 *  rct2: 0x007667BC
 */
static void top_spin_paint_setup_rot_0(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	switch (trackSequence)
	{
	case 0:
		top_spin_paint_tile_0(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 1:
		top_spin_paint_tile_1(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 2:
		top_spin_paint_tile_2(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 3:
		top_spin_paint_tile_3(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 4:
		top_spin_paint_tile_4(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 5:
		top_spin_paint_tile_5(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 6:
		top_spin_paint_tile_6(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 7:
		top_spin_paint_tile_7(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 8:
		top_spin_paint_tile_8(rideIndex, trackSequence, direction, height, mapElement);
		break;
	}
	return;
}

/**
 *
 *  rct2: 0x007667EC
*/
static void top_spin_paint_setup_rot_1(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	switch (trackSequence)
	{
	case 0:
		top_spin_paint_tile_0(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 1:
		top_spin_paint_tile_3(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 2:
		top_spin_paint_tile_5(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 3:
		top_spin_paint_tile_7(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 4:
		top_spin_paint_tile_2(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 5:
		top_spin_paint_tile_8(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 6:
		top_spin_paint_tile_1(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 7:
		top_spin_paint_tile_6(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 8:
		top_spin_paint_tile_4(rideIndex, trackSequence, direction, height, mapElement);
		break;
	}
	return;
}

/**
 *
 *  rct2: 0x0076681C
*/
static void top_spin_paint_setup_rot_2(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	switch (trackSequence)
	{
	case 0:
		top_spin_paint_tile_0(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 1:
		top_spin_paint_tile_7(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 2:
		top_spin_paint_tile_8(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 3:
		top_spin_paint_tile_6(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 4:
		top_spin_paint_tile_5(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 5:
		top_spin_paint_tile_4(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 6:
		top_spin_paint_tile_3(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 7:
		top_spin_paint_tile_1(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 8:
		top_spin_paint_tile_2(rideIndex, trackSequence, direction, height, mapElement);
		break;
	}
	return;
}

/**
 *
 *  rct2: 0x0076684C
*/
static void top_spin_paint_setup_rot_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement) {
	switch (trackSequence)
	{
	case 0:
		top_spin_paint_tile_0(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 1:
		top_spin_paint_tile_6(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 2:
		top_spin_paint_tile_4(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 3:
		top_spin_paint_tile_1(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 4:
		top_spin_paint_tile_8(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 5:
		top_spin_paint_tile_2(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 6:
		top_spin_paint_tile_7(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 7:
		top_spin_paint_tile_3(rideIndex, trackSequence, direction, height, mapElement);
		break;
	case 8:
		top_spin_paint_tile_5(rideIndex, trackSequence, direction, height, mapElement);
		break;
	}
	return;
}

/* 0x0076659C */
TRACK_PAINT_FUNCTION get_track_paint_function_topspin(int trackType, int direction)
{
	switch (trackType) {
	case 123:
		switch (direction) {
		case 0: return top_spin_paint_setup_rot_0;
		case 1: return top_spin_paint_setup_rot_1;
		case 2: return top_spin_paint_setup_rot_2;
		case 3: return top_spin_paint_setup_rot_3;
		}
		break;
	}
	return NULL;
}

/**
 *
 *  rct2: 0x00761378
 *  rct2: 0x007614DB
 *  rct2: 0x0076163F
 *  rct2: 0x007617A5
 */
static void shop_paint_setup(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement)
{
	bool hasSupports = wooden_a_supports_paint_setup(direction & 1, 0, height, RCT2_GLOBAL(0x00F441A4, uint32), NULL);

	RCT2_GLOBAL(0x0141E9D0, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C4, sint16) = -1;
	RCT2_GLOBAL(0x0141E9CC, sint16) = -1;
	RCT2_GLOBAL(0x0141E9B8, sint16) = -1;
	RCT2_GLOBAL(0x0141E9BC, sint16) = -1;
	RCT2_GLOBAL(0x0141E9B4, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C0, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C8, sint16) = -1;
	RCT2_GLOBAL(0x0141E9D4, sint16) = -1;

	rct_ride *ride = get_ride(rideIndex);
	rct_ride_entry *rideEntry = get_ride_entry(ride->subtype);
	rct_ride_entry_vehicle *firstVehicleEntry = &rideEntry->vehicles[0];

	uint32 imageId = RCT2_GLOBAL(0x00F44198, uint32);
	if (imageId & 0x80000000) {
		imageId &= 0x60FFFFFF;
	}
	imageId += firstVehicleEntry->base_image_id;
	imageId += direction;

	sint16 height16 = (sint16)height;
	int rotation = get_current_rotation();
	if (hasSupports) {
		uint32 foundationImageId = RCT2_GLOBAL(0x00F441A4, uint32);
		foundationImageId |= 3395;

		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98197C(foundationImageId, 0, 0, 28, 28, 45, height, rotation);

		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98199C(imageId, 0, 0, 28, 28, 45, height, rotation);
	} else {
		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98197C(imageId, 0, 0, 28, 28, 45, height, rotation);
	}

	height16 += 48;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height16) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height16;
		RCT2_GLOBAL(0x00141E9DA, uint8) = 32;
	}
}

/* 0x00761160 */
TRACK_PAINT_FUNCTION get_track_paint_function_shop(int trackType, int direction)
{
	switch (trackType) {
	case 118:
	case 121: return shop_paint_setup;
	}
	return NULL;
}

/**
 *
 *  rct2: 0x00763234
 *  rct2: 0x0076338C
 *  rct2: 0x00762F50
 *  rct2: 0x007630DE
 */
static void facility_paint_setup(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement)
{
	bool hasSupports = wooden_a_supports_paint_setup(direction & 1, 0, height, RCT2_GLOBAL(0x00F441A4, uint32), NULL);

	RCT2_GLOBAL(0x0141E9D0, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C4, sint16) = -1;
	RCT2_GLOBAL(0x0141E9CC, sint16) = -1;
	RCT2_GLOBAL(0x0141E9B8, sint16) = -1;
	RCT2_GLOBAL(0x0141E9BC, sint16) = -1;
	RCT2_GLOBAL(0x0141E9B4, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C0, sint16) = -1;
	RCT2_GLOBAL(0x0141E9C8, sint16) = -1;
	RCT2_GLOBAL(0x0141E9D4, sint16) = -1;

	rct_ride *ride = get_ride(rideIndex);
	rct_ride_entry *rideEntry = get_ride_entry(ride->subtype);
	rct_ride_entry_vehicle *firstVehicleEntry = &rideEntry->vehicles[0];

	uint32 imageId = RCT2_GLOBAL(0x00F44198, uint32);
	imageId |= firstVehicleEntry->base_image_id;
	imageId += (direction + 2) & 3;

	sint16 height16 = (sint16)height;
	int rotation = get_current_rotation();
	int lengthX = (direction & 1) == 0 ? 28 : 2;
	int lengthY = (direction & 1) == 0 ? 2 : 28;
	if (hasSupports) {
		uint32 foundationImageId = RCT2_GLOBAL(0x00F441A4, uint32);
		foundationImageId |= 3395;

		RCT2_GLOBAL(0x009DEA52, uint16) = direction == 3 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = direction == 0 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98197C(foundationImageId, 0, 0, lengthX, lengthY, 29, height, rotation);

		// Door image or base
		RCT2_GLOBAL(0x009DEA52, uint16) = direction == 3 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = direction == 0 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98199C(imageId, 0, 0, lengthX, lengthY, 29, height, rotation);
	} else {
		// Door image or base
		RCT2_GLOBAL(0x009DEA52, uint16) = direction == 3 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = direction == 0 ? 28 : 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;

		sub_98197C(imageId, 0, 0, lengthX, lengthY, 29, height, rotation);
	}

	// Base image if door was drawn
	if (direction == 1) {
		imageId += 2;
		RCT2_GLOBAL(0x009DEA52, uint16) = 28;
		RCT2_GLOBAL(0x009DEA54, uint16) = 2;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98197C(imageId, 0, 0, 2, 28, 29, height, rotation);
	} else if (direction == 2) {
		imageId += 4;
		RCT2_GLOBAL(0x009DEA52, uint16) = 2;
		RCT2_GLOBAL(0x009DEA54, uint16) = 28;
		RCT2_GLOBAL(0x009DEA56, sint16) = height16;
		sub_98197C(imageId, 0, 0, 28, 2, 29, height, rotation);
	}

	height16 += 32;
	if (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) < height16) {
		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PAINT_TILE_MAX_HEIGHT, sint16) = height16;
		RCT2_GLOBAL(0x00141E9DA, uint8) = 32;
	}
}

/* 0x00762D44 */
TRACK_PAINT_FUNCTION get_track_paint_function_facility(int trackType, int direction)
{
	switch (trackType) {
	case 118: return facility_paint_setup;
	}
	return NULL;
}
