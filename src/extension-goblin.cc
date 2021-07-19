#define MIN_LIST_CONCAT_LIMIT 1022

#include <stdlib.h>

#include "bf_register.h"
#include "functions.h"
#include "list.h"
#include "storage.h"
#include "streams.h"
#include "utils.h"
#include "collection.h"

static package
bf_setremove_all(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var dup = var_dup(arglist.v.list[1]);
    int i;

    while ((i = ismember(arglist.v.list[2], dup, 0)) != 0)
	dup = listdelete(dup, i);

    free_var(arglist);
    return make_var_pack(dup);
}
void register_goblin() {
  register_function("setremove_all", 2, 2, bf_setremove_all, TYPE_LIST, TYPE_ANY);
}
