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

#ifndef _TRACK_PAINT_H
#define _TRACK_PAINT_H

#include "ride_data.h"
#include "../common.h"
#include "../paint/map_element/map_element.h"
#include "../paint/paint.h"
#include "../world/map.h"

extern const uint8 track_map_2x2[][4];
extern const uint8 edges_2x2[];

extern const uint8 track_map_3x3[][9];
extern const uint8 edges_3x3[];

extern const uint8 track_map_4x4[][16];
extern const uint8 edges_4x4[];

extern const uint8 track_map_1x4[][4];

enum {
	SPR_FLOOR_PLANKS = 3395,
	SPR_FLOOR_PLANKS_90_DEG = 3396,

	SPR_FLOOR_METAL = 14567,
	SPR_FENCE_METAL_NE = 14568,
	SPR_FENCE_METAL_SE = 14569,
	SPR_FENCE_METAL_SW = 14570,
	SPR_FENCE_METAL_NW = 14571,

	SPR_FLOOR_METAL_B = 14989,
	SPR_FENCE_METAL_B_NE = 14990,
	SPR_FENCE_METAL_B_SE = 14991,
	SPR_FENCE_METAL_B_SW = 14992,
	SPR_FENCE_METAL_B_NW = 14993,

	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW = 16870,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW = 16871,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_0 = 16872,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_1 = 16873,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_2 = 16874,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_0 = 16875,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_1 = 16876,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_2 = 16877,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_0 = 16878,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_1 = 16879,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_2 = 16880,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_0 = 16881,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_1 = 16882,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_2 = 16883,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SW_NE = 16884,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NW_SE = 16885,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NE_SW = 16886,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SE_NW = 16887,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SW_NE = 16888,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NW_SE = 16889,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NE_SW = 16890,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SE_NW = 16891,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SW_NE = 16892,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NW_SE = 16893,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NE_SW = 16894,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SE_NW = 16895,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SW_NW = 16896,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NW_NE = 16897,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NE_SE = 16898,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SE_SW = 16899,

    SPR_FLOOR_CORK_SE_SW = 22134,
    SPR_FLOOR_CORK_SW = 22135,
    SPR_FLOOR_CORK_SE = 22136,
    SPR_FLOOR_CORK = 22137,
    SPR_FENCE_ROPE_NE = 22138,
    SPR_FENCE_ROPE_SE = 22139,
    SPR_FENCE_ROPE_SW = 22140,
    SPR_FENCE_ROPE_NW = 22141,

	SPR_STATION_PLATFORM_SW_NE = 22362,
	SPR_STATION_PLATFORM_NW_SE = 22363,
	SPR_STATION_PLATFORM_FENCED_SW_NE = 22364,
	SPR_STATION_PLATFORM_FENCED_NW_SE = 22365,
	SPR_STATION_PLATFORM_BEGIN_FENCED_SW_NE = 22366,
	SPR_STATION_PLATFORM_BEGIN_FENCED_NW_SE = 22367,
	SPR_STATION_PLATFORM_BEGIN_SW_NE = 22368,
	SPR_STATION_PLATFORM_BEGIN_NW_SE = 22369,
	SPR_STATION_FENCE_SW_NE = 22370,
	SPR_STATION_FENCE_NW_SE = 22371,
	SPR_STATION_BEGIN_ANGLE_FENCE_SW_NE = 22372,
	SPR_STATION_BEGIN_ANGLE_FENCE_NW_SE = 22373,
	SPR_STATION_FENCE_SMALL_NW_SE = 22374,
	SPR_STATION_FENCE_SMALL_SW_NE = 22375,

	SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_SW_NE = 22380,
	SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_NW_SE = 22381,
	SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_SW_NE = 22382,
	SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_NW_SE = 22383,
	SPR_STATION_LIGHT_BACK_NE_SW = 22384,
	SPR_STATION_LIGHT_BACK_NW_SE = 22385,
	SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NE_SW = 22386,
	SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NW_SE = 22387,
	SPR_STATION_PLATFORM_END_RED_LIGHT_SW_NE = 22388,
	SPR_STATION_PLATFORM_END_RED_LIGHT_NW_SE = 22389,
	SPR_STATION_PLATFORM_END_GREEN_LIGHT_SW_NE = 22390,
	SPR_STATION_PLATFORM_END_GREEN_LIGHT_NW_SE = 22391,

    SPR_STATION_PIER_EDGE_SE = 22404,
    SPR_STATION_PIER_EDGE_SW = 22405,
    SPR_STATION_PIER_EDGE_NW = 22406,
    SPR_STATION_PIER_EDGE_NE = 22407,
    SPR_STATION_PIER_EDGE_NW_FENCED = 22408,
    SPR_STATION_PIER_EDGE_NE_FENCED = 22409,
    SPR_STATION_PIER_FENCE_SE = 22410,
    SPR_STATION_PIER_FENCE_SW = 22411,
	SPR_STATION_NARROW_EDGE_SE = 22412,
	SPR_STATION_NARROW_EDGE_SW = 22413,
	SPR_STATION_NARROW_EDGE_FENCED_NW = 22414,
	SPR_STATION_NARROW_EDGE_FENCED_NE = 22415,
	SPR_STATION_NARROW_EDGE_NW = 22416,
	SPR_STATION_NARROW_EDGE_NE = 22417,

	SPR_STATION_BASE_A_SW_NE = 22426,
	SPR_STATION_BASE_A_NW_SE = 22427,
	SPR_STATION_BASE_B_SW_NE = 22428,
	SPR_STATION_BASE_B_NW_SE = 22429,

	SPR_STATION_BASE_D = 22432,

	SPR_ON_RIDE_PHOTO_CAMERA_N = 25615,
	SPR_ON_RIDE_PHOTO_CAMERA_E = 25616,
	SPR_ON_RIDE_PHOTO_CAMERA_S = 25617,
	SPR_ON_RIDE_PHOTO_CAMERA_W = 25618,
	SPR_ON_RIDE_PHOTO_CAMERA_FLASH_N = 25619,
	SPR_ON_RIDE_PHOTO_CAMERA_FLASH_E = 25620,
	SPR_ON_RIDE_PHOTO_CAMERA_FLASH_S = 25621,
	SPR_ON_RIDE_PHOTO_CAMERA_FLASH_W = 25622,
	SPR_ON_RIDE_PHOTO_SIGN_SW_NE = 25623,
	SPR_ON_RIDE_PHOTO_SIGN_NW_SE = 25624,
	SPR_ON_RIDE_PHOTO_SIGN_NE_SW = 25625,
	SPR_ON_RIDE_PHOTO_SIGN_SE_NW = 25626,

	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_0 = 28865,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_1 = 28866,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_2 = 28867,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_3 = 28868,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_0 = 28869,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_1 = 28870,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_2 = 28871,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_3 = 28872,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_0 = 28873,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_1 = 28874,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_2 = 28875,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_3 = 28876,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_0 = 28877,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_1 = 28878,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_2 = 28879,
	SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_3 = 28880,
};

enum {
	SCHEME_TRACK = 0,
	SCHEME_SUPPORTS = 1,
	SCHEME_MISC = 2,
	SCHEME_3 = 3,
};

#ifdef NO_RCT2
extern uint32 gTrackColours[4];
#else
#define gTrackColours	RCT2_ADDRESS(0x00F44198, uint32)
#endif

extern const uint32 floorSpritesCork[];

extern const uint32 fenceSpritesRope[];
extern const uint32 fenceSpritesMetalB[];

extern const uint32 trackSpritesSubmarineRideMiniHelicoptersQuarterTurn3Tiles[4][3];
extern const uint32 trackSpritesSubmarineRideMiniHelicoptersQuarterTurn1Tile[4];

extern const uint8 mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[];
extern const rct_xy16 defaultRightQuarterTurn5TilesOffsets[4][5];
extern const rct_xyz16 defaultRightQuarterTurn5TilesBoundOffsets[4][5];
extern const rct_xy16 defaultRightQuarterTurn5TilesBoundLengths[4][5];

extern const uint8 mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[];
extern const rct_xy16 defaultRightQuarterTurn3TilesOffsets[4][3];
extern const rct_xyz16 defaultRightQuarterTurn3TilesBoundOffsets[4][3];
extern const rct_xy16 defaultRightQuarterTurn3TilesBoundLengths[4][3];

extern const rct_xy16 defaultRightHelixUpSmallQuarterBoundLengths[4][3][2];
extern const rct_xyz16 defaultRightHelixUpSmallQuarterBoundOffsets[4][3][2];

extern const rct_xy16 defaultRightHelixUpLargeQuarterBoundLengths[4][5][2];
extern const rct_xyz16 defaultRightHelixUpLargeQuarterBoundOffsets[4][5][2];

extern const rct_xyz16 defaultLeftEighthToDiagBoundOffsets[4][4];
extern const rct_xy16 defaultLeftEighthToDiagBoundLengths[4][4];
extern const rct_xyz16 defaultRightEighthToDiagBoundOffsets[4][4];
extern const rct_xy16 defaultRightEighthToDiagBoundLengths[4][4];
extern const sint8 defaultEighthToDiagThickness[4][4];

extern const rct_xy16 defaultDiagBoundLengths[4];
extern const rct_xy16 defaultDiagTileOffsets[4];

extern bool gUseOriginalRidePaint;

bool track_paint_util_has_fence(enum edge edge, rct_xy16 position, rct_map_element * mapElement, rct_ride * ride, uint8 rotation);
void track_paint_util_paint_floor(uint8 edges, uint32 colourFlags, uint16 height, const uint32 floorSprites[4], uint8 rotation);
void track_paint_util_paint_fences(uint8 edges, rct_xy16 position, rct_map_element * mapElement, rct_ride * ride, uint32 colourFlags, uint16 height, const uint32 fenceSprites[4], uint8 rotation);
bool track_paint_util_draw_station_covers(enum edge edge, bool hasFence, const rct_ride_entrance_definition * entranceStyle, uint8 direction, uint16 height);
void track_paint_util_draw_station_platform(rct_ride *ride, uint8 direction, int height, int zOffset, rct_map_element * mapElement);
void track_paint_util_draw_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement);
bool track_paint_util_should_paint_supports(rct_xy16 position);
void track_paint_util_draw_pier(rct_ride * ride, const rct_ride_entrance_definition * entranceStyle, rct_xy16 position, uint8 direction, int height, rct_map_element * mapElement, uint8 rotation);

void track_paint_util_right_quarter_turn_5_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][5], const rct_xy16 offsets[4][5], const rct_xy16 boundsLengths[4][5], const rct_xyz16 boundsOffsets[4][5], uint8 rotation);
void track_paint_util_right_quarter_turn_5_tiles_paint_2(sint16 height, int direction, uint8 rotation, uint8 trackSequence, uint32 colourFlags, const sprite_bb sprites[][5]);
void track_paint_util_right_quarter_turn_3_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3], const rct_xy16 offsets[4][3], const rct_xy16 boundsLengths[4][3], const rct_xyz16 boundsOffsets[4][3], uint8 rotation);
void track_paint_util_right_quarter_turn_3_tiles_tunnel(sint16 height, uint8 direction, uint8 trackSequence, uint8 tunnelType);
void track_paint_util_left_quarter_turn_3_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3], uint8 rotation);
void track_paint_util_left_quarter_turn_3_tiles_tunnel(sint16 height, uint8 direction, uint8 trackSequence);
void track_paint_util_left_quarter_turn_1_tile_paint(sint8 thickness, sint16 height, sint16 boundBoxZOffset, int direction, uint32 colourFlags, const uint32 * sprites, uint8 rotation);
void track_paint_util_left_quarter_turn_1_tile_tunnel(sint16 height, uint8 direction, uint8 trackSequence);
void track_paint_util_spinning_tunnel_paint(sint8 thickness, sint16 height, uint8 direction, uint8 rotation);
void track_paint_util_right_helix_up_small_quarter_tiles_paint(const sint8 thickness[2], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3][2], const rct_xy16 offsets[4][3][2], const rct_xy16 boundsLengths[4][3][2], const rct_xyz16 boundsOffsets[4][3][2], uint8 rotation);
void track_paint_util_right_helix_up_large_quarter_tiles_paint(const sint8 thickness[2], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][5][2], const rct_xy16 offsets[4][5][2], const rct_xy16 boundsLengths[4][5][2], const rct_xyz16 boundsOffsets[4][5][2], uint8 rotation);
void track_paint_util_eighth_to_diag_tiles_paint(const sint8 thickness[4][4], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][4], const rct_xy16 offsets[4][4], const rct_xy16 boundsLengths[4][4], const rct_xyz16 boundsOffsets[4][4], uint8 rotation);
void track_paint_util_diag_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4], const rct_xy16 offsets[4], const rct_xy16 boundsLengths[4], const rct_xyz16 boundsOffsets[4], uint8 rotation);

typedef void (*TRACK_PAINT_FUNCTION)(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element* mapElement);
typedef TRACK_PAINT_FUNCTION (*TRACK_PAINT_FUNCTION_GETTER)(int trackType, int direction);

TRACK_PAINT_FUNCTION get_track_paint_function_monorail(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_boat_ride(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_car_ride(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_launched_freefall(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_observation_tower(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_chairlift(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_maze(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_spiral_slide(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_go_karts(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_river_rapids(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_dodgems(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_pirate_ship(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_swinging_inverter_ship(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_ferris_wheel(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_motionsimulator(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_3d_cinema(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_topspin(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_space_rings(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_lift(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_shop(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_merry_go_round(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_facility(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_twist(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_haunted_house(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_circus_show(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_ghost_train(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_virginia_reel(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_helicopters(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_golf(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_roto_drop(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_flying_saucers(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_crooked_house(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_monorail_cycles(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_magic_carpet(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_submarine_ride(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_river_rafts(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_enterprise(int trackType, int direction);
TRACK_PAINT_FUNCTION get_track_paint_function_junior_rc(int trackType, int direction);

#endif
