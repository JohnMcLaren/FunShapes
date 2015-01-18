FunShapes
=========
Editor 2D graphical  objects / Редактор графических 2D объектов

![screenshot](https://github.com/JohnMcLaren/FunShapes/funshapes_screenshot.png)

####Description

The **editor** is written on C ++ using cross-platform **Qt5**. It can serve as a template for novice programmers using Qt to create their own programs using 2D graphics. In the program code can be found examples:

1.	Class [**QSignalMapper**] as switch  events / signals arising in the program
2.	Writing to file, read from file [**QFile, QFileDialog, QTextStream**]
3.	Creating your own context menu [**QMenu**]
4.	Implementation mechanism undo / redo actions made by the user (**Undo/Redo**). He can also be used to automation software - as record/playback macros, animation etc.
5.	Transformation of a graphic view of the scene / objects (scale, rotation) [**QTransform**]
6.	Working with View of Scene [**QGraphicsView**] coordinate transformation (mapFrom…)
7.	Drawing with [**QPainterPath**]
8.	Overriding the paint () method of the object to control the process of drawing (use gradient fill, "highlighting", the definition of the order of drawing intersecting objects, control the scale drawing) [**QPainter**]
9.	Convert binary data to Base64 and back [**QString, QByteArray**]
10.	Selecting multiple objects with the mouse [**Rubber Band Region**]

The **editor** allows you to create and edit embedded types of objects, such as:

1.	Triangle
2.	Rectangle
3.	Circle
4.	Text
5.	Image

**Objects** might change the following parameters:

1.	Position
2.	Geometry(for objects "Image"/"Text", image/text scaled for object area)
3.	Orientation (angle on the Z axis)
4.	Color (except object "Image")
5.	Embedded text of object as well as the font, size and color of this text (except "Text" object)

**Scene** supports clipboard operations (**Cut / Copy / Paste**), and has a mechanism of undo / redo changes for objects (**Undo / Redo**). The state of the scene with objects and all their parameters (including images of objects "Image") can be saved to a file. Scene's file is a simple text file where the scene, objects and their parameters are described in the **XML** format.


