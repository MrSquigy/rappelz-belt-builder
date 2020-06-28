#include <QDebug>
#include "include/beltbuilder.h"

BeltBuilder::BeltBuilder() {
    resetBuild();
}

QMap<Stats::Stat, float> BeltBuilder::getStatBenefits() {
    return statBenefits;
}

void BeltBuilder::printStats() {
    qInfo() << "Stat Benefits";
    for (QMap<Stats::Stat, float>::const_iterator i = statBenefits.begin(); i != statBenefits.constEnd(); ++i) {
        qInfo() << i.key() << ": " << i.value();
    }
}

void BeltBuilder::resetBuild() {
    for (int i = Stats::luck; i < Stats::numStats; i++) statBenefits[(Stats::Stat) i] = 0;
}
