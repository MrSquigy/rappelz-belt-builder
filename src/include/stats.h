#pragma once

#include <QObject>

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
               block,
               atkSpd,
               castSpd,
               crit,
               hpReg,
               mpReg,
               numStats
              };
    Q_ENUM(Stat)

};
