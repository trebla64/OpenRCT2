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

#ifndef _FINANCE_H_
#define _FINANCE_H_

#include "../common.h"

typedef int rct_expenditure_type;

enum {
	RCT_EXPENDITURE_TYPE_RIDE_CONSTRUCTION,
	RCT_EXPENDITURE_TYPE_RIDE_RUNNING_COSTS,
	RCT_EXPENDITURE_TYPE_LAND_PURCHASE,
	RCT_EXPENDITURE_TYPE_LANDSCAPING,
	RCT_EXPENDITURE_TYPE_PARK_ENTRANCE_TICKETS,
	RCT_EXPENDITURE_TYPE_PARK_RIDE_TICKETS,
	RCT_EXPENDITURE_TYPE_SHOP_SHOP_SALES,
	RCT_EXPENDITURE_TYPE_SHOP_STOCK,
	RCT_EXPENDITURE_TYPE_FOODDRINK_SALES,
	RCT_EXPENDITURE_TYPE_FOODDRINK_STOCK,
	RCT_EXPENDITURE_TYPE_WAGES,
	RCT_EXPENDITURE_TYPE_MARKETING,
	RCT_EXPENDITURE_TYPE_RESEARCH,
	RCT_EXPENDITURE_TYPE_INTEREST,
	RCT_EXPENDITURE_TYPE_COUNT
};

#define EXPENDITURE_TABLE_MONTH_COUNT 16
#define EXPENDITURE_TABLE_TOTAL_COUNT (EXPENDITURE_TABLE_MONTH_COUNT * RCT_EXPENDITURE_TYPE_COUNT)

#define gInitialCash				RCT2_GLOBAL(RCT2_ADDRESS_INITIAL_CASH, money32)
#define gCashEncrypted				RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_MONEY_ENCRYPTED, money32)
#define gBankLoan					RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_LOAN, money32)
#define gBankLoanInterestRate		RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_INTEREST_RATE, sint8)
#define gMaxBankLoan				RCT2_GLOBAL(RCT2_ADDRESS_MAXIMUM_LOAN, money32)
#define gCurrentExpenditure			RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_EXPENDITURE, money32)
#define gCurrentProfit				RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_PROFIT, money32)

extern const money32 research_cost_table[4];

extern money32 *gCashHistory;
extern money32 *gWeeklyProfitHistory;
extern money32 *gParkValueHistory;
extern money32 *gExpenditureTable;

extern uint8 gCommandExpenditureType;

void finance_payment(money32 amount, rct_expenditure_type type);
void finance_pay_wages();
void finance_pay_research();
void finance_pay_interest();
void finance_pay_ride_upkeep();
void finance_reset_history();
void finance_init();
void finance_update_daily_profit();
void finance_shift_expenditure_table();
void finance_update_loan_hash();
void finance_reset_cash_to_initial();

void finance_set_loan(money32 loan);
money32 finance_get_initial_cash();
money32 finance_get_current_loan();
money32 finance_get_maximum_loan();
money32 finance_get_current_cash();
void game_command_set_current_loan(int* eax, int* ebx, int* ecx, int* edx, int* esi, int* edi, int* ebp);

#endif
