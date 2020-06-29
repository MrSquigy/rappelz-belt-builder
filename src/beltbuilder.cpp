#include <QDebug>
#include <QPair>
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

void BeltBuilder::setBuild(QList<QPair<QString, int>> build) {
    resetBuild();

    for (QPair<QString, int> slot : build) {
        if (slot.first == "None") continue;

        QList<QPair<Stats::Stat, float>> benefits = getPetBenefits(slot.first, slot.second);
        for (QPair<Stats::Stat, float> benefit : benefits) {
            statBenefits[benefit.first] = std::min(statBenefits[benefit.first] + benefit.second, 30.f);
        }
    }
}

QList<QPair<Stats::Stat, float>> BeltBuilder::getPetBenefits(QString pet, int stage) {
    QList<QPair<Stats::Stat, float>> benefits;

    if (pet == "Minotaurus") {
        float benefit = 9.5 + 0.5 * stage;
        benefits.append(QPair<Stats::Stat, float>(Stats::vit, benefit));
        benefits.append(QPair<Stats::Stat, float>(Stats::str, benefit));
        benefits.append(QPair<Stats::Stat, float>(Stats::patk, benefit));
        benefits.append(QPair<Stats::Stat, float>(Stats::pdef, benefit));
    }

    return benefits;
}
