/* Rappelz Belt Builder
 * Copyright (C) 2020 Jonathan Vice
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses.
 */

#pragma once

#include <QMainWindow>
#include "stats.h"
#include "beltbuilder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* Reset the build */
    void reset();

private:
    Ui::MainWindow *ui;
    BeltBuilder builder;

    void displayStats();

    void updateBuilder();

    void updateBeltEnhance();
};
