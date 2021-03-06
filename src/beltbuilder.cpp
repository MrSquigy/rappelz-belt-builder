#include <cmath>
#include <QDebug>
#include <QPair>
#include "include/beltbuilder.h"

BeltBuilder::BeltBuilder() : enhance(0) {
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
    float cap = 30.f; // +0 - +19 is 30% stat cap

    // Calculate stat cap
    if (enhance > 0) cap = enhance == 20 ? 31.f : 31.f + (enhance - 20) * 0.5;
    // The enhancement on the belt increases the maximum stat cap
    // from 30% to 33.5%, +20 is 31%, afterwards add 0.5% per enhance

    // Calculate stat benefits
    for (QPair<QString, int> slot : build) {
        if (slot.first == "None") continue;

        QList<QPair<Stats::Stat, float>> benefits = getPetBenefits(slot.first, slot.second);
        for (QPair<Stats::Stat, float> benefit : benefits) {
            statBenefits[benefit.first] = std::min(statBenefits[benefit.first] + benefit.second, cap);
        }
    }
}

void BeltBuilder::setBeltEnhance(int level) {
    enhance = level;
}

QList<QPair<Stats::Stat, float>> BeltBuilder::getPetBenefits(QString pet, int stage) {
    QList<QPair<Stats::Stat, float>> benefits;
    QList<Stats::Stat> stats;
    float benefit = 0;

    if (pet == "Angel") {
        benefit = 7.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::int_, Stats::pdef, Stats::matk});
    }

    if (pet == "Baphomet") {
        benefit = 19 + 1 * stage;
        stats.append({Stats::int_, Stats::castSpd});
    }

    if (pet == "Blight Ogre") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::int_, Stats::patk, Stats::matk});
    }

    if (pet == "Bloodthirsty Slaughterer") {
        benefit = 19 + 1 * stage;
        stats.append({Stats::str, Stats::patk});
    }

    if (pet == "Blue Pixie" || pet == "Red Pixie" || pet == "Octopus") {
        benefit = 11 + 1 * stage;
        stats.append({Stats::int_, Stats::matk});
    }

    if (pet == "Cerberus") {
        benefit = 8.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::dex, Stats::patk, Stats::pacc});
    }

    if (pet == "Crystal Golem") {
        benefit = 19 + 1 * stage;
        stats.append({Stats::vit, Stats::blockDef});
    }

    if (pet == "Crystal Spider") {
        benefit = 8.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::int_});

        // Some pets don't add the same benefit to all stats
        benefits.append(QPair<Stats::Stat, float>(Stats::matk, benefit + 1));
        benefits.append(QPair<Stats::Stat, float>(Stats::macc, benefit + 1));
    }

    if (pet == "Death Gladiator") {
        benefit = 10.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::agi, Stats::patk, Stats::eva});
    }

    if (pet == "Death Tyrant") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::patk, Stats::atkSpd});

        // Some pets don't add the same benefit to all stats
        benefits.append(QPair<Stats::Stat, float>(Stats::str, benefit * 2));
    }

    if (pet == "Drillbot") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::wis, Stats::pdef, Stats::mdef});
    }

    if (pet == "Ethereal Pixie") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::int_, Stats::wis, Stats::matk, Stats::macc});
    }

    if (pet == "Forest Pixie") {
        benefit = 5.5 + 0.5 * stage;
        stats.append({Stats::dex, Stats::agi, Stats::patk, Stats::eva});
    }

    if (pet == "Genie") {
        benefit = 17 + 1 * stage;
        stats.append({Stats::vit, Stats::hpReg});
    }

    if (pet == "Gnoll") {
        benefit = 15 + 1 * stage;
        stats.append({Stats::vit, Stats::blockPer});
    }

    if (pet == "Grandmaster Hector") {
        benefit = 10.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::int_, Stats::patk, Stats::matk});
    }

    if (pet == "Harpy") {
        benefit = 13 + 1 * stage;
        stats.append({Stats::dex, Stats::atkSpd});
    }

    if (pet == "Hawkman") {
        benefit = 6.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::str, Stats::patk, Stats::pdef});
    }

    if (pet == "Ifrit") {
        benefit = 17 + 1 * stage;
        stats.append({Stats::int_, Stats::mpReg});
    }

    if (pet == "Kentauros") {
        benefit = 15 + 1 * stage;
        stats.append({Stats::str, Stats::patk});
    }

    if (pet == "Lydian") {
        benefit = 5.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::str});

        // Some pets don't add the same benefit to all stats
        benefits.append(QPair<Stats::Stat, float>(Stats::pdef, benefit * 2));
    }

    if (pet == "Minotaurus") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::str, Stats::patk, Stats::pdef});
    }

    if (pet == "Naga" || pet == "Ice Maiden") {
        benefit = 15 + 1 * stage;
        stats.append({Stats::int_, Stats::matk});
    }

    if (pet == "Nightmare") {
        benefit = 13 + 1 * stage;
        stats.append({Stats::dex, Stats::pacc});
    }

    if (pet == "Orc") {
        benefit = 5.5 + 0.5 * stage;
        stats.append({Stats::vit, Stats::str, Stats::patk, Stats::pdef});
    }

    if (pet == "Pantera") {
        benefit = 6 + 1 * stage;
        stats.append({Stats::str, Stats::patk});
    }

    if (pet == "Poultry") {
        benefit = 6 + 1 * stage;
        stats.append({Stats::str, Stats::patk});
    }

    if (pet == "Salamander") {
        benefit = 6.5 + 0.5 * stage;
        stats.append({Stats::str, Stats::int_, Stats::patk, Stats::matk});
    }

    if (pet == "Siren") {
        benefit = 5.5 + 0.5 * stage;
        stats.append({Stats::dex, Stats::wis, Stats::pacc, Stats::macc});
    }

    if (pet == "Skeleton") {
        benefit = 11 + 1 * stage;
        stats.append({Stats::agi, Stats::atkSpd});
    }

    if (pet == "Snowman" || pet == "Mystic Koala") {
        benefit = 15 + 1 * stage;
        stats.append({Stats::luck, Stats::crit});
    }

    if (pet == "Stone Golem") {
        benefit = 17 + 1 * stage;
        stats.append({Stats::vit, Stats::pdef});
    }

    if (pet == "Tortus") {
        benefit = 6 + 1 * stage;
        stats.append({Stats::vit, Stats::pdef});
    }

    if (pet == "Unicorn") {
        benefit = 13 + 1 * stage;
        stats.append({Stats::agi, Stats::eva});
    }

    if (pet == "Undine") {
        benefit = 19 + 1 * stage;
        stats.append({Stats::vit, Stats::pdef});
    }

    if (pet == "White Dragon") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::int_, Stats::vit, Stats::matk, Stats::pdef});
    }

    if (pet == "Wind Pixie") {
        benefit = 9.5 + 0.5 * stage;
        stats.append({Stats::int_, Stats::wis, Stats::matk, Stats::mres});
    }

    if (pet == "Wolf") {
        benefit = 11 + 1 * stage;
        stats.append({Stats::agi, Stats::eva});
    }

    if (pet == "Yeti") {
        benefit = 11 + 1 * stage;
        stats.append({Stats::vit, Stats::pdef});
    }

    // All but one soul pet have the same benefit amount
    if (pet.contains("Soul:")) benefit = 13 + 1 * stage;

    if (pet == "Soul: Agility") stats.append(Stats::agi);
    if (pet == "Soul: Dexterity") stats.append(Stats::dex);
    if (pet == "Soul: Intelligence") stats.append(Stats::int_);
    if (pet == "Soul: Strength") stats.append(Stats::str);
    if (pet == "Soul: Wisdom") stats.append(Stats::wis);
    if (pet == "Soul: Vitality") stats.append(Stats::vit);

    if (pet == "Soul: Vitality & Wisdom") {
        benefit = 9 + 0.5 * stage; // Only soul pet with different benefit amount
        stats.append({Stats::vit, Stats::wis});
    }

    if (pet == "Soul: P.Atk") stats.append(Stats::patk);
    if (pet == "Soul: P.Def") stats.append(Stats::pdef);
    if (pet == "Soul: P.Acc") stats.append(Stats::pacc);
    if (pet == "Soul: Atk Spd") stats.append(Stats::atkSpd);
    if (pet == "Soul: M.Atk") stats.append(Stats::matk);
    if (pet == "Soul: M.Def") stats.append(Stats::mdef);
    if (pet == "Soul: M.Acc") stats.append(Stats::macc);
    if (pet == "Soul: Cast Spd") stats.append(Stats::castSpd);
    if (pet == "Soul: Evasion") stats.append(Stats::eva);
    if (pet == "Soul: Crit Rate") stats.append(Stats::crit);
    if (pet == "Soul: HP Recov") stats.append(Stats::hpReg);
    if (pet == "Soul: MP Recov") stats.append(Stats::mpReg);

    for (Stats::Stat stat : stats) benefits.append(QPair<Stats::Stat, float>(stat, benefit));

    return benefits;
}
