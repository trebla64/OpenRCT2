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

#ifdef OPENRCT2_BUILD_INFO_HEADER
#include OPENRCT2_BUILD_INFO_HEADER
#endif

#ifdef OPENRCT2_BUILD_NUMBER
	const char *gBuildNumber = OPENRCT2_BUILD_NUMBER;
#else
	const char *gBuildNumber = "";
#endif

#ifdef OPENRCT2_BUILD_SERVER
	const char *gBuildServer = OPENRCT2_BUILD_SERVER;
#else
	const char *gBuildServer = "";
#endif

#ifdef OPENRCT2_BRANCH
	const char *gGitBranch = OPENRCT2_BRANCH;
#else
	const char *gGitBranch = "";
#endif

#ifdef OPENRCT2_COMMIT_SHA1
	const char *gCommitSha1 = OPENRCT2_COMMIT_SHA1;
#else
	const char *gCommitSha1 = "";
#endif

#ifdef OPENRCT2_COMMIT_SHA1_SHORT
	const char *gCommitSha1Short = OPENRCT2_COMMIT_SHA1_SHORT;
#else
	const char *gCommitSha1Short = "";
#endif
