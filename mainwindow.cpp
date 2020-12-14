#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include<QColor>
static QString output;
static QString input;
static QString path;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap paper("C:/Users/zhuko/Desktop/paper.jpg");
    ui->pic->setPixmap(paper);
 ui-> pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0099ef, stop: 1 #6bcdf6);");
   ui-> textEdit->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d0e0fb, stop: 1 #d0e0fb);");
     ui-> lineEdit->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #deedf4, stop: 1 #deedf4);");
      ui-> lineEdit_2->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #deedf4, stop: 1 #deedf4);");
     ui-> pushButton_2->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0fafef, stop: 1 #00cdf6);");
      ui-> pushButton_3->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00cdf6, stop: 1 #0fafef);");
}



MainWindow::~MainWindow()
{
    delete ui;
}

void Skip(char c, QVector<unsigned char>& text, unsigned& i)
{
    while (i < text.size())
    {
        if (text[i] != c) { break; }
        ++i;
    }
}

QByteArray GetWord(QVector<unsigned char>& text, unsigned& from)
{
    QByteArray buffer;
    Skip(' ', text, from);
    Skip('\n', text, from);
    Skip('\r', text, from);
    while (from < text.size())
    {
        if (text[from] != ' ' && text[from] != '\n')
        {
            buffer += text[from]; ++from;
        }
        else break;
    }
    return buffer;
}

class TuringMachine
{
public:
    void AddState(State& state)
    {
        states.push_back(state);

    }

    void Run()
    {

        QString tmp = input;

        bool end = false;
        unsigned current_index = 0;
        State st = states[0];

        QString name_needed = st.name;



        while (!end)
        {

            unsigned i = 0;
            bool fail = true;
            while (i < states.size())
            {
                if (states[i].name == name_needed)
                {
                    if (states[i].input_symbol == tmp[current_index])
                    {
                        st = states[i];
                        fail = false;
                        break;
                    }
                }
                ++i;
            }
            if (fail) {
              output = "Error, not enough instructions" ;   break;
            }

            tmp[current_index] = st.output_symbol;
            name_needed = st.next_state;
            switch (st.dir)
            {
            case L: --current_index; break;
            case R: ++current_index; break;
            case S: break;
            case Q: end = true; break;
            }
           output=tmp;
        }
    }
private:
    QVector<State>states;

};

void MainWindow::on_pushButton_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(0,"Выбор файла","","*.txt");
    QFile mFile;
    path=str;
    mFile.setFileName(str);
    mFile.open(QIODevice::ReadOnly);
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textEdit->setText(buffer);


}
void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText("##");
            ui->lineEdit_2->setText("");
}


void MainWindow::on_pushButton_2_clicked()
{
    TuringMachine machine;
     input = ui->lineEdit->text();


        QFile file(path);
        file.open(QIODevice::ReadOnly);
        //QTextStream mFile(&file);
        QVector<unsigned char>source;
        char ch=0;
        while (file.getChar(&ch)) //считывание файла
        {
            source.push_back(ch);
        }

        file.close();

        class Exception
        {
        public:
        Exception(std::string error)
        {
        m_exception = error;
        }
        const char* getError()
        {

        return m_exception.c_str();
        }

        private:
        std::string m_exception;
        };
        try {
            for (unsigned i = 0; i < static_cast<unsigned>(source.size()); ) //формирование алфавита символов и состояний
             {
                        State st;
                       QByteArray tmp;
                       st.name = GetWord(source, i);
                       tmp = GetWord(source, i);
                      // if (tmp.size() > 1) {std::cout << 1 << std::endl; break; }
                       st.input_symbol = tmp[0];
                       st.next_state = GetWord(source, i);
                       tmp = GetWord(source, i);
                      // if (tmp.size() > 1) { std::cout << 2 << std::endl; break; }
                       st.output_symbol = tmp[0];
                       tmp = GetWord(source, i);
                      // if (tmp.size() > 2) { std::cout << 3 << std::endl; break; }
                       bool fail = false;
                       switch (tmp[0])
                       {
                       case 'L': st.dir = L; break;
                       case 'R': st.dir = R; break;
                       case 'S': st.dir = S; break;
                       case 'Q': st.dir = Q; break;
                       default: fail = true; break;
                       }
                       if (fail) { break; }
                       machine.AddState(st);
                       //if(source[i] != '\n') {break;}
                  }

        }
        catch (const std::exception& e)
        {
            std::cout   << e.what();
        }


               machine.Run();



     ui->lineEdit_2->setText(output);


}







