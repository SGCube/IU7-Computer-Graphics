#include <QApplication>
#include <vector>

#include "mainwindow.h"
#include "canvas.h"
#include "painter.h"
#include "polygon.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QImage img(640, 640, QImage::Format_RGB32);
	img.fill(QColor(255, 255, 255));
	Painter painter;
	
	std::vector<Polygon> polygon_set;
	Polygon cur_polygon;
	
	MainWindow w(&img, &polygon_set, &cur_polygon, &painter);
	Canvas scene(&img, &polygon_set, &cur_polygon, &painter, &w);
	w.set_scene(&scene);
	
	w.show();
	
	return a.exec();
}
