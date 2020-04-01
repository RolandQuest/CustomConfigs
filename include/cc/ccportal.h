#ifndef CCPORTAL_H
#define CCPORTAL_H

#include <map>
#include <string>
#include <set>
#include <ostream>

#include "cc/cclog.h"
#include "cc/cc_factory.h"
#include "cc/cc_loader.h"
#include "cc/cc_component.h"

namespace cc
{

    /*
    
    Public variables

    */


    //! Used for generating unique names in an iterative fashion.
    const std::string _UniqueNameHeader = "cc_reserved_";

    /**
        Why is this in the header?
    */
    //! The component map used to house all component loaded via the cc portal.
    extern cc_ComponentMap _CompMap;
    

    /*

    Public variables

    */


    //! Loads a configuration file into the cc portal.
    bool load(const std::string& configFile, std::set<std::string>* storage = nullptr);

    //! Initializes all components in the component map.
    bool initialize();

    //! Initializes a single component.
    bool initialize(cc_component* compPointer);

    //! Serializes all components in the component map.
    void serialize(std::ostream& stream);

    //! Serializes a single component.
    void serialize(std::ostream& stream, cc_component* compPointer);

    //! Sets the cc_loader to use on call to load(...).
    cc_loader* setLoader(cc_loader* loader);

    //! Registers factories to be used on call to load(...).
    cc_factory* registerFactory(cc_factory* factory);

    //! Inserts a component into the component map.
    bool insertComponent(cc_component* component);

    //! Clears out the component map. Calls delete on all components.
    void clearComponentMap();

    //! Sets the filebuf of cclog (std::clog).
    void setCCLogFileBuf(std::filebuf* fileBuf);

    //! Checks for the existence of a component in the map.
    bool checkForComponent(const std::string name);

    //! Returns a unique name to be used.
    std::string getUniqueName();


    /*

    Template Functions

    */


    //! Check on the type of a component.
    template<typename Comp>
    bool checkComponentType(const std::string& name)
    {
        if(!checkForComponent(name))
        {
            return false;
        }
        
        return dynamic_cast<Comp*>(_CompMap[name]);
    }
    
    //! Checks for the name in the portal and type. Also logs false returns.
    template<typename Comp>
    bool getComponentCheck(const std::string name)
    {
        if(checkForComponent(name))
        {
            if(checkComponentType<Comp>(name))
            {
                return true;
            }
            else
            {
                Log("cc::getComponentCheck failure: Type check did not succeed on component '", name, "'.");
            }
        }
        else
        {
            Log("cc::getComponentCheck failure: Component of name '", name, "' did not exist in map.");
        }
        return false;
    }
    
    //! Returns a component of the given name as a pointer.
    template<typename Comp>
    Comp* getComponentPointer(const std::string& name)
    {
        if(!getComponentCheck<Comp>(name))
        {
            return nullptr;
        }
        
        cc_component* orig = _CompMap[name];
        Comp* ret = dynamic_cast<Comp*>(orig);
        return ret;
    }
    
    //! Returns a component of the given name as a reference.
    template<typename Comp>
    Comp& getComponent(const std::string& name)
    {
        getComponentCheck<Comp>(name);
        Comp* ret = getComponentPointer<Comp>(name);
        return *ret;
    }
    
}

#endif // CCPORTAL_H





