#include <catch.hpp>

#include <mockturtle/traits.hpp>
#include <mockturtle/algorithms/mig_algebraic_rewriting.hpp>
#include <mockturtle/algorithms/cut_enumeration.hpp>
#include <mockturtle/networks/mig.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/networks/xag.hpp>
#include <mockturtle/networks/xmg.hpp>
#include <mockturtle/io/aiger_reader.hpp>
#include <mockturtle/io/write_bench.hpp>
#include <mockturtle/io/write_verilog.hpp>
#include <mockturtle/views/depth_view.hpp>
#include <lorina/aiger.hpp>
#include <lorina/blif.hpp>
#include <bits/stdc++.h>

using namespace mockturtle;

TEST_CASE( "MIG depth optimization with associativity", "[mig_algebraic_rewriting]" )
{

  // Recognized network types
  aig_network aig;
  mig_network mig;
  xag_network xag;
  xmg_network xmg;

  // Input networks
  std::string bAddrDir = "../../../networks/addrs/";
  std::vector <std::string> testnets;
  /*testnets.push_back("c1355.aig");
  testnets.push_back("c17.aig");
  testnets.push_back("c1908.aig");
  testnets.push_back("c2670.aig");
  testnets.push_back("c3540.aig");
  testnets.push_back("c432.aig");
  testnets.push_back("c499.aig");
  testnets.push_back("c5315.aig");
  testnets.push_back("c6288.aig");
  testnets.push_back("c7552.aig");
  testnets.push_back("c880.aig");*/
  testnets.push_back("RCAaddr8");
  testnets.push_back("RCAaddr16");
  testnets.push_back("RCAaddr32");
  testnets.push_back("RCAaddr64");

  // rewriting - optimization
  for (int i = 0; i < (int)testnets.size(); i++){

    // read input network
    lorina::read_aiger( bAddrDir + testnets[i] + ".aig", mockturtle::aiger_reader( mig ) );
    depth_view depth_mig{mig};
    
    std::cout << "-------- mig algebraic depth rewriting: " + testnets[i] + " --------- " << std::endl;
    std::cout << "MIG - depth: " << depth_mig.depth() << " num-gates: " << mig.num_gates()  << std::endl; 
    
    /*const auto cuts = cut_enumeration( aig );  
    aig.foreach_node( [&]( auto node ) {
      std::cout << cuts.cuts( aig.node_to_index( node ) ) << "\n";
    } );*/
    
    // mig depth rewriting 
    mig_algebraic_depth_rewriting_params ps; 
    ps.strategy = mig_algebraic_depth_rewriting_params::aggressive;
    //ps.overhead = 10.0;
    mig_algebraic_depth_rewriting( depth_mig, ps );
    std::cout << "MIG - depth: " << depth_mig.depth() << " num-gates: " << mig.num_gates()  << std::endl; 
    		
    // Output network to file
    std::ofstream outfile;
    outfile.open(bAddrDir + testnets[i] + "_mig_rw.v");

    std::ostringstream out;
    write_verilog( mig, out );
    outfile << out.str() << std::endl;
			
  }
  printf("Test Complete\n");
}

TEST_CASE( "MIG depth optimization with complemented associativity", "[mig_algebraic_rewriting]" )
{
  mig_network mig;

  const auto a = mig.create_pi();
  const auto b = mig.create_pi();
  const auto c = mig.create_pi();
  const auto d = mig.create_pi();

  const auto f1 = mig.create_and( a, b );
  const auto f2 = mig.create_and( f1, c );
  const auto f3 = mig.create_or( f2, d );

  mig.create_po( f3 );

  depth_view depth_mig{mig};

  CHECK( depth_mig.depth() == 3 );

  mig_algebraic_depth_rewriting( depth_mig );

  CHECK( depth_mig.depth() == 2 );
}

TEST_CASE( "MIG depth optimization with distributivity", "[mig_algebraic_rewriting]" )
{
  mig_network mig;

  const auto a = mig.create_pi();
  const auto b = mig.create_pi();
  const auto c = mig.create_pi();
  const auto d = mig.create_pi();
  const auto e = mig.create_pi();
  const auto f = mig.create_pi();
  const auto g = mig.create_pi();

  const auto f1 = mig.create_maj( e, f, g );
  const auto f2 = mig.create_maj( c, d, f1 );
  const auto f3 = mig.create_maj( a, b, f2 );

  mig.create_po( f3 );

  depth_view depth_mig{mig};

  CHECK( depth_mig.depth() == 3 );

  mig_algebraic_depth_rewriting( depth_mig );

  CHECK( depth_mig.depth() == 2 );
}
