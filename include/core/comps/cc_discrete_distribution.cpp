#include "cc_discrete_distribution.h"

#include "../../cc/cc_config_helper.h"
#include "cc_core_types.h"

namespace cc
{
  cc_discrete_distribution::cc_discrete_distribution( const std::vector<double>& weights ) {

    _Weights = weights;
    std::discrete_distribution<size_t> clone( std::begin( _Weights ), std::end( _Weights ) );
    _Dist = clone;
  }


  bool cc_discrete_distribution::cc_initialize( cc_kComponentMap& availableComponents ) {

    cc_component::cc_initialize( availableComponents );

    _cc_is_initialized &= cc::AsSingle( _cc_config, "cc_rng", _Rando, availableComponents );
    _cc_is_initialized &= cc::AsVector( _cc_config, "weights", _Weights, TemplateType::kUnsignedDouble );
    cc::AsSingle( _cc_config, "replacement", _replacement, TemplateType::kUnsigned );
    
    _CurrentWeights = _Weights;
    std::discrete_distribution<size_t> clone( std::begin( _CurrentWeights ), std::end( _CurrentWeights ) );
    _Dist = clone;

    return _cc_is_initialized;
  }

  std::string cc_discrete_distribution::cc_component_type() const {
    return cc_discrete_dist_type;
  }

  size_t cc_discrete_distribution::Next() {

    size_t retIndex = _Dist( *_Rando );
    switch(_replacement){
      case 1:
        _CurrentWeights[retIndex] -= 1.0;
        _Dist = std::discrete_distribution<size_t>( std::begin( _CurrentWeights ), std::end( _CurrentWeights ) );
        break;
      case 2:
        _CurrentWeights[retIndex] = 0.0;
        _Dist = std::discrete_distribution<size_t>( std::begin( _CurrentWeights ), std::end( _CurrentWeights ) );
        break;
    }
    return retIndex;
  }

  size_t cc_discrete_distribution::Size() {
    return _Weights.size();
  }

  double cc_discrete_distribution::GetWeightAtPosition( size_t position ) {
    return _Weights[position];
  }

  double cc_discrete_distribution::GetCurrentWeightAtPosition( size_t position ) {
    return _CurrentWeights[position];
  }

  void cc_discrete_distribution::Reset() {
    _CurrentWeights = _Weights;
    _Dist = std::discrete_distribution<size_t>( std::begin( _CurrentWeights ), std::end( _CurrentWeights ) );
  }
  
  void cc_discrete_distribution::SetReplacementStyle( int repl ) {
    _replacement = repl;
  }
  
}
