#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTextEdit>

class QPushButton;
class Window : public QWidget
{
public:
   explicit Window(QWidget *parent = 0);
private:
   QPushButton *convert_button;
   QPushButton *save_button;
   QTextEdit *text_edited; 
   QTextEdit *text_edit;
   QTextEdit *blacklist_edit;
};

#endif // WINDOW_H
