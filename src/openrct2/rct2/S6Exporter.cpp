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

#include "../core/Exception.hpp"
#include "../core/FileStream.hpp"
#include "../core/IStream.hpp"
#include "../core/String.hpp"
#include "../management/award.h"
#include "../object/Object.h"
#include "../object/ObjectManager.h"
#include "../object/ObjectRepository.h"
#include "../rct12/SawyerChunkWriter.h"
#include "S6Exporter.h"

extern "C"
{
    #include "../config/Config.h"
    #include "../game.h"
    #include "../interface/viewport.h"
    #include "../interface/window.h"
    #include "../localisation/date.h"
    #include "../localisation/localisation.h"
    #include "../management/finance.h"
    #include "../management/marketing.h"
    #include "../management/news_item.h"
    #include "../management/research.h"
    #include "../object.h"
    #include "../OpenRCT2.h"
    #include "../peep/staff.h"
    #include "../rct2.h"
    #include "../ride/ride.h"
    #include "../ride/ride_ratings.h"
    #include "../scenario/scenario.h"
    #include "../util/sawyercoding.h"
    #include "../util/util.h"
    #include "../world/climate.h"
    #include "../world/map_animation.h"
    #include "../world/park.h"
}

S6Exporter::S6Exporter()
{
    RemoveTracklessRides = false;
    memset(&_s6, 0, sizeof(_s6));
}

void S6Exporter::SaveGame(const utf8 * path)
{
    auto fs = FileStream(path, FILE_MODE_WRITE);
    SaveGame(&fs);
}

void S6Exporter::SaveGame(IStream * stream)
{
    Save(stream, false);
}

void S6Exporter::SaveScenario(const utf8 * path)
{
    auto fs = FileStream(path, FILE_MODE_WRITE);
    SaveScenario(&fs);
}

void S6Exporter::SaveScenario(IStream * stream)
{
    Save(stream, true);
}

void S6Exporter::Save(IStream * stream, bool isScenario)
{
    _s6.header.type = isScenario ? S6_TYPE_SCENARIO : S6_TYPE_SAVEDGAME;
    _s6.header.classic_flag = 0;
    _s6.header.num_packed_objects = uint16(ExportObjectsList.size());
    _s6.header.version = S6_RCT2_VERSION;
    _s6.header.magic_number = S6_MAGIC_NUMBER;
    _s6.game_version_number = 201028;

    auto chunkWriter = SawyerChunkWriter(stream);

    // 0: Write header chunk
    chunkWriter.WriteChunk(&_s6.header, SAWYER_ENCODING::ROTATE);

    // 1: Write scenario info chunk
    if (_s6.header.type == S6_TYPE_SCENARIO)
    {
        chunkWriter.WriteChunk(&_s6.info, SAWYER_ENCODING::ROTATE);
    }

    // 2: Write packed objects
    if (_s6.header.num_packed_objects > 0)
    {
        IObjectRepository * objRepo = GetObjectRepository();
        objRepo->WritePackedObjects(stream, ExportObjectsList);
    }

    // 3: Write available objects chunk
    chunkWriter.WriteChunk(_s6.objects, sizeof(_s6.objects), SAWYER_ENCODING::ROTATE);

    // 4: Misc fields (data, rand...) chunk
    chunkWriter.WriteChunk(&_s6.elapsed_months, 16, SAWYER_ENCODING::RLECOMPRESSED);

    // 5: Map elements + sprites and other fields chunk
    chunkWriter.WriteChunk(&_s6.map_elements, 0x180000, SAWYER_ENCODING::RLECOMPRESSED);

    if (_s6.header.type == S6_TYPE_SCENARIO)
    {
        // 6 to 13:
        chunkWriter.WriteChunk(&_s6.next_free_map_element_pointer_index, 0x27104C, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.guests_in_park, 4, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.last_guests_in_park, 8, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.park_rating, 2, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.active_research_types, 1082, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.current_expenditure, 16, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.park_value, 4, SAWYER_ENCODING::RLECOMPRESSED);
        chunkWriter.WriteChunk(&_s6.completed_company_value, 0x761E8, SAWYER_ENCODING::RLECOMPRESSED);
    }
    else
    {
        // 6: Everything else...
        chunkWriter.WriteChunk(&_s6.next_free_map_element_pointer_index, 0x2E8570, SAWYER_ENCODING::RLECOMPRESSED);
    }

    // Determine number of bytes written
    size_t fileSize = stream->GetLength();

    // Read all written bytes back into a single buffer
    stream->SetPosition(0);
    auto data = std::unique_ptr<uint8>(stream->ReadArray<uint8>(fileSize));
    uint32 checksum = sawyercoding_calculate_checksum(data.get(), fileSize);

    // Write the checksum on the end
    stream->SetPosition(fileSize);
    stream->WriteValue(checksum);
}

void S6Exporter::Export()
{
    _s6.info = gS6Info;

    for (sint32 i = 0; i < OBJECT_ENTRY_COUNT; i++)
    {
        const rct_object_entry * entry = get_loaded_object_entry(i);
        void * entryData = get_loaded_object_chunk(i);
        if (entryData == (void *)-1)
        {
            Memory::Set(&_s6.objects[i], 0xFF, sizeof(rct_object_entry));
        }
        else
        {
            _s6.objects[i] = *((rct_object_entry*)entry);
        }
    }

    _s6.elapsed_months = gDateMonthsElapsed;
    _s6.current_day = gDateMonthTicks;
    _s6.scenario_ticks = gScenarioTicks;
    _s6.scenario_srand_0 = gScenarioSrand0;
    _s6.scenario_srand_1 = gScenarioSrand1;

    memcpy(_s6.map_elements, gMapElements, sizeof(_s6.map_elements));

    _s6.next_free_map_element_pointer_index = gNextFreeMapElementPointerIndex;
    for (sint32 i = 0; i < MAX_SPRITES; i++)
    {
        memcpy(&_s6.sprites[i], get_sprite(i), sizeof(rct_sprite));
    }

    for (sint32 i = 0; i < NUM_SPRITE_LISTS; i++)
    {
        _s6.sprite_lists_head[i] = gSpriteListHead[i];
        _s6.sprite_lists_count[i] = gSpriteListCount[i];
    }
    _s6.park_name = gParkName;
    // pad_013573D6
    _s6.park_name_args = gParkNameArgs;
    _s6.initial_cash = gInitialCash;
    _s6.current_loan = gBankLoan;
    _s6.park_flags = gParkFlags;
    _s6.park_entrance_fee = gParkEntranceFee;
    // rct1_park_entrance_x
    // rct1_park_entrance_y
    // pad_013573EE
    // rct1_park_entrance_z
    memcpy(_s6.peep_spawns, gPeepSpawns, sizeof(_s6.peep_spawns));
    _s6.guest_count_change_modifier = gGuestChangeModifier;
    _s6.current_research_level = gResearchFundingLevel;
    // pad_01357400
    memcpy(_s6.researched_ride_types, gResearchedRideTypes, sizeof(_s6.researched_ride_types));
    memcpy(_s6.researched_ride_entries, gResearchedRideEntries, sizeof(_s6.researched_ride_entries));
    memcpy(_s6.researched_track_types_a, gResearchedTrackTypesA, sizeof(_s6.researched_track_types_a));
    memcpy(_s6.researched_track_types_b, gResearchedTrackTypesB, sizeof(_s6.researched_track_types_b));

    _s6.guests_in_park = gNumGuestsInPark;
    _s6.guests_heading_for_park = gNumGuestsHeadingForPark;

    memcpy(_s6.expenditure_table, gExpenditureTable, sizeof(_s6.expenditure_table));

    _s6.last_guests_in_park = gNumGuestsInParkLastWeek;
    // pad_01357BCA
    _s6.handyman_colour = gStaffHandymanColour;
    _s6.mechanic_colour = gStaffMechanicColour;
    _s6.security_colour = gStaffSecurityColour;

    memcpy(_s6.researched_scenery_items, gResearchedSceneryItems, sizeof(_s6.researched_scenery_items));

    _s6.park_rating = gParkRating;

    memcpy(_s6.park_rating_history, gParkRatingHistory, sizeof(_s6.park_rating_history));
    memcpy(_s6.guests_in_park_history, gGuestsInParkHistory, sizeof(_s6.guests_in_park_history));

    _s6.active_research_types = gResearchPriorities;
    _s6.research_progress_stage = gResearchProgressStage;
    _s6.last_researched_item_subject = gResearchLastItemSubject;
    // pad_01357CF8
    _s6.next_research_item = gResearchNextItem;
    _s6.research_progress = gResearchProgress;
    _s6.next_research_category = gResearchNextCategory;
    _s6.next_research_expected_day = gResearchExpectedDay;
    _s6.next_research_expected_month = gResearchExpectedMonth;
    _s6.guest_initial_happiness = gGuestInitialHappiness;
    _s6.park_size = gParkSize;
    _s6.guest_generation_probability = _guestGenerationProbability;
    _s6.total_ride_value = gTotalRideValue;
    _s6.maximum_loan = gMaxBankLoan;
    _s6.guest_initial_cash = gGuestInitialCash;
    _s6.guest_initial_hunger = gGuestInitialHunger;
    _s6.guest_initial_thirst = gGuestInitialThirst;
    _s6.objective_type = gScenarioObjectiveType;
    _s6.objective_year = gScenarioObjectiveYear;
    // pad_013580FA
    _s6.objective_currency = gScenarioObjectiveCurrency;
    _s6.objective_guests = gScenarioObjectiveNumGuests;
    memcpy(_s6.campaign_weeks_left, gMarketingCampaignDaysLeft, sizeof(_s6.campaign_weeks_left));
    memcpy(_s6.campaign_ride_index, gMarketingCampaignRideIndex, sizeof(_s6.campaign_ride_index));

    memcpy(_s6.balance_history, gCashHistory, sizeof(_s6.balance_history));

    _s6.current_expenditure = gCurrentExpenditure;
    _s6.current_profit = gCurrentProfit;
    _s6.weekly_profit_average_dividend = gWeeklyProfitAverageDividend;
    _s6.weekly_profit_average_divisor = gWeeklyProfitAverageDivisor;
    // pad_0135833A

    memcpy(_s6.weekly_profit_history, gWeeklyProfitHistory, sizeof(_s6.weekly_profit_history));

    _s6.park_value = gParkValue;

    memcpy(_s6.park_value_history, gParkValueHistory, sizeof(_s6.park_value_history));

    _s6.completed_company_value = gScenarioCompletedCompanyValue;
    _s6.total_admissions = gTotalAdmissions;
    _s6.income_from_admissions = gTotalIncomeFromAdmissions;
    _s6.company_value = gCompanyValue;
    memcpy(_s6.peep_warning_throttle, gPeepWarningThrottle, sizeof(_s6.peep_warning_throttle));

    // Awards
    for (sint32 i = 0; i < RCT12_MAX_AWARDS; i++)
    {
        Award * src = &gCurrentAwards[i];
        rct12_award * dst = &_s6.awards[i];
        dst->time = src->Time;
        dst->type = src->Type;
    }

    _s6.land_price = gLandPrice;
    _s6.construction_rights_price = gConstructionRightsPrice;
    // unk_01358774
    // pad_01358776
    // _s6.cd_key
    // _s6.game_version_number
    _s6.completed_company_value_record = gScenarioCompanyValueRecord;
    _s6.loan_hash = GetLoanHash(gInitialCash, gBankLoan, gMaxBankLoan);
    _s6.ride_count = gRideCount;
    // pad_013587CA
    _s6.historical_profit = gHistoricalProfit;
    // pad_013587D4
    memcpy(_s6.scenario_completed_name, gScenarioCompletedBy, sizeof(_s6.scenario_completed_name));
    _s6.cash = gCashEncrypted;
    // pad_013587FC
    _s6.park_rating_casualty_penalty = gParkRatingCasualtyPenalty;
    _s6.map_size_units = gMapSizeUnits;
    _s6.map_size_minus_2 = gMapSizeMinus2;
    _s6.map_size = gMapSize;
    _s6.map_max_xy = gMapSizeMaxXY;
    _s6.same_price_throughout = gSamePriceThroughoutParkA;
    _s6.suggested_max_guests = _suggestedGuestMaximum;
    _s6.park_rating_warning_days = gScenarioParkRatingWarningDays;
    _s6.last_entrance_style = gLastEntranceStyle;
    // rct1_water_colour
    // pad_01358842
    memcpy(_s6.research_items, gResearchItems, sizeof(_s6.research_items));
    _s6.map_base_z = gMapBaseZ;
    memcpy(_s6.scenario_name, gScenarioName, sizeof(_s6.scenario_name));
    memcpy(_s6.scenario_description, gScenarioDetails, sizeof(_s6.scenario_description));
    _s6.current_interest_rate = gBankLoanInterestRate;
    // pad_0135934B
    _s6.same_price_throughout_extended = gSamePriceThroughoutParkB;
    // Preserve compatibility with vanilla RCT2's save format.
    for (uint8 i = 0; i < RCT12_MAX_PARK_ENTRANCES; i++)
    {
        _s6.park_entrance_x[i] = gParkEntrances[i].x;
        _s6.park_entrance_y[i] = gParkEntrances[i].y;
        _s6.park_entrance_z[i] = gParkEntrances[i].z;
        _s6.park_entrance_direction[i] = gParkEntrances[i].direction;
    }
    safe_strcpy(_s6.scenario_filename, _scenarioFileName, sizeof(_s6.scenario_filename));
    memcpy(_s6.saved_expansion_pack_names, gScenarioExpansionPacks, sizeof(_s6.saved_expansion_pack_names));
    memcpy(_s6.banners, gBanners, sizeof(_s6.banners));
    memcpy(_s6.custom_strings, gUserStrings, sizeof(_s6.custom_strings));
    _s6.game_ticks_1 = gCurrentTicks;
    memcpy(_s6.rides, gRideList, sizeof(_s6.rides));
    _s6.saved_age = gSavedAge;
    _s6.saved_view_x = gSavedViewX;
    _s6.saved_view_y = gSavedViewY;
    _s6.saved_view_zoom = gSavedViewZoom;
    _s6.saved_view_rotation = gSavedViewRotation;
    memcpy(_s6.map_animations, gAnimatedObjects, sizeof(_s6.map_animations));
    _s6.num_map_animations = gNumMapAnimations;
    // pad_0138B582

    _s6.ride_ratings_calc_data = gRideRatingsCalcData;
    memcpy(_s6.ride_measurements, gRideMeasurements, sizeof(_s6.ride_measurements));
    _s6.next_guest_index = gNextGuestNumber;
    _s6.grass_and_scenery_tilepos = gGrassSceneryTileLoopPosition;
    memcpy(_s6.patrol_areas, gStaffPatrolAreas, sizeof(_s6.patrol_areas));
    memcpy(_s6.staff_modes, gStaffModes, sizeof(_s6.staff_modes));
    // unk_13CA73E
    // pad_13CA73F
    _s6.byte_13CA740 = gUnk13CA740;
    _s6.climate = gClimate;
    // pad_13CA741;
    // byte_13CA742
    // pad_013CA747
    _s6.climate_update_timer = gClimateUpdateTimer;
    _s6.current_weather = gClimateCurrentWeather;
    _s6.next_weather = gClimateNextWeather;
    _s6.temperature = gClimateCurrentTemperature;
    _s6.next_temperature = gClimateNextTemperature;
    _s6.current_weather_effect = gClimateCurrentWeatherEffect;
    _s6.next_weather_effect = gClimateNextWeatherEffect;
    _s6.current_weather_gloom = gClimateCurrentWeatherGloom;
    _s6.next_weather_gloom = gClimateNextWeatherGloom;
    _s6.current_rain_level = gClimateCurrentRainLevel;
    _s6.next_rain_level = gClimateNextRainLevel;

    // News items
    for (size_t i = 0; i < RCT12_MAX_NEWS_ITEMS; i++)
    {
        const NewsItem * src = &gNewsItems[i];
        rct12_news_item * dst = &_s6.news_items[i];

        dst->Type = src->Type;
        dst->Flags = src->Flags;
        dst->Assoc = src->Assoc;
        dst->Ticks = src->Ticks;
        dst->MonthYear = src->MonthYear;
        dst->Day = src->Day;
        memcpy(dst->Text, src->Text, sizeof(dst->Text));
    }

    // pad_13CE730
    // rct1_scenario_flags
    _s6.wide_path_tile_loop_x = gWidePathTileLoopX;
    _s6.wide_path_tile_loop_y = gWidePathTileLoopY;
    // pad_13CE778

    String::Set(_s6.scenario_filename, sizeof(_s6.scenario_filename), _scenarioFileName);

    if (RemoveTracklessRides)
    {
        scenario_remove_trackless_rides(&_s6);
    }

    scenario_fix_ghosts(&_s6);
    game_convert_strings_to_rct2(&_s6);
}

uint32 S6Exporter::GetLoanHash(money32 initialCash, money32 bankLoan, uint32 maxBankLoan)
{
    sint32 value = 0x70093A;
    value -= initialCash;
    value = ror32(value, 5);
    value -= bankLoan;
    value = ror32(value, 7);
    value += maxBankLoan;
    value = ror32(value, 3);
    return value;
}

extern "C"
{
    enum {
        S6_SAVE_FLAG_EXPORT    = 1 << 0,
        S6_SAVE_FLAG_SCENARIO  = 1 << 1,
        S6_SAVE_FLAG_AUTOMATIC = 1u << 31,
    };

    /**
     *
     *  rct2: 0x006754F5
     * @param flags bit 0: pack objects, 1: save as scenario
     */
    sint32 scenario_save(const utf8 * path, sint32 flags)
    {
        if (flags & S6_SAVE_FLAG_SCENARIO)
        {
            log_verbose("saving scenario");
        }
        else
        {
            log_verbose("saving game");
        }

        if (!(flags & S6_SAVE_FLAG_AUTOMATIC))
        {
            window_close_construction_windows();
        }

        map_reorganise_elements();
        sprite_clear_all_unused();

        viewport_set_saved_view();

        bool result = false;
        auto s6exporter = new S6Exporter();
        try
        {
            if (flags & S6_SAVE_FLAG_EXPORT)
            {
                IObjectManager * objManager = GetObjectManager();
                s6exporter->ExportObjectsList = objManager->GetPackableObjects();
            }
            s6exporter->RemoveTracklessRides = true;
            s6exporter->Export();
            if (flags & S6_SAVE_FLAG_SCENARIO)
            {
                s6exporter->SaveScenario(path);
            }
            else
            {
                s6exporter->SaveGame(path);
            }
            result = true;
        }
        catch (const Exception &)
        {
        }
        delete s6exporter;

        gfx_invalidate_screen();

        if (result && !(flags & S6_SAVE_FLAG_AUTOMATIC))
        {
            gScreenAge = 0;
        }
        return result;
    }
}
