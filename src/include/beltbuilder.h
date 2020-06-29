#pragma once

#include <QMap>
#include "stats.h"

class BeltBuilder {
public:
    BeltBuilder();

    QMap<Stats::Stat, float> getStatBenefits();

    void resetBuild();

    void setBuild(QList<QPair<QString, int>> build);

private:
    /* Build stat benefits */
    QMap<Stats::Stat, float> statBenefits;

    void printStats();

    QList<QPair<Stats::Stat, float>> getPetBenefits(QString pet, int stage);

};
