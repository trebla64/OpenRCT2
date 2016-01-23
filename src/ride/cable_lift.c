#include "../world/sprite.h"
#include "cable_lift.h"
#include "ride.h"
#include "track.h"

static void cable_lift_update_moving_to_end_of_station(rct_vehicle *vehicle);
static void cable_lift_update_waiting_to_depart(rct_vehicle *vehicle);
static void cable_lift_update_departing(rct_vehicle *vehicle);
static void cable_lift_update_travelling(rct_vehicle *vehicle);
static void cable_lift_update_arriving(rct_vehicle *vehicle);

rct_vehicle *cable_lift_segment_create(int rideIndex, int x, int y, int z, int direction, uint16 var_44, sint32 remaining_distance, bool head)
{
	rct_ride *ride = get_ride(rideIndex);
	rct_vehicle *current = &(create_sprite(1)->vehicle);
	current->sprite_identifier = SPRITE_IDENTIFIER_VEHICLE;
	current->ride = rideIndex;
	current->ride_subtype = 0xFF;
	if (head) {
		move_sprite_to_list((rct_sprite*)current, SPRITE_LINKEDLIST_OFFSET_VEHICLE);
		ride->cable_lift = current->sprite_index;
	}
	current->is_child = head ? 0 : 1;
	current->var_44 = var_44;
	current->remaining_distance = remaining_distance;
	current->sprite_width = 10;
	current->sprite_height_negative = 10;
	current->sprite_height_positive = 10;
	current->friction = 100;
	current->num_seats = 0;
	current->speed = 20;
	current->powered_acceleration = 80;
	current->velocity = 0;
	current->acceleration = 0;
	current->var_4A = 0;
	current->swinging_car_var_0 = 0;
	current->var_4E = 0;
	current->restraints_position = 0;
	current->var_BA = 0;
	current->var_B6 = 0;
	current->var_B8 = 0;
	current->sound1_id = 0xFF;
	current->sound2_id = 0xFF;
	current->var_C4 = 0;
	current->var_C5 = 0;
	current->var_C8 = 0;
	current->var_CA = 0;
	current->scream_sound_id = 0xFF;
	current->var_1F = 0;
	current->var_20 = 0;
	for (int j = 0; j < 32; j++) {
		current->peep[j] = SPRITE_INDEX_NULL;
	}
	current->var_CD = 0;
	current->sprite_direction = direction << 3;
	current->track_x = x;
	current->track_y = y;

	z = z * 8;
	current->track_z = z;
	z += RCT2_GLOBAL(0x0097D21A + (ride->type * 8), sint8);

	sprite_move(16, 16, z, (rct_sprite*)current);
	current->track_type = (TRACK_ELEM_CABLE_LIFT_HILL << 2) | (current->sprite_direction >> 3);
	current->track_progress = 164;
	current->update_flags = VEHICLE_UPDATE_FLAG_1;
	current->status = VEHICLE_STATUS_MOVING_TO_END_OF_STATION;
	current->sub_state = 0;
	current->num_peeps = 0;
	current->next_free_seat = 0;
	return current;
}

void cable_lift_update(rct_vehicle *vehicle)
{
	switch (vehicle->status) {
	case VEHICLE_STATUS_MOVING_TO_END_OF_STATION:
		cable_lift_update_moving_to_end_of_station(vehicle);
		break;
	case VEHICLE_STATUS_WAITING_FOR_PASSENGERS:
		// Stays in this state until a train puts it into next state
		break;
	case VEHICLE_STATUS_WAITING_TO_DEPART:
		cable_lift_update_waiting_to_depart(vehicle);
		break;
	case VEHICLE_STATUS_DEPARTING:
		cable_lift_update_departing(vehicle);
		break;
	case VEHICLE_STATUS_TRAVELLING:
		cable_lift_update_travelling(vehicle);
		break;
	case VEHICLE_STATUS_ARRIVING:
		cable_lift_update_arriving(vehicle);
		break;
	}
}

/**
 *
 *  rct2: 0x006DF8A4
 */
static void cable_lift_update_moving_to_end_of_station(rct_vehicle *vehicle)
{
	if (vehicle->velocity >= -439800)
		vehicle->acceleration = -2932;

	if (vehicle->velocity < -439800) {
		vehicle->velocity -= vehicle->velocity / 16;
		vehicle->acceleration = 0;
	}

	if (!(cable_lift_update_track_motion(vehicle) & (1 << 0)))
		return;

	vehicle->velocity = 0;
	vehicle->acceleration = 0;
	vehicle->status = VEHICLE_STATUS_WAITING_FOR_PASSENGERS;
}

/**
 *
 *  rct2: 0x006DF8F1
 */
static void cable_lift_update_waiting_to_depart(rct_vehicle *vehicle)
{
	if (vehicle->velocity >= -58640)
		vehicle->acceleration = -14660;

	if (vehicle->velocity < -58640) {
		vehicle->velocity -= vehicle->velocity / 16;
		vehicle->acceleration = 0;
	}

	cable_lift_update_track_motion(vehicle);

	// Next check to see if the second part of the cable lift
	// is at the front of the passenger vehicle to simulate the
	// cable being attached underneath the train.
	rct_vehicle* passengerVehicle = GET_VEHICLE(vehicle->var_C0);
	rct_vehicle* cableLiftSecondPart = GET_VEHICLE(vehicle->prev_vehicle_on_ride);

	sint16 dist_x = abs(passengerVehicle->x - cableLiftSecondPart->x);
	sint16 dist_y = abs(passengerVehicle->y - cableLiftSecondPart->y);

	if (dist_x + dist_y > 2)
		return;

	vehicle->velocity = 0;
	vehicle->acceleration = 0;
	vehicle->status = VEHICLE_STATUS_DEPARTING;
	vehicle->sub_state = 0;
}

/**
 *
 *  rct2: 0x006DF97A
 */
static void cable_lift_update_departing(rct_vehicle *vehicle)
{
	vehicle->sub_state++;
	if (vehicle->sub_state < 16)
		return;

	rct_vehicle* passengerVehicle = GET_VEHICLE(vehicle->var_C0);
	vehicle->status = VEHICLE_STATUS_TRAVELLING;
	passengerVehicle->status = VEHICLE_STATUS_TRAVELLING_CABLE_LIFT;
}

/**
 *
 *  rct2: 0x006DF99C
 */
static void cable_lift_update_travelling(rct_vehicle *vehicle)
{
	rct_vehicle* passengerVehicle = GET_VEHICLE(vehicle->var_C0);

	vehicle->velocity = min(passengerVehicle->velocity, 439800);
	vehicle->acceleration = 0;
	if (passengerVehicle->update_flags & VEHICLE_UPDATE_FLAG_BROKEN_TRAIN)
		return;

	if (!(cable_lift_update_track_motion(vehicle) & (1 << 1)))
		return;

	vehicle->velocity = 0;
	vehicle->acceleration = 0;
	vehicle->status = VEHICLE_STATUS_ARRIVING;
	vehicle->sub_state = 0;
}

/**
 *
 *  rct2: 0x006DF9F0
 */
static void cable_lift_update_arriving(rct_vehicle *vehicle)
{
	vehicle->sub_state++;
	if (vehicle->sub_state >= 64)
		vehicle->status = VEHICLE_STATUS_MOVING_TO_END_OF_STATION;
}

bool sub_6DF01A_loop(rct_vehicle* vehicle) {
	rct_ride* ride = get_ride(vehicle->ride);
	rct_xyz16 *unk_F64E20 = RCT2_ADDRESS(0x00F64E20, rct_xyz16);

	for (; vehicle->remaining_distance >= 13962; RCT2_GLOBAL(0x00F64E10, uint32)++) {
		uint8 trackType = vehicle->track_type >> 2;
		if (trackType == TRACK_ELEM_CABLE_LIFT_HILL &&
			vehicle->track_progress == 160) {
			RCT2_GLOBAL(0x00F64E18, uint32) |= (1 << 1);
		}

		uint16 trackProgress = vehicle->track_progress + 1;

		const rct_vehicle_info *moveInfo = vehicle_get_move_info(vehicle->var_CD, vehicle->track_type, 0);
		uint16 trackTotalProgress = *((uint16*)((int)moveInfo - 2));
		if (trackProgress >= trackTotalProgress) {
			RCT2_GLOBAL(0x00F64E36, uint8) = gTrackDefinitions[trackType].vangle_end;
			RCT2_GLOBAL(0x00F64E37, uint8) = gTrackDefinitions[trackType].bank_end;
			rct_map_element* trackElement =
				map_get_track_element_at_of_type_seq(
					vehicle->track_x,
					vehicle->track_y,
					vehicle->track_z / 8,
					trackType,
					0);

			rct_xy_element input;
			rct_xy_element output;
			int outputZ;
			int outputDirection;

			input.x = vehicle->track_x;
			input.y = vehicle->track_y;
			input.element = trackElement;

			if (!track_block_get_next(&input, &output, &outputZ, &outputDirection))
				return false;

			if (gTrackDefinitions[output.element->properties.track.type].vangle_start != RCT2_GLOBAL(0x00F64E36, uint8) ||
				gTrackDefinitions[output.element->properties.track.type].bank_start != RCT2_GLOBAL(0x00F64E37, uint8))
				return false;

			vehicle->track_x = output.x;
			vehicle->track_y = output.y;
			vehicle->track_z = outputZ;
			vehicle->track_direction = outputDirection;
			vehicle->track_type |= output.element->properties.track.type << 2;
			trackProgress = 0;
		}

		vehicle->track_progress = trackProgress;
		moveInfo = vehicle_get_move_info(vehicle->var_CD, vehicle->track_type, trackProgress);
		rct_xyz16 unk = {
			.x = moveInfo->x,
			.y = moveInfo->y,
			.z = moveInfo->z
		};

		unk.x += vehicle->track_x;
		unk.y += vehicle->track_y;
		unk.z += vehicle->track_z;

		uint8 bx = 0;
		unk.z += RCT2_GLOBAL(0x0097D21A + (ride->type * 8), sint8);
		if (unk.x != unk_F64E20->x)
			bx |= (1 << 0);
		if (unk.y != unk_F64E20->y)
			bx |= (1 << 1);
		if (unk.z != unk_F64E20->z)
			bx |= (1 << 2);

		vehicle->remaining_distance -= RCT2_ADDRESS(0x009A2930, sint32)[bx];
		unk_F64E20->x = unk.x;
		unk_F64E20->y = unk.y;
		unk_F64E20->z = unk.z;

		vehicle->sprite_direction = moveInfo->direction;
		vehicle->var_20 = moveInfo->var_08;
		vehicle->var_1F = moveInfo->var_07;

		if (vehicle->remaining_distance >= 13962) {
			vehicle->acceleration += RCT2_ADDRESS(0x009A2970, sint32)[vehicle->var_1F];
		}
	}
	return true;
}

bool sub_6DF21B_loop(rct_vehicle* vehicle) {
	rct_ride* ride = get_ride(vehicle->ride);
	rct_xyz16 *unk_F64E20 = RCT2_ADDRESS(0x00F64E20, rct_xyz16);

	for (; vehicle->remaining_distance < 0; RCT2_GLOBAL(0x00F64E10, uint32)++) {
		uint16 trackProgress = vehicle->track_progress - 1;
		const rct_vehicle_info *moveInfo;

		if ((sint16)trackProgress == -1) {
			uint8 trackType = vehicle->track_type >> 2;
			RCT2_GLOBAL(0x00F64E36, uint8) = gTrackDefinitions[trackType].vangle_start;
			RCT2_GLOBAL(0x00F64E37, uint8) = gTrackDefinitions[trackType].bank_start;
			rct_map_element* trackElement =
				map_get_track_element_at_of_type_seq(
					vehicle->track_x,
					vehicle->track_y,
					vehicle->track_z / 8,
					trackType,
					0);

			rct_xy_element input;

			input.x = vehicle->track_x;
			input.y = vehicle->track_y;
			input.element = trackElement;
			track_begin_end output;

			if (!track_block_get_previous(input.x, input.y, input.element, &output))
				return false;

			if (gTrackDefinitions[output.begin_element->properties.track.type].vangle_end != RCT2_GLOBAL(0x00F64E36, uint8) ||
				gTrackDefinitions[output.begin_element->properties.track.type].bank_end != RCT2_GLOBAL(0x00F64E37, uint8))
				return false;

			vehicle->track_x = output.begin_x;
			vehicle->track_y = output.begin_y;
			vehicle->track_z = output.begin_z;
			vehicle->track_direction = output.begin_direction;
			vehicle->track_type |= output.begin_element->properties.track.type << 2;

			if (output.begin_element->properties.track.type == TRACK_ELEM_END_STATION) {
				RCT2_GLOBAL(0x00F64E18, uint32) = (1 << 0);
			}

			moveInfo = vehicle_get_move_info(vehicle->var_CD, vehicle->track_type, 0);
			uint16 trackTotalProgress = *((uint16*)((int)moveInfo - 2));
			trackProgress = trackTotalProgress - 1;
		}
		vehicle->track_progress = trackProgress;

		moveInfo = vehicle_get_move_info(vehicle->var_CD, vehicle->track_type, trackProgress);
		rct_xyz16 unk = {
			.x = moveInfo->x,
			.y = moveInfo->y,
			.z = moveInfo->z
		};

		unk.x += vehicle->track_x;
		unk.y += vehicle->track_y;
		unk.z += vehicle->track_z;

		uint8 bx = 0;
		unk.z += RCT2_GLOBAL(0x0097D21A + (ride->type * 8), sint8);
		if (unk.x != unk_F64E20->x)
			bx |= (1 << 0);
		if (unk.y != unk_F64E20->y)
			bx |= (1 << 1);
		if (unk.z != unk_F64E20->z)
			bx |= (1 << 2);

		vehicle->remaining_distance += RCT2_ADDRESS(0x009A2930, sint32)[bx];
		unk_F64E20->x = unk.x;
		unk_F64E20->y = unk.y;
		unk_F64E20->z = unk.z;

		vehicle->sprite_direction = moveInfo->direction;
		vehicle->var_20 = moveInfo->var_08;
		vehicle->var_1F = moveInfo->var_07;

		if (vehicle->remaining_distance < 0) {
			vehicle->acceleration += RCT2_ADDRESS(0x009A2970, sint32)[vehicle->var_1F];
		}
	}
	return true;
}

/**
 *
 *  rct2: 0x006DEF56
 */
int cable_lift_update_track_motion(rct_vehicle *cableLift)
{
	rct_ride_type* rideEntry = get_ride_entry(cableLift->ride_subtype);
	rct_ride_type_vehicle* vehicleEntry = &rideEntry->vehicles[cableLift->vehicle_type];
	rct_ride* ride = get_ride(cableLift->ride);

	RCT2_GLOBAL(0x00F64E2C, uint8) = 0;
	RCT2_GLOBAL(0x00F64E04, rct_vehicle*) = cableLift;
	RCT2_GLOBAL(0x00F64E18, uint32) = 0;
	RCT2_GLOBAL(0x00F64E1C, uint32) = (uint32)-1;

	cableLift->velocity += cableLift->acceleration;
	RCT2_GLOBAL(0x00F64E08, sint32) = cableLift->velocity;
	RCT2_GLOBAL(0x00F64E0C, sint32) = (cableLift->velocity / 1024) * 42;

	rct_vehicle* frontVehicle = cableLift;
	if (cableLift->velocity < 0) {
		frontVehicle = vehicle_get_tail(cableLift);
	}

	RCT2_GLOBAL(0x00F64E00, rct_vehicle*) = frontVehicle;

	for (rct_vehicle* vehicle = frontVehicle;;) {
		vehicle->acceleration = RCT2_ADDRESS(0x009A2970, sint32)[vehicle->var_1F];
		RCT2_GLOBAL(0x00F64E10, uint32) = 1;
		vehicle->remaining_distance += RCT2_GLOBAL(0x00F64E0C, sint32);

		if (vehicle->remaining_distance < 0 || vehicle->remaining_distance >= 13962) {
			rct_xyz16 *unk_F64E20 = RCT2_ADDRESS(0x00F64E20, rct_xyz16);
			unk_F64E20->x = vehicle->x;
			unk_F64E20->y = vehicle->y;
			unk_F64E20->z = vehicle->z;
			invalidate_sprite_2((rct_sprite*)vehicle);

			while (true) {
				if (vehicle->remaining_distance < 0) {
					if (sub_6DF21B_loop(vehicle) == true) {
						break;
					}
					else {
						RCT2_GLOBAL(0x00F64E18, uint32) |= (1 << 5);
						RCT2_GLOBAL(0x00F64E0C, uint32) -= vehicle->remaining_distance - 13962;
						vehicle->remaining_distance = 13962;
						vehicle->acceleration += RCT2_ADDRESS(0x009A2970, uint32)[vehicle->var_1F];
						RCT2_GLOBAL(0x00F64E10, uint32)++;
						continue;
					}
				}
				else {
					if (sub_6DF01A_loop(vehicle) == true) {
						break;
					}
					else {
						RCT2_GLOBAL(0x00F64E18, uint32) |= (1 << 5);
						RCT2_GLOBAL(0x00F64E0C, uint32) -= vehicle->remaining_distance + 1;
						vehicle->remaining_distance = -1;
						vehicle->acceleration += RCT2_ADDRESS(0x009A2970, uint32)[vehicle->var_1F];
						RCT2_GLOBAL(0x00F64E10, uint32)++;
					}
				}
			}
			sprite_move(
				unk_F64E20->x,
				unk_F64E20->y,
				unk_F64E20->z,
				(rct_sprite*)vehicle);

			invalidate_sprite_2((rct_sprite*)vehicle);
		}
		vehicle->acceleration /= RCT2_GLOBAL(0x00F64E10, uint32);
		if (RCT2_GLOBAL(0x00F64E08, sint32) >= 0) {
			if (vehicle->next_vehicle_on_train == 0xFFFF)
				break;
			vehicle = GET_VEHICLE(vehicle->next_vehicle_on_train);
		}
		else {
			if (vehicle == cableLift)
				break;
			vehicle = GET_VEHICLE(vehicle->prev_vehicle_on_ride);
		}
	}

	uint32 vehicleCount = 0;
	uint16 frictionTotal = 0;
	sint32 var2CTotal = 0;

	for (uint16 spriteId = cableLift->sprite_index; spriteId != 0xFFFF;) {
		rct_vehicle* vehicle = GET_VEHICLE(spriteId);
		vehicleCount++;
		frictionTotal += vehicle->friction;
		var2CTotal += vehicle->acceleration;
		spriteId = vehicle->next_vehicle_on_train;
	}

	sint32 ecx = (var2CTotal / vehicleCount) >> 9;
	ecx -= cableLift->velocity >> 12;

	sint32 edx = cableLift->velocity >> 8;
	edx *= edx;
	if (cableLift->velocity < 0)
		edx = -edx;
	edx >>= 4;
	ecx -= edx / frictionTotal;

	cableLift->acceleration = ecx;
	return RCT2_GLOBAL(0x00F64E18, uint32);
}
