#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <string>
#include <random>
#include <vector>
#include <map>

#include "../../cc/cc_component.h"
#include "cc_base_distribution.h"

namespace cc
{
  /**
   * @brief A discrete distribution class.
   * 
   * cc Configuration
   * -------------
   * - "cc_rng" (required) : The rng to use.
   * - "weights" (required) : 1d vector of double weights for each index.
   * - "replacement" (optional) : 0 => WITH replacement, 1 => decrement weight, 2 => zero out weight
   * 
   * Default replacement is WITH replacement.
   * 
   */
  class cc_discrete_distribution : public cc_base_distribution
  {
    
  protected:
  
    size_t _replacement = 0;

    std::vector<double> _Weights;
    std::vector<double> _CurrentWeights;

    std::discrete_distribution<size_t> _Dist;

  public:

    //! Constructor
    cc_discrete_distribution() = default;

    //! Constructor
    cc_discrete_distribution( const std::vector<double>& weights );

    //! Destructor
    virtual ~cc_discrete_distribution() = default;


    //!Initializes the component and linking names in the configuration with actual objects.
    bool cc_initialize( cc::cc_kComponentMap& availableComponents ) override;

    //!Returns the type of the component.
    std::string cc_component_type() const override;


    //! Returns a number from the distribution.
    size_t Next() override;

    //! Returns the size of the distribution.
    size_t Size() override;

    //! Returns the weight at a given position.
    double GetWeightAtPosition( size_t position ) override;

    //! Returns the current weight in cases of no replacement.
    double GetCurrentWeightAtPosition( size_t position );
    
    void SetReplacementStyle( int repl );
    
    //! Resets the distribution in cases of no replacement.
    void Reset();

  };

}

#endif // CC_DISTRIBUTION_H
