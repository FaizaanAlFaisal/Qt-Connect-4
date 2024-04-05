#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QGridLayout>

int board[8][8] = { {0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0},};

int col0_pos = 7, col1_pos = 7, col2_pos = 7, col3_pos = 7, col4_pos = 7, col5_pos = 7,
col6_pos = 7, col7_pos = 7; //which row is currently available on each column

int turnCount = 1;
int playerTurn = 1;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap grid (":/Connect4pngs/Connect4-Grid.png");

    ui->Grid->setPixmap(grid);


    QPushButton *colButtons[8];
    for (int i = 0; i <= 7; i++){
        QString colNum = "Col" + QString::number(i);
        colButtons[i] = MainWindow::findChild<QPushButton *>(colNum);
        connect(colButtons[i], SIGNAL(released()), this, SLOT(moves()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moves(){

    QPushButton *button = (QPushButton *)sender();
    QString col = button->objectName();

    int column;

    if (col == "Col0") column = 0;
    else if (col == "Col1") column = 1;
    else if (col == "Col2") column = 2;
    else if (col == "Col3") column = 3;
    else if (col == "Col4") column = 4;
    else if (col == "Col5") column = 5;
    else if (col == "Col6") column = 6;
    else column = 7;

    int move=0;

    switch (column) {

        case 0:
            if (col0_pos > -1) {
                board[col0_pos][column] = playerTurn;
                --col0_pos;
                move = 1;
            }
            break;


        case 1:
            if (col1_pos > -1) {
                board[col1_pos][column] = playerTurn;
                --col1_pos;
                move = 1;
            }
            break;

        case 2:
            if (col2_pos > -1) {
                board[col2_pos][column] = playerTurn;
                --col2_pos;
                move = 1;
            }
            break;


        case 3:
            if (col3_pos > -1) {
                board[col3_pos][column] = playerTurn;
                --col3_pos;
                move = 1;
            }
            break;


        case 4:
            if (col4_pos > -1) {
                board[col4_pos][column] = playerTurn;
                --col4_pos;
                move = 1;
            }
            break;


        case 5:
            if (col5_pos > -1) {
                board[col5_pos][column] = playerTurn;
                --col5_pos;
                move = 1;
            }
            break;


        case 6:
            if (col6_pos > -1) {
                board[col6_pos][column] = playerTurn;
                --col6_pos;
                move = 1;
            }
            break;


        case 7:
            if (col7_pos > -1) {
                board[col7_pos][column] = playerTurn;
                --col7_pos;
                move = 1;
            }
            break;

        default:
            break;
    }

    if (move == 1) {


        turnCount++;        //increment turn counter



    int row; //determine row on which piece was just placed
    switch (column) {

        case 0:
            row = col0_pos + 1;
            break;

        case 1:
            row = col1_pos + 1;
            break;

        case 2:
            row = col2_pos + 1;
            break;

        case 3:
            row = col3_pos + 1;
            break;

        case 4:
            row = col4_pos + 1;
            break;

        case 5:
            row = col5_pos + 1;
            break;

        case 6:
            row = col6_pos + 1;
            break;

        case 7:
            row = col7_pos + 1;
            break;

        default:
            row = -1;
            break;
    }


    //change the labels on grid to match that of the player placing their piece.



    QPixmap player1 (":/Connect4pngs/P1Piece-Square.png");
    QPixmap player2 (":/Connect4pngs/P2Piece-Square.png");

    QLabel *cell = findChild<QLabel *>("Cell"+QString::number(row)+QString::number(column));

    if (playerTurn == 1) {
        cell->setPixmap(player1);
    }
    else {
        cell->setPixmap(player2);
    }


    if (playerTurn == 1) playerTurn = 2;        //once a move is made
    else if (playerTurn == 2) playerTurn = 1;   //toggle player turns

    int win;



    ui->infoText->setAutoFillBackground(true);

    win = wincheck(row, column);     //run winchecker

    if (win == 1) {
        ui->infoText->setStyleSheet("QLabel { color: red}");
        ui->infoText->setText("P1 Wins!");

        QMessageBox::about(this, "Victory!","<font color=\"Red\">Player 1 has won!");

        //pop-up window for victory

        close();

    }
    else if (win == 2) {
        ui->infoText->setStyleSheet("QLabel { color: #EAAB00}");
        ui->infoText->setText("P2 Wins!");

        QMessageBox::about(this, "Victory!", "<font color=\"#BB8900\">Player 2 has won!");

        close();

    }
    else if (win == 3){
        ui->infoText->setStyleSheet("QLabel { color: gray}");
        ui->infoText->setText("Draw!");

        QMessageBox::about(this, "Draw!", "<font color=\"# \">The game has tied!");

        close();
    }
    else {

        if(playerTurn == 1) {
            ui->infoText->setStyleSheet("QLabel { color: red}");
            ui->infoText->setText("P1's Turn");
        }
        else {
            ui->infoText->setStyleSheet("QLabel { color: #EAAB00}");
            ui->infoText->setText("P2's Turn");
        }

        ui->turnText->setText("Turn #"+QString::number(turnCount));;
    }



    }
    move = 0;
}





int MainWindow::wincheck(int row, int column) {


    int p1Count = 0, p2Count = 0;



    int minRowCheck = row, maxRowCheck = row, minColCheck = column, maxColCheck = column;

    //for a 4-in-a-row, we must check sequences of pieces in each diagonal, vertical and horizontal

    if (minRowCheck - 3 >= 0) minRowCheck -= 3; //ensure check values remain within board confines
    else minRowCheck = 0;

    if (maxRowCheck + 3 <= 7) maxRowCheck += 3;
    else maxRowCheck = 7;

    if (minColCheck - 3 >= 0) minColCheck -= 3;
    else minColCheck = 0;

    if (maxColCheck + 3 <= 7) maxColCheck += 3;
    else maxColCheck = 7;


    //using row and column, check two diagonals, horizontal and vertical for win/4 in a row

    //vertical win check:
    for (int rowCheck = minRowCheck; rowCheck <= maxRowCheck; rowCheck++) {

        if (board[rowCheck][column] == 1) { //sequence counter
            p1Count++; //if check spot has 1, increment p1count
            p2Count = 0; //and set p2count to 0
        }
        if (board[rowCheck][column] == 2) {
            p2Count++; //if check spot has 2, increment p2count
            p1Count = 0; //and set p1count to 0
        }
        if (board[rowCheck][column] == 0) {
            p1Count = 0; //if spot has 0, set both p1 and p2 count to 0
            p2Count = 0;
        }
        if (p1Count >= 4) return 1; //if 4 have been connected, return 1 for p1 and 2 for p2
        if (p2Count >= 4) return 2;
    }

    p1Count = 0;
    p2Count = 0;

    //horizontal win check:
    for (int columnCheck = minColCheck; columnCheck <= maxColCheck; columnCheck++) {

        if (board[row][columnCheck] == 1) {
            p1Count++;
            p2Count = 0;
        }
        if (board[row][columnCheck] == 2) {
            p2Count++;
            p1Count = 0;
        }
        if (board[row][columnCheck] == 0) {
            p1Count = 0;
            p2Count = 0;
        }
        if (p1Count >= 4) return 1;
        if (p2Count >= 4) return 2;
    }

    p1Count = 0;
    p2Count = 0;


    int leftRowBLTR = row, rightRowBLTR = row, leftColBLTR = column, rightColBLTR = column; //Diagonal check var - bottom left to top right
    int leftRowTLBR = row, rightRowTLBR = row, leftColTLBR = column, rightColTLBR = column; //Diagonal check var - top left to bottom right
    int i = 0;

    //initialize the BLTR diagonal left side variable checks:
    while (leftRowBLTR < 7 && leftColBLTR > 0 && i < 3) {
        leftRowBLTR++;
        leftColBLTR--;
        i++;
    }
    i = 0;
    //initialize right-side BLTR variable checks:
    while (rightRowBLTR > 0 && rightColBLTR < 7 && i < 3) {
        rightRowBLTR--;
        rightColBLTR++;
        i++;
    }
    i = 0;
    //initialize left-side TLBR variable checks:
    while (leftRowTLBR > 0 && leftColTLBR > 0 && i < 3) {
        leftRowTLBR--;
        leftColTLBR--;
        i++;
    }
    i = 0;
    //initialize right-side TLBR variable checks:
    while (rightRowTLBR < 7 && rightColTLBR < 7 && i < 3) {
        rightRowTLBR++;
        rightColTLBR++;
        i++;
    }



    p1Count = 0;
    p2Count = 0;

    //run check for 4 connected pieces for BLTR diagonal:
    for (int rowCheck = leftRowBLTR, colCheck = leftColBLTR; rowCheck >= rightRowBLTR && colCheck <= rightColBLTR; rowCheck--, colCheck++) {

        if (board[rowCheck][colCheck] == 1) {
            p1Count++;
            p2Count = 0;
        }
        if (board[rowCheck][colCheck] == 2) {
            p2Count++;
            p1Count = 0;
        }
        if (board[rowCheck][colCheck] == 0) {
            p1Count = 0;
            p2Count = 0;
        }

        if (p1Count >= 4) return 1;
        if (p2Count >= 4) return 2;
    }

    p1Count = 0;
    p2Count = 0;

    //run check for 4 connected pieces in TLBR diagonal:
    for (int rowCheck = leftRowTLBR, colCheck = leftColTLBR; rowCheck <= rightRowTLBR && colCheck <= rightColTLBR; rowCheck++, colCheck++) {

        if (board[rowCheck][colCheck] == 1) {
            p1Count++;
            p2Count = 0;
        }
        if (board[rowCheck][colCheck] == 2) {
            p2Count++;
            p1Count = 0;
        }
        if (board[rowCheck][colCheck] == 0) {
            p1Count = 0;
            p2Count = 0;
        }

        if (p1Count >= 4) return 1;
        if (p2Count >= 4) return 2;
    }
    if (turnCount == 65) return 3;
    p1Count = 0;
    p2Count = 0;
    return 0; //return 0 if 4 have not been connected
}
