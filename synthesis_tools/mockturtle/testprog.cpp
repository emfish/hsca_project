#include <mockturtle/mockturtle.hpp>
#include <lorina/aiger.hpp>
#include <lorina/blif.hpp>

int main(int argc, char* argv[]){

  //network types 
  aig_network aig;
  mig_network mig;
  xag_network xag;
  xmg_network xmg;


  if (argc > 0){
    for (int i = 1; i <= argc; i++){
      lorina.read_aiger( argv[i], mockturtle::aiger_reader( aig ) );

      depth_view depth_aig{aig};
      std::cout << "depth: " << depth_aig.depth() << " num gates" << aig.num_gates()  << endl; 

      const auto cuts = cut_enumeration( aig );  
      aig.foreach_node( [&]( auto node ) {
        std::cout << cuts.cuts( aig.node_to_index( node ) ) << "\n";
      });
    }
  } else {
    printf("specify the input network to optimize in XXXX format\n");
  }
  return 0;
}
