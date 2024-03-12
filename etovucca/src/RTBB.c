#include "RTBB.h"
#include "Database.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ERROR -1
   
static sqlite3 *db;

const char * USAGE = "Usage:\n\
   add-election <deadline date> -> <election id>\n\
   add-office <election id> <name> -> <office id>\n\
   add-candidate <office id> <name> -> <candidate id>\n\
   add-zip <office id> <zip code>\n\
   add-voter <name> <county name> <zip code> <date of birth> -> <voter id>\n\
   open-election <election id>\n\
   close-election <election id>\n\
   publish-election <election id>\n\
   delete-election <election id>\n\
   vote <voter id> <election id> <office id> <candidate id>\n\
   get-elections\n\
   get-voters\n\
";

bool isEligible(_id_t election, _id_t office, _id_t voter);
bool is18AtDeadline(Date dob, Date deadline);
int compareDates(Date a, Date b);

bool parseDate(const char * const date_in, Date *date_out) {
   int year_in, month_in, day_in;
   int result = sscanf(date_in, "%d-%d-%d", &year_in, &month_in, &day_in);
   if (result != 3) {
      fprintf(stderr, "Error parsing date. yyyy-mm-dd\n");
      return false;
   }
   year_in -= 1900;
   if (year_in < 0 || year_in > 255) {
      return false;
   }
   date_out->year = (int)year_in;
   if (month_in < 1 || month_in > 12) {
      return false;
   }
   date_out->month = (int)month_in;
   if (day_in < 1 || day_in > 31) {
      return false;
   }
   date_out->day = (int)day_in;
   return true;
}

void close_db() {
   sqlite3_close(db);
}

int main(int argc, char **argv) {
   if (argc < 2) {
      printf("%s", USAGE);
      return ERROR;
   }
   if (sqlite3_open_v2(DB_PATH, &db,
                       SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX,
                       "unix-none") != SQLITE_OK) {
      printf("Error opening database\n");
      return ERROR;
   }
   if (atexit(close_db)) {
      printf("Error registering callback\n");
      return ERROR;
   }
   if (!strncmp("add-election", argv[1], MAX_NAME_LEN)) {
      if (argc < 3) {
         printf("%s", USAGE);
         return ERROR;
      }
      Date deadline;
      if (!parseDate(argv[2], &deadline)) {
         printf("Invalid date\n");
         return ERROR;
      }
      printf("%d\n", storeElection(db, deadline));
   } else if (!strncmp("add-office", argv[1], MAX_NAME_LEN)) {
      if (argc < 4) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election;
      char name[MAX_NAME_LEN];
      if (sscanf(argv[2], "%d", &election) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      strncpy(name, argv[3], MAX_NAME_LEN-1);
      printf("%d\n", storeOffice(db, election, name));
      return 0;
   } else if (!strncmp("add-candidate", argv[1], MAX_NAME_LEN)) {
      if (argc < 4) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t office;
      char name[MAX_NAME_LEN];
      if (sscanf(argv[2], "%d", &office) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      strncpy(name, argv[3], MAX_NAME_LEN-1);
      printf("%d\n", storeCandidate(db, office, name));
   } else if (!strncmp("add-zip", argv[1], MAX_NAME_LEN)) {
      if (argc < 4) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t office;
      int zip;
      if (sscanf(argv[2], "%d", &office) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      if (sscanf(argv[3], "%d", &zip) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      addZip(db, office, zip);
      return 0;
   } else if (!strncmp("add-voter", argv[1], MAX_NAME_LEN)) {
      if (argc < 6) {
         printf("%s", USAGE);
         return ERROR;
      }
      char name[MAX_NAME_LEN];
      char county[MAX_NAME_LEN];
      int zip;
      Date dob;
      strncpy(name, argv[2], MAX_NAME_LEN-1);
      strncpy(county, argv[3], MAX_NAME_LEN-1);
      if (sscanf(argv[4], "%d", &zip) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      if (!parseDate(argv[5], &dob)) {
         printf("%s", USAGE);
         return ERROR;
      }
      printf("%d\n", storeVoter(db, name, county, zip, dob));
      return 0;
   } else if (!strncmp("open-election", argv[1], MAX_NAME_LEN)) {
      if (argc < 3) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election;
      if (sscanf(argv[2], "%d", &election) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      storeStatus(db, election, ACTIVE);
      return 0;
   } else if (!strncmp("close-election", argv[1], MAX_NAME_LEN)) {
      if (argc < 3) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election;
      if (sscanf(argv[2], "%d", &election) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      storeStatus(db, election, INACTIVE);
      return 0;
   } else if (!strncmp("publish-election", argv[1], MAX_NAME_LEN)) {
      if (argc < 3) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election;
      if (sscanf(argv[2], "%d", &election) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      storeStatus(db, election, PUBLISHED);
      return 0;
   } else if (!strncmp("delete-election", argv[1], MAX_NAME_LEN)) {
      if (argc < 3) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election;
      if (sscanf(argv[2], "%d", &election) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      deleteElection(db, election);
      return 0;
   } else if (!strncmp("vote", argv[1], MAX_NAME_LEN)) {
      if (argc < 6) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t voter_id;
      if (sscanf(argv[2], "%d", &voter_id) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t election_id;
      if (sscanf(argv[3], "%d", &election_id) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t office_id;
      if (sscanf(argv[4], "%d", &office_id) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      _id_t candidate_id;
      if (sscanf(argv[5], "%d", &candidate_id) != 1) {
         printf("%s", USAGE);
         return ERROR;
      }
      if (!isEligible(election_id, office_id, voter_id)) {
         return ERROR;
      }
      storeVote(db, voter_id, candidate_id, office_id);
      return 0;
   } else if (!strncmp("get-elections", argv[1], MAX_NAME_LEN)) {
      getElections(db);
      return 0;
   } else if (!strncmp("get-voters", argv[1], MAX_NAME_LEN)) {
      getVoters(db);
      return 0;
   } else {
      printf("%s", USAGE);
      return ERROR;
   }
   return 0;
}

void getDate(Date *today) {
   time_t curTime = time(NULL);
   struct tm *curDate = localtime(&curTime);
   today->day = (int)(curDate->tm_mday);
   today->month = (int)(curDate->tm_mon+1); /* 0-index to 1-index */
   today->year = (int)(curDate->tm_year);
}

bool isEligible(_id_t election_id, _id_t office_id, _id_t voter_id) {
   Registration registration;
   Election election;
   Date today;
   getDate(&today);
   getVoter(db, voter_id, &registration);
   if (getVote(db, voter_id, office_id) > 0) {
      printf("Already voted\n");
      return false;
   }
   getElection(db, election_id, &election);
   if (election.status != ACTIVE) {
      printf("Election not open\n");
      return false;
   }
   if (!is18AtDeadline(registration.dob, election.deadline)) {
      printf("Voter underage\n");
      return false;
   }
   /* check ballot cast on-time */
   if (compareDates(today, election.deadline) > 0) {
      printf("After deadline\n");
      return false;
   }
   if (!checkZip(db, office_id, registration.zip)) {
      printf("Invalid ZIP code\n");
      return false;
   }
   return true;
}

/* Compare two dates
 * Returns -1 if a is before b
 * Returns  1 if a is after b
 * Returns  0 if a and b are equal
 */
int compareDates(Date a, Date b) {
   if (a.year < b.year) {
      return -1;
   } else if (a.year > b.year) {
      return 1;
   } else if (a.month < b.month) {
      return -1;
   } else if (a.month > b.month) {
      return 1;
   } else if (a.day < b.day) {
      return -1;
   } else if (a.day > b.day) {
      return 1;
   }
   return 0;
}

bool is18AtDeadline(Date dob, Date deadline) {
   int age = deadline.year - dob.year;
   /* if birthday is after deadline */
   if (dob.month > deadline.month ||
       (dob.month == deadline.month &&
        dob.day > deadline.day)) {
      age -= 1; /* then this year doesn't count yet */
   }
   return age >= 18;
}
