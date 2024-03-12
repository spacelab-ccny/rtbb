#pragma once
#ifndef __RTBBDATA_H
#define __RTBBDATA_H
/* RTBB Data and Helper Functions */
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 128 /* arbitrary, but may be passed on stack */
typedef int _id_t;

typedef struct {
   int year; /* 1900+year, e.g. 95 for 1995 or 120 for 2020 */
   int month;
   int day;
} Date;

typedef struct {
   _id_t id; /* short identifier */
   char name[MAX_NAME_LEN];
   char county[MAX_NAME_LEN];
   int zip;
   Date dob; /* date of birth */
} Registration;

typedef struct {
   _id_t id; /* short identifier */
   char name[MAX_NAME_LEN];
   int num_votes;
   _id_t office_id;
} Candidate;

typedef struct {
   _id_t id; /* short identifier */
   char name[MAX_NAME_LEN];
   int num_zips;
   int *zips;
   int num_candidates;
   Candidate *candidates;
   _id_t election;
} Office;

typedef enum {
   INACTIVE = 0,
   ACTIVE = 1,
   PUBLISHED = 2,
} Status;
typedef struct {
   _id_t id; /* short identifier */
   Date deadline; /* No more votes allowed after this day */
   int num_offices;
   Office *offices;
   Status status;
} Election;
#endif
