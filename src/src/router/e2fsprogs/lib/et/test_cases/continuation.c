/*
 * continuation.c:
 * This file is automatically generated; please do not edit it.
 */

#include <stdlib.h>

static const char * const text[] = {
	"New password was found in a dictionary of possible passwords and\ntherefore may be easily guessed. Please choose another password.\nSee the ovpasswd man page for help in choosing a good password.",
    0
};

struct error_table {
    char const * const * msgs;
    long base;
    int n_msgs;
};
struct et_list {
    struct et_list *next;
    const struct error_table * table;
};
extern struct et_list *_et_list;

const struct error_table et_ovk_error_table = { text, 43787520L, 1 };

static struct et_list link = { 0, 0 };

void initialize_ovk_error_table_r(struct et_list **list);
void initialize_ovk_error_table(void);

void initialize_ovk_error_table(void) {
    initialize_ovk_error_table_r(&_et_list);
}

/* For Heimdal compatibility */
void initialize_ovk_error_table_r(struct et_list **list)
{
    struct et_list *et, **end;

    for (end = list, et = *list; et; end = &et->next, et = et->next)
        if (et->table->msgs == text)
            return;
    et = malloc(sizeof(struct et_list));
    if (et == 0) {
        if (!link.table)
            et = &link;
        else
            return;
    }
    et->table = &et_ovk_error_table;
    et->next = 0;
    *end = et;
}
