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

#ifndef _RESEARCH_H_
#define _RESEARCH_H_

#include "../common.h"

#pragma pack(push, 1)
typedef struct rct_research_item {
	// Bit 16 (0: scenery entry, 1: ride entry)
	sint32 entryIndex;
	uint8 category;
} rct_research_item;
assert_struct_size(rct_research_item, 5);
#pragma pack(pop)

enum{
	RESEARCH_ENTRY_FLAG_SCENERY_SET_ALWAYS_RESEARCHED = (1 << 29),
	RESEARCH_ENTRY_FLAG_RIDE_ALWAYS_RESEARCHED = (1 << 30),
};

// Everything before this point has been researched
#define RESEARCHED_ITEMS_SEPARATOR -1
// Everything before this point and after separator still requires research
#define RESEARCHED_ITEMS_END -2
// Extra end of list entry. Unsure why?
#define RESEARCHED_ITEMS_END_2 -3

enum {
	RESEARCH_FUNDING_NONE,
	RESEARCH_FUNDING_MINIMUM,
	RESEARCH_FUNDING_NORMAL,
	RESEARCH_FUNDING_MAXIMUM
};

enum {
	RESEARCH_STAGE_INITIAL_RESEARCH,
	RESEARCH_STAGE_DESIGNING,
	RESEARCH_STAGE_COMPLETING_DESIGN,
	RESEARCH_STAGE_UNKNOWN,
	RESEARCH_STAGE_FINISHED_ALL
};

enum {
	RESEARCH_CATEGORY_TRANSPORT,
	RESEARCH_CATEGORY_GENTLE,
	RESEARCH_CATEGORY_ROLLERCOASTER,
	RESEARCH_CATEGORY_THRILL,
	RESEARCH_CATEGORY_WATER,
	RESEARCH_CATEGORY_SHOP,
	RESEARCH_CATEGORY_SCENERYSET
};

#define gResearchFundingLevel		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_RESEARCH_LEVEL, uint8)
#define gResearchPriorities			RCT2_GLOBAL(RCT2_ADDRESS_ACTIVE_RESEARCH_TYPES, uint8)
#define gResearchProgress			RCT2_GLOBAL(RCT2_ADDRESS_RESEARH_PROGRESS, uint16)
#define gResearchProgressStage		RCT2_GLOBAL(RCT2_ADDRESS_RESEARH_PROGRESS_STAGE, uint8)
#define gResearchLastItemSubject	RCT2_GLOBAL(RCT2_ADDRESS_LAST_RESEARCHED_ITEM_SUBJECT, uint32)
#define gResearchExpectedMonth		RCT2_GLOBAL(RCT2_ADDRESS_NEXT_RESEARCH_EXPECTED_MONTH, uint8)
#define gResearchExpectedDay		RCT2_GLOBAL(RCT2_ADDRESS_NEXT_RESEARCH_EXPECTED_DAY, uint8)
#define gResearchNextCategory		RCT2_GLOBAL(RCT2_ADDRESS_NEXT_RESEARCH_CATEGORY, uint8)
#define gResearchNextItem			RCT2_GLOBAL(RCT2_ADDRESS_NEXT_RESEARCH_ITEM, uint32)

extern rct_research_item *gResearchItems;
extern uint8 gResearchUncompletedCategories;
extern uint32 *gResearchedRideTypes;
extern uint32 *gResearchedRideEntries;
extern uint32 *gResearchedTrackTypesA;
extern uint32 *gResearchedTrackTypesB;
extern uint32 *gResearchedSceneryItems;
extern bool gSilentResearch;

void research_reset_items();
void research_update_uncompleted_types();
void research_update();
void sub_684AC3();
void research_remove_non_separate_vehicle_types();
void research_populate_list_random();
void research_populate_list_researched();

void research_set_funding(int amount);
void research_set_priority(int activeCategories);
void game_command_set_research_funding(int* eax, int* ebx, int* ecx, int* edx, int* esi, int* edi, int* ebp);
void research_finish_item(sint32 entryIndex);
void research_insert(int researched, int entryIndex, int category);
void research_remove(sint32 entryIndex);

void research_insert_ride_entry(uint8 entryIndex, bool researched);
void research_insert_scenery_group_entry(uint8 entryIndex, bool researched);

bool ride_type_is_invented(int rideType);
bool ride_entry_is_invented(int rideEntryIndex);
bool track_type_is_invented(uint8 rideType, int trackType);
bool scenery_is_invented(uint16 sceneryItem);

#endif
