#include <iostream>
#include <fstream>
#include <QTime>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>

void error_msg(QString error_msg_content){
    QMessageBox debug_msgbx;
    debug_msgbx.setStyleSheet("QMessageBox {background-color:red;}");
    debug_msgbx.setText(error_msg_content);
    debug_msgbx.exec();
}

bool ip_floor_length(int ip_floor_length_parameter_1, int ip_floor_length_parameter_2, int ip_floor_length_parameter_3){
    if(ip_floor_length_parameter_1 - ip_floor_length_parameter_2 - ip_floor_length_parameter_3 > 3){
        return true;
    } else {
        return false;
    }
}

bool ip_floor_value_size(int ip_floor_value_size_parameter_1){
    if(ip_floor_value_size_parameter_1 > 255){
        return true;
    } else {
        return false;
    }
}

void add_fav_fn(std::string fav_start_ip_fnvar, std::string target_ip_fnvar){
    std::ofstream fout("data/fav_data.csv", std::ios::app);    
    if(!fout.is_open()){
        error_msg("Data file cannot be open");
        fout.close();
    }

    fout << "\n" + fav_start_ip_fnvar + " - " + target_ip_fnvar;
    if(fout.fail()){
        error_msg("Write error");
        fout.close();
    }
}

void read_fav_fn(QWidget &main_window_fnvar){
    std::ifstream fin("data/fav_data.csv");
    if(!fin.is_open()){
        error_msg("Data file cannot be open");
        fin.close();
    }

    std::string line;
    std::string read_value;

    QListWidget *fav_listfav_list = new QListWidget(&main_window_fnvar);
    QList<QString> fav_ip_array;

    int read_fav_fn_counter = 0;
    while(std::getline(fin, line)){
        read_value = line;
        QString fav_ip_cnv_value = QString::fromLocal8Bit(read_value.c_str());
        fav_ip_array.append(fav_ip_cnv_value);

        fav_listfav_list->addItem(fav_ip_array[read_fav_fn_counter]);
        read_fav_fn_counter++;
    }
    if(fin.fail() && !fin.eof()){
        error_msg("read error");
        fin.close();
    }
}

void delay_fn(){
    QTime dieTime = QTime::currentTime().addMSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
}

QString your_ip_fn(){
    QProcess process_userip;
    process_userip.start("bash", QStringList() << "-c" << "bash script/usr_ip.sh");
    process_userip.waitForFinished();
    QString your_ip_var = process_userip.readAllStandardOutput().trimmed();
    process_userip.deleteLater();
    return your_ip_var;
}

QString system_fn(QString script_file_path, QString completed_finish_parameter){
    QProcess process_system;
    process_system.start("bash", QStringList() << "-c" << "bash " + script_file_path + ".sh " + completed_finish_parameter);
    process_system.waitForFinished();
    QString result = process_system.readAllStandardOutput().trimmed();
    process_system.deleteLater();
    return result;
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QWidget main_window;
    QWidget favourites_window;

    main_window.setStyleSheet("QWidget {background-color:#F2F2F2;}");
    main_window.setWindowTitle("LNSky - IP Scanner");

    // main window items
    QPushButton *tool_bar_bg = new QPushButton("----------", &main_window);
    tool_bar_bg->setStyleSheet("QPushButton {width: 10000%; margin-left:-10px; background-color:white;}");
    tool_bar_bg->setEnabled(false);

    QLabel *your_ip_label = new QLabel("Your IP; " + your_ip_fn(), &main_window);
    your_ip_label->setStyleSheet("QLabel {color:blue; background-color:white; font-size:13px; margin-top:3px;}");

    QPushButton *favourites_button = new QPushButton("Favourites", &main_window);
    favourites_button->setStyleSheet("QPushButton {color:blue; background-color:white; margin-left:170px; margin-top:1px; border:none;}");

    QLabel *start_ip_label = new QLabel("Start IP", &main_window);
    start_ip_label->setGeometry(0, 50, 150, 20);

    QTextEdit *start_ip_var = new QTextEdit(&main_window);
    start_ip_var->setGeometry(0, 80, 150, 30);
    start_ip_var->setPlaceholderText("0.0.0.0");

    QLabel *target_ip_label = new QLabel("Target IP", &main_window);
    target_ip_label->setGeometry(160, 50, 150, 20);

    QTextEdit *target_ip_var = new QTextEdit(&main_window);
    target_ip_var->setGeometry(160, 80, 150, 30);
    target_ip_var->setPlaceholderText("255.255.255.255");

    QListWidget *write_list = new QListWidget(&main_window);
    write_list->setGeometry(0, 130, 480, 500);
    write_list->setStyleSheet("QListWidget {color:black; background-color:#FFFFFF;}");

    QPushButton *scan_button = new QPushButton("IP Scan" ,&main_window);
    scan_button->setGeometry(330, 80, 150, 30);
    scan_button->setStyleSheet("QPushButton {background-color:green; color:white;}");

    QPushButton *stop_button = new QPushButton("STOP" ,&main_window);
    stop_button->setGeometry(330, 40, 150, 30);
    stop_button->setStyleSheet("QPushButton {background-color:red; color:white;}");

    // favourites window items
    QTextEdit *start_ip_fav_txtbx_start  = new QTextEdit(&favourites_window);
    start_ip_fav_txtbx_start->setGeometry(260, 10, 200, 30);
    start_ip_fav_txtbx_start->setPlaceholderText("Start IP : 0.0.0.0");

    QTextEdit *start_ip_fav_txtbx_target = new QTextEdit(&favourites_window);
    start_ip_fav_txtbx_target->setGeometry(260, 50, 200, 30);
    start_ip_fav_txtbx_target->setPlaceholderText("Target IP : 255.255.255.255");

    QPushButton *add_fav_bttn = new QPushButton("Add Fav IP Scala", &favourites_window);
    add_fav_bttn->setGeometry(260, 90, 200, 30);
    add_fav_bttn->setStyleSheet("background-color:green; color:white;");

    QPushButton *clear_list_bttn = new QPushButton("Clear List", &favourites_window);
    clear_list_bttn->setGeometry(260, 130, 200, 30);
    clear_list_bttn->setStyleSheet("background-color:red; color:white;");

    QObject::connect(favourites_button, &QPushButton::clicked, [&](){
        favourites_window.setStyleSheet("QWidget {background-color:#F2F2F2;}");
        favourites_window.setWindowTitle("Favourites");

        read_fav_fn(favourites_window);

        QObject::connect(add_fav_bttn, &QPushButton::clicked, [&](){
            std::string start_ip_fav_val_std = start_ip_fav_txtbx_start->toPlainText().toStdString();
            std::string target_ip_fav_val_std = start_ip_fav_txtbx_target->toPlainText().toStdString();

            add_fav_fn(start_ip_fav_val_std, target_ip_fav_val_std);

            favourites_window.close();
            read_fav_fn(favourites_window);
            favourites_window.show();
        });

        QObject::connect(clear_list_bttn, &QPushButton::clicked, [&](){
            system_fn("script/clear_list", "");

            favourites_window.close();
            read_fav_fn(favourites_window);
            favourites_window.show();
        });

        favourites_window.resize(470, 270);
        favourites_window.show();
    });

    QObject::connect(scan_button, &QPushButton::clicked, [&](){
        bool wrong_input = false;
        bool stoper = false;
        write_list->clear();
        QString values = start_ip_var->toPlainText() + ".";
        QString target = target_ip_var->toPlainText();

        QStringList floor_1;
        int counter_dat_finder_1 = 0;
        int ip_char_1 = 0;
        while(values.at(counter_dat_finder_1) != "."){
            counter_dat_finder_1++;
            floor_1.append(values.at(ip_char_1));
            ip_char_1++;
        }
        wrong_input = ip_floor_length(counter_dat_finder_1, 0, 0);
        stoper = ip_floor_length(counter_dat_finder_1, 0, 0);
        QString ip_floor_string_1 = floor_1.join(""); 
        int convert_1 = ip_floor_string_1.toInt();        
        wrong_input = ip_floor_value_size(convert_1);
        stoper = ip_floor_value_size(convert_1);

        QStringList floor_2;
        int counter_dat_finder_2 = counter_dat_finder_1 + 1;
        int ip_char_2 = ip_char_1 + 1;
        while(values.at(counter_dat_finder_2) != "."){
            counter_dat_finder_2++;
            floor_2.append(values.at(ip_char_2));
            ip_char_2++;
        }
        QString ip_floor_string_2 = floor_2.join(""); 
        int convert_2 = ip_floor_string_2.toInt();
        if(wrong_input == false){
            wrong_input = ip_floor_length(counter_dat_finder_2, counter_dat_finder_1, 1);
            stoper = ip_floor_length(counter_dat_finder_2, counter_dat_finder_1, 1);
            wrong_input = ip_floor_value_size(convert_2);
            stoper = ip_floor_value_size(convert_2);        	
        }
        //
        QStringList floor_3;
        int counter_dat_finder_3 = counter_dat_finder_2 + 1;
        int ip_char_3 = ip_char_2 + 1;
        while(values.at(counter_dat_finder_3) != "."){
            counter_dat_finder_3++;
            floor_3.append(values.at(ip_char_3));
            ip_char_3++;
        }
        QString ip_floor_string_3 = floor_3.join(""); 
        int convert_3 = ip_floor_string_3.toInt();
        if(wrong_input == false){
            wrong_input = ip_floor_length(counter_dat_finder_3, counter_dat_finder_2, 1);
            stoper = ip_floor_length(counter_dat_finder_3, counter_dat_finder_2, 1);        
            wrong_input = ip_floor_value_size(convert_3);
            stoper = ip_floor_value_size(convert_3);        	
        }
        //
        QStringList floor_4;
        int counter_dat_finder_4 = counter_dat_finder_3 + 1;
        int ip_char_4 = ip_char_3 + 1;
        while(values.at(counter_dat_finder_4) != "."){
            counter_dat_finder_4++;          
            floor_4.append(values.at(ip_char_4));
            ip_char_4++;
        }
        QString ip_floor_string_4 = floor_4.join(""); 
        int convert_4 = ip_floor_string_4.toInt();
        if(wrong_input == false){
            wrong_input = ip_floor_length(counter_dat_finder_4, counter_dat_finder_3, 1);
            stoper = ip_floor_length(counter_dat_finder_4, counter_dat_finder_3, 1);
            wrong_input = ip_floor_value_size(convert_4);
            stoper = ip_floor_value_size(convert_4);
        }

        int success_ip_counter = 0;
        bool first_match_query = false;
        while(true){
            delay_fn();
            if(first_match_query == false){
                goto first_match_l;
            }
            convert_4++;
            if(convert_4 == 256){
                convert_4 = 0;
                convert_3++;
                if(convert_3 == 256){
                    convert_3 = 0;
                    convert_2++;
                    if(convert_2 == 256){
                        convert_2 = 0;
                        convert_1++;
                        if(convert_1 == 256){
                            convert_1 = 0;
                        }
                    }
                }
            }
            first_match_l:
            first_match_query = true;
            QString completed_1 = QString::number(convert_1);
            QString completed_2 = QString::number(convert_2);
            QString completed_3 = QString::number(convert_3);
            QString completed_4 = QString::number(convert_4);
            QString completed_finish = completed_1 + "." + completed_2 + "." + completed_3 + "." + completed_4;

            QString query_finish = completed_1 + completed_2 + completed_3 + completed_4;
            int query_finish_converter = query_finish.toInt();

            QString test_target = target + "x";

            QStringList test_1;
            int counter_test = 0;
            while(test_target.at(counter_test) != "x"){
                if(target.at(counter_test) == "."){
                    counter_test++;
                    continue;            		
                }
                test_1.append(target.at(counter_test));
                counter_test++;
            }
            QString compile_target = test_1.join("");
            int compile_target_converter = compile_target.toInt();

            if(query_finish_converter > compile_target_converter){
                wrong_input = true;
                stoper = true;
            }

            QString host_and_ms_port = system_fn("script/find_hostname", completed_finish);
            QString ping_port = system_fn("script/find_port", completed_finish);

            QString compile_value = "IP : " + completed_finish + "     HN/MS; " + host_and_ms_port;

            QListWidgetItem *write_object = new QListWidgetItem();

            if(ping_port != "64"){
                QPixmap pixmap("img/ip-false.png");
                QIcon icon(pixmap);
                write_object->setIcon(icon);
                write_object->setText(compile_value);
            }else {
                success_ip_counter++;
                QPixmap pixmap("img/ip-true.png");
                QIcon icon(pixmap);
                write_object->setIcon(icon);
                write_object->setText(compile_value);
            }

            write_list->addItem(write_object);    

            if(completed_finish == target){
                QMessageBox success_value_msgbx;
                QString success_value_cvrt = QString::number(success_ip_counter);
                success_value_msgbx.setStyleSheet("QMessageBox {background-color:green;}");
                success_value_msgbx.setText("Successful IP Count; " + success_value_cvrt);
                success_value_msgbx.exec();
                break;
            }else if(stoper == true){
                if(wrong_input == true){
                    error_msg("Wrong Scala");
                    break;
                }
                QMessageBox success_value_msgbx;
                QString success_value_cvrt = QString::number(success_ip_counter);
                success_value_msgbx.setStyleSheet("QMessageBox {background-color:green;}");
                success_value_msgbx.setText("Successful IP Count; " + success_value_cvrt);
                success_value_msgbx.exec();
                break;
            }
            QObject::connect(stop_button, &QPushButton::clicked, [&](){
                stoper = true;
            });
        }    
    });
    main_window.resize(500, 300);
    main_window.show();
    return a.exec();
}
