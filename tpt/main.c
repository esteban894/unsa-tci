#include "TAD_tree.h"

int main(int argc, char const *argv[])
{

  tData s1, set1, set2, lis1;

  s1 = crearNodoStr(load2("uno")) // -> tData.string

      s2 = crearNodoStr(load2("dos")) // -> tData.string

      s3 = crearNodoStr(load2("uno")) // -> tData.string

      s4 = crearNodoStr(load2("tres")) // -> tData.string

      set1 = crearSet();
  set2 = crearSet();
  append(&set1, s1);
  append(&set1, s2);

  append(&set1, s3);
  append(&set1, s4);

  set3 = union(set1, set2)

      set3 = append(&set1, set2) return 0;
}
