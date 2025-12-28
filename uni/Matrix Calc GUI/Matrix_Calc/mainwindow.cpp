#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "matrixops.h"

#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QTableWidgetItem>


bool fillFromLine(QLineEdit* line, QTableWidget* table,
                  int rows, int cols, QString* err = nullptr)
{
    QString s = line->text().trimmed();
    if (s.isEmpty()) {
        if (err) *err = "Please enter some numbers.";
        return false;
    }

    s.replace(',', ' ');
    QStringList toks = s.split(QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);
    int need = rows * cols;

    if (toks.size() != need) {
        if (err) *err =
                QString("Expected %1 values, got %2.")
                    .arg(need).arg(toks.size());
        return false;
    }

    table->setRowCount(rows);
    table->setColumnCount(cols);

    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j, ++k) {
            bool ok;
            double v = toks[k].toDouble(&ok);
            if (!ok) {
                if (err) *err = QString("Invalid number: %1").arg(toks[k]);
                return false;
            }
            auto* item = new QTableWidgetItem(QString::number(v));
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(i, j, item);
        }
    }
    return true;
}

// ------------------------------------
// helper: read QTableWidget → double**
// ------------------------------------
static double** readTable(QTableWidget* t, int r, int c, bool* ok = nullptr)
{
    if (ok) *ok = true;
    auto M = new double*[r];
    for (int i = 0; i < r; ++i)
        M[i] = new double[c]{};

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            QTableWidgetItem* it = t->item(i, j);
            bool good = false;
            double val = it ? it->text().toDouble(&good) : 0.0;

            if (!good) {
                if (ok) *ok = false;
            }
            M[i][j] = val;
        }
    }
    return M;
}

// -----------------------------------
// helper: delete double**
// -----------------------------------
static void freeUiMatrix(double** M, int r)
{
    if (!M) return;
    for (int i = 0; i < r; ++i)
        delete[] M[i];
    delete[] M;
}

// -----------------------------------
// helper: write double** → QTableWidget
// -----------------------------------
static void writeTable(QTableWidget* t, double** M, int r, int c)
{
    t->setRowCount(r);
    t->setColumnCount(c);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            auto* item = new QTableWidgetItem(QString::number(M[i][j], 'f', 2));
            item->setTextAlignment(Qt::AlignCenter);
            t->setItem(i, j, item);
        }
    }
}


// =================================================================
//                          MAINWINDOW
// =================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);


    // --- validator for numeric list input ---
    auto numList = new QRegularExpressionValidator(
        QRegularExpression(
            R"(^\s*[+-]?(?:\d+(?:\.\d+)?|\.\d+)(?:[eE][+-]?\d+)?(?:\s+[+-]?(?:\d+(?:\.\d+)?|\.\d+)(?:[eE][+-]?\d+)?)*\s*$)"
            ),
        this
        );

    // Setup matrix1 input box
    ui->m1e_in->setValidator(numList);
    ui->m1e_in->setPlaceholderText("e.g. 1 2 3 4 ...");

    connect(ui->m1e_in, &QLineEdit::returnPressed, this, [=]{
        QString err;
        if (!fillFromLine(ui->m1e_in, ui->m1_tab,
                          ui->r1_sb->value(),
                          ui->c1_sb->value(), &err))
            QMessageBox::warning(this, "Matrix 1", err);
    });

    // Setup matrix2 input box
    ui->m2e_in->setValidator(numList);
    ui->m2e_in->setPlaceholderText("e.g. 5 6 7 8 ...");

    connect(ui->m2e_in, &QLineEdit::returnPressed, this, [=]{
        QString err;
        if (!fillFromLine(ui->m2e_in, ui->m2_tab,
                          ui->r2_sb->value(),
                          ui->c2_sb->value(), &err))
            QMessageBox::warning(this, "Matrix 2", err);
    });

    // ========================
    // Page navigation buttons
    // ========================
    connect(ui->next_btn, &QPushButton::clicked, this, [=]{
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->back_btn, &QPushButton::clicked, this, [=]{
        ui->stackedWidget->setCurrentIndex(0);
    });

    // ========================
    //         ADD
    // ========================
    connect(ui->add_btn, &QPushButton::clicked, this, [=]{
        int r1 = ui->r1_sb->value();
        int c1 = ui->c1_sb->value();
        int r2 = ui->r2_sb->value();
        int c2 = ui->c2_sb->value();

        if (r1 != r2 || c1 != c2) {
            QMessageBox::warning(this, "Add", "Sizes must match.");
            return;
        }

        bool ok1, ok2;
        double** A = readTable(ui->m1_tab, r1, c1, &ok1);
        double** B = readTable(ui->m2_tab, r2, c2, &ok2);

        if (!ok1 || !ok2) {
            QMessageBox::warning(this, "Add", "Invalid numbers.");
            freeUiMatrix(A, r1);
            freeUiMatrix(B, r2);
            return;
        }

        double** R = addMatrices(A, B, r1, c1, r2, c2);
        writeTable(ui->res_tab, R, r1, c1);

        freeUiMatrix(A, r1);
        freeUiMatrix(B, r2);
        freeUiMatrix(R, r1);
    });

    // ========================
    //         SUBTRACT
    // ========================
    connect(ui->sub_btn, &QPushButton::clicked, this, [=]{
        int r1 = ui->r1_sb->value(), c1 = ui->c1_sb->value();
        int r2 = ui->r2_sb->value(), c2 = ui->c2_sb->value();

        if (r1 != r2 || c1 != c2) {
            QMessageBox::warning(this, "Subtract", "Sizes must match.");
            return;
        }

        bool ok1, ok2;
        double** A = readTable(ui->m1_tab, r1, c1, &ok1);
        double** B = readTable(ui->m2_tab, r2, c2, &ok2);

        if (!ok1 || !ok2) {
            QMessageBox::warning(this, "Subtract", "Invalid numeric values.");
            freeUiMatrix(A, r1);
            freeUiMatrix(B, r2);
            return;
        }

        double** R = subtractMatrices(A, B, r1, c1, r2, c2);
        writeTable(ui->res_tab, R, r1, c1);

        freeUiMatrix(A, r1);
        freeUiMatrix(B, r2);
        freeUiMatrix(R, r1);
    });

    // ========================
    //      MULTIPLY
    // ========================
    connect(ui->mul_btn, &QPushButton::clicked, this, [=]{
        int r1 = ui->r1_sb->value(), c1 = ui->c1_sb->value();
        int r2 = ui->r2_sb->value(), c2 = ui->c2_sb->value();

        if (c1 != r2) {
            QMessageBox::warning(this, "Multiply", "c1 must equal r2.");
            return;
        }

        bool ok1, ok2;
        double** A = readTable(ui->m1_tab, r1, c1, &ok1);
        double** B = readTable(ui->m2_tab, r2, c2, &ok2);

        if (!ok1 || !ok2) {
            QMessageBox::warning(this, "Multiply", "Invalid numeric values.");
            freeUiMatrix(A, r1);
            freeUiMatrix(B, r2);
            return;
        }

        double** R = multiplyMatrices(A, B, r1, c1, r2, c2);
        writeTable(ui->res_tab, R, r1, c2);

        freeUiMatrix(A, r1);
        freeUiMatrix(B, r2);
        freeUiMatrix(R, r1);
    });

    // ========================
    //   TRANSPOSE (Matrix 1)
    // ========================
    connect(ui->t1_btn, &QPushButton::clicked, this, [=]{
        int r = ui->r1_sb->value();
        int c = ui->c1_sb->value();

        bool ok;
        double** A = readTable(ui->m1_tab, r, c, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Transpose", "Invalid numbers.");
            freeUiMatrix(A, r);
            return;
        }

        double** R = transposeMatrix(A, r, c);
        writeTable(ui->res_tab, R, c, r);

        freeUiMatrix(A, r);
        freeUiMatrix(R, c);
    });

    // ========================
    //   TRANSPOSE (Matrix 2)
    // ========================
    connect(ui->t2_btn, &QPushButton::clicked, this, [=]{
        int r = ui->r2_sb->value();
        int c = ui->c2_sb->value();

        bool ok;
        double** A = readTable(ui->m2_tab, r, c, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Transpose", "Invalid numbers.");
            freeUiMatrix(A, r);
            return;
        }

        double** R = transposeMatrix(A, r, c);
        writeTable(ui->res_tab, R, c, r);

        freeUiMatrix(A, r);
        freeUiMatrix(R, c);
    });

    // ========================
    //     DETERMINANT M1
    // ========================
    connect(ui->det1_btn, &QPushButton::clicked, this, [=]{
        int n = ui->r1_sb->value();
        if (n != ui->c1_sb->value()) {
            QMessageBox::warning(this, "Determinant", "Matrix must be square.");
            return;
        }

        bool ok;
        double** A = readTable(ui->m1_tab, n, n, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Determinant", "Invalid numbers.");
            freeUiMatrix(A, n);
            return;
        }

        double d = detMatrix((const double* const*)A, n, n);
        freeUiMatrix(A, n);

        ui->res_tab->setRowCount(1);
        ui->res_tab->setColumnCount(1);
        ui->res_tab->setItem(0, 0,
                             new QTableWidgetItem(QString::number(d)));
    });

    // ========================
    //     DETERMINANT M2
    // ========================
    connect(ui->det2_btn, &QPushButton::clicked, this, [=]{
        int n = ui->r2_sb->value();
        if (n != ui->c2_sb->value()) {
            QMessageBox::warning(this, "Determinant", "Matrix must be square.");
            return;
        }

        bool ok;
        double** A = readTable(ui->m2_tab, n, n, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Determinant", "Invalid numbers.");
            freeUiMatrix(A, n);
            return;
        }

        double d = detMatrix((const double* const*)A, n, n);
        freeUiMatrix(A, n);

        ui->res_tab->setRowCount(1);
        ui->res_tab->setColumnCount(1);
        ui->res_tab->setItem(0, 0,
                             new QTableWidgetItem(QString::number(d)));
    });

    // ========================
    //        INVERSE M1
    // ========================
    connect(ui->inv1_btn, &QPushButton::clicked, this, [=]{
        int n = ui->r1_sb->value();
        if (n != ui->c1_sb->value()) {
            QMessageBox::warning(this, "Inverse", "Matrix must be square.");
            return;
        }

        bool ok;
        double** A = readTable(ui->m1_tab, n, n, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Inverse", "Invalid numbers.");
            freeUiMatrix(A, n);
            return;
        }

        double** R = inverseMatrix((const double* const*)A, n, n);
        freeUiMatrix(A, n);

        if (!R) {
            QMessageBox::information(this, "Inverse",
                                     "Matrix is singular (det ~ 0).");
            return;
        }

        writeTable(ui->res_tab, R, n, n);
        freeUiMatrix(R, n);
    });

    // ========================
    //        INVERSE M2
    // ========================
    connect(ui->inv2_btn, &QPushButton::clicked, this, [=]{
        int n = ui->r2_sb->value();
        if (n != ui->c2_sb->value()) {
            QMessageBox::warning(this, "Inverse", "Matrix must be square.");
            return;
        }

        bool ok;
        double** A = readTable(ui->m2_tab, n, n, &ok);

        if (!ok) {
            QMessageBox::warning(this, "Inverse", "Invalid numbers.");
            freeUiMatrix(A, n);
            return;
        }

        double** R = inverseMatrix((const double* const*)A, n, n);
        freeUiMatrix(A, n);

        if (!R) {
            QMessageBox::information(this, "Inverse",
                                     "Matrix is singular.");
            return;
        }

        writeTable(ui->res_tab, R, n, n);
        freeUiMatrix(R, n);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
