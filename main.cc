#include "sdf/sdf/sdf.h"

int main(int argc, char **argv)
{
  SDF::SDF sdf = SDF::SDF();
  sdf.write("test.sdf");
  return 0;
}