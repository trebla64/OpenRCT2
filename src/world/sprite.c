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

#include "../rct2/addresses.h"
#include "../audio/audio.h"
#include "../cheats.h"
#include "../game.h"
#include "../interface/viewport.h"
#include "../localisation/date.h"
#include "../localisation/localisation.h"
#include "../OpenRCT2.h"
#include "../scenario/scenario.h"
#include "fountain.h"
#include "sprite.h"

#ifdef NO_RCT2
uint16 gSpriteListHead[6];
uint16 gSpriteListCount[6];
static rct_sprite _spriteList[MAX_SPRITES];
#else
uint16 *gSpriteListHead = RCT2_ADDRESS(RCT2_ADDRESS_SPRITE_LISTS_HEAD, uint16);
uint16 *gSpriteListCount = RCT2_ADDRESS(RCT2_ADDRESS_SPRITE_LISTS_COUNT, uint16);
static rct_sprite *_spriteList = RCT2_ADDRESS(RCT2_ADDRESS_SPRITE_LIST, rct_sprite);
#endif

uint16 gSpriteSpatialIndex[0x10001];

static rct_xyz16 _spritelocations1[MAX_SPRITES];
static rct_xyz16 _spritelocations2[MAX_SPRITES];

rct_sprite *get_sprite(size_t sprite_idx)
{
	openrct2_assert(sprite_idx < MAX_SPRITES, "Tried getting sprite %u", sprite_idx);
	return &_spriteList[sprite_idx];
}

uint16 sprite_get_first_in_quadrant(int x, int y)
{
	int offset = ((x & 0x1FE0) << 3) | (y >> 5);
	return gSpriteSpatialIndex[offset];
}

static void invalidate_sprite_max_zoom(rct_sprite *sprite, int maxZoom)
{
	if (sprite->unknown.sprite_left == SPRITE_LOCATION_NULL) return;

	for (int i = 0; i < MAX_VIEWPORT_COUNT; i++) {
		rct_viewport *viewport = &g_viewport_list[i];
		if (viewport->width != 0 && viewport->zoom <= maxZoom) {
			viewport_invalidate(
				viewport,
				sprite->unknown.sprite_left,
				sprite->unknown.sprite_top,
				sprite->unknown.sprite_right,
				sprite->unknown.sprite_bottom
			);
		}
	}
}

/**
 * Invalidate the sprite if at closest zoom.
 *  rct2: 0x006EC60B
 */
void invalidate_sprite_0(rct_sprite* sprite)
{
	invalidate_sprite_max_zoom(sprite, 0);
}

/**
 * Invalidate sprite if at closest zoom or next zoom up from closest.
 *  rct2: 0x006EC53F
 */
void invalidate_sprite_1(rct_sprite *sprite)
{
	invalidate_sprite_max_zoom(sprite, 1);
}

/**
 * Invalidate sprite if not at furthest zoom.
 *  rct2: 0x006EC473
 *
 * @param sprite (esi)
 */
void invalidate_sprite_2(rct_sprite *sprite)
{
	invalidate_sprite_max_zoom(sprite, 2);
}

/**
 *
 *  rct2: 0x0069EB13
 */
void reset_sprite_list()
{
	gSavedAge = 0;
	memset(_spriteList, 0, sizeof(rct_sprite) * MAX_SPRITES);

	for (int i = 0; i < NUM_SPRITE_LISTS; i++) {
		gSpriteListHead[i] = SPRITE_INDEX_NULL;
		gSpriteListCount[i] = 0;
	}

	rct_sprite* previous_spr = (rct_sprite*)SPRITE_INDEX_NULL;

	for (int i = 0; i < MAX_SPRITES; ++i){
		rct_sprite *spr = get_sprite(i);
		spr->unknown.sprite_identifier = SPRITE_IDENTIFIER_NULL;
		spr->unknown.sprite_index = i;
		spr->unknown.next = SPRITE_INDEX_NULL;
		spr->unknown.linked_list_type_offset = 0;

		if (previous_spr != (rct_sprite*)SPRITE_INDEX_NULL){
			spr->unknown.previous = previous_spr->unknown.sprite_index;
			previous_spr->unknown.next = i;
		}
		else{
			spr->unknown.previous = SPRITE_INDEX_NULL;
			gSpriteListHead[SPRITE_LIST_NULL] = i;
		}
		previous_spr = spr;
		spr++;
	}

	gSpriteListCount[SPRITE_LIST_NULL] = MAX_SPRITES;

	reset_sprite_spatial_index();
}

/**
 *
 *  rct2: 0x0069EBE4
 * This function looks as though it sets some sort of order for sprites.
 * Sprites can share thier position if this is the case.
 */
void reset_sprite_spatial_index()
{
	memset(gSpriteSpatialIndex, -1, 0x10001 * sizeof(uint16));
	for (size_t i = 0; i < MAX_SPRITES; i++) {
		rct_sprite *spr = get_sprite(i);
		if (spr->unknown.sprite_identifier != SPRITE_IDENTIFIER_NULL) {
			uint32 index;
			if (spr->unknown.x == SPRITE_LOCATION_NULL) {
				index = 0x10000;
			} else {
				sint16 x = floor2(spr->unknown.x, 32);
				uint8 tileY = spr->unknown.y >> 5;
				index = (x << 3) | tileY;
			}
			uint16 nextSpriteId = gSpriteSpatialIndex[index];
			gSpriteSpatialIndex[index] = spr->unknown.sprite_index;
			spr->unknown.next_in_quadrant = nextSpriteId;
		}
	}
}

#ifndef DISABLE_NETWORK

static unsigned char _spriteChecksum[EVP_MAX_MD_SIZE + 1];

const char * sprite_checksum()
{
	if (EVP_DigestInit_ex(gHashCTX, EVP_sha1(), NULL) <= 0)
	{
		openrct2_assert(false, "Failed to initialise SHA1 engine");
	}
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		rct_sprite *sprite = get_sprite(i);
		if (sprite->unknown.sprite_identifier != SPRITE_IDENTIFIER_NULL && sprite->unknown.sprite_identifier != SPRITE_IDENTIFIER_MISC)
		{
			rct_sprite copy = *sprite;
			copy.unknown.sprite_left = copy.unknown.sprite_right = copy.unknown.sprite_top = copy.unknown.sprite_bottom = 0;
			if (EVP_DigestUpdate(gHashCTX, &copy, sizeof(rct_sprite)) <= 0)
			{
				openrct2_assert(false, "Failed to update digest");
			}
		}
	}
	unsigned char localhash[EVP_MAX_MD_SIZE + 1];
	unsigned int size = sizeof(localhash);
	EVP_DigestFinal(gHashCTX, localhash, &size);
	assert(size <= sizeof(localhash));
	localhash[sizeof(localhash) - 1] = '\0';
	char *x = (char *)_spriteChecksum;
	for (unsigned int i = 0; i < size; i++)
	{
		snprintf(x, EVP_MAX_MD_SIZE + 1, "%02x", localhash[i]);
		x += 2;
	}
	*x = '\0';
	return (char *)_spriteChecksum;
}
#else

const char * sprite_checksum()
{
	return NULL;
}

#endif // DISABLE_NETWORK

/**
 * Clears all the unused sprite memory to zero. Probably so that it can be compressed better when saving.
 *  rct2: 0x0069EBA4
 */
void sprite_clear_all_unused()
{
	rct_unk_sprite *sprite;
	uint16 spriteIndex, nextSpriteIndex, previousSpriteIndex;

	spriteIndex = gSpriteListHead[SPRITE_LIST_NULL];
	while (spriteIndex != SPRITE_INDEX_NULL) {
		sprite = &get_sprite(spriteIndex)->unknown;
		nextSpriteIndex = sprite->next;
		previousSpriteIndex = sprite->previous;
		memset(sprite, 0, sizeof(rct_sprite));
		sprite->sprite_identifier = SPRITE_IDENTIFIER_NULL;
		sprite->next = nextSpriteIndex;
		sprite->previous = previousSpriteIndex;
		sprite->linked_list_type_offset = SPRITE_LIST_NULL * 2;
		sprite->sprite_index = spriteIndex;
		spriteIndex = nextSpriteIndex;
	}
}

static void sprite_reset(rct_unk_sprite *sprite)
{
	// Need to retain how the sprite is linked in lists
	uint8 llto = sprite->linked_list_type_offset;
	uint16 next = sprite->next;
	uint16 prev = sprite->previous;
	uint16 sprite_index = sprite->sprite_index;

	memset(sprite, 0, sizeof(rct_sprite));

	sprite->linked_list_type_offset = llto;
	sprite->next = next;
	sprite->previous = prev;
	sprite->sprite_index = sprite_index;
}

/*
* rct2: 0x0069EC6B
* bl: if bl & 2 > 0, the sprite ends up in the MISC linked list.
*/
rct_sprite *create_sprite(uint8 bl)
{
	size_t linkedListTypeOffset = SPRITE_LIST_UNKNOWN * 2;
	if ((bl & 2) != 0) {
		// 69EC96;
		uint16 cx = 0x12C - gSpriteListCount[SPRITE_LIST_MISC];
		if (cx >= gSpriteListCount[SPRITE_LIST_NULL]) {
			return NULL;
		}
		linkedListTypeOffset = SPRITE_LIST_MISC * 2;
	} else if (gSpriteListCount[SPRITE_LIST_NULL] == 0) {
		return NULL;
	}

	rct_unk_sprite *sprite = &(get_sprite(gSpriteListHead[SPRITE_LIST_NULL]))->unknown;

	move_sprite_to_list((rct_sprite *)sprite, (uint8)linkedListTypeOffset);

	// Need to reset all sprite data, as the uninitialised values
	// may contain garbage and cause a desync later on.
	sprite_reset(sprite);

	sprite->x = SPRITE_LOCATION_NULL;
	sprite->y = SPRITE_LOCATION_NULL;
	sprite->z = 0;
	sprite->name_string_idx = 0;
	sprite->sprite_width = 0x10;
	sprite->sprite_height_negative = 0x14;
	sprite->sprite_height_positive = 0x8;
	sprite->flags = 0;
	sprite->sprite_left = SPRITE_LOCATION_NULL;

	sprite->next_in_quadrant = gSpriteSpatialIndex[0x10000];
	gSpriteSpatialIndex[0x10000] = sprite->sprite_index;

	return (rct_sprite*)sprite;
}

/*
 * rct2: 0x0069ED0B
 * This function moves a sprite to the specified sprite linked list.
 * There are 5/6 of those, and cl specifies a pointer offset
 * of the desired linked list in a uint16 array. Known valid values are
 * 2, 4, 6, 8 or 10 (SPRITE_LIST_... * 2)
 */
void move_sprite_to_list(rct_sprite *sprite, uint8 newListOffset)
{
	rct_unk_sprite *unkSprite = &sprite->unknown;
	uint8 oldListOffset = unkSprite->linked_list_type_offset;
	int oldList = oldListOffset >> 1;
	int newList = newListOffset >> 1;

	// No need to move if the sprite is already in the desired list
	if (oldListOffset == newListOffset) {
		return;
	}

	// If the sprite is currently the head of the list, the
	// sprite following this one becomes the new head of the list.
	if (unkSprite->previous == SPRITE_INDEX_NULL) {
		gSpriteListHead[oldList] = unkSprite->next;
	} else {
		// Hook up sprite->previous->next to sprite->next, removing the sprite from its old list
		get_sprite(unkSprite->previous)->unknown.next = unkSprite->next;
	}

	// Similarly, hook up sprite->next->previous to sprite->previous
	if (unkSprite->next != SPRITE_INDEX_NULL) {
		get_sprite(unkSprite->next)->unknown.previous = unkSprite->previous;
	}

	unkSprite->previous = SPRITE_INDEX_NULL; // We become the new head of the target list, so there's no previous sprite
	unkSprite->linked_list_type_offset = newListOffset;

	unkSprite->next = gSpriteListHead[newList]; // This sprite's next sprite is the old head, since we're the new head
	gSpriteListHead[newList] = unkSprite->sprite_index; // Store this sprite's index as head of its new list

	if (unkSprite->next != SPRITE_INDEX_NULL)
	{
		// Fix the chain by settings sprite->next->previous to sprite_index
		get_sprite(unkSprite->next)->unknown.previous = unkSprite->sprite_index;
	}

	// These globals are probably counters for each sprite list?
	// Decrement old list counter, increment new list counter.
	gSpriteListCount[oldList]--;
	gSpriteListCount[newList]++;
}

/**
 *
 *  rct2: 0x00673200
 */
static void sprite_steam_particle_update(rct_steam_particle *steam)
{
	invalidate_sprite_2((rct_sprite*)steam);

	steam->var_24 += 0x5555;
	if (steam->var_24 < 0x5555) {
		sprite_move(
			steam->x,
			steam->y,
			steam->z + 1,
			(rct_sprite*)steam
		);
	}
	steam->frame += 64;
	if (steam->frame >= (56 * 64)) {
		sprite_remove((rct_sprite*)steam);
	}
}

/**
 *
 *  rct2: 0x0067363D
 */
void sprite_misc_explosion_cloud_create(int x, int y, int z)
{
	rct_unk_sprite *sprite = (rct_unk_sprite*)create_sprite(2);
	if (sprite != NULL) {
		sprite->sprite_width = 44;
		sprite->sprite_height_negative = 32;
		sprite->sprite_height_positive = 34;
		sprite->sprite_identifier = SPRITE_IDENTIFIER_MISC;
		sprite_move(x, y, z + 4, (rct_sprite*)sprite);
		sprite->misc_identifier = SPRITE_MISC_EXPLOSION_CLOUD;
		sprite->frame = 0;
	}
}

/**
 *
 *  rct2: 0x00673385
 */
static void sprite_misc_explosion_cloud_update(rct_sprite * sprite)
{
	invalidate_sprite_2(sprite);
	sprite->unknown.frame += 128;
	if (sprite->unknown.frame >= (36 * 128)) {
		sprite_remove(sprite);
	}
}

/**
 *
 *  rct2: 0x0067366B
 */
void sprite_misc_explosion_flare_create(int x, int y, int z)
{
	rct_unk_sprite *sprite = (rct_unk_sprite*)create_sprite(2);
	if (sprite != NULL) {
		sprite->sprite_width = 25;
		sprite->sprite_height_negative = 85;
		sprite->sprite_height_positive = 8;
		sprite->sprite_identifier = SPRITE_IDENTIFIER_MISC;
		sprite_move(x, y, z + 4, (rct_sprite*)sprite);
		sprite->misc_identifier = SPRITE_MISC_EXPLOSION_FLARE;
		sprite->frame = 0;
	}
}

/**
 *
 *  rct2: 0x006733B4
 */
static void sprite_misc_explosion_flare_update(rct_sprite * sprite)
{
	invalidate_sprite_2(sprite);
	sprite->unknown.frame += 64;
	if (sprite->unknown.frame >= (124 * 64)) {
		sprite_remove(sprite);
	}
}

/**
 *
 *  rct2: 0x006731CD
 */
static void sprite_misc_update(rct_sprite *sprite)
{
	switch (sprite->unknown.misc_identifier) {
	case SPRITE_MISC_STEAM_PARTICLE:
		sprite_steam_particle_update((rct_steam_particle*)sprite);
		break;
	case SPRITE_MISC_MONEY_EFFECT:
		money_effect_update(&sprite->money_effect);
		break;
	case SPRITE_MISC_CRASHED_VEHICLE_PARTICLE:
		crashed_vehicle_particle_update((rct_crashed_vehicle_particle*)sprite);
		break;
	case SPRITE_MISC_EXPLOSION_CLOUD:
		sprite_misc_explosion_cloud_update(sprite);
		break;
	case SPRITE_MISC_CRASH_SPLASH:
		crash_splash_update((rct_crash_splash*)sprite);
		break;
	case SPRITE_MISC_EXPLOSION_FLARE:
		sprite_misc_explosion_flare_update(sprite);
		break;
	case SPRITE_MISC_JUMPING_FOUNTAIN_WATER:
	case SPRITE_MISC_JUMPING_FOUNTAIN_SNOW:
		jumping_fountain_update(&sprite->jumping_fountain);
		break;
	case SPRITE_MISC_BALLOON:
		balloon_update(&sprite->balloon);
		break;
	case SPRITE_MISC_DUCK:
		duck_update(&sprite->duck);
		break;
	}
}

/**
 *
 *  rct2: 0x00672AA4
 */
void sprite_misc_update_all()
{
	rct_sprite *sprite;
	uint16 spriteIndex;

	spriteIndex = gSpriteListHead[SPRITE_LIST_MISC];
	while (spriteIndex != SPRITE_INDEX_NULL) {
		sprite = get_sprite(spriteIndex);
		spriteIndex = sprite->unknown.next;
		sprite_misc_update(sprite);
	}
}

/**
 * Moves a sprite to a new location.
 *  rct2: 0x0069E9D3
 *
 * @param x (ax)
 * @param y (cx)
 * @param z (dx)
 * @param sprite (esi)
 */
void sprite_move(sint16 x, sint16 y, sint16 z, rct_sprite* sprite){
	if (x < 0 || y < 0 || x > 0x1FFF || y > 0x1FFF)
		x = SPRITE_LOCATION_NULL;

	int new_position = x;
	if (x == SPRITE_LOCATION_NULL)new_position = 0x10000;
	else{
		new_position &= 0x1FE0;
		new_position = (y >> 5) | (new_position << 3);
	}

	int current_position = sprite->unknown.x;
	if (sprite->unknown.x == SPRITE_LOCATION_NULL)current_position = 0x10000;
	else{
		current_position &= 0x1FE0;
		current_position = (sprite->unknown.y >> 5) | (current_position << 3);
	}

	if (new_position != current_position){
		uint16* sprite_idx = &gSpriteSpatialIndex[current_position];
		rct_sprite* sprite2 = get_sprite(*sprite_idx);
		while (sprite != sprite2){
			sprite_idx = &sprite2->unknown.next_in_quadrant;
			sprite2 = get_sprite(*sprite_idx);
		}
		*sprite_idx = sprite->unknown.next_in_quadrant;

		int temp_sprite_idx = gSpriteSpatialIndex[new_position];
		gSpriteSpatialIndex[new_position] = sprite->unknown.sprite_index;
		sprite->unknown.next_in_quadrant = temp_sprite_idx;
	}

	if (x == SPRITE_LOCATION_NULL){
		sprite->unknown.sprite_left = SPRITE_LOCATION_NULL;
		sprite->unknown.x = x;
		sprite->unknown.y = y;
		sprite->unknown.z = z;
		return;
	}
	sprite_set_coordinates(x, y, z, sprite);
}

void sprite_set_coordinates(sint16 x, sint16 y, sint16 z, rct_sprite *sprite){
	sint16 new_x = x, new_y = y, start_x = x;
	switch (get_current_rotation()){
	case 0:
		new_x = new_y - new_x;
		new_y = (new_y + start_x) / 2 - z;
		break;
	case 1:
		new_x = -new_y - new_x;
		new_y = (new_y - start_x) / 2 - z;
		break;
	case 2:
		new_x = -new_y + new_x;
		new_y = (-new_y - start_x) / 2 - z;
		break;
	case 3:
		new_x = new_y + new_x;
		new_y = (-new_y + start_x) / 2 - z;
		break;
	}

	sprite->unknown.sprite_left = new_x - sprite->unknown.sprite_width;
	sprite->unknown.sprite_right = new_x + sprite->unknown.sprite_width;
	sprite->unknown.sprite_top = new_y - sprite->unknown.sprite_height_negative;
	sprite->unknown.sprite_bottom = new_y + sprite->unknown.sprite_height_positive;
	sprite->unknown.x = x;
	sprite->unknown.y = y;
	sprite->unknown.z = z;
}

/**
 *
 *  rct2: 0x0069EDB6
 */
void sprite_remove(rct_sprite *sprite)
{
	move_sprite_to_list(sprite, SPRITE_LIST_NULL * 2);
	user_string_free(sprite->unknown.name_string_idx);
	sprite->unknown.sprite_identifier = SPRITE_IDENTIFIER_NULL;

	uint32 quadrantIndex = sprite->unknown.x;
	if (sprite->unknown.x == SPRITE_LOCATION_NULL) {
		quadrantIndex = 0x10000;
	} else {
		quadrantIndex = (floor2(sprite->unknown.x, 32) << 3) | (sprite->unknown.y >> 5);
	}

	uint16 *spriteIndex = &gSpriteSpatialIndex[quadrantIndex];
	rct_sprite *quadrantSprite;
	while ((quadrantSprite = get_sprite(*spriteIndex)) != sprite) {
		spriteIndex = &quadrantSprite->unknown.next_in_quadrant;
	}
	*spriteIndex = sprite->unknown.next_in_quadrant;
}

static bool litter_can_be_at(int x, int y, int z)
{
	rct_map_element *mapElement;

	if (!map_is_location_owned(x & 0xFFE0, y & 0xFFE0, z))
		return false;

	mapElement = map_get_first_element_at(x >> 5, y >> 5);
	do {
		if (map_element_get_type(mapElement) != MAP_ELEMENT_TYPE_PATH)
			continue;

		int pathZ = mapElement->base_height * 8;
		if (pathZ < z || pathZ >= z + 32)
			continue;

		if (map_element_is_underground(mapElement))
			return false;

		return true;
	} while (!map_element_is_last_for_tile(mapElement++));
	return false;
}

/**
 *
 *  rct2: 0x0067375D
 */
void litter_create(int x, int y, int z, int direction, int type)
{
	if (gCheatsDisableLittering)
		return;

	x += TileDirectionDelta[direction >> 3].x / 8;
	y += TileDirectionDelta[direction >> 3].y / 8;

	if (!litter_can_be_at(x, y, z))
		return;

	rct_litter *litter, *newestLitter;
	uint16 spriteIndex, nextSpriteIndex;
	uint32 newestLitterCreationTick;

	if (gSpriteListCount[SPRITE_LIST_LITTER] >= 500) {
		newestLitter = NULL;
		newestLitterCreationTick = 0;
		for (spriteIndex = gSpriteListHead[SPRITE_LIST_LITTER]; spriteIndex != SPRITE_INDEX_NULL; spriteIndex = nextSpriteIndex) {
			litter = &get_sprite(spriteIndex)->litter;
			nextSpriteIndex = litter->next;
			if (newestLitterCreationTick <= litter->creationTick) {
				newestLitterCreationTick = litter->creationTick;
				newestLitter = litter;
			}
		}

		if (newestLitter != NULL) {
			invalidate_sprite_0((rct_sprite*)newestLitter);
			sprite_remove((rct_sprite*)newestLitter);
		}
	}

	litter = (rct_litter*)create_sprite(1);
	if (litter == NULL)
		return;

	move_sprite_to_list((rct_sprite*)litter, SPRITE_LIST_LITTER * 2);
	litter->sprite_direction = direction;
	litter->sprite_width = 6;
	litter->sprite_height_negative = 6;
	litter->sprite_height_positive = 3;
	litter->sprite_identifier = SPRITE_IDENTIFIER_LITTER;
	litter->type = type;
	sprite_move(x, y, z, (rct_sprite*)litter);
	invalidate_sprite_0((rct_sprite*)litter);
	litter->creationTick = gScenarioTicks;
}

/**
 *
 *  rct2: 0x006738E1
 */
void litter_remove_at(int x, int y, int z)
{
	uint16 spriteIndex = sprite_get_first_in_quadrant(x, y);
	while (spriteIndex != SPRITE_INDEX_NULL) {
		rct_sprite *sprite = get_sprite(spriteIndex);
		uint16 nextSpriteIndex = sprite->unknown.next_in_quadrant;
		if (sprite->unknown.linked_list_type_offset == SPRITE_LIST_LITTER * 2) {
			rct_litter *litter = &sprite->litter;

			if (abs(litter->z - z) <= 16) {
				if (abs(litter->x - x) <= 8 && abs(litter->y - y) <= 8) {
					invalidate_sprite_0(sprite);
					sprite_remove(sprite);
				}
			}
		}
		spriteIndex = nextSpriteIndex;
	}
}

/**
 * Determines whether its worth tweening a sprite or not when frame smoothing is on.
 */
static bool sprite_should_tween(rct_sprite *sprite)
{
	switch (sprite->unknown.linked_list_type_offset >> 1) {
	case SPRITE_LIST_VEHICLE:
	case SPRITE_LIST_PEEP:
	case SPRITE_LIST_UNKNOWN:
		return true;
	}
	return false;
}

static void store_sprite_locations(rct_xyz16 * sprite_locations)
{
	for (uint16 i = 0; i < MAX_SPRITES; i++) {
		// skip going through `get_sprite` to not get stalled on assert,
		// this can get very expensive for busy parks with uncap FPS option on
		const rct_sprite *sprite = &_spriteList[i];
		sprite_locations[i].x = sprite->unknown.x;
		sprite_locations[i].y = sprite->unknown.y;
		sprite_locations[i].z = sprite->unknown.z;
	}
}

void sprite_position_tween_store_a()
{
	store_sprite_locations(_spritelocations1);
}

void sprite_position_tween_store_b()
{
	store_sprite_locations(_spritelocations2);
}

void sprite_position_tween_all(float nudge)
{
	for (uint16 i = 0; i < MAX_SPRITES; i++) {
		rct_sprite * sprite = get_sprite(i);
		if (sprite_should_tween(sprite)) {
			rct_xyz16 posA = _spritelocations1[i];
			rct_xyz16 posB = _spritelocations2[i];

			sprite_set_coordinates(
				posB.x + (sint16)((posA.x - posB.x) * nudge),
				posB.y + (sint16)((posA.y - posB.y) * nudge),
				posB.z + (sint16)((posA.z - posB.z) * nudge),
				sprite
			);
			invalidate_sprite_2(sprite);
		}
	}
}

/**
 * Restore the real positions of the sprites so they aren't left at the mid-tween positions
 */
void sprite_position_tween_restore()
{
	for (uint16 i = 0; i < MAX_SPRITES; i++) {
		rct_sprite * sprite = get_sprite(i);
		if (sprite_should_tween(sprite)) {
			invalidate_sprite_2(sprite);

			rct_xyz16 pos = _spritelocations2[i];
			sprite_set_coordinates(pos.x, pos.y, pos.z, sprite);
		}
	}
}

void sprite_position_tween_reset()
{
	for (uint16 i = 0; i < MAX_SPRITES; i++) {
		rct_sprite * sprite = get_sprite(i);
		_spritelocations1[i].x =
		_spritelocations2[i].x = sprite->unknown.x;
		_spritelocations1[i].y =
		_spritelocations2[i].y = sprite->unknown.y;
		_spritelocations1[i].z =
		_spritelocations2[i].z = sprite->unknown.z;
	}
}
