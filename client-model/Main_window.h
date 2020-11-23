#include <QMainWindow>
#include <string>

class Main_window : public QMainWindow {    
public:
	explicit Main_window(std::string image_root);
	virtual ~Main_window();

private:
	void paintEvent(QPaintEvent* event) override;

    QImage image;
};