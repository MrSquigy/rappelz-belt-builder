#pragma once

#include <QMap>
#include "stats.h"

class BeltBuilder {
public:
    BeltBuilder();

    QMap<Stats::Stat, float> getStatBenefits();

    void resetBuild();

private:
    /* Build stat benefits */
    QMap<Stats::Stat, float> statBenefits;

    void printStats();
};
