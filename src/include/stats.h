#pragma once

#include <QObject>
#include <QMap>


class Stats : public QObject {
    Q_OBJECT

public:
    /* Stats enum */
    enum Stat {luck = 0,
               str,
               vit,
               agi,
               dex,
               int_,
               wis,
               patk,
               matk,
               pacc,
               macc,
               pdef,
               mdef,
               eva,
               blockPer,
               blockDef,
               atkSpd,
               castSpd,
               crit,
               hpReg,
               mpReg,
               mres,
               numStats
              };
    Q_ENUM(Stat)

    static QMap<Stat, QString> initStatNames() {
        QMap<Stat, QString> names;

        names[luck] = "Luck";
        names[str] = "Strength";
        names[vit] = "Vitality";
        names[agi] = "Agility";
        names[dex] = "Dexterity";
        names[int_] = "Intelligence";
        names[wis] = "Wisdom";
        names[patk] = "P. Attack";
        names[matk] = "M. Attack";
        names[pacc] = "P. Accuracy";
        names[macc] = "M. Accuracy";
        names[pdef] = "P. Defense";
        names[mdef] = "M. Defense";
        names[eva] = "Evasion";
        names[blockPer] = "Block Per";
        names[blockDef] = "Block Def";
        names[atkSpd] = "Attack Speed";
        names[castSpd] = "Cast Speed";
        names[crit] = "Crit Rate";
        names[hpReg] = "HP Regen";
        names[mpReg] = "MP Regen";
        names[mres] = "M. Res";

        return names;
    }
};
