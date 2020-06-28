/* Rappelz Belt Builder
 * Copyright (C) 2020 Jonathan Vice
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses.
 */

#include <QDebug>
#include <QMetaEnum>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Pet names
    QStringList pets = {"None",
                        "Angel",
                        "Baphomet",
                        "Blight Ogre",
                        "Blue Pixie",
                        "Cerberus",
                        "Death Gladiator",
                        "Death Tyrant",
                        "Drillbot",
                        "Genie",
                        "Gnoll",
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
                        "Wolf",
                        "Yeti",
                       };
    QStringList stages = {"0", "1", "2", "3", "4", "5"};

    // Setup slot dropdowns
    ui->cbxSlot1->addItems(pets);
    ui->cbxSlot2->addItems(pets);
    ui->cbxSlot3->addItems(pets);
    ui->cbxSlot4->addItems(pets);
    ui->cbxSlot5->addItems(pets);
    ui->cbxSlot6->addItems(pets);
    ui->cbxSlot7->addItems(pets);
    ui->cbxSlot8->addItems(pets);

    // Setup stage dropdowns
    ui->cbxStage1->addItems(stages);
    ui->cbxStage2->addItems(stages);
    ui->cbxStage3->addItems(stages);
    ui->cbxStage4->addItems(stages);
    ui->cbxStage5->addItems(stages);
    ui->cbxStage6->addItems(stages);
    ui->cbxStage7->addItems(stages);
    ui->cbxStage8->addItems(stages);

    // Add connections
    ui->btnReset->connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::reset);
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

        // Get the stat from the name
        float stat = metaEnum.keyToValue(statName.toStdString().c_str());
        stat = stats[(Stats::Stat) stat];

        label->setText(QString(statName + QString("\t\t") + QString::number(stat))); // Display the stat
    }
}

/* Reset the build */
void MainWindow::reset() {
    ui->cbxSlot1->setCurrentIndex(0);
    ui->cbxSlot2->setCurrentIndex(0);
    ui->cbxSlot3->setCurrentIndex(0);
    ui->cbxSlot4->setCurrentIndex(0);
    ui->cbxSlot5->setCurrentIndex(0);
    ui->cbxSlot6->setCurrentIndex(0);
    ui->cbxSlot7->setCurrentIndex(0);
    ui->cbxSlot8->setCurrentIndex(0);
    ui->cbxStage1->setCurrentIndex(0);
    ui->cbxStage2->setCurrentIndex(0);
    ui->cbxStage3->setCurrentIndex(0);
    ui->cbxStage4->setCurrentIndex(0);
    ui->cbxStage5->setCurrentIndex(0);
    ui->cbxStage6->setCurrentIndex(0);
    ui->cbxStage7->setCurrentIndex(0);
    ui->cbxStage8->setCurrentIndex(0);
    builder.resetBuild();
    displayStats();
}
