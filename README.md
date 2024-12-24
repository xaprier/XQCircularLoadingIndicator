# XQCircularLoadingIndicator
CircularLoadingIndicator is a circular loading indicator written in C++ using Qt Widgets. This indicator offers a range of features and customization options, making it a versatile choice for various applications.

You can use QtQuick but if you don't want you can use my project which is produced by QPainter.

The indicator is under namespace xaprier::qt::widgets and it has multiple props!

## Features
- Circular Design: The indicator adopts a circular layout, providing a visually appealing representation of progress.
- Namespace: All components are encapsulated within the <b>xaprier::qt::widgets</b> namespace for better organization and to avoid naming conflicts.
- Signals and Slots: The indicator emits signals on every property change, providing flexibility in handling updates. Corresponding slots are available for convenient interaction.
- Setter Functions: A set of setter functions allow easy adjustment of various properties, enabling dynamic updates to the progress bar.
- Getter Functions: Access current property values using getter functions, ensuring encapsulation of private properties.

## Usage
To use <b>CircularLoadingIndicator</b> in your project, follow these steps:
### Link to your project
If you add this repository as submodule of your project, add this project's directory as subdirectory to CMake determine this project. Then you can link to your CMake project by
```cmake
target_link_libraries(YOUR_PROJECT PRIVATE XQCircularLoadingIndicator)
```
### Include Header:
Include the necessary header files in your project to access the CircularLoadingIndicator functionalities.
```cpp
#include "CircularLoadingIndicator.hpp"
```
### Instantiate the Progress Bar:
Create an instance of CircularLoadingIndicator in your application.
```cpp
xaprier::qt::widgets::CircularLoadingIndicator indicator;
```
### Customize and Update:
Utilize the setter functions to customize the progress bar according to your requirements. Connect signals to slots for dynamic updates.
```cpp
indicator.SetSegmentSize(36); // 36 degree 
indicator.Start();
// ... add more customization
```
### Integrate with Qt Widgets:
Integrate the progress bar into your Qt Widgets application effortlessly.
```cpp
// Example of setting up a layout and adding the progress bar
QVBoxLayout* layout = new QVBoxLayout;
layout->addWidget(&indicator);
setLayout(layout);
```
## Properties
### Handlers
```cpp
// @brief Starts the thread for animate loading
void Start();
// @brief Stops the thread for animation of loading
void Stop();
```

### Signals
* The signals will be emitted on every setter function works.
```cpp
void si_MaximumSpeedChanged(double speed);
void si_MinimumSpeedChanged(double speed);
void si_SegmentChanged(int segmentSize);
void si_WidthChanged(int width);
void si_HeightChanged(int height);
void si_MarginChanged(int x, int y);
void si_MarginXChanged(int x);
void si_MarginYChanged(int y);
void si_ProgressWidthChanged(int width);
void si_SquareChanged(bool enable);
void si_ShadowChanged(bool enable);
void si_ProgressRoundedCapChanged(bool enable);
void si_EnableBgChanged(bool enable);
void si_EnableTextChanged(bool enable);
void si_ProgressAlignmentChanged(Qt::Alignment alignment);
void si_BgColorChanged(QColor color);
void si_ProgressColorChanged(QColor color);
void si_TextColorChanged(QColor color);
void si_TextChanged(QString text);
```

### Setter functions
* Set the current value and update the progress bar
```cpp
void SetMaximumSpeed(const double &speed = 3.0);
void SetMinimumSpeed(const double &speed = 1.0);
void SetUpdateValue(const int &updateValue = 2);
void SetSegmentSize(const int &segmentSize = 12);
void SetWidth(const int &width = 200);
void SetHeight(const int &height = 200);
void SetMargin(const int &x = 0, const int &y = 0);
void SetMarginX(const int &x = 0);
void SetMarginY(const int &y = 0);
void SetProgressWidth(const int &width = 10);
void SetSquare(const bool &enable = false);
void SetShadow(const bool &enable = true);
void SetProgressRoundedCap(const bool &enable = true);
void SetEnableBg(const bool &enable = true);
void SetEnableText(const bool &enable = false);
void SetProgressAlignment(const Qt::Alignment &alignment = Qt::AlignCenter);
void SetBgColor(const QColor &color = "#44475a");
void SetProgressColor(const QColor &color = "#498BD1");
void SetTextColor(const QColor &color = "#498BD1");
void SetText(const QString &text = "Loading...");
```
### Getter functions 
* Accessing current value(all props are under private construction, so use getter for access it)
```cpp
double GetMaximumSpeed() const;
double GetMinimumSpeed() const;
int GetSegmentSize() const;
int GetWidth() const;
int GetHeight() const;
int GetMarginX() const;
int GetMarginY() const;
int GetProgressWidth() const;
bool GetSquare() const;
bool GetShadow() const;
bool GetProgressRoundedCap() const;
bool GetEnableBg() const;
bool GetEnableText() const;
bool GetRunning() const;
Qt::Alignment GetProgressAlignment() const;
QColor GetBgColor() const;
QColor GetProgressColor() const;
QColor GetTextColor() const;
QString GetText() const;
```

# An example MainWindow for testing these features
- All the implementation can be tested with created MainWindow class.
- Video of MainWindow
[![Watch the video](https://raw.githubusercontent.com/xaprier/XQCircularLoadingIndicator/assets/MainWindow.png)](https://raw.githubusercontent.com/xaprier/XQCircularLoadingIndicator/assets/MainWindow.mp4)
