#include <catch.hpp>

#include <vector>

#include <mockturtle/algorithms/dont_cares.hpp>
#include <mockturtle/networks/aig.hpp>

using namespace mockturtle;

TEST_CASE( "dont cares in simple AIG", "[dont_cares]" )
{
  aig_network aig;
  auto a = aig.create_pi();
  auto b = aig.create_pi();
  auto f1 = aig.create_and( a, b );
  auto f2 = aig.create_and( a, !b );
  auto f3 = aig.create_and( f1, f2 );
  aig.create_po( f3 );

  std::vector<node<aig_network>> leaves{{aig.get_node( f1 ), aig.get_node( f2 )}};
  const auto tt = satisfiability_dont_cares( aig, leaves );

  CHECK( tt._bits[0] == 0x8u );
}
