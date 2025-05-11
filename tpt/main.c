#include "TAD_string.h"
#include "TAD_set.h"
#include "TAD_list.h"
#include "TAD_tree.h"
#include <stdlib.h>

int main()
{

    //   tData s1, set1, set2, lis1;

    //   s1 = crearNodoStr(load2("uno")) // -> tData.string

    //       s2 = crearNodoStr(load2("dos")) // -> tData.string

    //       s3 = crearNodoStr(load2("uno")) // -> tData.string

    //       s4 = crearNodoStr(load2("tres")) // -> tData.string

    //       set1 = crearSet();
    //   set2 = crearSet();
    //   append(&set1, s1);
    //   append(&set1, s2);

    //   append(&set1, s3);
    //   append(&set1, s4);

    //   set3 = union(set1, set2)

    //       set3 = append(&set1, set2) return 0;

    List l1 = NULL;
    l1 = createList();
    Str s1 = load2("uno");
    Str s2 = load2("dos");
    Str s3 = load2("tres");

    append(&l1, s1);
    append(&l1, s2);
    append(&l1, s3);
    show(l1);
}
