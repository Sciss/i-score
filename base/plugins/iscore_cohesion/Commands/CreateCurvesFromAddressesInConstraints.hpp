#pragma once
#include <iscore/command/AggregateCommand.hpp>

class CreateCurvesFromAddressesInConstraints : public iscore::AggregateCommand
{
    public:
        CreateCurvesFromAddressesInConstraints():
            AggregateCommand{"IScoreCohesionControl",
                             "CreateCurvesFromAddressesInConstraints",
                             "TODO"}
        { }
};