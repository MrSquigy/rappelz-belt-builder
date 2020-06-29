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

    // Get all dropdowns
    QList<QComboBox*> dropdowns = ui->slotsParent->findChildren<QComboBox*>();

    // Setup dropdowns
    for (QComboBox* cbx : dropdowns) {
        if (cbx->objectName().contains("Slot")) cbx->addItems(pets);
        else if (cbx->objectName().contains("Stage")) cbx->addItems(stages);
        cbx->connect(cbx, &QComboBox::currentTextChanged, this, &MainWindow::updateBuilder);
    }

    // Add reset connection
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

        // Get the stat benefit from the name
        float stat = metaEnum.keyToValue(statName.toStdString().c_str());
        stat = stats[(Stats::Stat) stat];

        // Grey out if stat gains no benefit
        if (stat > 0) label->setStyleSheet("color: #000000");
        else label->setStyleSheet("color: #C8C8C8");

        label->setText(QString(statName + QString("\t\t") + QString::number(stat))); // Display the stat
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

/* Reset the build */
void MainWindow::reset() {
    // Get all dropdowns
    QList<QComboBox*> dropdowns = ui->slotsParent->findChildren<QComboBox*>();
    for (QComboBox* dropdown : dropdowns) dropdown->setCurrentIndex(0); // Reset all dropdowns

    builder.resetBuild();
    displayStats();
}
