/* Rappelz Belt Builder
 * Copyright (C) 2020 Jonathan Vice
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses.
 */

#include <QDebug>
#include <QMetaEnum>
#include <QPair>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Pet stuff
    QStringList pets = {"None",
                        "Angel",
                        "Baphomet",
                        "Blight Ogre",
                        "Bloodthirsty Slaughterer",
                        "Blue Pixie",
                        "Cerberus",
                        "Crystal Golem",
                        "Crystal Spider",
                        "Death Gladiator",
                        "Death Tyrant",
                        "Drillbot",
                        "Ethereal Pixie",
                        "Forest Pixie",
                        "Genie",
                        "Gnoll",
                        "Grandmaster Hector",
                        "Harpy",
                        "Hawkman",
                        "Ice Maiden",
                        "Ifrit",
                        "Kentauros",
                        "Lydian",
                        "Minotaurus",
                        "Mystic Koala",
                        "Naga",
                        "Nightmare",
                        "Octopus",
                        "Orc",
                        "Pantera",
                        "Poultry",
                        "Red Pixie",
                        "Salamander",
                        "Siren",
                        "Skeleton",
                        "Snowman",
                        "Stone Golem",
                        "Tortus",
                        "Undine",
                        "Unicorn",
                        "White Dragon",
                        "Wind Pixie",
                        "Wolf",
                        "Yeti",
                        "Soul: Agility",
                        "Soul: Dexterity",
                        "Soul: Intelligence",
                        "Soul: Strength",
                        "Soul: Vitality",
                        "Soul: Vitality & Wisdom",
                        "Soul: P.Atk",
                        "Soul: P.Def",
                        "Soul: P.Acc",
                        "Soul: Atk Spd",
                        "Soul: M.Atk",
                        "Soul: M.Def",
                        "Soul: M.Acc",
                        "Soul: Cast Spd",
                        "Soul: Evasion",
                        "Soul: Crit Rate",
                        "Soul: HP Recov",
                        "Soul: MP Recov",
                       };
    QStringList stages = {"0", "1", "2", "3", "4", "5"};

    // Stat names
    statNames = Stats::initStatNames();

    // Get all dropdowns
    QList<QComboBox*> dropdowns = ui->slotsParent->findChildren<QComboBox*>();

    // Setup dropdowns
    for (QComboBox* cbx : dropdowns) {
        if (cbx->objectName().contains("7") || cbx->objectName().contains("8")) continue;
        if (cbx->objectName().contains("Slot")) cbx->addItems(pets);
        else if (cbx->objectName().contains("Stage")) cbx->addItems(stages);
        cbx->connect(cbx, &QComboBox::currentTextChanged, this, &MainWindow::updateBuilder);
    }

    // Add connections
    ui->btnReset->connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::reset);
    ui->cbxBeltEnhance->connect(ui->cbxBeltEnhance, &QComboBox::currentTextChanged, this, &MainWindow::updateBeltEnhance);
    displayStats();
}

MainWindow::~MainWindow() {
    delete ui;
}

/* Display the build stats */
void MainWindow::displayStats() {
    QMap<Stats::Stat, float> stats = builder.getStatBenefits();
    QList<QLabel*> statLabels = ui->statsParent->findChildren<QLabel*>();
    QMetaEnum metaEnum = QMetaEnum::fromType<Stats::Stat>();

    for (QLabel* label : statLabels) {
        if (label->objectName() == "lblStatBenefits") continue;

        // Get the stat's name
        QString statName = label->objectName().remove("lbl");
        statName[0] = statName[0].toLower();

        // Get the stat benefit from the name
        float stat = metaEnum.keyToValue(statName.toStdString().c_str());
        QString displayName = statNames[(Stats::Stat) stat];
        stat = stats[(Stats::Stat) stat];

        // Grey out if stat gains no benefit
        if (stat > 0) label->setStyleSheet("color: #000000");
        else label->setStyleSheet("color: #C8C8C8");

        // Formatting
        QString tabs = (displayName.length() > 7) ? "\t" : "\t\t";

        // Formatting Exceptions
        if (displayName == "Vitality") tabs = "\t\t";
        if (displayName == "Wisdom") tabs = "\t";

        label->setText(QString(displayName + tabs + QString::number(stat) + "%"));
    }
}

void MainWindow::updateBuilder() {
    QList<QPair<QString, int>> build;
    QList<QComboBox*> dropdowns = ui->slotsParent->findChildren<QComboBox*>(); // get dropdowns
    int count = 0;

    for (QComboBox* cbx : dropdowns) {
        if (count < 8) build.append(QPair<QString, int>(cbx->currentText(), 0));
        else if (count >= 8) build[count % 8].second = cbx->currentIndex();
        count++;
    }

    builder.setBuild(build);
    displayStats();
}

void MainWindow::updateBeltEnhance() {
    int enhance = ui->cbxBeltEnhance->currentText() == "0-19" ? 0 : ui->cbxBeltEnhance->currentText().toInt();
    builder.setBeltEnhance(enhance);
    updateBuilder();
}

/* Reset the build */
void MainWindow::reset() {
    // Get all dropdowns
    QList<QComboBox*> dropdowns = ui->slotsParent->findChildren<QComboBox*>();
    for (QComboBox* dropdown : dropdowns) dropdown->setCurrentIndex(0); // Reset all dropdowns

    builder.resetBuild();
    displayStats();
}
