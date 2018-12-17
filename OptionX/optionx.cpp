#include "optionx.h"
#include "ui_optionx.h"
#include <vector>
#include <string>
#include "FEMInterface.h"
#include <QMessageBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

OptionX::OptionX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionX)
{
    ui->setupUi(this);
}

OptionX::~OptionX()
{
    delete ui;
}

void OptionX::on_pushButton_clicked()
{
    QMessageBox::about(this, "Help", "Please select an option type. \n "
                                     "The number of days until expiration must be a positive integer. \n"
                                     "The initial stock price in dollars must be a positive number. \n"
                                     "The current interest rate in percent may range from -100 to 100. \n"
                                     "The stock's approximate volatility must be in between 0 and 100 exclusive. \n"
                                     "The strike price in dollars must be a positive number. \n"
                                     "The power ranges from 0 exclusive to 2 inclusive. \n"
                                     "The upper barrier must be positive. Set to a number greater than"
                                     "0 to set to no upper barrier. \n"
                                     "The rebate must be non-negative. \n"
                                     "The current to average price ratio must be between 1 and 50 inclusive. \n"
                                     "\n \n The resulting plot will show the value "
                                     "of the option given the stock price at "
                                     "the specified time until expiration.");
}

void OptionX::on_pushButton_2_clicked()
{
    // Read in user input.
    QString OptType = ui->QtOptionType->currentText();
    QString DTE = ui->QtDaysUntilExpiration->text();
    QString IP = ui->QtInitialPrice->text();
    QString IR = ui->QtInterestRate->text();
    QString V = ui->QtVolatility->text();
    QString SP = ui->QtStrikePrice->text();
    QString P = ui->QtPower->text();
    QString UB = ui->QtUpperBarrier->text();
    QString R = ui->QtRebate->text();
    QString CtAP = ui->QtCurrentToAveragePrice->text();
    std::string OptionType = OptType.toStdString();

    bool DTEValid = true; // Restricted to positive integers
    bool IPValid = true; // Restricted to positives
    bool IRValid = true; // Restricted from -100 to 100
    bool VValid = true; // Restricted from 0 to 100 exclusive
    bool SPValid = true; // Restricted to positives
    bool PValid = true; // Restricted from (0, 2]
    bool UBValid = true; // Restricted to positives
    bool RValid = true; // Restricted to non negatives
    bool CtAPValid = true; // Restricted from [1, 50]

    // Error check input for non-numerical symbols
    for (int i = 0;i<DTE.size();i++)
    {
        if (!(DTE[i].isNumber()  || DTE[i] == '.'  || DTE[i] == '-')){
            DTEValid = false;
        } else {

        }
    }
    for (int i = 0;i<IP.size();i++)
    {
        if (!(IP[i].isNumber() || IP[i] == '.') || IP[i] == '-'){
            IPValid = false;
        }
    }
    for (int i = 0;i<IR.size();i++)
    {
        if (!(IR[i].isNumber() || IR[i] == '.' || IR[i] == '-')){
            IRValid = false;
        }
    }
    for (int i = 0;i<V.size();i++)
    {
        if (!(V[i].isNumber() || V[i] == '.' || V[i] == '-')){
            VValid = false;
        }
    }
    for (int i = 0;i<SP.size();i++)
    {
        if (!(SP[i].isNumber() || SP[i] == '.' || SP[i] == '-')){
            SPValid = false;
        }
    }
    for (int i = 0;i<P.size();i++)
    {
        if (!(P[i].isNumber() || P[i] == '.' || P[i] == '-')){
            PValid = false;
        }
    }
    for (int i = 0;i<UB.size();i++)
    {
        if (!(UB[i].isNumber() || UB[i] == '.') || UB[i] == '-'){
            UBValid = false;
        }
    }
    for (int i = 0;i<R.size();i++)
    {
        if (!(R[i].isNumber() || R[i] == '.' || R[i] == '-')){
            RValid = false;
        }
    }
    for (int i = 0;i<CtAP.size();i++)
    {
        if (!(CtAP[i].isNumber() || CtAP[i] == '.' || CtAP[i] == '-')){
            CtAPValid = false;
        }
    }

    if ((DTEValid && IPValid && IRValid && VValid && SPValid && PValid && UBValid && RValid && CtAPValid)){
        double DaysTillExpiration = DTE.toDouble();
        double InitPrice = IP.toDouble();
        double IntRate = IR.toDouble();
        double Vol = V.toDouble();
        double StrikePrice = SP.toDouble();
        double Power = P.toDouble();
        double LowerBarrier = -1;
        double UpperBarrier = UB.toDouble();
        double Rebate = R.toDouble();
        double CtAPDouble = CtAP.toDouble();
        // Check if the input is within the given ranges
        if ((DaysTillExpiration > 0) && ((InitPrice > 0) && (Vol > 0) && (IntRate >= -100) && (IntRate <= 100)
                                         && (StrikePrice > 0) && (Power > 0) && (Power <= 2)
                                         && (UpperBarrier >= 0) && (Rebate >= 0) && Vol < 100
                                         && (CtAPDouble >= 1) && (CtAPDouble <= 50))){
            // Default Upper Barrier set to 0
            if (UpperBarrier == 0){
                UpperBarrier = -1.0;
            }

            // Solve function called here based on user input!
            std::vector<std::vector<double>> Solution = solve_problem(
                        InitPrice,
                        Vol/100,
                        IntRate/100,
                        DaysTillExpiration/365.0,
                        OptionType,
                        -1,
                        -1,
                        -1,
                        StrikePrice,
                        Power,
                        LowerBarrier,
                        UpperBarrier,
                        Rebate);
            std::vector<double> FinalSolution = Solution[Solution.size()-1];
            if (OptionType == "Asian") {
                // Reverse and take second half
                std::reverse(FinalSolution.begin(), FinalSolution.end());
                int mid = (FinalSolution.size()-1.0)/2.0;
                std::vector<double> temp(1 + mid);
                for (int i = 0; i < temp.size(); i++) {
                    temp[i] = FinalSolution[mid+i];
                }
                FinalSolution = temp;
            }

            int sz = FinalSolution.size();
            std::vector<double> xAxis(sz);
            double step;
            // In case the Option Type was Asian, adjust parameters accordingly.
            if (OptionType != "Asian") {
                double MaxValue = 2*InitPrice;
                if (StrikePrice > InitPrice) { MaxValue = 2*StrikePrice; }
                step = MaxValue / (sz-1);
                for (int i = 0; i < sz; i++) {
                    xAxis[i] = step * i;
                }
            } else {
                double MaxValue = 0.02;
                double MinValue = 1.0;
                step = (MinValue - MaxValue) / (sz-1);
                double v, d;
                for (int i = 0; i < sz; i++) {
                    d = MinValue - (i*step);
                    v = 1.0 / d;
                    xAxis[i] = v;
                }
            }

            // Plot the data points
            QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

            for (int i = 0; i < sz; i++){
                series->append(xAxis[i], FinalSolution[i]);
            }

            QtCharts::QChart *chart = new QtCharts::QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Stock Price vs Option Value");

            QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            window.setCentralWidget(chartView);
            window.resize(800, 600);
            window.show();

            int LowerIndex = 0;
            double Value;
            double comp = InitPrice;
            if (OptionType == "Asian") { comp = CtAPDouble; }
            for (int i = 0; i < sz; i++){
                if (xAxis[i] < comp){
                    LowerIndex = i;
                }
            }
            if (xAxis[LowerIndex + 1] == comp){
                Value = FinalSolution[LowerIndex + 1];
            } else{
                double Frac = (comp - xAxis[LowerIndex])/(xAxis[LowerIndex+1] - xAxis[LowerIndex]);
                Value = (Frac*FinalSolution[LowerIndex]) + ((1 - Frac)*FinalSolution[LowerIndex + 1]);
            }

            QString NewMessage = "The value of the option you have entered is: ";
            NewMessage.append(QString::number(Value));
            QMessageBox::about(this, "Option Value", NewMessage);
        } else {
            QMessageBox::about(this, "Error", "Days until expiration, initial price, "
                                              "volatility, strike price, and upper barrier, "
                                              "must all be positive. \n \n"
                                              "Rebate must be non-negative. \n \n"
                                              "Power must be between 0 and 2 inclusive and"
                                              "interest rate must be between -100 and 100 inclusive.");
        }
    } else {
        // Print out error messages
        QString ErrorMessage;
        if (!DTEValid){
            ErrorMessage.append("Days until expiration is not valid \n");
        }
        if (!IPValid){
            ErrorMessage.append("Initial price is not valid \n");
        }
        if (!IRValid){
            ErrorMessage.append("Interest rate is not valid \n");
        }
        if (!VValid){
            ErrorMessage.append("Volatility is not valid \n");
        }
        if (!SPValid){
            ErrorMessage.append("Strike price is not valid \n");
        }
        if (!PValid){
            ErrorMessage.append("Power is not valid \n");
        }
        if (!UBValid){
            ErrorMessage.append("Upper barrier is not valid \n");
        }
        if (!RValid){
            ErrorMessage.append("Rebate is not valid \n");
        }
        if (!CtAPValid){
            ErrorMessage.append("Current to average price ratio is not valid \n");
        }
        QMessageBox::about(this, "Error", ErrorMessage);
    }
}
