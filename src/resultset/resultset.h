/*
* Copyright 2018-2020 Redis Labs Ltd. and Contributors
*
* This file is available under the Redis Labs Source Available License Agreement
*/

#pragma once

#include "resultset_statistics.h"
#include "../redismodule.h"
#include "../execution_plan/record.h"
#include "rax.h"
#include "./formatters/resultset_formatters.h"

#define RESULTSET_UNLIMITED UINT_MAX
#define RESULTSET_OK 1
#define RESULTSET_FULL 0

typedef struct {
	RedisModuleCtx *ctx;            /* Redis context. */
	GraphContext *gc;               /* Context used for mapping attribute strings and IDs */
	uint column_count;              /* Number of columns in result set. */
	bool compact;                   /* Whether records should be returned in compact form. */
	bool header_emitted;            /* Whether a header row has been issued to the user. */
	const char **columns;           /* Field names for each column of results. */
	size_t recordCount;             /* Number of records introduced. */
	double timer[2];                /* Query runtime tracker. */
	ResultSetStatistics stats;      /* ResultSet statistics. */
	ResultSetFormatter *formatter;  /* ResultSet data formatter. */
} ResultSet;

ResultSet *NewResultSet(RedisModuleCtx *ctx, bool compact);

int ResultSet_AddRecord(ResultSet *set, Record r);

void ResultSet_IndexCreated(ResultSet *set, int status_code);
void ResultSet_IndexDeleted(ResultSet *set, int status_code);

void ResultSet_Replay(ResultSet *set);

void ResultSet_ReportQueryRuntime(RedisModuleCtx *ctx);

void ResultSet_Free(ResultSet *set);

