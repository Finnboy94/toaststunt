#include <assert.h>
#include <stdlib.h>
#include "bf_register.h"
#include "collection.h"
#include "functions.h"
#include "list.h"
#include "log.h"
#include "map.h"
#include "options.h"
#include "pattern.h"
#include "program.h"
#include "server.h"
#include "streams.h"
#include "storage.h"
#include "structures.h"
#include "unparse.h"
#include "utils.h"
#include "verbs.h"
static package
bf_find_location(Var arglist, Byte next, void *vdata, Objid progr)
{
Var what = arglist.v.list[1];
Var dest = arglist.v.list[2];
free_var(arglist);
    db_prop_handle h;
    if (!what.is_object()) {
return make_error_pack(E_TYPE);
} else if (!is_valid(what)) {
return make_error_pack(E_INVARG);
} else if (!dest.is_object()) {
return make_error_pack(E_TYPE);
} else if (!is_valid(dest)) {
return make_error_pack(E_INVARG);
}
while (is_valid(what)) {
if (db_object_isa(what, dest)) {
free_var(dest);
return make_var_pack(what);
}
    h = db_find_property(what, "location", 0);
what=db_property_value(h);
}
free_var(what);
free_var(dest);
    return make_var_pack(Var::new_int(0));
}
void
register_custom()
{
register_function("find_location", 2, 2, bf_find_location, TYPE_OBJ, TYPE_OBJ);
}
