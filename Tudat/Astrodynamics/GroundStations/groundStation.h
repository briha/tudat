#ifndef GROUNDSTATION_H
#define GROUNDSTATION_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "Tudat/Mathematics/BasicMathematics/linearAlgebra.h"
#include "Tudat/Astrodynamics/BasicAstrodynamics/unitConversions.h"
#include "Tudat/Astrodynamics/BasicAstrodynamics/physicalConstants.h"

#include "Tudat/Mathematics/Interpolators/linearInterpolator.h"

#include "Tudat/Astrodynamics/ReferenceFrames/referenceFrameTransformations.h"
#include "Tudat/Astrodynamics/BasicAstrodynamics/timeConversions.h"
#include "Tudat/Astrodynamics/GroundStations/nominalGroundStationState.h"
#include "Tudat/Astrodynamics/GroundStations/pointingAnglesCalculator.h"

namespace tudat
{

namespace ground_stations
{

class GroundStation
{
public:
    GroundStation( const boost::shared_ptr< NominalGroundStationState > stationState,
                   const boost::shared_ptr< PointingAnglesCalculator > pointingAnglesCalculator,
                   const std::string& stationId ):
        nominalStationState_( stationState ), pointingAnglesCalculator_( pointingAnglesCalculator ),
        stationId_( stationId )
    {  }


    //! Function returns nominal (at reference epoch) state of ground station (no velocity included).
    template< typename TimeType >
    basic_mathematics::Vector6d getStateInPlanetFixedFrame( const TimeType& time )
    {
        basic_mathematics::Vector6d stateInPlanetFixedFrame = basic_mathematics::Vector6d::Zero( );
        stateInPlanetFixedFrame.segment( 0, 3 ) = nominalStationState_->getCartesianPositionInTime( static_cast< double >( time ) );
        return stateInPlanetFixedFrame;
    }

    boost::shared_ptr< NominalGroundStationState > getNominalStationState( )
    {
        return nominalStationState_;
    }

    std::string getStationId( )
    {
        return stationId_;
    }

    boost::shared_ptr< PointingAnglesCalculator > getPointingAnglesCalculator( )
    {
        return pointingAnglesCalculator_;
    }

private:

    boost::shared_ptr< NominalGroundStationState > nominalStationState_;

    boost::shared_ptr< PointingAnglesCalculator > pointingAnglesCalculator_;

    std::string stationId_;
};


bool isTargetInView( const double time,
                     const Eigen::Vector3d targetRelativeState,
                     const boost::shared_ptr< PointingAnglesCalculator > pointingAngleCalculator,
                     const double minimumElevationAngle );

}

}

#endif // GROUNDSTATION_H
