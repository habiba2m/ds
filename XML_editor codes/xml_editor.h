#ifndef XML_EDITOR_H
#define XML_EDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class XML_editor; }
QT_END_NAMESPACE

class XML_editor : public QMainWindow
{
    Q_OBJECT

public:
    XML_editor(QWidget *parent = nullptr);
    ~XML_editor();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private slots:


    void on_load_clicked();

    void on_format_clicked();

    void on_minify_clicked();

    void on_convert_clicked();

    void on_compress_clicked();

    void on_decompress_clicked();

    void on_check_clicked();

    void on_correct_clicked();

private:
    Ui::XML_editor *ui;
};
#endif // XML_EDITOR_H
