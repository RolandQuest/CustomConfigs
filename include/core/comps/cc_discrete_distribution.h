#ifndef CC_DISTRIBUTION_H
#define CC_DISTRIBUTION_H

#include <string>
#include <random>
#include <vector>
#include <map>

#include "cc/cc_component.h"
#include "core/comps/cc_base_distribution.h"

namespace cc
{
  //! A discrete distribution class.
  class cc_discrete_distribution : public cc_base_distribution
  {

  protected:

    bool _replacement = true;

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
    std::string cc_component_type() const;


    //! Returns a number from the distribution.
    size_t Next() override;

    //! Returns the size of the distribution.
    size_t Size() override;

    //! Returns the weight at a given position.
    double GetWeightAtPosition( size_t position ) override;

    //!
    double GetCurrentWeightAtPosition( size_t position );

    //! 
    void Reset();

  };

}

#endif // CC_DISTRIBUTION_H
